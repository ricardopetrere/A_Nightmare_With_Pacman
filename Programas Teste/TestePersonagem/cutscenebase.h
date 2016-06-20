#ifndef CUTSCENEBASE_H
#define CUTSCENEBASE_H
#include "globais.h"
//#include "imagem.h"
#include "sprite.h"

class CutsceneBase:public ElementoGrafico{
	public:
		int delay_cutscene;
		Sprite cutscene;
		char texto[200];
		CutsceneBase()
		{
			
		}
		CutsceneBase(int delay_cutscene, int x, int y, int largura, int altura, char caminho_bitmap[50],char texto[200])
		{
			this->x=x;
			this->y=y;
			this->largura=largura;
			this->altura=altura;
			this->delay_cutscene=delay_cutscene;
			cutscene.CarregaBitmaps(x,y,Right(),Bottom(),"",caminho_bitmap);
			strcpy(this->texto,texto);
		}
		CutsceneBase(int delay_cutscene, int largura, int altura, char caminho_bitmap[50],char texto[200])
		{
			CutsceneBase(delay_cutscene, 0,0,largura, altura, caminho_bitmap,texto);
		}
		void Desenhar()
		{
			cutscene.Desenhar();
		}
};

#endif
