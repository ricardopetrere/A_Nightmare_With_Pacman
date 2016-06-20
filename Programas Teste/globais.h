#ifndef GLOBAIS_H
#define GLOBAIS_H
#include <graphics.h>
#include <iostream>
#include <time.h>

//Variáveis globais
bool LBPressed=false;
bool ESCPressed=false;
bool LeftPressed=false;
bool RightPressed=false;
bool UpPressed=false;
bool DownPressed=false;
bool RControlPressed=false;

HWND MainWindow;
POINT P;

int paginaatual=1;

enum telas_cutscenes{
	TELA_PRINCIPAL,TELA_1,TELA_2,TELA_3,TELA_JOGO,
	CUTSCENE01
};
int telamostrando = TELA_PRINCIPAL;

//Constantes globais
#define DELAY 50
#define LARGURA_TELA 760
#define LARGURA_PAINEL 200
#define ALTURA_TELA 620

//Métodos globais
void CapturaMainWindow()
{
	MainWindow = GetForegroundWindow();
}
bool BASE_OcorreuClick(int VKey, bool &KeyPressed)
{
	GetCursorPos(&P);
	if(GetKeyState(VKey)&0x80)
	{
		KeyPressed=true;
	}
	else
	{
		if(KeyPressed)
		{
			KeyPressed=false;
			if(GetForegroundWindow()==MainWindow)
			{
				if (ScreenToClient(MainWindow, &P))
				{
					return true;
				}
			}
		}
		KeyPressed=false;
	}
	return false;
}
bool OcorreuClickLButton()
{
	return BASE_OcorreuClick(VK_LBUTTON,LBPressed);
}
bool OcorreuClickESC()
{
	return BASE_OcorreuClick(VK_ESCAPE,ESCPressed);
}
void TrocaPaginaAtiva()
{
	paginaatual=(paginaatual==1)?2:1;
	setactivepage(paginaatual);
}
void SetPaginaVisual()
{
	setvisualpage(paginaatual);
}
void ExibeTextoPlano(int x, int y, int cor, int cor_fundo, char* texto)
{
	setcolor(cor);
	int tmp_corbk=getbkcolor();
	if(cor_fundo==cor)
	{
		if(cor==BLACK)
			setcolor(WHITE);
		else
			setcolor(BLACK);
	}
	setbkcolor(cor_fundo);
	outtextxy(x,y,texto);
	setbkcolor(tmp_corbk);
}
void SetTimer(time_t &timer)
{
	time(&timer);
}
void ContaTimeout(int timeout_s,bool PulaComESC=false)
{
	time_t marcador;
	time(&marcador);
	time_t agora;
	
	while(difftime(agora,marcador)<timeout_s)
	{
		time(&agora);
		if(PulaComESC && OcorreuClickESC())
			break;
	}
}
bool CheckTimeout(time_t timer_base, int timeout_s)
{
	time_t agora;
	time(&agora);
	
	if(difftime(agora,timer_base)<timeout_s)
		return false;
	else
		return true;
}
#endif
