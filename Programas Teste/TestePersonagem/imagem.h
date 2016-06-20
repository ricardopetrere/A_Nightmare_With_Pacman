#ifndef IMAGEM_H
#define IMAGEM_H
#include <graphics.h>

class Imagem {
	public:
		int largura;
		int altura;
		char caminho_bitmap[50];
		int tamanho;
		void* bmp;
		Imagem()
		{
//			bmp=NULL;
		}
		static Imagem GerarBitmap(char caminho_bitmap[50],int left,int top,int right,int bottom)
		{
			Imagem retorno;
			retorno.CarregaBitmap(caminho_bitmap,left,top,right,bottom);
			return retorno;
		}
		void CarregaBitmap(char caminho_bitmap[50],int left,int top,int right,int bottom)
		{
			this->largura=right-left;
			this->altura=bottom-top;
			strcpy(this->caminho_bitmap,caminho_bitmap);
			
			readimagefile(this->caminho_bitmap,left,top,right,bottom);
			this->tamanho=imagesize(left,top,right,bottom);
			this->bmp=malloc(this->tamanho);
			getimage(left,top,right,bottom,this->bmp);
		}
		void ExibirImagem(int left, int top, int OP)
		{
			putimage(left,top,bmp,OP);
		}
};

#endif
