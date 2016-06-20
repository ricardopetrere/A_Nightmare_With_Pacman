#ifndef ELEMENTOGRAFICO_H
#define ELEMENTOGRAFICO_H
#include "globais.h"
class ElementoGrafico{
	public:
		int x,y;
		int largura,altura;
		char texto[TAMANHO_TEXTO];
		int cor;
		int Right()
		{
			return x+largura-1;
		}
		int Bottom()
		{
			return y+altura-1;
		}
		
		bool CursorEstaEmCima()
		{
			if((mousex()>=x&&mousex()<=Right())
				&&(mousey()>=y&&mousey()<=Bottom()))
			{
				return true;
			}
			return false;
		}
		bool Clicked()
		{
			return CursorEstaEmCima()&&OcorreuClickLButton();
		}
		//Para fazer funcionar: http://www.tutorialspoint.com/cplusplus/cpp_polymorphism.htm
		virtual void Desenhar()
		{
			setcolor(GREEN);
			outtextxy(x,y,"Base Class");
		}
		
};
#endif
