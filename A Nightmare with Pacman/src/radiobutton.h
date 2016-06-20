#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H
#include "elementografico.h"

class RadioButton:public ElementoGrafico {
	public:
//		int cor;
		bool Checked=false;
		int raioCheck=0;
//		char texto[20];
		RadioButton()
		{
		}
		RadioButton(int x, int y, int raioCheck, char texto[TAMANHO_TEXTO], int cor)
		{
			this->x=x;
			this->y=y;
			this->raioCheck=raioCheck;
			Checked=false;
			strcpy(this->texto,texto);
			this->cor=cor;
			largura=2*raioCheck;
			altura=2*raioCheck;
		}
		void Desenhar()
		{
			setfillstyle(SOLID_FILL,LIGHTGRAY);
			setcolor(BLACK);
			fillellipse(x+raioCheck,y+raioCheck,raioCheck,raioCheck);
			if(Checked)
			{
				setfillstyle(SOLID_FILL,BLACK);
				fillellipse(x+raioCheck,y+raioCheck,raioCheck-5,raioCheck-5);
			}
			ExibeTextoPlano(x+2*raioCheck+1,y+1,cor,getbkcolor(),texto);
		}
};

#endif
