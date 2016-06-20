#ifndef PLAYER_H
#define PLAYER_H
#include "personagem.h"
class Player:public Personagem {
	public:
		int seed;
		int score;
		int vidas;
		Timer t_respawn;
		Player()
			:Personagem()
		{
			
		}
		void Init()
		{
			int tmp_posicao=rand()%4;
			Init(tmp_posicao);
		}
		void Init(int seed)//um número de 0 a 3, pra escolher lugar
		{
			this->seed=seed;
			char_identificador='J';
			score=0;
			vidas=6;
			x_inicial=X_TELA(12+3*(seed/2))+MEIA_CELULA;
			y_inicial=Y_TELA(5+21*(seed%2))+MEIA_CELULA;
			t_respawn=Timer(1000);
			ResetaPosicao();
		}
		void SetMovimentoInicial()
		{
			movimento=LEFT;
		}
};

#endif
