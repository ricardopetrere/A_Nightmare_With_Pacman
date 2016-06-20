#ifndef SPRITE_H
#define SPRITE_H
#include <graphics.h>
#include "globais.h"

class Sprite{
	public:
		void* bmp;
		void* mask;
		
		Sprite()
		{
		}
		static void* GeraBitmap(int left, int top, int right, int bottom)
		{
			void* retorno=0x0;
			int tamanho;
			tamanho=imagesize(left,top,right,bottom);
			retorno=malloc(tamanho);
			getimage(left,top,right,bottom,retorno);
			return retorno;
		}
		Sprite(int left_mask, int top_mask, int right_mask, int bottom_mask
				, int left_bmp, int top_bmp, int right_bmp, int bottom_bmp)
		{
			mask=Sprite::GeraBitmap(left_mask,top_mask,right_mask,bottom_mask);
			bmp=Sprite::GeraBitmap(left_bmp,top_bmp,right_bmp,bottom_bmp);
		}
		Sprite(int x0_mask, int y0_mask, int x0_bmp, int y0_bmp, int tiles8=2)
		{
			int right_mask = x0_mask+(tiles8*TAMANHO_CELULA)-1;
			int bottom_mask = y0_mask+(tiles8*TAMANHO_CELULA)-1;
			int right_bmp = x0_bmp+(tiles8*TAMANHO_CELULA)-1;
			int bottom_bmp = y0_bmp+(tiles8*TAMANHO_CELULA)-1;
			mask=Sprite::GeraBitmap(x0_mask,y0_mask,right_mask,bottom_mask);
			bmp=Sprite::GeraBitmap(x0_bmp,y0_bmp,right_bmp,bottom_bmp);
		}
		Sprite(int x0, int y0, int tiles8=2)
			:Sprite(x0,y0,x0+LARGURA_FUNDO,y0,tiles8)
		{
		}
		void Desenhar(int p_x, int p_y)//Pra poder desenhar em um lugar diferente da localização original do sprite
		{
			if(mask==NULL)
			{
				putimage(p_x,p_y,bmp,COPY_PUT);
			}
			else
			{
				putimage(p_x,p_y,mask,AND_PUT);
				putimage(p_x,p_y,bmp,OR_PUT);
			}
		}
};

#endif
