#include <graphics.h>
#include <stdlib.h>
#include <Mmsystem.h>
//#include "Globais.h"
#include "Botao.h"

#define ESC 27
char tecla=0;
int largura=500;
int altura=500;
int pg=1;
//bool teclapressionada=false;

//POINT P;
//HWND hwnd;
Botao b1(100,100,80,20,LIGHTGRAY,"cartoon001.wav");
Botao b2(200,200,80,20,WHITE,"background001.wav");

int main()
{
	initwindow(largura,altura,"TesteSom",(getmaxwidth()-largura)/2,(getmaxheight()-altura)/2);
	MainWindow = GetForegroundWindow();
	setbkcolor(LIGHTGREEN);
	while(tecla!=ESC)
	{
		pg=(pg==1)?2:1;
		setactivepage(pg);
		
		cleardevice();
		b1.Desenhar();
		b2.Desenhar();
		GetCursorPos(&P);
		if(OcorreuClickESC())
			tecla=ESC;
		if(OcorreuClickLButton())
		{
			if(b1.CursorEstaEmCima())
			{
				PlaySound("cartoon001.wav",NULL,SND_ASYNC);
			}
			else if(b2.CursorEstaEmCima())
			{
				PlaySound("background001.wav",NULL,SND_ASYNC);
			}
		}
		
		
		
		setvisualpage(pg);
//		if(kbhit())
//			tecla=getch();
		delay(50);
	}
	closegraph();
	return 0;
}
