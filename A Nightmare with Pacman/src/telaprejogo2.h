#ifndef TELAPREJOGO2_H
#define TELAPREJOGO2_H
#include "telabase.h"

class TelaPreJogo2:public TelaBase {
	public:
		Texto txtEscolhaPersonagem;
		
		Animacao animacoes[QTD_JOGADORES];
		Texto txtPersonagem;
		Botao btnChangeLeft;
		Botao btnChangeRight;
		
		Texto txtPersonagem2;
		Botao btnChangeLeft2;
		Botao btnChangeRight2;
		
		Botao btnComecar;
		Timer t_inputusuario;
		bool comecarpartida;
		
		void TrocaImagemPraEsquerda(int player=1);
		void TrocaImagemPraDireita(int player=1);
		
		TelaPreJogo2(int delay)
			:TelaBase(delay)
		{
		}
		TelaPreJogo2()
			:TelaPreJogo2(DELAY)
		{
		}
		void InitializeComponents()
		{
			setbkcolor(COLOR(20,0,50));
			txtEscolhaPersonagem = Texto("Escolha seu personagem", 250, 100, GREEN);
			
			txtPersonagem = Texto("Você:",100,300,GREEN);
			btnChangeLeft = Botao(50,350,50,100,LIGHTGRAY,"<");
			btnChangeRight = Botao(200,350,50,100,LIGHTGRAY,">");
			
			txtPersonagem2 = Texto("Outro Jogador:",CENTROX_TELA+100,300,GREEN);
			btnChangeLeft2 = Botao(CENTROX_TELA+50,350,50,100,LIGHTGRAY,"<");
			btnChangeRight2 = Botao(CENTROX_TELA+200,350,50,100,LIGHTGRAY,">");
			
			btnComecar=Botao(LARGURA_TELA/3,500,LARGURA_TELA/3,30,LIGHTGRAY,"Começar");
			t_inputusuario=Timer(100);
			comecarpartida=false;
			
			for(int i=0;i<QTD_JOGADORES;i++)
			{
				animacoes[i] = Animacao(-1);
				animacoes[i].InsereSprite(thumbs[i]);
			}
		}
		void Loop()
		{
			if(config.TemOnline())
			{
				comm.EnviarPacote(ConvertInt(config.indexplayer1));
				comm.RecebePacote();
				if(CharIsNumber(comm.pacote[0]))
				{
					if(atoi(comm.pacote)!=config.indexplayer2)
						config.indexplayer2=atoi(comm.pacote);
				}
			}
		}
		void DesenharObjetos()
		{
			txtEscolhaPersonagem.Desenhar();
			
			txtPersonagem.Desenhar();
			btnChangeLeft.Desenhar();
			animacoes[config.indexplayer1].Desenhar(100,350);
			btnChangeRight.Desenhar();
			if(config.TemPlayer2())
			{
				txtPersonagem2.Desenhar();
				animacoes[config.indexplayer2].Desenhar(CENTROX_TELA+100,350);
				if(config.modo_atual==COOP)
				{
					btnChangeLeft2.Desenhar();
					btnChangeRight2.Desenhar();
				}
			}
			
			btnComecar.Desenhar();
		}
		void Eventos_Click()
		{
			Controle_XINPUT* ptr_controlexinput = dynamic_cast<Controle_XINPUT*>(config.controles[1]);
			if(ptr_controlexinput)
				ptr_controlexinput->MoverMouse();
			if(config.controles[0]->ComandoSelecionar())
//			if(OcorreuClickLButton())
			{
				if(btnChangeLeft.CursorEstaEmCima())
				{
					TrocaImagemPraEsquerda();
				}
				else if(btnChangeRight.CursorEstaEmCima())
				{
					TrocaImagemPraDireita();
				}
				else if(config.modo_atual==COOP)
				{
					if(btnChangeLeft2.CursorEstaEmCima())
					{
						TrocaImagemPraEsquerda(2);
					}
					else if(btnChangeRight2.CursorEstaEmCima())
					{
						TrocaImagemPraDireita(2);
					}
					else if(btnComecar.CursorEstaEmCima())
					{
						telamostrando=TELA_JOGO;
						exibindo=false;
					}
				}
				else if(btnComecar.CursorEstaEmCima())
				{
					if(config.TemPlayer2()&&config.indexplayer1==config.indexplayer2)
					{
					}
					else
					{
						if(config.TemOnline())
						{
							while(!comecarpartida)
							{
								if(GetAsyncKeyState(VK_ESCAPE)&0x80)
									break;
								comm.EnviarPacote("COMECAR");
								if(strcmp(comm.pacote,"COMECAR")==0)//Se já havia recebido um pedido de começar partida, não precisa esperar confirmação
								{
									comecarpartida=true;
								}
								else
								{
									comm.RecebePacote();
									if(strcmp(comm.pacote,"COMECAR")==0)
									{
										comecarpartida=true;
									}
									else if(CharIsNumber(comm.pacote[0]))// comm.pacote[0]>='0'&&comm.pacote[0]<='9')
									{
										if(atoi(comm.pacote)!=config.indexplayer2)
										{
											config.indexplayer2=atoi(comm.pacote);
											break;
										}
									}
								}
							}
							if(comecarpartida)
							{
								telamostrando=TELA_JOGO;
								exibindo=false;
							}
						}
						else
						{
							telamostrando=TELA_JOGO;
							exibindo=false;
						}
					}
				}
			}
//			if(OcorreuClickESC())
			if(config.controles[0]->ComandoVoltar()||config.controles[1]->ComandoVoltar())
			{
				exibindo=false;
				telamostrando=TELA_PREJOGO;
			}
			
			if(!t_inputusuario.CheckTimeout())
				return;
			
//			if(BASE_OcorreuClick(VK_LEFT,LeftPressed))
			if(config.controles[0]->ComandoParaEsquerda())
			{
				TrocaImagemPraEsquerda();
			}
//			else if(BASE_OcorreuClick(VK_RIGHT,RightPressed))
			else if(config.controles[0]->ComandoParaDireita())
			{
				TrocaImagemPraDireita();
			}
			
			if(config.modo_atual==COOP)
			{
				if(config.controles[1]->ComandoParaEsquerda(false))
				{
					TrocaImagemPraEsquerda(2);
				}
				else if(config.controles[1]->ComandoParaDireita(false))
				{
					TrocaImagemPraDireita(2);
				}
			}

			t_inputusuario.Start();
			
		}
		void OnClosed()
		{
			if(telamostrando!=TELA_JOGO&&config.TemOnline())
				comm.FechaConexaoClient();
		}
};
void TelaPreJogo2::TrocaImagemPraEsquerda(int player)
{
	if(player==1)
	{
		TrocarIndexPlayerPraEsquerda(&config.indexplayer1);
	}
	else if(player==2)
	{
		TrocarIndexPlayerPraEsquerda(&config.indexplayer2);
	}
}
void TelaPreJogo2::TrocaImagemPraDireita(int player)
{
	if(player==1)
	{
		TrocarIndexPlayerPraDireita(&config.indexplayer1);
	}
	else if(player==2)
	{
		TrocarIndexPlayerPraDireita(&config.indexplayer2);
	}
}
#endif
