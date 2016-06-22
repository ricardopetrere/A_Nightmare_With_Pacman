#ifndef CONTROLEJOGO_H
#define CONTROLEJOGO_H
#include <stdlib.h>
#include <iostream>
#include "player.h"
#include "controle_xinput.h"
#include "controle_keyboard_mouse.h"

enum ModosDeJogo{
	NENHUM=-1,SINGLEPLAYER,CLIENT,SERVER,COOP
};
#define QTD_JOGADORES (4)

void TrocarIndexPlayerPraEsquerda(int* variavel_index)
{
	*variavel_index=(*variavel_index+QTD_JOGADORES-1)%QTD_JOGADORES;
}
void TrocarIndexPlayerPraDireita(int* variavel_index)
{
	*variavel_index=(*variavel_index+1)%QTD_JOGADORES;
}

struct ControleJogo {
	bool gameover=false;
	bool sair=false;
	int fases=0;
	char ip[16]="127.0.0.1";
	int porta=4000;
	ModosDeJogo modo_atual=NENHUM;
	
	Player jogadores[QTD_JOGADORES];
	int indexplayer1=0;
	int indexplayer2=1;
	
	ControleBase* controles[4];//XINPUT só aceita até 4 controles
	
	
	void CarregaSpritesJogadores(int indexjogador)
	{
		for(int n=ID_CHAR1_LEFT1+8*indexjogador;n<=ID_CHAR1_LEFT4+8*indexjogador;n++)
		{
			jogadores[indexjogador].anim_left.InsereSprite(imagensplayers[n]);
			jogadores[indexjogador].anim_up.InsereSprite(imagensplayers[n]);
		}
		for(int n=ID_CHAR1_RIGHT1+8*indexjogador;n<=ID_CHAR1_RIGHT4+8*indexjogador;n++)
		{
			jogadores[indexjogador].anim_right.InsereSprite(imagensplayers[n]);
			jogadores[indexjogador].anim_down.InsereSprite(imagensplayers[n]);
		}
	}
	
	void Init()
	{
		//Char1
		CarregaSpritesJogadores(0);
		
		//Char2
		CarregaSpritesJogadores(1);
		
		//Char3
		CarregaSpritesJogadores(2);
		
		//Char4
		CarregaSpritesJogadores(3);
		
		controles[0] = new Controle_KeyboardMouse();
		controles[1] = new Controle_XINPUT(1);
	}
	
	bool TemOnline()
	{
		return modo_atual==CLIENT||modo_atual==SERVER;
	}
	bool TemPlayer2()
	{
		return modo_atual==COOP||TemOnline();
	}
};
ControleJogo config;

#endif
