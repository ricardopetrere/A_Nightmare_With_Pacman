#ifndef SOMETHING_H
#define SOMETHING_H
#include "elementografico.h"

enum Modos_Texto{
	PLANO,LETRA_A_LETRA,PARAGRAFO
};



class Texto:public ElementoGrafico{
	public:
		int delay_letras=0;
		Modos_Texto modo;
		Texto(){}
		Texto(char texto[TAMANHO_TEXTO], int x, int y, int cor, int largura_caixatexto,int altura_caixatexto, Modos_Texto modo,int delay_letras=100)
		{
			strcpy(this->texto,texto);
			this->x=x;
			this->y=y;
			this->cor=cor;
			this->largura=largura_caixatexto;
			this->altura=altura_caixatexto;
			this->modo=modo;
			this->delay_letras=delay_letras;
		}
		Texto(char texto[TAMANHO_TEXTO], int x, int y, int cor)
		{
			strcpy(this->texto,texto);
			this->x=x;
			this->y=y;
			this->cor=cor;
			this->largura=0;
			this->altura=0;
			this->modo=PLANO;
			this->delay_letras=0;
		}
		void DesenharLetra(int c_x, int c_y, char c)
		{
			setcolor(cor);
			int tmp_corbk=getbkcolor();
			setbkcolor(tmp_corbk);
			outtextxy(c_x,c_y,ConvertChar(c));
			setbkcolor(tmp_corbk);
			while(!CheckTimeout(clock(),delay_letras));
		}
		void DesenharPalavra(int p_x, int p_y, char* palavra)
		{
//			char* tmp_p;
//			strcpy(tmp_p,palavra);
			int tmp_x=p_x;
			for(int i=0;palavra[i]!='\0';i++)
			{
				DesenharLetra(tmp_x,p_y,palavra[i]);
				tmp_x+=PASSOX_LETRA;
			}
		}
		void PularLinha(int &_x, int &_y)
		{
			_y+=PASSOY_LETRA;
			_x=x;
		}
		void Desenhar()
		{
			if(strcmp(texto,"")!=0)
			{
				switch(modo)
				{
					case PLANO:
						ExibeTextoPlano(x,y,cor,getbkcolor(),texto);
						break;
					case LETRA_A_LETRA:
						SetPaginaVisual();
						DesenharPalavra(x,y,texto);
						break;
					case PARAGRAFO:
						SetPaginaVisual();
						char buffer[TAMANHO_TEXTO];
						strcpy(buffer,"");
						int i;
						char c;
						int tmp_x=x;
						int tmp_y=y;
						while(c != '\0')
						{
							if(c=='\n')
							{
								PularLinha(tmp_x,tmp_y);
							}
							else if(c==' ')
							{
								if(tmp_x+PASSOX_LETRA>largura)
								{
									PularLinha(tmp_x,tmp_y);
								}
								DesenharPalavra(tmp_x,tmp_y,buffer);
								strcpy(buffer,"");
							}
							else
							{
								strcat(buffer,ConvertChar(c));
							}
						}
				}
			}
		}
};

#endif
