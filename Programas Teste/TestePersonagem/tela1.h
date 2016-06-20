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
		//http://www.cplusplus.com/forum/general/17754/
		vector<ElementoGrafico *> elementos;
//		vector<ElementoGrafico> elementos0;//Não funcicona, pois, ao inserir no vector, só coleta as informações da classe-pai (gera objetos da classe-pai)
		Tela1()
		{
			elementos.clear();
		}
		void Exibir()
		{
			for(i=0;i<elementos.size();i++)
			{
				elementos[i]->Desenhar();
				outtextxy(elementos[i]->x-10,elementos[i]->y,"i");
			}
//			for(i=0;i<elementos0.size();i++)
//			{
//				elementos0[i].Desenhar();//Está chamando .Desenhar() da classe-pai, independente do que faço
//				outtextxy(elementos0[i].x-10,elementos0[i].y,"i");
//			}
		}
};

#endif
