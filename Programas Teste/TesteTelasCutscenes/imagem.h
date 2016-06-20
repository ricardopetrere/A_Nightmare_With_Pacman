#ifndef IMAGEM_H
#define IMAGEM_H
#include <graphics.h>

//struct TImagem{
//	int largura;
//	int altura;
//	int tamanho;
//	void *bmp;
//	char caminho[50];
//	
//	void GeraTImagem(int largura,int altura, char caminho[50])
//	{
//		this->largura=largura;
//		this->altura=altura;
//		strcpy(this->caminho,caminho);
//		readimagefile(this->caminho,0,0,this->largura,this->altura);
//		this->tamanho=imagesize(0,0,this->largura,this->altura);
//		this->bmp=malloc(this->tamanho);
//		getimage(0,0,this->largura,this->altura,this->bmp);
//	}
//};

class Imagem {
	public:
		int largura;
		int altura;
		char caminho_bitmap[50];
		int tamanho;
		void* bmp;
		Imagem()
		{
			
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
};

#endif
