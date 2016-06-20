#ifndef CUTSCENEBASE_H
#define CUTSCENEBASE_H
#include "globais.h"
//#include "imagem.h"
#include "sprite.h"
#include <time.h>

class CutsceneBase:public ElementoGrafico{
	public:
		int delay_cutscene;
		Sprite sprite;
		bool PulaComESC;
		bool executando;
		bool fimexecucao;
		time_t timer_cutscene;
		
		CutsceneBase()
		{
		}
		CutsceneBase(int delay_cutscene, int x, int y, int largura, int altura, char caminho_bitmap[50],bool PulaComESC)
			:CutsceneBase()
		{
			this->delay_cutscene=delay_cutscene;
			this->x=x;
			this->y=y;
			this->largura=largura;
			this->altura=altura;
			sprite=Sprite(x,y,Right(),Bottom(),"",caminho_bitmap);
			this->PulaComESC=PulaComESC;
			executando=false;
			fimexecucao=false;
		}
		CutsceneBase(int delay_cutscene, int largura, int altura, char caminho_bitmap[50])
			:CutsceneBase(delay_cutscene, 0,0,largura, altura, caminho_bitmap,true)
		{
		}
		void Desenhar()
		{
			if(!fimexecucao)
			{
				if(!executando)
				{
					executando=true;
					time(&timer_cutscene);
				}
				sprite.Desenhar();
			}
			if(executando)
			{
				if(CheckTimeout(timer_cutscene,delay_cutscene/1000))
				{
					executando=false;
					fimexecucao=true;
				}
			}
		}
		void ResetaExecucao()
		{
			fimexecucao=false;
			executando=false;
		}
};

#endif
