#ifndef GLOBAIS_H
#define GLOBAIS_H
#include <graphics.h>
#include <iostream>
#include <time.h>
#include <math.h>

#include "rede.h"
Rede comm;

#define DELAY 					(50)
#define DELAY60FPS				((int)(1000/60))
#define LARGURA_PAINELDIREITA 	(240)
#define COLUNAS_MAPA 			(28)
#define LINHAS_MAPA 			(31)
#define LINHAS_PAINELSUPERIOR 	(2)
#define LINHAS_PAINELINFERIOR 	(2)
#define PROPORCAO_FUNDO 		(2)
#define TAMANHO_CELULA 			((int)(8*PROPORCAO_FUNDO))
#define MEIA_CELULA 			(TAMANHO_CELULA/2)
#define LARGURA_FUNDO 			(COLUNAS_MAPA*TAMANHO_CELULA)
#define ALTURA_FUNDO 			(LINHAS_MAPA*TAMANHO_CELULA)
#define ALTURA_PAINELSUPERIOR 	(LINHAS_PAINELSUPERIOR*TAMANHO_CELULA)
#define ALTURA_PAINELINFERIOR 	(LINHAS_PAINELINFERIOR*TAMANHO_CELULA)
#define ALTURA_TELA 			(ALTURA_PAINELSUPERIOR+ALTURA_FUNDO+ALTURA_PAINELINFERIOR)
#define LARGURA_TELA 			(LARGURA_FUNDO+LARGURA_PAINELDIREITA)
#define LARGURA_VIRUTALSCREEN	(GetSystemMetrics(SM_CXVIRTUALSCREEN))
#define ALTURA_VIRUTALSCREEN	(GetSystemMetrics(SM_CYVIRTUALSCREEN))
#define LARGURA_SCREEN			(GetSystemMetrics(SM_CXSCREEN)/2)
#define ALTURA_SCREEN			(GetSystemMetrics(SM_CYSCREEN)/2)
#define LARGURA_MONITOR			(getmaxwidth())
#define ALTURA_MONITOR			(getmaxheight())
#define CENTROX_MONITOR			(getmaxwidth()/2)
#define CENTROY_MONITOR			(getmaxheight()/2)
#define X_TELANOCENTRO			((LARGURA_MONITOR-LARGURA_TELA)/2)
#define Y_TELANOCENTRO			((ALTURA_MONITOR-ALTURA_TELA)/2)
#define CENTROX_TELA 			((LARGURA_TELA)/2)
#define CENTROY_TELA 			((ALTURA_TELA)/2)
#define TITULO_TELA 			("A Nightmare with Pacman")
#define TAMANHO_CAMINHO 		(50)
#define TAMANHO_TEXTO 			(200)
#define PASSOX_LETRA 			(10)
#define PASSOY_LETRA 			(20)
#define TAM_BUF_INT				(10)

int Pixels(int px)
{
	return px*PROPORCAO_FUNDO;
}
int Tiles8(double qtd)
{
	return qtd*Pixels(8);
}
int Tiles8(int qtd)
{
	return qtd*Pixels(8);
}
int Tiles(double qtd)
{
	return Tiles8(qtd)*2;
}
int Tiles(int qtd)
{
	return Tiles8(qtd)*2;
}

//Gerenciamento de qual tela deve mostrar
enum telas_cutscenes{
	TELA_INICIAL,TELA_MENU,TELA_PREJOGO,TELA_PREJOGO2,TELA_JOGO,TELA_ENDGAME,TELA_CREDITOS
};
telas_cutscenes telamostrando = TELA_INICIAL;

//-------------Tela do programa
HWND MainWindow;
HWND ConsoleWindow;
void CapturaMainWindow()
{
	MainWindow = GetForegroundWindow();
	ConsoleWindow = GetConsoleWindow();
	ShowWindow(ConsoleWindow,SW_HIDE);
}
void VerificaUI()//fail-safe
{
	if(MainWindow==NULL)
	{
		initwindow(LARGURA_TELA,ALTURA_TELA,TITULO_TELA,X_TELANOCENTRO,Y_TELANOCENTRO);
		CapturaMainWindow();
	}
}
void EscreveEmConsole(char s[50])
{
	std::cout<<s<<std::endl;
}
void EscreveEmConsole(bool b)
{
	std::cout<<b<<std::endl;
}
void EscreveEmConsole(int i)
{
	std::cout<<i<<std::endl;
}
//----------------Inicialização e término do programa
void InicializacaoPrograma()
{
	srand(time(NULL));
	VerificaUI();
	comm.WinSockInit();
	comm.FlagsInit();
}
void TerminoPrograma()
{
	comm.FechaConexaoClient();
	comm.EncerraWinSock();
	MainWindow=NULL;
	ShowWindow(ConsoleWindow,SW_RESTORE);
	ConsoleWindow=NULL;
	closegraph();
}
//-------------Eventos de entrada do usuário (teclado e mouse)
POINT P;
bool LBPressed=false;
bool RBPressed=false;
bool ESCPressed=false;
bool LeftPressed=false;
bool RightPressed=false;
bool UpPressed=false;
bool DownPressed=false;
bool RControlPressed=false;
bool BASE_OcorreuKeyDown(int VKey)
{
	if(GetKeyState(VKey)&0x80)
	{
		if(GetForegroundWindow()==MainWindow)//&&mousey()>=0)
			return true;
	}
	return false;
}
bool BASE_OcorreuKeyDown(int VKey, bool &KeyPressed)
{
	GetCursorPos(&P);
	ScreenToClient(MainWindow, &P);
	if(BASE_OcorreuKeyDown(VKey))
	{
		KeyPressed=true;
		if(GetForegroundWindow()==MainWindow)//&&mousey()>=0)
			return true;
	}
	return false;
}
bool BASE_OcorreuClick(int VKey, bool &KeyPressed)
{
	if(!BASE_OcorreuKeyDown(VKey,KeyPressed))
	{
		if(KeyPressed)
		{
			KeyPressed=false;
			if(GetForegroundWindow()==MainWindow)//&&mousey()>=0)
				return true;
		}
		KeyPressed=false;
	}
	return false;
}
bool OcorreuClickLButton()
{
	return BASE_OcorreuClick(VK_LBUTTON,LBPressed);
}
bool OcorreuClickRButton()
{
	return BASE_OcorreuClick(VK_RBUTTON,RBPressed);
}
bool OcorreuClickESC()
{
	return BASE_OcorreuClick(VK_ESCAPE,ESCPressed);
}
bool DownKey_KeyDown()
{
	return BASE_OcorreuKeyDown(VK_DOWN);
}
bool UpKey_KeyDown()
{
	return BASE_OcorreuKeyDown(VK_UP);
}
bool LeftKey_KeyDown()
{
	return BASE_OcorreuKeyDown(VK_LEFT);
}
bool RightKey_KeyDown()
{
	return BASE_OcorreuKeyDown(VK_RIGHT);
}
bool CharIsNumber(char tecla)
{
	return (tecla>='0'&&tecla<='9');
}
bool PressionouNumeroBackspaceOuPonto(char &tecla)
{
	tecla=getch();
	if(CharIsNumber(tecla)||(tecla=='.')||tecla==VK_BACK)
		return true;
}
//------------Páginas
int paginaatual=1;
void TrocaPaginaAtiva()
{
	paginaatual=(paginaatual==1)?2:1;
	setactivepage(paginaatual);
}
void SetPaginaVisual()
{
	setvisualpage(paginaatual);
}
//----------------Exibir texto plano
void ExibeTextoPlano(int x, int y, int cor, int cor_fundo, char* texto)
{
	if(strcmp(texto,"")!=0)
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
}
//---------------time.h
class Timer{
	public:
		clock_t timer;
		int timeout_ms;
		int tmp_passedtime;
		bool ativo;
		int qtd_execucoes;
		Timer(){
			timeout_ms=0;
			tmp_passedtime=0;
			ativo=false;
			qtd_execucoes=0;
		}
		Timer(int timeout_ms, bool start=false)
			:Timer()
		{
			this->timeout_ms=timeout_ms;
			if(start)
				Start();
		}
		int TargetTime()
		{
			return timer+timeout_ms*CLOCKS_PER_SEC/1000;
		}
		bool CheckTimeout()
		{
			if(ativo)
			{
				if(timeout_ms<0)
				{
					return false;
				}
				if(clock()>=TargetTime())
				{
					ativo=false;
					qtd_execucoes++;
					return true;
				}
				else
					return false;
			}
			else
				return true;
		}
		int TimePassed()
		{
			return clock()-timer;
		}
		int TimeRemaining()
		{
			return TargetTime()-clock();
		}
		void Pause()
		{
			if(ativo)
			{
				tmp_passedtime=TimePassed();
				ativo=false;
			}
		}
		void Resume()
		{
			if(!ativo)
			{
				timer=clock()-tmp_passedtime;
				tmp_passedtime=0;
				ativo=true;
			}
		}
		bool isPaused()
		{
			return !ativo&&tmp_passedtime>0;
		}
		void Start(bool RunOnce=false)
		{
			if(RunOnce&&qtd_execucoes>0)
			{
			}
			else
			{
				tmp_passedtime=0;
				timer = clock();
				ativo=true;
			}
		}
		void Stop()
		{
			tmp_passedtime=0;
			ativo=false;
			qtd_execucoes++;
		}
};
bool CheckTimeout(clock_t timer_start,int millis)
{
	clock_t timer_end=timer_start+millis*CLOCKS_PER_SEC/1000;
//	std::cout<<"Timer: "<<timer_end-clock()<<std::endl;
	return (clock()>=timer_end);
}
bool CheckTimeout(Timer t)
{
	return CheckTimeout(t.timer,t.timeout_ms);
}
void Delay_Ms(int millis)
{
	clock_t timer=clock();
	while(timer+millis*CLOCKS_PER_SEC/1000>clock());
}
//Cálculo de distância entre pontos
double CalculaDistanciaReta(int x0, int y0, int x1, int y1)
{
	double d;
	d=sqrt(pow(x1-x0,2)+pow(y1-y0,2));
	return d;
}
//---------------Conversões
char* ConvertChar(char caractere)
{
	char temp[2];
	temp[0] = caractere;
	temp[1] = '\0';
	return temp;
}
char* ConvertInt(int i)
{
	char temp[TAM_BUF_INT];
	strcpy(temp,"");
	itoa(i,temp,10);
	return temp;
}
char* MontaMensagemChar(char *s1)
{
	char mensagem[50];
	strcpy(mensagem,s1);
	strcat(mensagem,"|");
	return mensagem;
}
char* MontaMensagemCharInt(char *s1,int i1)
{
	char mensagem[50];
	strcpy(mensagem,MontaMensagemChar(s1));
	char temp[2];
	strcat(mensagem,ConvertInt(i1));
	strcat(mensagem,"|");
	return mensagem;
}
//------Modo Debug
bool Debug=false;
#endif
