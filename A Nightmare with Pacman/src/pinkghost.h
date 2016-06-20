#ifndef PINKGHOST_H
#define PINKGHOST_H
#include "ghost.h"

class PinkGhost:public Ghost {
	public:
		PinkGhost()
			:Ghost()
		{}
		void Init()
		{
			Ghost::Init();
			char_identificador='2';
//			contador_sair=0;
			y_inicial=MEIA_CELULA+ ALTURA_PAINELSUPERIOR+(TAMANHO_CELULA*14);
			x_inicial=TAMANHO_CELULA*14;
			ResetaPosicao();
			x_scatter=X_TELA(2);
			y_scatter=Y_TELA(-3);
			anim_left.InsereSprite(imagens[ID_GHOSTPINK_LEFT]);
			anim_right.InsereSprite(imagens[ID_GHOSTPINK_RIGHT]);
			anim_up.InsereSprite(imagens[ID_GHOSTPINK_UP]);
			anim_down.InsereSprite(imagens[ID_GHOSTPINK_DOWN]);
			
			anim_left.InsereSprite(imagens[ID_GHOSTPINK_LEFT2]);
			anim_right.InsereSprite(imagens[ID_GHOSTPINK_RIGHT2]);
			anim_up.InsereSprite(imagens[ID_GHOSTPINK_UP2]);
			anim_down.InsereSprite(imagens[ID_GHOSTPINK_DOWN2]);
			
			//Começa olhando pra baixo
			anim_none.InsereSprite(imagens[ID_GHOSTPINK_DOWN]);	
			anim_none.InsereSprite(imagens[ID_GHOSTPINK_DOWN2]);
			anim_none.InsereSprite(imagens[ID_GHOSTPINK_UP]);	
			anim_none.InsereSprite(imagens[ID_GHOSTPINK_UP2]);
		}
		void SetMovimentoInicial()
		{
			movimento=NONE;
		}
		void DefineAlvo()
		{
			Ghost::DefineAlvo();
			if(comportamento==CHASE)
			{
				switch(pac->movimento){
					case UP:
						x_target=pac->x;
						y_target=pac->y-4*TAMANHO_CELULA;
						break;
					case RIGHT:
						x_target=pac->x+4*TAMANHO_CELULA;
						y_target=pac->y;
						break;
					case DOWN:
						x_target=pac->x;
						y_target=pac->y+4*TAMANHO_CELULA;
						break;
					case LEFT:
						x_target=pac->x-4*TAMANHO_CELULA;
						y_target=pac->y;
						break;
					case NONE:
						x_target=pac->x;
						y_target=pac->y;
						break;
					
				}
			}
		}
};

#endif
