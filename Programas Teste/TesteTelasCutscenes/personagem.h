#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include "elementografico.h"

class Personagem : public ElementoGrafico {
	public:
		 int passox;
		 int passoy;
		 Personagem()
		 {
		 	
		 }
		 void MoverX()
		 {
		 	x+=passox;
		 }
		 void MoverY()
		 {
		 	y+=passoy;
		 }
		 void Mover()
		 {
		 	MoverX();
		 	MoverY();
		 }
		 void Desenhar()
		 {
		 	
		 }
};

#endif
