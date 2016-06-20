#ifndef BOTAO_H
#define BOTAO_H
#include <graphics.h>
#include "globais.h"
#include "elementografico.h"

class Botao : public ElementoGrafico{
	public:
		int cor;
		char texto[20];
		
		Botao(){}
		
		Botao(int x, int y, int largura, int altura, int cor, char texto[20])
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
//			if(cor==BLACK)
//			{
//				setcolor(WHITE);
//			}
//			else
//			{
//				setcolor(BLACK);
//			}
			int tmp_corbk=getbkcolor();
			setbkcolor(cor);
			outtextxy(x+1,y+1,texto);
			setbkcolor(tmp_corbk);
		}
};
#endif
