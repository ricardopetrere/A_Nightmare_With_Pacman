#ifndef TELAINICIAL_H
#define TELAINICIAL_H
#include "telabase.h"

class TelaInicial:public TelaBase {
	public:
		Botao btnJogar;
//		Botao btnMenu;
		Botao btnCreditos;
		TelaInicial(int delay)
			:TelaBase(delay)
		{
		}
		TelaInicial()
			:TelaInicial(DELAY)
		{
		}
		void InitializeComponents()
		{
			setbkcolor(COLOR(20,0,50));
			btnJogar = Botao(LARGURA_FUNDO/3,100,LARGURA_FUNDO/3,100,LIGHTBLUE,"Jogar");
			btnCreditos = Botao(LARGURA_FUNDO/3,300,LARGURA_FUNDO/3,100,LIGHTBLUE,"Créditos");
		}
		void Loop()
		{
		}
		void DesenharObjetos()
		{
			btnJogar.Desenhar();
			btnCreditos.Desenhar();
		}
		void Eventos_Click()
		{
			if(OcorreuClickLButton())
			{
				if(btnJogar.CursorEstaEmCima())
				{
					telamostrando=TELA_PREJOGO;
					exibindo=false;
				}
				else if(btnCreditos.CursorEstaEmCima())
				{
					telamostrando=TELA_CREDITOS;
					exibindo=false;
				}
			}
			if(OcorreuClickESC())
			{
				exibindo=false;
				config.sair=true;
			}
		}
		void OnClosed()
		{
		}
};

#endif
