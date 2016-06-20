#include <graphics.h>
#include <stdlib.h>
#include "globais.h"
#include "telajogo.h"

int main()
{
	initwindow(LARGURA_TELA,ALTURA_TELA,"TestePersonagem",(getmaxwidth()-LARGURA_TELA)/2,(getmaxheight()-ALTURA_TELA)/2);
	CapturaMainWindow();
	TelaJogo jogo;
	telamostrando=TELA_JOGO;
	while(!OcorreuClickESC())
	{
		switch(telamostrando)
		{
			case TELA_JOGO:
				jogo.Exibir();
				break;
		}
	}
	closegraph();
	return 0;
}
