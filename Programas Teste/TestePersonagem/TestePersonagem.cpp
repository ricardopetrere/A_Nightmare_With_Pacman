#include <graphics.h>
#include <stdlib.h>
#include "globais.h"
#include "sprite.h"
#include "tela1.h"
#include "cutscenetextoplano.h"

int TILE_W = 20;
int TILE_H = 20;
int i;
char texto_largura[25];
char texto_altura[25];
char buf_i[4];

bool LeftPressed=false;
bool RightPressed=false;
bool UpPressed=false;
bool DownPressed=false;
bool RControlPressed=false;
bool modoDebug=false;
void Debug();

Tela1 tela1;
Botao btnTela1;
Botao b1;
Botao b2;
CutsceneTextoPlano cut1;

int main()
{
	initwindow(LARGURA_TELA,ALTURA_TELA,"TestePersonagem",(getmaxwidth()-LARGURA_TELA)/2,(getmaxheight()-ALTURA_TELA)/2);
	CapturaMainWindow();
	btnTela1 = Botao(LARGURA_TELA-150,300,100,20,LIGHTGRAY,"Tela 1");
	Sprite fundo = Sprite(0,0,LARGURA_TELA-1-200,ALTURA_TELA-1,"","115771.bmp");
	b1 = Botao(LARGURA_TELA-150,300,100,20,LIGHTGRAY,"Voltar");
	b2 = Botao(LARGURA_TELA-150,400,100,20,LIGHTGRAY,"Voltar2");
	cut1 = CutsceneTextoPlano(5000,400,400,"115771.bmp","Texto exemplo");
	
	tela1.elementos.push_back(&b1);
	tela1.elementos.push_back(&cut1);
	
	while(!OcorreuClickESC())
	{
		TrocaPaginaAtiva();
		cleardevice();
		if(telamostrando==TELA_PRINCIPAL)
		{
			fundo.Desenhar();
			if(modoDebug) Debug();
			
			btnTela1.Desenhar();
			if(OcorreuClickLButton())
			{
				if(btnTela1.CursorEstaEmCima())
				{
					telamostrando=TELA_1;
				}
			}
			if(BASE_OcorreuClick(VK_RCONTROL,RControlPressed))
			{
				modoDebug=!modoDebug;
			}
		}
		else
		{
			tela1.Exibir();
		}
		SetPaginaVisual();
		delay(DELAY);
	}
	closegraph();
	return 0;
}
void Debug()
{
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
