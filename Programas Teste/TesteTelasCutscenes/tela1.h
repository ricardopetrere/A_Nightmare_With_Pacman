#ifndef TELA1_H
#define TELA1_H
#include "elementografico.h"
#include "botao.h"
#include <vector>
//#include <list>

using namespace std;

class Tela1 {
	public:
		int i;
		vector<ElementoGrafico> elementos;
//		vector<Botao> elementos;
//		list<ElementoGrafico> elementos;
				ElementoGrafico *tmp;
		Tela1()
		{
			elementos.clear();
		}
		void Exibir()
		{
//			cleardevice();
			for(i=0;i<elementos.size();i++)
			{
				tmp = &elementos[i];
				tmp->Desenhar();
//				elementos[i].Desenhar();//Está chamando .Desenhar() da classe-pai, independente do que faço
				outtextxy(elementos[i].x-10,elementos[i].y,"i");
			}
		}
};

#endif
