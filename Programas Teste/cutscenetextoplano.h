#ifndef CUTSCENETEXTOPLANO_H
#define CUTSCENETEXTOPLANO_H
#include "cutscenebase.h"

class CutsceneTextoPlano : public CutsceneBase{
	public:
		char texto[200];
		CutsceneTextoPlano()
			:CutsceneBase()
		{
		}
		CutsceneTextoPlano(int delay_cutscene, int x, int y, int largura, int altura, char caminho_bitmap[50],char texto[200],bool PulaComESC)
			:CutsceneBase(delay_cutscene, x, y, largura, altura, caminho_bitmap,PulaComESC)
		{
			strcpy(this->texto,texto);
		}
		CutsceneTextoPlano(int delay_cutscene, int largura, int altura, char caminho_bitmap[50],char texto[200])
			:CutsceneTextoPlano(delay_cutscene, 0, 0, largura, altura, caminho_bitmap,texto,true)
		{
		}
		
		void Desenhar()
		{
			CutsceneBase::Desenhar();
			if(!fimexecucao)
				ExibeTextoPlano(10,ALTURA_TELA - 50,GREEN,BLACK,texto);
		}
};

#endif
