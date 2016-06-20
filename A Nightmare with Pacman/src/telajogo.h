#ifndef TELAJOGO_H
#define TELAJOGO_H
#include "telabase.h"
#include "mapa.h"
#include "pacman.h"
#include "redghost.h"
#include "pinkghost.h"
#include "blueghost.h"
#include "orangeghost.h"
#include "cutcomandos.h"

enum enum_EstadosFase{
	GHOSTSCATTER,GHOSTCHASE,GHOSTFEAR,PACMANFEAR
};

class TelaJogo:public TelaBase {
	public:
		CutComandos mostrarcomandos;
		Animacao anim_fundo;
		Pacman pacman;
		RedGhost redghost;
		PinkGhost pinkghost;
		BlueGhost blueghost;
		OrangeGhost orangeghost;
		Sprite pacbit;
		Sprite pellet;
		int score;
		int ghoststreak=1;
		int bits_restantes;
		int pellets_restantes;
		int pontos_bit;
		int pontos_pellet;
		int final_fase;
		bool logicaexecutando;
		Timer t_inicio;
		Timer t_pellet;
		int delay_endfear;
		Timer t_fimdejogo;
		int delay_trocadefundo;
		Timer t_mortepacman;
		Timer t_resetfase;
		int waves;
		Timer t_wave;
		int delay_trocaparachase;
		int qtdMortesPacmanPorFantasmas;
		int resetarpellets;
		
		Timer t_acabardots;
		double tempo_para_gameover;
		Timer t_gameover;
		
		enum_EstadosFase estado_atual;
		Player* player1;
		Player* player2;
		int vidaspacman;
		char mensagemrede[TAMANHO_TEXTO];
		
		void InicializaVariaveisJogo();
		void MudaComportamentoFantasmas(comportamentos comp, bool forcar=false);
		void VerificaColisoesPlayer(Player &_player);
		void VerificaPosicaoPlayer(Player &_player);
		void ComeFantasma(Ghost &fantasma);
		void MortePacman();
		void MortePlayer(Player &_player);
		void MostraInformacoesJogador(int offset, Player _player);
		void ResetaChars();
		void SetTrocaSpritesGeral(bool valor);
		void DeuGameOver();
		void VerificaPosicaoGhostComPacman(Ghost &_ghost);
		
		char* MontarSubPacote(Personagem _p);
		char* MontarPacote();
		void AtualizarInformacoesPersonagem(Personagem &_p, char dados[100]);
		void TratarPacote();
		
		void DebugFundo();
		
		TelaJogo(int delay)
			:TelaBase(delay)
		{

		}
		TelaJogo()
			:TelaJogo(DELAY)
		{
		}

//---------------------Métodos-base da tela
		void InitializeComponents()
		{
			setbkcolor(BLACK);
			config.gameover=false;
			anim_fundo = Animacao(500);
			anim_fundo.InsereSprite(imagens[ID_BACKGROUND]);
			anim_fundo.InsereSprite(imagens[ID_BACKGROUNDEND]);
			config.fases=0;
			mapa_path.InitMapaColisao();
			pacman.Init();
			Ghost::AmarrarPacman(pacman);
			redghost.Init();
			blueghost.Init();
			BlueGhost::AmarrarRedGhost(redghost);
			pinkghost.Init();
			orangeghost.Init();
			pacbit = Sprite(imagens[ID_PACBIT]);
			pellet = Sprite(imagens[ID_PELLET]);
			score=0;
			pontos_bit=10;
			pontos_pellet=5*pontos_bit;
			player1=&config.jogadores[config.indexplayer1];
			player1->Init();
			if(config.TemPlayer2())
			{
				player2=&config.jogadores[config.indexplayer2];
				if(config.TemOnline())
				{
					char buf_seed[2];
					comm.EnviarPacote(itoa(player1->seed,buf_seed,10));
					comm.RecebePacote();
					player2->Init(atoi(comm.pacote));
				}
				else
					player2->Init();
			}
			vidaspacman=2;
			resetarpellets=3;
			//Colocar Cutscene inicial
			mostrarcomandos = CutComandos(10000,true);
			mostrarcomandos.Start();
			//Colocar introdução
			InicializaVariaveisJogo();
			t_inicio = Timer(3500,true);
			TocaSom(sons[ID_SOMINICIOJOGO],true,false,true);
		}
		void Loop()
		{
			logicaexecutando=true;
			
			if(t_inicio.CheckTimeout())
			{
				if(waves==0&&!t_resetfase.ativo&&!t_wave.ativo)//Assim que terminar o timer de introdução
				{
					ResetaChars();
					t_resetfase.Start();
				}
			}
			else
			{
				logicaexecutando=false;
				SetTrocaSpritesGeral(false);
				return;
			}
			
			if(t_mortepacman.CheckTimeout())
			{
				if(vidaspacman==0)
				{
					telamostrando=TELA_CREDITOS;
					config.modo_atual=NENHUM;
					exibindo=false;
				}
				else if(pacman.comportamento==DEAD)
				{
					ResetaChars();
					t_resetfase.Start();
					if(qtdMortesPacmanPorFantasmas>=resetarpellets)
					{
						mapa.ResetarPellets();
						qtdMortesPacmanPorFantasmas=0;
						pellets_restantes=mapa.pellets;
					}
				}
			}
			else
			{
				if(t_mortepacman.TimePassed()>=1000)
				{
					if(pacman.comportamento!=DEAD)
					{
						TocaSom(sons[ID_SOMPACMANDEATH],true,false,true,true);
						pacman.MudaComportamento(DEAD);
					}
				}
				else
					InterrompeSom();

				logicaexecutando=false;
				SetTrocaSpritesGeral(false);
				return;
			}
			
			if(t_resetfase.CheckTimeout())
			{
				if(waves==0&&!t_wave.isPaused())
				{
					waves=1;
					t_wave.Start();
				}
				if(t_acabardots.isPaused())
					t_acabardots.Resume();
			}
			else
			{
				logicaexecutando=false;
				SetTrocaSpritesGeral(false);
				return;
			}
			
			if(t_acabardots.ativo&&t_acabardots.CheckTimeout())
			{
				if(pellets_restantes==0)
				{
					MortePlayer(*player1);
//					player1->vidas--;
					if(config.TemPlayer2())
						MortePlayer(*player2);
//						player2->vidas--;
//					if(!AcabouVidasPlayers())
//					{
					InterrompeSom();
					if(!t_gameover.ativo)
					{
						ResetaChars();
						t_resetfase.Start();
					}
					return;
//					}
				}
			}
			else
			{
			}
			
			if(t_gameover.ativo)
			{
				if(t_gameover.CheckTimeout())
				{
					DeuGameOver();
					return;
				}
				else
				{
					logicaexecutando=false;
					SetTrocaSpritesGeral(false);
					return;
				}
			}
			
			if(t_fimdejogo.CheckTimeout())
			{
				if(anim_fundo.trocaspriteautomatico)//Acabou de piscar o fundo. Hora de terminar a fase
				{
					config.fases++;
					InicializaVariaveisJogo();
					return;
				}
			}
			else
			{
				logicaexecutando=false;
				SetTrocaSpritesGeral(false);
				return;
			}

			SetTrocaSpritesGeral(true);
			requestsom=false;
			
			//Mecânica da fase
			if(pacman.AI)//Lógica pro Pac-man pensar
			{
				double d_1=999;
				double d_2=999;
				double d_3=999;
				double d_4=999;
				switch(estado_atual)
				{
					case GHOSTSCATTER://Correr atrás do pellet mais próximo
						if(mapa.HaPelletMaisProximo(pacman.x,pacman.y,&pacman.x_target,&pacman.y_target))
						{
						}
						break;
					case GHOSTCHASE://Fugir dos fantasmas
						if(redghost.comportamento==CHASE)
						{
							d_1=CalculaDistanciaReta(pacman.x,pacman.y,redghost.x,redghost.y);
						}
						if(pinkghost.comportamento==CHASE)
						{
							d_2=CalculaDistanciaReta(pacman.x,pacman.y,pinkghost.x,pinkghost.y);
						}
						if(blueghost.comportamento==CHASE)
						{
							d_3=CalculaDistanciaReta(pacman.x,pacman.y,blueghost.x,blueghost.y);
						}
						if(orangeghost.comportamento==CHASE)
						{
							d_4=CalculaDistanciaReta(pacman.x,pacman.y,orangeghost.x,orangeghost.y);
						}
						
						if(d_1<=d_2&&d_1<=d_3&&d_1<=d_4)
						{
							pacman.x_target = pacman.x+(pacman.x-redghost.x);
							pacman.y_target = pacman.y+(pacman.y-redghost.y);
						}
						else if(d_2<=d_1&&d_2<=d_3&&d_2<=d_4)
						{
							pacman.x_target = pacman.x+(pacman.x-pinkghost.x);
							pacman.y_target = pacman.y+(pacman.y-pinkghost.y);
						}
						else if(d_3<=d_1&&d_3<=d_2&&d_3<=d_4)
						{
							pacman.x_target = pacman.x+(pacman.x-blueghost.x);
							pacman.y_target = pacman.y+(pacman.y-blueghost.y);
						}
						else if(d_4<=d_1&&d_4<=d_2&&d_4<=d_3)
						{
							pacman.x_target = pacman.x+(pacman.x-orangeghost.x);
							pacman.y_target = pacman.y+(pacman.y-orangeghost.y);
						}
						break;
					case GHOSTFEAR://Comer os fantasmas
						if(redghost.EmFear())
						{
							d_1=CalculaDistanciaReta(pacman.x,pacman.y,redghost.x,redghost.y);
						}
						if(pinkghost.EmFear())
						{
							d_2=CalculaDistanciaReta(pacman.x,pacman.y,pinkghost.x,pinkghost.y);
						}
						if(blueghost.EmFear())
						{
							d_3=CalculaDistanciaReta(pacman.x,pacman.y,blueghost.x,blueghost.y);
						}
						if(orangeghost.EmFear())
						{
							d_4=CalculaDistanciaReta(pacman.x,pacman.y,orangeghost.x,orangeghost.y);
						}
						
						if(d_1<=d_2&&d_1<=d_3&&d_1<=d_4)
						{
							pacman.x_target = redghost.x;
							pacman.y_target = redghost.y;
						}
						else if(d_2<=d_1&&d_2<=d_3&&d_2<=d_4)
						{
							pacman.x_target = pinkghost.x;
							pacman.y_target = pinkghost.y;
						}
						else if(d_3<=d_1&&d_3<=d_2&&d_3<=d_4)
						{
							pacman.x_target = blueghost.x;
							pacman.y_target = blueghost.y;
						}
						else if(d_4<=d_1&&d_4<=d_2&&d_4<=d_3)
						{
							pacman.x_target = orangeghost.x;
							pacman.y_target = orangeghost.y;
						}
						break;
					case PACMANFEAR://DecidirProximoPasso() já vai lidar com isso. Randômico
						break;
				}
			}
			if(player1->t_respawn.CheckTimeout())
				player1->LogicaMover();
			if(config.modo_atual==COOP&&player2->t_respawn.CheckTimeout())
				player2->LogicaMover();
			if(!config.TemOnline()||!comm.IsCliente())
			{
				pacman.LogicaMover();
				redghost.LogicaMover();
				pinkghost.LogicaMover();
				blueghost.LogicaMover();
				orangeghost.LogicaMover();
			}
			if(config.TemOnline())
			{
				strcpy(mensagemrede,MontarPacote());
//				std::cout<<mensagemrede<<std::endl;
				comm.EnviarPacote(mensagemrede);
				comm.RecebePacote();
				TratarPacote();
			}
			
			if(!t_pellet.CheckTimeout())
			{
				t_wave.Pause();
//				InterrompeSom();
				if(redghost.comportamento==DEAD
					||pinkghost.comportamento==DEAD
					||blueghost.comportamento==DEAD
					||orangeghost.comportamento==DEAD)
				{
					TocaSom(sons[ID_SOMGHOSTMORTO],true,false,true);
				}
				else
					TocaSom(sons[ID_SOMGHOSTFEAR],true,false,true,true);
				if(
					(!redghost.EmFear()
					&&!pinkghost.EmFear()
					&&!blueghost.EmFear()
					&&!orangeghost.EmFear()
					&&estado_atual==GHOSTFEAR)
					||
					(
					estado_atual==PACMANFEAR
					&&!pacman.EmFear()
					)
				)
				{
					t_pellet.Stop();
				}
				else if(t_pellet.TimePassed()>=delay_endfear)
				{
					if(pacman.comportamento==FEAR)
						pacman.MudaComportamento(ENDFEAR);
					else
					{
						if(redghost.comportamento==FEAR)
							redghost.MudaComportamento(ENDFEAR);
						if(pinkghost.comportamento==FEAR)
							pinkghost.MudaComportamento(ENDFEAR);
						if(blueghost.comportamento==FEAR)
							blueghost.MudaComportamento(ENDFEAR);
						if(orangeghost.comportamento==FEAR)
							orangeghost.MudaComportamento(ENDFEAR);
					}
				}
			}
			else
			{
				if(t_wave.isPaused())
				{
					t_wave.Resume();
				}
				estado_atual=GHOSTSCATTER;
				if(pacman.comportamento==ENDFEAR)
				{
					pacman.MudaComportamento(SCATTER,true);
				}
				else
				{
					if(redghost.comportamento==ENDFEAR)
						redghost.MudaComportamento(SCATTER,true);
					if(pinkghost.comportamento==ENDFEAR)
						pinkghost.MudaComportamento(SCATTER,true);
					if(blueghost.comportamento==ENDFEAR)
						blueghost.MudaComportamento(SCATTER,true);
					if(orangeghost.comportamento==ENDFEAR)
						orangeghost.MudaComportamento(SCATTER,true);
					ghoststreak=1;
				}
			}
			if(!t_wave.CheckTimeout())//Wave tá rolando
			{
				if(t_wave.TimePassed()>=delay_trocaparachase)//trocou de scatter pra chase
				{
					estado_atual=GHOSTCHASE;
					MudaComportamentoFantasmas(CHASE,true);
				}
				else
				{
					estado_atual=GHOSTSCATTER;
					MudaComportamentoFantasmas(SCATTER,true);
				}
			}
			else if(!t_wave.isPaused())//Foi fim de wave mesmo
			{
				waves++;
				if(waves>2)
				{
					if(config.fases>0)
					{
						t_wave.timeout_ms=1033000;
						delay_trocaparachase=(1000/60);
					}
					else
						delay_trocaparachase=5000;
					if(waves==4)
						t_wave.timeout_ms=-1;//infinitamente
				}
				t_wave.Start();
			}
			VerificaPosicaoGhostComPacman(redghost);
			VerificaPosicaoGhostComPacman(pinkghost);
			VerificaPosicaoGhostComPacman(blueghost);
			VerificaPosicaoGhostComPacman(orangeghost);
			
			VerificaColisoesPlayer(*player1);
			
			if(config.TemPlayer2())
			{
				VerificaColisoesPlayer(*player2);
			}
			switch(pacman.EstaSobre(mapa))
			{
				case char_pellet:
					if(pacman.EmFear())
						break;
					mapa.SetPosicao(pacman.X_MATRIZ(),pacman.Y_MATRIZ(),char_vazio);
					score+=pontos_pellet;
					pellets_restantes--;
					InterrompeSom();
//					TocaSom(sons[ID_SOMCOMEPELLET],true,false,true);
					t_pellet.Start();
					
					estado_atual=GHOSTFEAR;
					MudaComportamentoFantasmas(FEAR,true);
					break;
				case char_bit:
					mapa.SetPosicao(pacman.X_MATRIZ(),pacman.Y_MATRIZ(),char_vazio);
					score+=pontos_bit;
					if(pinkghost.contador_sair<pinkghost.limite_sair)
					{
						pinkghost.contador_sair++;
					}
					else if(blueghost.contador_sair<blueghost.limite_sair)
					{
						blueghost.contador_sair++;
					}
					else if(orangeghost.contador_sair<orangeghost.limite_sair)
					{
						orangeghost.contador_sair++;
					}
					bits_restantes--;
//					TocaSom(sons[ID_SOMCOMEPACBIT],true,false);
					break;
			}
			VerificaPosicaoPlayer(*player1);
			
			if(config.TemPlayer2())
			{
				VerificaPosicaoPlayer(*player2);
			}
			if(pinkghost.contador_sair>=pinkghost.limite_sair)
				pinkghost.Sair();
			if(blueghost.contador_sair>=blueghost.limite_sair&&!pinkghost.saindo)
				blueghost.Sair();
			if(orangeghost.contador_sair>=orangeghost.limite_sair&&!pinkghost.saindo&&!blueghost.saindo)
				orangeghost.Sair();
			
			if(bits_restantes==0)
			{
				if(t_acabardots.ativo)
					t_acabardots.Stop();
				logicaexecutando=false;
				pinkghost.contador_sair=0;
				blueghost.contador_sair=0;
				orangeghost.contador_sair=0;
				anim_fundo.trocaspriteautomatico=true;
				t_fimdejogo.Start();
			}
			else if(pellets_restantes==0)
			{
				if(!t_acabardots.ativo&&!t_acabardots.isPaused())
				{
					t_acabardots.Start();
				}
			}
			else
			{
				if(t_acabardots.ativo)
					t_acabardots.Stop();
			}
			if(exibindo==false)
			{
				//Cutscene de fim de jogo. Talvez Usar TelaEndGame
				telamostrando=TELA_CREDITOS;
				return;
			}
			if(!requestsom)
			{
				//Se nenhum som tocou, toca esses
				if(bits_restantes<final_fase)
					TocaSom(sons[ID_SOMBACKGROUND2],true,false,true);
				else
					TocaSom(sons[ID_SOMBACKGROUND1],true,false,true);
			}
		}
		void DesenharObjetos()
		{
			if(config.gameover)
				return;
			anim_fundo.Desenhar(0,Mapa::y0);
			for(int i=1;i<LINHAS_MAPA-1;i++)
			{
				for(int j=1;j<COLUNAS_MAPA-1;j++)
				{
					if(mapa.Posicao(j,i)==char_bit)
					{
						pacbit.Desenhar(j*TAMANHO_CELULA,Mapa::y0+i*TAMANHO_CELULA);
					}
					else if(mapa.Posicao(j,i)==char_pellet)
					{
						pellet.Desenhar(j*TAMANHO_CELULA,Mapa::y0+i*TAMANHO_CELULA);
					}
				}
			}
			
			pacman.Desenhar();
			if(pacman.comportamento!=DEAD)
			{
				redghost.Desenhar();
				pinkghost.Desenhar();
				blueghost.Desenhar();
				orangeghost.Desenhar();
				player1->Desenhar();
				if(config.TemPlayer2())
					player2->Desenhar();
				for(int i=0;i<vidaspacman;i++)
				{
					imagens[ID_PACMAN_LIVES].Desenhar(Tiles(1)+(i*Tiles(1)),ALTURA_PAINELSUPERIOR+ALTURA_FUNDO);
				}
			}
			
			//No túnel direito, é necessário "esconder" os personagens. Isso deve ser desenhado após todos os personagens
			setfillstyle(SOLID_FILL,BLACK);
			bar(LARGURA_FUNDO,0,LARGURA_FUNDO+(2*TAMANHO_CELULA),ALTURA_TELA);
			
			setcolor(WHITE);
			outtextxy(LARGURA_FUNDO,0,"Você: ");
			MostraInformacoesJogador(0,*player1);
			if(config.TemPlayer2())
			{
				outtextxy(LARGURA_FUNDO+100,0,"Outro jogador: ");
				MostraInformacoesJogador(100,*player2);
			}
			if(t_gameover.ativo)
			{
				setcolor(RED);
				outtextxy(mapa.X_TELA(12),mapa.Y_TELA(17),"Game Over");
			}
			else if(t_acabardots.ativo)
			{
				outtextxy(LARGURA_FUNDO,ALTURA_TELA/2,"Acabe os pontos!");
				moveto(LARGURA_FUNDO,ALTURA_TELA/2+PASSOY_LETRA);
				char temp_acabardots[4];
				strcpy(temp_acabardots,"");
				int tmp_restante=t_acabardots.TimeRemaining();
				itoa((tmp_restante/1000),temp_acabardots,10);
//				_snprintf(temp_acabardots,4,"%f",(tmp_restante/1000.0));
				outtext(temp_acabardots);
				outtext("s");
			}
			
			if(Debug)
			{
				DebugFundo();
			}
		}
		void Eventos_Click()
		{
			if(!logicaexecutando)
				return;
			if(OcorreuClickESC())
			{
				DeuGameOver();
			}
			if(BASE_OcorreuKeyDown(VK_RCONTROL))
			{
				Debug=true;
			}
			else
				Debug=false;
			if(DownKey_KeyDown())
			{
				if(player1->PixelsRestantes_X()==0)
				{
					if(player1->ProximaCasaLivre(DOWN))
					{
						player1->movimento=DOWN;
					}
				}
			}
			else if(UpKey_KeyDown())
			{
				if(player1->PixelsRestantes_X()==0)
				{
					if(player1->ProximaCasaLivre(UP))
					{
						player1->movimento=UP;
					}
				}
			}
			else if(RightKey_KeyDown())
			{
				if(player1->PixelsRestantes_Y()==0)
				{
					if(player1->ProximaCasaLivre(RIGHT))
					{
						player1->movimento=RIGHT;
					}
				}
			}
			else if(LeftKey_KeyDown())
			{
				if(player1->PixelsRestantes_Y()==0)
				{
					if(player1->ProximaCasaLivre(LEFT))
					{
						player1->movimento=LEFT;
					}
				}
			}
			if(config.modo_atual==COOP)
			{
				if(BASE_OcorreuKeyDown('W'))
				{
					if(player2->PixelsRestantes_X()==0)
					{
						if(player2->ProximaCasaLivre(UP))
						{
							player2->movimento=UP;
						}
					}
				}
				else if(BASE_OcorreuKeyDown('S'))
				{
					if(player2->PixelsRestantes_X()==0)
					{
						if(player2->ProximaCasaLivre(DOWN))
						{
							player2->movimento=DOWN;
						}
					}
				}
				else if(BASE_OcorreuKeyDown('A'))
				{
					if(player2->PixelsRestantes_Y()==0)
					{
						if(player2->ProximaCasaLivre(LEFT))
						{
							player2->movimento=LEFT;
						}
					}
				}
				else if(BASE_OcorreuKeyDown('D'))
				{
					if(player2->PixelsRestantes_Y()==0)
					{
						if(player2->ProximaCasaLivre(RIGHT))
						{
							player2->movimento=RIGHT;
						}
					}
				}
			}
			if(OcorreuClickLButton())//Chase
			{
//				MudaComportamentoFantasmas(CHASE,true);
			}
			else if(OcorreuClickRButton())//Scatter
			{
//				MudaComportamentoFantasmas(SCATTER,true);
			}
		}
		void OnClosed()
		{
			InterrompeSom();
			if(config.TemOnline())
			{
				comm.EnviarPacote("0");
				comm.FechaConexaoClient();
			}
		}
};
//---------Métodos exclusivos dessa classe
void TelaJogo::InicializaVariaveisJogo()
{
	anim_fundo.trocaspriteautomatico=false;
	mapa.Init();
	bits_restantes=mapa.pontos;
	pellets_restantes=mapa.pellets;
	final_fase=bits_restantes*0.2;
	logicaexecutando=false;
	t_pellet = Timer(7000);
	delay_endfear=4000;
	t_fimdejogo = Timer(4000);
//	t_mortepacman = Timer(2500);
	t_mortepacman=Timer(3500);
	t_resetfase = Timer(1000);
	qtdMortesPacmanPorFantasmas=0;
	waves=0;//vai até 4
	t_wave = Timer(27000);//Pros primeiros estágios. Pro último, são 5 segundos de scatter + infinito de chase
	delay_trocaparachase=7000;//A partir da 3ª onda, passa a ser 5 segundos
	t_acabardots=Timer(90000);
//	t_acabardots=Timer(10000);
	tempo_para_gameover=5000;
	t_gameover=Timer(tempo_para_gameover);
	estado_atual=GHOSTSCATTER;
	requestsom=false;
	ResetaChars();
}
void TelaJogo::MudaComportamentoFantasmas(comportamentos comp,bool forcar)
{
	redghost.MudaComportamento(comp,forcar);
	pinkghost.MudaComportamento(comp,forcar);
	blueghost.MudaComportamento(comp,forcar);
	orangeghost.MudaComportamento(comp,forcar);
}
void TelaJogo::VerificaColisoesPlayer(Player &_player)
{
	if(_player.EstaNoMesmoTile(pacman))
	{
		if(pacman.EmFear()&&!_player.t_respawn.ativo)
		{
			_player.score+=1000;
			qtdMortesPacmanPorFantasmas=0;
			MortePacman();
			vidaspacman--;
		}
	}
	if(_player.EstaNoMesmoTile(redghost))
	{
		if(!redghost.EmFear()&&!_player.t_respawn.ativo)
		{
			MortePlayer(_player);
		}
	}
	if(_player.EstaNoMesmoTile(pinkghost))
	{
		if(!pinkghost.EmFear()&&!_player.t_respawn.ativo)
		{
			MortePlayer(_player);
		}
	}
	if(_player.EstaNoMesmoTile(blueghost))
	{
		if(!blueghost.EmFear()&&!_player.t_respawn.ativo)
		{
			MortePlayer(_player);
		}
	}
	if(_player.EstaNoMesmoTile(orangeghost))
	{
		if(!orangeghost.EmFear()&&!_player.t_respawn.ativo)
		{
			MortePlayer(_player);
		}
	}
}
void TelaJogo::VerificaPosicaoPlayer(Player &_player)
{
	switch(_player.EstaSobre(mapa))
	{
		case char_pellet:
			mapa.SetPosicao(_player.X_MATRIZ(),_player.Y_MATRIZ(),char_vazio);
			_player.score+=pontos_pellet;
			pellets_restantes--;
			InterrompeSom();
			TocaSom(sons[ID_SOMCOMEPELLET],true,false,true);
			t_pellet.Start();
			estado_atual=PACMANFEAR;
			pacman.MudaComportamento(FEAR,true);
			break;
		case char_bit:
			mapa.SetPosicao(_player.X_MATRIZ(),_player.Y_MATRIZ(),char_vazio);
			_player.score+=pontos_bit;
			if(pinkghost.contador_sair<pinkghost.limite_sair)
			{
				pinkghost.contador_sair++;
			}
			else if(blueghost.contador_sair<blueghost.limite_sair)
			{
				blueghost.contador_sair++;
			}
			else if(orangeghost.contador_sair<orangeghost.limite_sair)
			{
				orangeghost.contador_sair++;
			}
			bits_restantes--;
			TocaSom(sons[ID_SOMCOMEPACBIT],true,false);
			break;
	}
}
void TelaJogo::ComeFantasma(Ghost &fantasma)
{
	score+=200*ghoststreak;
	ghoststreak*=2;
	InterrompeSom();
	TocaSom(sons[ID_SOMCOMEGHOST],true,false,true,true);
	fantasma.MudaComportamento(DEAD,true);
}
void TelaJogo::MortePacman()
{
	t_acabardots.Pause();
	t_mortepacman.Start();
}
void TelaJogo::MortePlayer(Player &_player)
{
	_player.vidas--;
	if(_player.vidas<=0)
		t_gameover.Start();
	else
	{
		_player.t_respawn.Start();
		_player.ResetaPosicao();
	}
}
void TelaJogo::MostraInformacoesJogador(int offset, Player _player)
{
	setcolor(WHITE);
	outtextxy(LARGURA_FUNDO+offset,PASSOY_LETRA,"Score: ");
	outtextxy(LARGURA_FUNDO+offset+50,PASSOY_LETRA,ConvertInt(_player.score));
	outtextxy(LARGURA_FUNDO+offset,2*PASSOY_LETRA,"Vidas: ");
	outtextxy(LARGURA_FUNDO+offset+50,2*PASSOY_LETRA,ConvertInt(_player.vidas));
}
void TelaJogo::ResetaChars()
{
	pacman.MudaComportamento(SCATTER);
	MudaComportamentoFantasmas(SCATTER);
	pacman.ResetaPosicao();
	redghost.ResetaPosicao();
	pinkghost.ResetaPosicao();
	blueghost.ResetaPosicao();
	orangeghost.ResetaPosicao();
	player1->ResetaPosicao();
	if(config.TemPlayer2())
		player2->ResetaPosicao();
	redghost.ForcaRenascimento();
//	redghost.saindo=false;
	pinkghost.ForcaRenascimento();
//	pinkghost.saindo=false;
	blueghost.ForcaRenascimento();
//	blueghost.saindo=false;
	orangeghost.ForcaRenascimento();
//	orangeghost.saindo=false;
}
void TelaJogo::SetTrocaSpritesGeral(bool valor)
{
	pacman.setTrocaSprites(valor);
	redghost.setTrocaSprites(valor);
	pinkghost.setTrocaSprites(valor);
	blueghost.setTrocaSprites(valor);
	orangeghost.setTrocaSprites(valor);
	player1->setTrocaSprites(valor);
	if(config.TemPlayer2())
		player2->setTrocaSprites(valor);
}
//-----------Rede-------------------------
char* TelaJogo::MontarSubPacote(Personagem _p)
{
	/*
	Cada personagem (pacman, ghosts e players) vai conter, em seu "sub-pacote":
		- o identificador de quem é ('P' pra pacman, 'J' pra jogador, '1' pra ghost1, vulgo redghost, '2' pra pinkghost, '3' pra blueghost e '4' pra orangeghost)
		- '|'
		- posição em X
		- '|'
		- posição em Y
		- '|'
		- comportamento
		- '|'
		- movimento atual
		- ';'
	*/
	char retorno[100];
	strcpy(retorno,"");
//	_p.char_identificador;
	strcat(retorno,ConvertChar(_p.char_identificador));
	strcat(retorno,"|");
//	_p.x;
	strcat(retorno,ConvertInt(_p.x));
	strcat(retorno,"|");
//	_p.y;
	strcat(retorno,ConvertInt(_p.y));
	strcat(retorno,"|");
//	_p.comportamento;
	strcat(retorno,ConvertInt(_p.comportamento));
	strcat(retorno,"|");
//	_p.movimento;
	strcat(retorno,ConvertInt(_p.movimento));
	strcat(retorno,";");
	return retorno;
}
char* TelaJogo::MontarPacote()
{
	/*
	O client só vai enviar o sub-pacote de seu jogador, e o server vai enviar do seu jogador e dos outros personagens não-jogáveis
	*/
	char retorno[TAMANHO_TEXTO];
	strcpy(retorno,"");
	strcat(retorno,MontarSubPacote(*player1));
	if(!comm.IsCliente())
	{
		strcat(retorno,MontarSubPacote(pacman));
		strcat(retorno,MontarSubPacote(redghost));
		strcat(retorno,MontarSubPacote(pinkghost));
		strcat(retorno,MontarSubPacote(blueghost));
		strcat(retorno,MontarSubPacote(orangeghost));
	}
	return retorno;
}
void TelaJogo::AtualizarInformacoesPersonagem(Personagem &_p, char dados[100])
{
	int i_dados;
	char c_dados;
	char buffer_dados[100];
	int informacoes=0;//0=x;1=y;2=comportamento;3=movimento
	
	c_dados = dados[0];
	i_dados = 0;
	strcpy(buffer_dados,"");
	
	while(c_dados != '\0')
	{
		if(c_dados=='|'||c_dados==';')
		{
			switch(informacoes)
			{
				case 0:
					_p.x=atoi(buffer_dados);
					break;
				case 1:
					_p.y=atoi(buffer_dados);
					break;
				case 2:
					_p.comportamento=(comportamentos)atoi(buffer_dados);
					break;
				case 3:
					_p.movimento=(movimentos)atoi(buffer_dados);
					break;
			}
			strcpy(buffer_dados,"");
			informacoes++;
		}
		else
		{
			strcat(buffer_dados,ConvertChar(c_dados));
		}
		i_dados++;
		c_dados = dados[i_dados];
	}
}
void TelaJogo::TratarPacote()
{
	int i_pacote;
	char c_pacote;
	char buffer_pacote[100];
	
	c_pacote = comm.pacote[0];
	i_pacote = 0;
	strcpy(buffer_pacote,"");
	while(c_pacote != '\0')
	{
		if(c_pacote==';')
		{
			strcat(buffer_pacote,ConvertChar(c_pacote));
			if(buffer_pacote[0]==player2->char_identificador)
				AtualizarInformacoesPersonagem(*player2, buffer_pacote+2);
			else if(buffer_pacote[0]==pacman.char_identificador)
			{
				AtualizarInformacoesPersonagem(pacman, buffer_pacote+2);
				if(pacman.comportamento==DEAD)
					MortePacman();
			}
			else if(buffer_pacote[0]==redghost.char_identificador)
				AtualizarInformacoesPersonagem(redghost, buffer_pacote+2);
			else if(buffer_pacote[0]==pinkghost.char_identificador)
				AtualizarInformacoesPersonagem(pinkghost, buffer_pacote+2);
			else if(buffer_pacote[0]==blueghost.char_identificador)
				AtualizarInformacoesPersonagem(blueghost, buffer_pacote+2);
			else if(buffer_pacote[0]==orangeghost.char_identificador)
				AtualizarInformacoesPersonagem(orangeghost, buffer_pacote+2);
			strcpy(buffer_pacote,"");
		}
		else
		{
			strcat(buffer_pacote,ConvertChar(c_pacote));
		}
		i_pacote++;
		c_pacote = comm.pacote[i_pacote];
	}
}
void TelaJogo::DeuGameOver()
{
	config.gameover=true;
	telamostrando=TELA_INICIAL;
	config.modo_atual=NENHUM;
	exibindo=false;
}
void TelaJogo::VerificaPosicaoGhostComPacman(Ghost &_ghost)
{
	if(pacman.EstaNoMesmoTile(_ghost))
	{
		/*
		Ghost em fear e pacman normal: ComeFantasma
		Ghost em fear e pacman em fear: nada
		Ghost normal e pacman normal: MortePacman
		Ghost normal e pacman em fear: nada
		*/
		if(!pacman.EmFear())
		{
			if(_ghost.EmFear())
			{
				ComeFantasma(_ghost);
			}
			else
			{
				qtdMortesPacmanPorFantasmas++;
				MortePacman();
			}
		}
	}
}
//-----------Rede-------------------------
void TelaJogo::DebugFundo()//O jogo fica bem mais lento
{
	char console_buf[TAMANHO_TEXTO];
	char texto_largura[25];
	char texto_altura[25];
	int i,j;
	setcolor(GREEN);
	setfillstyle(SLASH_FILL,RED);
	strcpy(texto_largura,"Largura: ");
	strcpy(texto_altura,"Altura: ");
	for(i=0;i*TAMANHO_CELULA<ALTURA_FUNDO;i++)
	{
		for(j=0;j*TAMANHO_CELULA<LARGURA_FUNDO;j++)
		{
			line(j*TAMANHO_CELULA,ALTURA_PAINELSUPERIOR,j*TAMANHO_CELULA,ALTURA_PAINELSUPERIOR+ALTURA_FUNDO);//Linhas verticais
			
			switch(mapa.Posicao(j,i)){
				//Exibir paredes do mapa
				case char_parede:
					bar(j*TAMANHO_CELULA,ALTURA_PAINELSUPERIOR+(i*TAMANHO_CELULA)
					,(j+1)*TAMANHO_CELULA,ALTURA_PAINELSUPERIOR+((i+1)*TAMANHO_CELULA));
					break;
				case char_bit:
					outtextxy(j*TAMANHO_CELULA,ALTURA_PAINELSUPERIOR+(i*TAMANHO_CELULA),".");
					break;
				case char_pellet:
					outtextxy(j*TAMANHO_CELULA,ALTURA_PAINELSUPERIOR+(i*TAMANHO_CELULA),"O");
					break;
			}
			if(mapa_path.Posicao(j,i)==char_interseccao)
			{
				outtextxy(j*TAMANHO_CELULA,ALTURA_PAINELSUPERIOR+(i*TAMANHO_CELULA),"?");
			}
		}
		line(j*TAMANHO_CELULA,ALTURA_PAINELSUPERIOR,j*TAMANHO_CELULA,ALTURA_PAINELSUPERIOR+ALTURA_FUNDO);//Linhas verticais
		
		line(0,ALTURA_PAINELSUPERIOR+(i*TAMANHO_CELULA),LARGURA_FUNDO,ALTURA_PAINELSUPERIOR+(i*TAMANHO_CELULA));//Linhas horizontais
	}
	line(0,ALTURA_PAINELSUPERIOR+(i*TAMANHO_CELULA),LARGURA_FUNDO,ALTURA_PAINELSUPERIOR+(i*TAMANHO_CELULA));//Linhas horizontais

	strcat(texto_largura,ConvertInt(TAMANHO_CELULA*j));
	outtextxy(LARGURA_TELA-200,20,texto_largura);
	outtextxy(LARGURA_TELA-200,40,"# Tiles: ");
	outtextxy(LARGURA_TELA-140,40,ConvertInt(j));
	
	strcat(texto_altura,ConvertInt(TAMANHO_CELULA*i));
	outtextxy(LARGURA_TELA-200,80,texto_altura);
	outtextxy(LARGURA_TELA-200,100,"# Tiles: ");
	outtextxy(LARGURA_TELA-140,100,ConvertInt(i));
	
	outtextxy(LARGURA_TELA-200,140,"Lado: ");
	outtextxy(LARGURA_TELA-160,140,ConvertInt(TAMANHO_CELULA));
}
#endif
