#ifndef ORANGEGHOST_H
#define ORANGEGHOST_H
#include "ghost.h"

class OrangeGhost:public Ghost {
	public:
		OrangeGhost()
			:Ghost()
		{}
		void Init()
		{
			Ghost::Init();
			char_identificador='4';
			limite_sair=60;
			y_inicial=MEIA_CELULA+ ALTURA_PAINELSUPERIOR+(TAMANHO_CELULA*14);
			x_inicial=TAMANHO_CELULA*16;
			ResetaPosicao();
			x_scatter=X_TELA(0);
			y_scatter=Y_TELA(LINHAS_MAPA+1);
			anim_left.InsereSprite(imagens[ID_GHOSTORANGE_LEFT]);
			anim_right.InsereSprite(imagens[ID_GHOSTORANGE_RIGHT]);
			anim_up.InsereSprite(imagens[ID_GHOSTORANGE_UP]);
			anim_down.InsereSprite(imagens[ID_GHOSTORANGE_DOWN]);
			
			anim_left.InsereSprite(imagens[ID_GHOSTORANGE_LEFT2]);
			anim_right.InsereSprite(imagens[ID_GHOSTORANGE_RIGHT2]);
			anim_up.InsereSprite(imagens[ID_GHOSTORANGE_UP2]);
			anim_down.InsereSprite(imagens[ID_GHOSTORANGE_DOWN2]);
			
			//Começa olhando pra cima
			anim_none.InsereSprite(imagens[ID_GHOSTORANGE_UP]);
			anim_none.InsereSprite(imagens[ID_GHOSTORANGE_UP2]);
			anim_none.InsereSprite(imagens[ID_GHOSTORANGE_DOWN]);
			anim_none.InsereSprite(imagens[ID_GHOSTORANGE_DOWN2]);
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
				double d_target=CalculaDistanciaReta(X_MATRIZ(x),Y_MATRIZ(y),X_MATRIZ(pac->x),Y_MATRIZ(pac->y));
				if(d_target>8)
				{
					x_target=pac->x;
					y_target=pac->y;
				}
				else
				{
					x_target=x_scatter;
					y_target=y_scatter;
				}
			}
		}
};

#endif
