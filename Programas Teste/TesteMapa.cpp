#include <graphics.h>
#include <stdlib.h>
#include "globais.h"
#include "sprite.h"
#include "tela1.h"
#include "botao.h"
#include "cutscenetextoplano.h"

int TILE_W = 20;
int TILE_H = 20;
int i;
char texto_largura[25];
char texto_altura[25];
char buf_i[4];

//bool LeftPressed=false;
//bool RightPressed=false;
//bool UpPressed=false;
//bool DownPressed=false;
//bool RControlPressed=false;
bool modoDebug=false;
void Debug();
Sprite fundo;

int largura=224*2;
int altura=288*2;

int main()
{
//	initwindow(LARGURA_TELA,ALTURA_TELA,"TesteMapa",(getmaxwidth()-LARGURA_TELA)/2,(getmaxheight()-ALTURA_TELA)/2);
	initwindow(largura+LARGURA_PAINEL,altura,"TesteMapa",(getmaxwidth()-(largura+LARGURA_PAINEL))/2,(getmaxheight()-altura)/2);
	CapturaMainWindow();
	Tela1 tela1;
	Botao btnTela1;
	btnTela1 = Botao(largura+50,300,100,20,LIGHTGRAY,"Tela 1");
	fundo = Sprite(0,0,largura-1,altura-1,"","Pac-man.bmp");
//	fundo = Sprite(0,0,511,511,"","pacman_layout.JPG");
//	fundo = Sprite(0,0,625,767,"","QjFCmHybgwQ.bmp");
//	Sprite fundo = Sprite(0,0,LARGURA_TELA-1-200,ALTURA_TELA-1,"","115771.bmp");
	
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
			tela1.Exibir(TELA_PRINCIPAL);
//			telamostrando=TELA_PRINCIPAL;
		}
		SetPaginaVisual();
		delay(DELAY);
	}
	closegraph();
	return 0;
}
void Debug()
{
	setcolor(GREEN);
	strcpy(texto_largura,"Largura: ");
	strcpy(texto_altura,"Altura: ");
	for(i=1;i*TILE_W<=largura;i++)
	{
		line(i*TILE_W,0,i*TILE_W,altura);//Linhas verticais
	}
	itoa(TILE_W*(i-1),buf_i,10);
	strcat(texto_largura,buf_i);
	outtextxy(largura+10,20,texto_largura);
	outtextxy(largura+10,40,"# Tiles: ");
	outtextxy(largura+70,40,itoa(i-1,buf_i,10));
	outtextxy(largura+10,60,"TILE_W: ");
	outtextxy(largura+70,60,itoa(TILE_W,buf_i,10));
	
	for(i=1;i*TILE_H<=altura;i++)
	{
		line(0,i*TILE_H,largura,i*TILE_H);//Linhas horizontais
	}
	itoa(TILE_H*(i-1),buf_i,10);
	strcat(texto_altura,buf_i);
	outtextxy(largura+10,80,texto_altura);
	outtextxy(largura+10,100,"# Tiles: ");
	outtextxy(largura+70,100,itoa(i-1,buf_i,10));
	outtextxy(largura+10,120,"TILE_H: ");
	outtextxy(largura+70,120,itoa(TILE_H,buf_i,10));
	
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
			if(TILE_W>=largura/2) TILE_W=largura/2;
		}
		if(BASE_OcorreuClick(VK_UP,UpPressed))
		{
			TILE_H--;
			if(TILE_H<=0) TILE_H=1;
		}
		if(BASE_OcorreuClick(VK_DOWN,DownPressed))
		{
			TILE_H++;
			if(TILE_H>=altura/2) TILE_H=altura/2;
		}
	}
	else
	{
		if(BASE_OcorreuClick(VK_LEFT,LeftPressed))
		{
			fundo.x--;
		}
		if(BASE_OcorreuClick(VK_RIGHT,RightPressed))
		{
			fundo.x++;
		}
		if(BASE_OcorreuClick(VK_UP,UpPressed))
		{
			fundo.y--;
		}
		if(BASE_OcorreuClick(VK_DOWN,DownPressed))
		{
			fundo.y++;
		}
	}
}
