#ifndef TELACREDITOS_H
#define TELACREDITOS_H
#include "telabase.h"
#include "pacman.h"
#include "redghost.h"
#include "pinkghost.h"
#include "blueghost.h"
#include "orangeghost.h"

class TelaCreditos:public TelaBase {
	public:
		Botao btnVoltar;
		
		Pacman p_pacman;
		Texto txtEquipe;
		RedGhost p_redghost;
		Texto txtNomeJan;
		PinkGhost p_pinkghost;
		Texto txtNomeNatasha;
		BlueGhost p_blueghost;
		Texto txtNomeNathalia;
		OrangeGhost p_orangeghost;
		Texto txtNomeRicardo;
		Ghost p_fearghost;
		Texto txtAgradecimentos;
		Ghost p_fearendghost;
		Texto txtNomesAgradecidos;
		
		TelaCreditos(int delay)
			:TelaBase(delay)
		{
		}
		TelaCreditos()
			:TelaCreditos(DELAY)
		{
		}
		void InitializeComponents()
		{
			setbkcolor(BLACK);
			p_pacman.InitBig();
			p_pacman.SetOrigem(Tiles(-5),Tiles(3));
			p_pacman.ResetaPosicao();
			p_pacman.movimento=RIGHT;
			txtEquipe = Texto("Equipe:",0,0,YELLOW);
			
			p_redghost.Init();
			p_redghost.SetOrigem(Tiles(-5),Tiles(4));
			p_redghost.ResetaPosicao();
			p_redghost.movimento=RIGHT;
			txtNomeJan = Texto("Jan Michael Nowikow Popoff",0,0,RED);
			
			p_pinkghost.Init();
			p_pinkghost.SetOrigem(Tiles(-5),Tiles(5));
			p_pinkghost.ResetaPosicao();
			p_pinkghost.movimento=RIGHT;
			txtNomeNatasha = Texto("Natasha Barreira Flausino",0,0,COLOR(255,0,255));
			
			p_blueghost.Init();
			p_blueghost.SetOrigem(Tiles(-5),Tiles(6));
			p_blueghost.ResetaPosicao();
			p_blueghost.movimento=RIGHT;
			txtNomeNathalia = Texto("Nathalia Regina Rinaldi Pereira",0,0,CYAN);
			
			p_orangeghost.Init();
			p_orangeghost.SetOrigem(Tiles(-5),Tiles(7));
			p_orangeghost.ResetaPosicao();
			p_orangeghost.movimento=RIGHT;
			txtNomeRicardo = Texto("Ricardo Cardoso Petrére",0,0,COLOR(255,128,0));
			
			p_fearghost.Init();
			p_fearghost.SetOrigem(Tiles(-5),Tiles(10));
			p_fearghost.ResetaPosicao();
			p_fearghost.movimento=RIGHT;
			p_fearghost.comportamento=FEAR;
			txtAgradecimentos = Texto("Agradecimentos:",0,0,BLUE);
			
			p_fearendghost.Init();
			p_fearendghost.SetOrigem(Tiles(-5),Tiles(11));
			p_fearendghost.ResetaPosicao();
			p_fearendghost.movimento=RIGHT;
			p_fearendghost.comportamento=ENDFEAR;
			txtNomesAgradecidos = Texto("Turma JOGNA2 do primeiro semestre de 2016",0,0,WHITE);
			
			btnVoltar=Botao(LARGURA_FUNDO/3,ALTURA_TELA-100,100,20,LIGHTGRAY,"Voltar");
			TocaSom(sons[ID_SOMFIMJOGO],true,true,false,true);
		}
		void MoverPersonagemEmX(Personagem &_personagem)
		{
			if(_personagem.x<LARGURA_FUNDO/2)
			{
				_personagem.x+=_personagem.passox;
			}
		}
		void AmarrarTextoAoPersonagem(Texto &_txt, Personagem &_personagem,int _distancia_x, int _distancia_y=0)
		{
			_txt.x=_personagem.x+_distancia_x;
			_txt.y=_personagem.y+_distancia_y;
		}
		void Loop()
		{
			MoverPersonagemEmX(p_pacman);
			MoverPersonagemEmX(p_redghost);
			MoverPersonagemEmX(p_pinkghost);
			MoverPersonagemEmX(p_blueghost);
			MoverPersonagemEmX(p_orangeghost);
			MoverPersonagemEmX(p_fearghost);
			MoverPersonagemEmX(p_fearendghost);
			
			AmarrarTextoAoPersonagem(txtEquipe,p_pacman,Tiles(0.5),Tiles(-1));
			AmarrarTextoAoPersonagem(txtNomeJan,p_redghost,Tiles(1));
			AmarrarTextoAoPersonagem(txtNomeNatasha,p_pinkghost,Tiles(1));
			AmarrarTextoAoPersonagem(txtNomeNathalia,p_blueghost,Tiles(1));
			AmarrarTextoAoPersonagem(txtNomeRicardo,p_orangeghost,Tiles(1));
			AmarrarTextoAoPersonagem(txtAgradecimentos,p_fearghost,Tiles(1));
			AmarrarTextoAoPersonagem(txtNomesAgradecidos,p_fearendghost,Tiles(1));
		}
		void DesenharTextoEPersonagem(Texto &_texto, Personagem &_personagem)
		{
			_personagem.Desenhar();
			_texto.Desenhar();
		}
		void DesenharObjetos()
		{
			DesenharTextoEPersonagem(txtEquipe,p_pacman);
			DesenharTextoEPersonagem(txtNomeJan,p_redghost);
			DesenharTextoEPersonagem(txtNomeNatasha,p_pinkghost);
			DesenharTextoEPersonagem(txtNomeNathalia,p_blueghost);
			DesenharTextoEPersonagem(txtNomeRicardo,p_orangeghost);
			DesenharTextoEPersonagem(txtAgradecimentos,p_fearghost);
			DesenharTextoEPersonagem(txtNomesAgradecidos,p_fearendghost);
			
			btnVoltar.Desenhar();
		}
		void Eventos_Click()
		{
			if(OcorreuClickLButton())
			{
				if(btnVoltar.CursorEstaEmCima())
				{
					telamostrando=TELA_INICIAL;
					exibindo=false;
				}
			}
			if(OcorreuClickESC())
			{
				telamostrando=TELA_INICIAL;
				exibindo=false;
			}
		}
		void OnClosed()
		{
			InterrompeSom();
		}
};

#endif
