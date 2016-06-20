#ifndef CUTSCENEBASE_H
#define CUTSCENEBASE_H
#include "globais.h"
#include "imagem.h"

class CutsceneBase {
	public:
		int delay_cutscene;
		Imagem bmp;
		char texto[200];
		CutsceneBase()
		{
			
		}
		CutsceneBase(int delay_cutscene, int largura, int altura, char caminho_bitmap[50],char texto[200])
		{
			this->delay_cutscene=delay_cutscene;
			bmp = Imagem::GerarBitmap(caminho_bitmap,0,0,largura,altura);
			strcpy(this->texto,texto);
		}
};

#endif
