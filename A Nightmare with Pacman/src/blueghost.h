#ifndef BLUEGHOST_H
#define BLUEGHOST_H
#include "ghost.h"
#include "redghost.h"
class BlueGhost:public Ghost {
	public:
		BlueGhost()
			:Ghost()
		{}
		static RedGhost* red;
		void Init()
		{
			Ghost::Init();
			char_identificador='3';
			limite_sair=30;
			y_inicial=MEIA_CELULA+ ALTURA_PAINELSUPERIOR+(TAMANHO_CELULA*14);
			x_inicial=TAMANHO_CELULA*12;
			ResetaPosicao();
			x_scatter=X_TELA(COLUNAS_MAPA);
			y_scatter=Y_TELA(LINHAS_MAPA+1);
			anim_left.InsereSprite(imagens[ID_GHOSTBLUE_LEFT]);
			anim_right.InsereSprite(imagens[ID_GHOSTBLUE_RIGHT]);
			anim_up.InsereSprite(imagens[ID_GHOSTBLUE_UP]);
			anim_down.InsereSprite(imagens[ID_GHOSTBLUE_DOWN]);
			
			anim_left.InsereSprite(imagens[ID_GHOSTBLUE_LEFT2]);
			anim_right.InsereSprite(imagens[ID_GHOSTBLUE_RIGHT2]);
			anim_up.InsereSprite(imagens[ID_GHOSTBLUE_UP2]);
			anim_down.InsereSprite(imagens[ID_GHOSTBLUE_DOWN2]);
			
			//Começa olhando pra cima
			anim_none.InsereSprite(imagens[ID_GHOSTBLUE_UP]);
			anim_none.InsereSprite(imagens[ID_GHOSTBLUE_UP2]);
			anim_none.InsereSprite(imagens[ID_GHOSTBLUE_DOWN]);
			anim_none.InsereSprite(imagens[ID_GHOSTBLUE_DOWN2]);
		}
		static void AmarrarRedGhost(RedGhost &r)
		{
			BlueGhost::red=&r;
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
				int tmp_x;
				int tmp_y;
				switch(pac->movimento){
					case UP:
						tmp_x=pac->x-red->x;
						tmp_y=(pac->y-2*TAMANHO_CELULA)-red->y;
						x_target=red->x+2*tmp_x;
						y_target=red->y+2*tmp_y;
						break;
					case RIGHT:
						tmp_x=(pac->x+2*TAMANHO_CELULA)-red->x;
						tmp_y=(pac->y)-red->y;
						x_target=red->x+2*tmp_x;
						y_target=red->y+2*tmp_y;
						break;
					case DOWN:
						tmp_x=(pac->x)-red->x;
						tmp_y=(pac->y+2*TAMANHO_CELULA)-red->y;
						x_target=red->x+2*tmp_x;
						y_target=red->y+2*tmp_y;
						break;
					case LEFT:
						tmp_x=(pac->x-2*TAMANHO_CELULA)-red->x;
						tmp_y=(pac->y)-red->y;
						x_target=red->x+2*tmp_x;
						y_target=red->y+2*tmp_y;
						break;
					case NONE:
						tmp_x=(pac->x)-red->x;
						tmp_y=(pac->y)-red->y;
						x_target=red->x+2*tmp_x;
						y_target=red->y+2*tmp_y;
						break;
				}
			}
		}
};
RedGhost* BlueGhost::red;
#endif
