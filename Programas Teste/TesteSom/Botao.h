#ifndef BOTAO_H_
#define BOTAO_H_
#include <graphics.h>
#include "Globais.h"
#include "ElementoGrafico.h"

class Botao : public ElementoGrafico{
	public:
		int cor;
		char texto[20];
	
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
			if(cor==BLACK)
			{
				setcolor(WHITE);
			}
			else
			{
				setcolor(BLACK);
			}
			int tmp_corbk=getbkcolor();
			setbkcolor(cor);
			outtextxy(x+1,y+1,texto);
			setbkcolor(tmp_corbk);
		}
};
#endif
