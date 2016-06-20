#ifndef ELEMENTOGRAFICO_H
#define ELEMENTOGRAFICO_H
#include "globais.h"
class ElementoGrafico{
	public:
		int x=0,y=0;
		int largura=0,altura=0;
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
			if((P.x>=x&&P.x<=Right())
				&&(P.y>=y&&P.y<=Bottom()))
			{
				return true;
			}
			return false;
		}
		//Para fazer funcionar: http://www.tutorialspoint.com/cplusplus/cpp_polymorphism.htm
		virtual void Desenhar()
		{
			setcolor(GREEN);
			outtextxy(x,y,"Base Class");
		}
		
};
#endif
