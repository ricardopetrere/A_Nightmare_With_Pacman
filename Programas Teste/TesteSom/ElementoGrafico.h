#ifndef ELEMENTOGRAFICO_H_
#define ELEMENTOGRAFICO_H_
#include "Globais.h"
class ElementoGrafico{
	public:
		int x,y;
		int largura,altura;
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
};
#endif
