#include <graphics.h>
#include <stdlib.h>
#include <Mmsystem.h>
#include "globais.h"
#include "botao.h"
#include "tela1.h"
#include "tela2.h"
#include "tela3.h"
//#include "objetos.h"
#include "cutscenetextoplano.h"

#define ESC 27
char tecla=0;

Botao b1;
ElementoGrafico b2;
Botao btnTela1;
Botao btnTela2;
Botao btnTela3;
Botao btnCutscene01;
Botao btnCutscene02;

Tela1 tela1;
Tela3 tela3;
CutsceneTextoPlano cut1;
//CutsceneTextoPlano cut2;

void DesenharObjetos();
void Eventos_Click();

int main()
{
	initwindow(LARGURA_TELA,ALTURA_TELA,"Teste Telas e Cutscenes",(getmaxwidth()-LARGURA_TELA)/2,(getmaxheight()-ALTURA_TELA)/2);
	CapturaMainWindow();
	
//	tela1 = Tela1();
	b1 = Botao(10,10,100,20,BLUE,"Texto 1");
//	MainWindow = GetForegroundWindow();
//	tela1.elementos.push_back(b1);
	b2 = Botao(10,100,100,20,BLUE,"Texto2");
	btnTela1 = Botao(20,300,80,20,LIGHTGRAY,"Tela 1");
	btnTela2 = Botao(120,300,80,20,LIGHTGRAY,"Tela 2");
	btnTela3 = Botao(220,300,80,20,LIGHTGRAY,"Tela 3");
	btnCutscene01 = Botao(320,300,140,20,LIGHTGRAY,"Cutscene01 com ESC");
	btnCutscene02 = Botao(320,350,140,20,LIGHTGRAY,"Cutscene01 sem ESC");
	cut1 = CutsceneTextoPlano(5000,LARGURA_TELA-1,ALTURA_TELA-50,"solitaire.jpg","Texto exemplo");
//	cut2 = CutsceneTextoPlano(5000,LARGURA_TELA-1,ALTURA_TELA-50,"solitaire.jpg","Texto exemplo");
	while(tecla!=ESC)
	{
		TrocaPaginaAtiva();
		cleardevice();
		switch(telamostrando) {
			case TELA_PRINCIPAL:
				DesenharObjetos();
				Eventos_Click();
				break;
			case TELA_1:
				tela1.Exibir();
				break;
			case TELA_2:
				ExibirTela2();
				break;
			case TELA_3:
				tela3.Exibir();
				break;
		}
		SetPaginaVisual();
		delay(DELAY);
		
	}
	closegraph();
	return 0;
}
void DesenharObjetos()
{
//	b1.Desenhar();
	b2.Desenhar();
//	btnTela1.Desenhar();//Não tem o porquê de mostrar, a classe Tela1 não é funcional no momento
//	btnTela2.Desenhar();
	btnTela3.Desenhar();
	btnCutscene01.Desenhar();
	btnCutscene02.Desenhar();
}
void Eventos_Click()
{
	if(OcorreuClickESC())
		tecla=ESC;
	if(OcorreuClickLButton())
	{
		if(btnTela2.CursorEstaEmCima())
		{
			telamostrando=TELA_2;
		}
		else if(btnTela3.CursorEstaEmCima())
		{
			telamostrando=TELA_3;
		}
		else if(btnCutscene01.CursorEstaEmCima())
		{
			cut1.PulaComESC=true;
			cut1.Desenhar();
		}
		else if(btnCutscene02.CursorEstaEmCima())
		{
			cut1.PulaComESC=false;
			cut1.Desenhar();
		}
	}
}
