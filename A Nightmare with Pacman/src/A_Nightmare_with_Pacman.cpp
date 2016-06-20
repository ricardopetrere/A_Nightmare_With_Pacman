#include "telainicial.h"
#include "telamenu.h"
#include "telaprejogo.h"
#include "telaprejogo2.h"
#include "telajogo.h"
#include "telaendgame.h"
#include "telacreditos.h"
using namespace std;

TelaInicial title = TelaInicial(DELAY60FPS);
TelaMenu menu = TelaMenu(DELAY60FPS);
TelaPreJogo prejogo = TelaPreJogo(DELAY60FPS);
TelaPreJogo2 prejogo2 = TelaPreJogo2(DELAY60FPS);
TelaJogo jogo = TelaJogo(DELAY60FPS);
TelaEndGame endgame = TelaEndGame(DELAY60FPS);
TelaCreditos creditos = TelaCreditos(DELAY60FPS);
int main()
{
	InicializacaoPrograma();
	CarregarResources();
	config.Init();
	//Splash
	while(!config.sair)
	{
		switch(telamostrando){
			case TELA_INICIAL:
				title.Exibir();
				break;
			case TELA_MENU:
	//			menu.Exibir(TELA_INICIAL);
				break;
			case TELA_PREJOGO:
				prejogo.Exibir();
				break;
			case TELA_PREJOGO2:
				prejogo2.Exibir();
				break;
			case TELA_JOGO:
				//Escolher personagem e se vai ser cliente ou servidor
				jogo.Exibir();
				break;
			case TELA_ENDGAME:
				break;
			case TELA_CREDITOS:
				creditos.Exibir();
				//Exibir créditos
				break;
		}
	}
	TerminoPrograma();
	return 0;
}
