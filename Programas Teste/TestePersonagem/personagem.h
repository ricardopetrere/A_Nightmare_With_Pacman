#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include "elementografico.h"
#include "sprite.h"
#include <vector>

class Personagem : public ElementoGrafico {
	public:
		 int passox;
		 int passoy;
		 vector<Sprite> sprites;
		 Personagem()
		 {
		 	sprites.clear();
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
		 	Desenhar(0);
		 }
		 void Desenhar(int spriteid)
		 {
		 	if(spriteid>=0&&spriteid<sprites.size())
		 		sprites[spriteid].Desenhar();
		 }
};

#endif
