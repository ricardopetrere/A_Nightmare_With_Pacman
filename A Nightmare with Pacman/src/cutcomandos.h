#ifndef CUTCOMANDOS_H
#define CUTCOMANDOS_H
#include "cutscenebase.h"
class CutComandos : public CutsceneBase{
	public:
		bool PulouCutscene=false;
		bool JaEnviouSolicitacao=false;
		Texto txtESC;
		Texto txtAguardandoOutroJogador;
		Texto txtComandos1;
		Texto txtTeclas1;
		Texto txtComandos2;
		Texto txtTeclas2;
		CutComandos()
			:CutsceneBase()
		{
		}
		CutComandos(int delay_ms, bool PulaComESC)
			:CutsceneBase(delay_ms,PulaComESC)
		{
		}
		void InitializeComponents()
		{
			txtESC=Texto("ESC Pula a Cutscene",10,ALTURA_TELA-50,GREEN);
			txtAguardandoOutroJogador = Texto("Aguardando outro jogador...",LARGURA_FUNDO-100,ALTURA_TELA-50,RED);
			
			txtComandos1 = Texto("Comandos:",100,120,GREEN);
			txtTeclas1 = Texto("Setas direcionais: Movimento",100,200,GREEN);
			
			txtComandos2 = Texto("Comandos (Player 2):",CENTROX_TELA+100,120,GREEN);
			txtTeclas2 = Texto("W,A,S,D: Movimento",CENTROX_TELA+100,200,GREEN);
		}
		void Loop()
		{
			if(t_start.CheckTimeout())
				exibindo=false;
			else if(PulouCutscene)
			{
				if(config.TemOnline())
				{
					if(JaEnviouSolicitacao)
					{
						comm.RecebePacote();
						if(strcmp(comm.pacote,"PULAR")==0)
						{
							exibindo=false;
						}
					}
					else
					{
						comm.EnviarPacote("PULAR");
						JaEnviouSolicitacao=true;
					}
				}
				else
				{
					exibindo=false;
				}
			}
		}
		void Eventos_Click()
		{
			if(PulaComESC&&OcorreuClickESC())
			{
//				exibindo=false;
				PulouCutscene=true;
			}
		}
		void DesenharObjetos()
		{
			txtESC.Desenhar();
			if(PulouCutscene)
			{
				txtAguardandoOutroJogador.Desenhar();
			}
			txtComandos1.Desenhar();
			txtTeclas1.Desenhar();
			outtextxy(150,350,"Seu Personagem:");
			thumbs[config.indexplayer1].Desenhar(150,400);
			if(config.TemPlayer2())
			{
				if(config.modo_atual==COOP)
				{
					txtComandos2.Desenhar();
					txtTeclas2.Desenhar();
				}
				outtextxy(CENTROX_TELA+150,350,"Personagem 2:");
				thumbs[config.indexplayer2].Desenhar(CENTROX_TELA+150,400);
			}
		}
		void OnClosed()
		{
			if(!JaEnviouSolicitacao&&config.TemOnline())
			{
				comm.EnviarPacote("PULAR");
			}
		}
};

#endif
