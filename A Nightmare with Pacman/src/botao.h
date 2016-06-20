#ifndef BOTAO_H
#define BOTAO_H
#include <graphics.h>
#include "elementografico.h"
//#include "texto.h"

class Botao : public ElementoGrafico{
	public:
//		int cor;
//		char texto[20];
		
		Botao(){}
		
		Botao(int x, int y, int largura, int altura, int cor, char texto[TAMANHO_TEXTO])
		{
			this->x=x;
			this->y=y;
			this->largura=largura;
			this->altura=altura;
			this->cor=cor;
			strcpy(this->texto,texto);
		}
		void Desenhar()
		{
			setfillstyle(SOLID_FILL,cor);
			bar(x,y,Right(),Bottom());
			ExibeTextoPlano(x+1,y+1,BLACK,cor,texto);
		}
};
#endif
