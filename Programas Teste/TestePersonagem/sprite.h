#ifndef SPRITE_H
#define SPRITE_H
#include "elementografico.h"
#include "imagem.h"

class Sprite: public ElementoGrafico {
	public:
		Imagem bitmap;
		Imagem mask;
		Sprite()
		{
			
		}
		Sprite(int left,int top, int right, int bottom, char caminhomascara[50], char caminhobitmap[50])
		{
			x=left;
			y=top;
			largura=right-left+1;
			altura=bottom-top+1;
			CarregaBitmaps(left,top,right,bottom,caminhomascara,caminhobitmap);
		}
		void CarregaBitmaps(int left,int top, int right, int bottom, char caminhomascara[50], char caminhobitmap[50])
		{
			if(strcmp(caminhomascara,"")!=0)
			{
				this->mask.CarregaBitmap(caminhomascara,left,top,right,bottom);
			}
			this->bitmap.CarregaBitmap(caminhobitmap,left,top,right,bottom);
		}
		void Desenhar()
		{
			if(this->mask.bmp==NULL)
			{
				this->bitmap.ExibirImagem(x,y,COPY_PUT);
			}
			else
			{
				this->mask.ExibirImagem(x,y,AND_PUT);
				this->bitmap.ExibirImagem(x,y,OR_PUT);
			}
		}
};

#endif
