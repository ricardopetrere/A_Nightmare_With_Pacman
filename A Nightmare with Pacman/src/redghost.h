#ifndef REDGHOST_H
#define REDGHOST_H
#include "ghost.h"

class RedGhost:public Ghost {
	public:
		RedGhost()
			:Ghost()
		{}
		void Init()
		{
			Ghost::Init();
			char_identificador='1';
			y_inicial=MEIA_CELULA+ALTURA_PAINELSUPERIOR+(TAMANHO_CELULA*11);
			x_inicial=TAMANHO_CELULA*14;
			ResetaPosicao();
			x_scatter=X_TELA(COLUNAS_MAPA-3);
			y_scatter=Y_TELA(-3);
			anim_left.InsereSprite(imagens[ID_GHOSTRED_LEFT]);
			anim_left.InsereSprite(imagens[ID_GHOSTRED_LEFT2]);
			anim_right.InsereSprite(imagens[ID_GHOSTRED_RIGHT]);
			anim_right.InsereSprite(imagens[ID_GHOSTRED_RIGHT2]);
			anim_down.InsereSprite(imagens[ID_GHOSTRED_DOWN]);
			anim_down.InsereSprite(imagens[ID_GHOSTRED_DOWN2]);
			anim_up.InsereSprite(imagens[ID_GHOSTRED_UP]);
			anim_up.InsereSprite(imagens[ID_GHOSTRED_UP2]);
			anim_none.InsereSprite(imagens[ID_GHOSTRED_LEFT]);
			anim_none.InsereSprite(imagens[ID_GHOSTRED_LEFT2]);
		}
		void SetMovimentoInicial()
		{
			movimento=LEFT;
		}
		void DefineAlvo()
		{
			Ghost::DefineAlvo();
			if(comportamento==CHASE)
			{
				x_target=pac->x;
				y_target=pac->y;
			}
		}
};

#endif
