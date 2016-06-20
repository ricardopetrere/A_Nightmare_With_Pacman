#ifndef PACMAN_H
#define PACMAN_H
#include "personagem.h"

class Pacman :public Personagem{
	public:
		Pacman()
			:Personagem()
		{
		}
		void Init()
		{
			char_identificador='P';
			y_inicial=MEIA_CELULA+ ALTURA_PAINELSUPERIOR+(TAMANHO_CELULA*23);
			x_inicial=TAMANHO_CELULA*14;
			ResetaPosicao();
			AI=true;
			
			x_scatter=x_inicial;
			y_scatter=y_inicial;
			
			
			anim_up=Animacao(100);
			anim_down=Animacao(100);
			anim_left=Animacao(100);
			anim_right=Animacao(100);
			anim_none=Animacao(100);
			anim_fear=Animacao(200);
			anim_endfear=Animacao(200);
			anim_dead=Animacao(200);
			
			anim_down.InsereSprite(imagens[ID_PACMAN_FULL]);
			anim_up.InsereSprite(imagens[ID_PACMAN_FULL]);
			anim_left.InsereSprite(imagens[ID_PACMAN_FULL]);
			anim_right.InsereSprite(imagens[ID_PACMAN_FULL]);
			anim_none.InsereSprite(imagens[ID_PACMAN_FULL]);
			
			anim_down.InsereSprite(imagens[ID_PACMAN_DOWN]);
			anim_up.InsereSprite(imagens[ID_PACMAN_UP]);
			anim_left.InsereSprite(imagens[ID_PACMAN_LEFT]);
			anim_right.InsereSprite(imagens[ID_PACMAN_RIGHT]);
			
			anim_down.InsereSprite(imagens[ID_PACMAN_DOWN2]);
			anim_up.InsereSprite(imagens[ID_PACMAN_UP2]);
			anim_left.InsereSprite(imagens[ID_PACMAN_LEFT2]);
			anim_right.InsereSprite(imagens[ID_PACMAN_RIGHT2]);
			
			anim_down.InsereSprite(imagens[ID_PACMAN_DOWN]);
			anim_up.InsereSprite(imagens[ID_PACMAN_UP]);
			anim_left.InsereSprite(imagens[ID_PACMAN_LEFT]);
			anim_right.InsereSprite(imagens[ID_PACMAN_RIGHT]);
			
			anim_fear.InsereSprite(imagens[ID_PACMAN_FEAR]);
			
			anim_endfear.InsereSprite(imagens[ID_PACMAN_FEAR]);
			anim_endfear.InsereSprite(imagens[ID_PACMAN_FEAR_WHITE]);
			
			//Animação de morte é composta por: ID_PACMAN_FULL, ID_PACMAN_UP e as abaixo
			anim_dead.InsereSprite(imagens[ID_PACMAN_FULL]);
			anim_dead.InsereSprite(imagens[ID_PACMAN_UP]);
			anim_dead.InsereSprite(imagens[ID_PACMAN_DEATH1]);
			anim_dead.InsereSprite(imagens[ID_PACMAN_DEATH2]);
			anim_dead.InsereSprite(imagens[ID_PACMAN_DEATH3]);
			anim_dead.InsereSprite(imagens[ID_PACMAN_DEATH4]);
			anim_dead.InsereSprite(imagens[ID_PACMAN_DEATH5]);
			anim_dead.InsereSprite(imagens[ID_PACMAN_DEATH6]);
			anim_dead.InsereSprite(imagens[ID_PACMAN_DEATH7]);
			anim_dead.InsereSprite(imagens[ID_PACMAN_DEATH8]);
			anim_dead.InsereSprite(imagens[ID_PACMAN_DEATH9]);
			anim_dead.InsereSprite(imagens[ID_PACMAN_DEATH10]);
			anim_dead.InsereSprite(imagens[ID_PACMAN_DEATH11]);
		}
		void InitBig()
		{
			offsetimagem_x=-Tiles(1)*PROPORCAO_FUNDO;
			offsetimagem_y=-Tiles(1)*PROPORCAO_FUNDO;
//			passox=DEFAULT_PASSO;
//			passoy=DEFAULT_PASSO;
			ResetaPosicao();
			anim_right=Animacao(100);
			anim_right.InsereSprite(imagens[ID_BIGPACMAN_FULL]);
			anim_right.InsereSprite(imagens[ID_BIGPACMAN_RIGHT1]);
			anim_right.InsereSprite(imagens[ID_BIGPACMAN_RIGHT2]);
			movimento=RIGHT;
		}
		void SetMovimentoInicial()
		{
			movimento=NONE;
		}
		void SetPassoDEAD()
		{
			passox=0;
			passoy=0;
			anim_dead.counter=0;
		}
		void LogicaMover()
		{
			if(movimento==NONE)//Só no começo da fase/após morrer é assim
			{
				movimento=RIGHT;
			}
			Personagem::LogicaMover();
		}
		void AnimacaoMorte()
		{
			anim_dead.Desenhar(X_Imagem(),Y_Imagem());
		}
		void DecidirProximoPasso(bool forcar=false)
		{
			if(comportamento==FEAR||comportamento==ENDFEAR)
			{
				bool calculou=false;
				int escolha=-1;
				if(EstaSobre(mapa)==char_parede)
				{
					movimento=NONE;
					return;
				}
				while(!calculou)
				{
					escolha=rand()%4;
					switch(escolha){
						case UP:
							movimento=UP;
							if(CharProximaCasa()!=char_parede)
								calculou=true;
							break;
						case RIGHT:
							movimento=RIGHT;
							if(CharProximaCasa()!=char_parede)
								calculou=true;
							break;
						case DOWN:
							movimento=DOWN;
							if(CharProximaCasa()!=char_parede)
								calculou=true;
							break;
						case LEFT:
							movimento=LEFT;
							if(CharProximaCasa()!=char_parede)
								calculou=true;
							break;
							
					}
				}
			}
			else
			{
				double d_left = 999;
				double d_right = 999;
				double d_up = 999;
				double d_down = 999;
				if(comportamento==SCATTER||comportamento==CHASE)
				{
//					DefineAlvo();
				}
				//if I go left?
				if(CharProximaCasa(LEFT)!=char_parede
				&&PixelsRestantes_Y()==0)
				{
					d_left=CalculaDistanciaReta(X_MATRIZ()-1,Y_MATRIZ(),X_MATRIZ(x_target),Y_MATRIZ(y_target));
				}
				//if I go right?
				if(CharProximaCasa(RIGHT)!=char_parede
				&&PixelsRestantes_Y()==0)
				{
					d_right=CalculaDistanciaReta(X_MATRIZ()+1,Y_MATRIZ(),X_MATRIZ(x_target),Y_MATRIZ(y_target));
				}
				//if I go up?
				if(CharProximaCasa(UP)!=char_parede
				&&PixelsRestantes_X()==0)
				{
					d_up=CalculaDistanciaReta(X_MATRIZ(),Y_MATRIZ()-1,X_MATRIZ(x_target),Y_MATRIZ(y_target));
				}
				//if I go down?
				if(CharProximaCasa(DOWN)!=char_parede
				&&PixelsRestantes_X()==0)
				{
					d_down=CalculaDistanciaReta(X_MATRIZ(),Y_MATRIZ()+1,X_MATRIZ(x_target),Y_MATRIZ(y_target));
				}
				
				//Ordem de prioridades no caso de resultados semelhantes: UP>LEFT>DOWN
				if(d_up<=d_left&&d_up<=d_right&&d_up<=d_down)
				{
					movimento=UP;
				}
				else if(d_left<=d_up&&d_left<=d_right&&d_left<=d_down)
				{
					movimento=LEFT;
				}
				else if(d_down<=d_left&&d_down<=d_up&&d_down<=d_right)
				{
					movimento=DOWN;
				}
				else if(d_right<=d_left&&d_right<=d_up&&d_right<=d_down)
				{
					movimento=RIGHT;
				}
				else//Impossível, mas vai que...
				{
					movimento=NONE;
				}
			}
		}
};

#endif
