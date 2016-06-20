#ifndef CUTSCENETEXTOPLANO_H
#define CUTSCENETEXTOPLANO_H
#include "cutscenebase.h"

class CutsceneTextoPlano : public CutsceneBase{
	public:
		CutsceneTextoPlano()
			:CutsceneBase()
		{
			
		}
		CutsceneTextoPlano(int delay_cutscene, int largura, int altura, char caminho_bitmap[50],char texto[200])
			:CutsceneBase(delay_cutscene, largura, altura, caminho_bitmap,texto)
		{
		}
		void ExibirTextoPlano(bool PulaComESC=true)
		{
			ExibeTextoPlano(10,ALTURA_TELA - 50,GREEN,BLACK,texto);
			SetPaginaVisual();
			ContaTimeout((delay_cutscene/1000),PulaComESC);
		}
		void Desenhar()
		{
			CutsceneBase::Desenhar();
			ExibirTextoPlano();
		}
};

#endif
