#ifndef TELAJOGO_H
#define TELAJOGO_H
#include "telabase.h"
#include "sprite.h"
#include "tela1.h"

class TelaJogo:public TelaBase {
	public:
		Tela1 tela1;
		Sprite fundo;
		bool modoDebug=false;
		TelaJogo(int delay)
			:TelaBase(delay)
		{
		}
		TelaJogo()
			:TelaJogo(DELAY)
		{
		}
		void InitializeComponents()
		{
			fundo = Sprite(0,0,LARGURA_TELA-LARGURA_PAINEL-1,ALTURA_TELA-1,"","115771.bmp");
			elementos.push_back(&fundo);
		}
		void Loop()
		{
		}
		void Eventos_Click()
		{
			if(OcorreuClickLButton())
			{
			}
			if(BASE_OcorreuClick(VK_RCONTROL,RControlPressed))
			{
				modoDebug=!modoDebug;
			}
		}
		void OnClosed()
		{
		}
		
		
void Debug()
{
	int TILE_W=20,TILE_H=20;
	int i;
	char texto_largura[25];
	char texto_altura[25];
	char buf_i[4];
	strcpy(texto_largura,"Largura: ");
	strcpy(texto_altura,"Altura: ");
	setcolor(GREEN);
	for(i=0;i*TILE_W<=LARGURA_TELA-200;i++)
	{
		line(i*TILE_W,0,i*TILE_W,ALTURA_TELA);//Linhas verticais
	}
	itoa(TILE_W,buf_i,10);
	strcat(texto_largura,buf_i);
	outtextxy(LARGURA_TELA-190,20,texto_largura);
	outtextxy(LARGURA_TELA-190,40,"# Tiles: ");
	outtextxy(LARGURA_TELA-130,40,itoa(i-1,buf_i,10));
	
	for(i=0;i*TILE_H<=ALTURA_TELA;i++)
	{
		line(0,i*TILE_H,LARGURA_TELA-200,i*TILE_H);//Linhas horizontais
	}
	itoa(TILE_H,buf_i,10);
	strcat(texto_altura,buf_i);
	outtextxy(LARGURA_TELA-190,80,texto_altura);
	outtextxy(LARGURA_TELA-190,100,"# Tiles: ");
	outtextxy(LARGURA_TELA-130,100,itoa(i-1,buf_i,10));
	
	if(GetKeyState(VK_LCONTROL)&0x80)
	{
		if(BASE_OcorreuClick(VK_LEFT,LeftPressed))
		{
			TILE_W--;
			if(TILE_W<=0) TILE_W=1;
		}
		if(BASE_OcorreuClick(VK_RIGHT,RightPressed))
		{
			TILE_W++;
			if(TILE_W>=LARGURA_TELA/2) TILE_W=LARGURA_TELA/2;
		}
		if(BASE_OcorreuClick(VK_UP,UpPressed))
		{
			TILE_H--;
			if(TILE_H<=0) TILE_H=1;
		}
		if(BASE_OcorreuClick(VK_DOWN,DownPressed))
		{
			TILE_H++;
			if(TILE_H>=ALTURA_TELA/2) TILE_H=ALTURA_TELA/2;
		}
	}
}
};

#endif
