#ifndef MAPA_H
#define MAPA_H
#include "globais.h"

#define char_parede 'X'
#define char_vazio '0'
#define char_interseccao '?'	//Só vai ser necessário realizar alguma lógica de verdade na IA quando chegar em intersecções. Até então, o personagem vai seguir o único caminho possível. É assim no jogo original
#define char_pellet 'P'
#define char_bit 'B'
class Mapa {
	public:
		static int x0;
		static int y0;
		int pontos=0;
		int pellets=0;
		static const char matriz_base[LINHAS_MAPA][COLUNAS_MAPA];
		char matriz[LINHAS_MAPA][COLUNAS_MAPA];
		void ZeraMapa()
		{
			//http://stackoverflow.com/a/16047752
			memcpy(matriz,matriz_base,sizeof(matriz_base));
			pontos=0;
			pellets=0;
		}
		void ResetarPellets()
		{
			pellets=0;

			if(matriz[3][1]==char_bit)
				pontos--;
			matriz[3][1] = char_pellet;
			pellets++;

			if(matriz[3][26]==char_bit)
				pontos--;
			matriz[3][26] = char_pellet;
			pellets++;
			
			if(matriz[23][1]==char_bit)
				pontos--;
			matriz[23][1] = char_pellet;
			pellets++;
			
			if(matriz[23][26]==char_bit)
				pontos--;
			matriz[23][26] = char_pellet;
			pellets++;
		}
		void Init()
		{
			//http://stackoverflow.com/a/16047752
			ZeraMapa();
			int MAX_J = COLUNAS_MAPA/2;
			for(int i=0;i<LINHAS_MAPA;i++)
			{
				for(int j=0;j<MAX_J;j++)
				{
					if(
						(matriz[i][j]!=char_parede)
						&&
						(i<9||i>19||j==6)
					)//Pac-bits
					{
						if(i==23&&j==13)//posição do pac-man
						{
							
						}
						else
						{
							matriz[i][j]=char_bit;
							matriz[i][COLUNAS_MAPA-1-j]=char_bit;
							pontos+=2;
						}
					}
				}
			}
			//Pellets
			ResetarPellets();
		}
		void InitMapaColisao()
		{
			ZeraMapa();
			int MAX_J = COLUNAS_MAPA/2;
			int celulas_vazias=0;
			for(int i=0;i<LINHAS_MAPA;i++)
			{
				for(int j=0;j<MAX_J;j++)
				{
					if(matriz[i][j]==char_parede)
						continue;
					
					celulas_vazias=0;
					if(matriz[i-1][j]!=char_parede)
						celulas_vazias++;
					if(matriz[i][j-1]!=char_parede)
						celulas_vazias++;
					if(matriz[i][j+1]!=char_parede)
						celulas_vazias++;
					if(matriz[i+1][j]!=char_parede)
						celulas_vazias++;
					if(celulas_vazias>2)
					{
						matriz[i][j]=char_interseccao;
						matriz[i][COLUNAS_MAPA-1-j]=char_interseccao;
					}
				}
			}
		}
		char Posicao(int x_matriz,int y_matriz)
		{
			return matriz[y_matriz][x_matriz];
		}
		void SetPosicao(int x_matriz, int y_matriz, char valor)
		{
			matriz[y_matriz][x_matriz] = valor;
		}
		static int X_MATRIZ(int p_x)
		{
			return (p_x-Mapa::x0)/TAMANHO_CELULA;
		}
		static int Y_MATRIZ(int p_y)
		{
			return (p_y-Mapa::y0)/TAMANHO_CELULA;
		}
		static int X_TELA(int x_matriz)
		{
			return (x_matriz*TAMANHO_CELULA)+Mapa::x0;
		}
		static int Y_TELA(int y_matriz)
		{
			return (y_matriz*TAMANHO_CELULA)+Mapa::y0;
		}
		static bool EstaNaGhostHouse(int x_matriz, int y_matriz)
		{
			return x_matriz>9&&x_matriz<18
				&&y_matriz>11&&y_matriz<17;
		}
		bool HaPelletMaisProximo(int p_x, int p_y, int* x_saida, int* y_saida)
		{
			bool retorno=false;
			double d_1=999;
			double d_2=999;
			double d_3=999;
			double d_4=999;
			if(matriz[3][1]==char_pellet)
			{
				d_1=CalculaDistanciaReta(p_x,p_y,Mapa::X_TELA(1),Mapa::Y_TELA(3));
				retorno=true;
			}
			if(matriz[3][26]==char_pellet)
			{
				d_2=CalculaDistanciaReta(p_x,p_y,Mapa::X_TELA(26),Mapa::Y_TELA(3));
				retorno=true;
			}
			if(matriz[23][1]==char_pellet)
			{
				d_3=CalculaDistanciaReta(p_x,p_y,Mapa::X_TELA(1),Mapa::Y_TELA(23));
				retorno=true;
			}
			if(matriz[23][26]==char_pellet)
			{
				d_4=CalculaDistanciaReta(p_x,p_y,Mapa::X_TELA(26),Mapa::Y_TELA(23));
				retorno=true;
			}
			
			if(d_1<=d_2&&d_1<=d_3&&d_1<=d_4)
			{
				*x_saida = X_TELA(1);
				*y_saida = Y_TELA(3);
			}
			else if(d_2<=d_1&&d_2<=d_3&&d_2<=d_4)
			{
				*x_saida = X_TELA(26);
				*y_saida = Y_TELA(3);
			}
			else if(d_3<=d_1&&d_3<=d_2&&d_3<=d_4)
			{
				*x_saida = X_TELA(1);
				*y_saida = Y_TELA(23);
			}
			else if(d_4<=d_1&&d_4<=d_2&&d_4<=d_3)
			{
				*x_saida = X_TELA(26);
				*y_saida = Y_TELA(23);
			}
			return retorno;
		}
};
const char Mapa::matriz_base[LINHAS_MAPA][COLUNAS_MAPA]  = 
{
	{'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'},
	{'X','0','0','0','0','0','0','0','0','0','0','0','0','X','X','0','0','0','0','0','0','0','0','0','0','0','0','X'},
	{'X','0','X','X','X','X','0','X','X','X','X','X','0','X','X','0','X','X','X','X','X','0','X','X','X','X','0','X'},
	{'X','0','X','X','X','X','0','X','X','X','X','X','0','X','X','0','X','X','X','X','X','0','X','X','X','X','0','X'},
	{'X','0','X','X','X','X','0','X','X','X','X','X','0','X','X','0','X','X','X','X','X','0','X','X','X','X','0','X'},
	{'X','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','X'},
	{'X','0','X','X','X','X','0','X','X','0','X','X','X','X','X','X','X','X','0','X','X','0','X','X','X','X','0','X'},
	{'X','0','X','X','X','X','0','X','X','0','X','X','X','X','X','X','X','X','0','X','X','0','X','X','X','X','0','X'},
	{'X','0','0','0','0','0','0','X','X','0','0','0','0','X','X','0','0','0','0','X','X','0','0','0','0','0','0','X'},
	{'X','X','X','X','X','X','0','X','X','X','X','X','0','X','X','0','X','X','X','X','X','0','X','X','X','X','X','X'},
	{'X','X','X','X','X','X','0','X','X','X','X','X','0','X','X','0','X','X','X','X','X','0','X','X','X','X','X','X'},
	{'X','X','X','X','X','X','0','X','X','0','0','0','0','0','0','0','0','0','0','X','X','0','X','X','X','X','X','X'},
	{'X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X'},
	{'X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X'},
	{'0','0','0','0','0','0','0','0','0','0','X','X','X','X','X','X','X','X','0','0','0','0','0','0','0','0','0','0'},
	{'X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X'},
	{'X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X'},
	{'X','X','X','X','X','X','0','X','X','0','0','0','0','0','0','0','0','0','0','X','X','0','X','X','X','X','X','X'},
	{'X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X'},
	{'X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X'},
	{'X','0','0','0','0','0','0','0','0','0','0','0','0','X','X','0','0','0','0','0','0','0','0','0','0','0','0','X'},
	{'X','0','X','X','X','X','0','X','X','X','X','X','0','X','X','0','X','X','X','X','X','0','X','X','X','X','0','X'},
	{'X','0','X','X','X','X','0','X','X','X','X','X','0','X','X','0','X','X','X','X','X','0','X','X','X','X','0','X'},
	{'X','0','0','0','X','X','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','X','X','0','0','0','X'},
	{'X','X','X','0','X','X','0','X','X','0','X','X','X','X','X','X','X','X','0','X','X','0','X','X','0','X','X','X'},
	{'X','X','X','0','X','X','0','X','X','0','X','X','X','X','X','X','X','X','0','X','X','0','X','X','0','X','X','X'},
	{'X','0','0','0','0','0','0','X','X','0','0','0','0','X','X','0','0','0','0','X','X','0','0','0','0','0','0','X'},
	{'X','0','X','X','X','X','X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X','X','X','X','X','0','X'},
	{'X','0','X','X','X','X','X','X','X','X','X','X','0','X','X','0','X','X','X','X','X','X','X','X','X','X','0','X'},
	{'X','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','X'},
	{'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'}
};
int Mapa::x0=0;
int Mapa::y0=ALTURA_PAINELSUPERIOR;

Mapa mapa;
Mapa mapa_path;
#endif
