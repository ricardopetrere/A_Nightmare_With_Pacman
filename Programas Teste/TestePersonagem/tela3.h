#ifndef TELA3_H
#define TELA3_H
#include "elementografico.h"
#include "botao.h"
#include <vector>
#include "telabase.h"

using namespace std;

class Tela3 : public TelaBase{
	public:
		Botao btnTelaPrincipal = Botao(300,50,100,20,WHITE,"Main");
		Botao btnTela1 = Botao(300,150,100,20,WHITE,"Tela 1");
		Botao btnTela2 = Botao(300,250,100,20,WHITE,"Tela 2");
		
		Tela3()
		{
			
		}
		void DesenharObjetos()
		{
			cleardevice();
			btnTelaPrincipal.Desenhar();
			btnTela1.Desenhar();
			btnTela2.Desenhar();
		}
		void Eventos_Click()
		{
			if(OcorreuClickLButton())
			{
				if(btnTelaPrincipal.CursorEstaEmCima())
				{
					telamostrando=TELA_PRINCIPAL;
					exibindo=false;
				}
				else if(btnTela1.CursorEstaEmCima())
				{
					telamostrando=TELA_1;
					exibindo=false;
				}
				else if(btnTela2.CursorEstaEmCima())
				{
					telamostrando=TELA_2;
					exibindo=false;
				}
			}
		}
};

#endif
