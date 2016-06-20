#ifndef PERSONAGEM_H
#define PERSONAGEM_H
#include "elementografico.h"
#include <vector>
#include "resources.h"
#include "mapa.h"
#include "animacao.h"

#define DEFAULT_PASSO (PROPORCAO_FUNDO)

enum movimentos{
	NONE=-1,UP=0,RIGHT=1,DOWN=2,LEFT=3
};
enum comportamentos{
	SCATTER=0, CHASE=1, FEAR=2, ENDFEAR=3, DEAD=4
};

class Personagem : public ElementoGrafico {
	public:
		char char_identificador;
		int x_inicial,y_inicial;
		Animacao anim_up;
		Animacao anim_down;
		Animacao anim_left;
		Animacao anim_right;
		Animacao anim_none;
		Animacao anim_fear;
		Animacao anim_endfear;
		Animacao anim_dead;
		
		int passox=DEFAULT_PASSO;
		int passoy=DEFAULT_PASSO;
		movimentos movimento=NONE;
		int offsetimagem_x=-8*PROPORCAO_FUNDO;
		int offsetimagem_y=-8*PROPORCAO_FUNDO;
		int r_colisao=6*PROPORCAO_FUNDO;
		
		bool AI=false;
		comportamentos comportamento;
		
		int x_scatter;
		int y_scatter;
		int x_target;
		int y_target;
		
		Personagem()
		{
		}
		virtual void Init(){
			anim_up;
			anim_down;
			anim_left;
			anim_right;
			anim_none;
			anim_fear;
			anim_endfear;
			anim_dead;
			ResetaPosicao();
		}
		virtual void ExibeDebug();
		void SetOrigem(int p_x, int p_y)
		{
			x_inicial=p_x;
			y_inicial=p_y;
		}
		int X_Imagem(int p_x)
		{
			return p_x+offsetimagem_x;
		}
		int X_Imagem()
		{
			return X_Imagem(x);
		}
		int Y_Imagem(int p_y)
		{
			return p_y+offsetimagem_y;
		}
		int Y_Imagem()
		{
			return Y_Imagem(y);
		}
		virtual void Loop()
		{
			
		}
		virtual void SetMovimentoInicial()
		{
			movimento=RIGHT;
		}
		virtual void DefineAlvo()
		{
			x_target=0;
			y_target=0;
		}
		void ResetaPosicao()
		{
			x=x_inicial;
			y=y_inicial;
			SetMovimentoInicial();
		}
		virtual void setTrocaSprites(bool valor)//Pra poder congelar as imagens
		{
			anim_up.trocaspriteautomatico=valor;
			anim_down.trocaspriteautomatico=valor;
			anim_left.trocaspriteautomatico=valor;
			anim_right.trocaspriteautomatico=valor;
			anim_none.trocaspriteautomatico=valor;
			anim_fear.trocaspriteautomatico=valor;
			anim_endfear.trocaspriteautomatico=valor;
		}
		void AjustarX()
		{
			if(passox==0)
				passox=1;
			int x_defasado=x%passox;
			if(x_defasado>(passox/2))
				x+=x_defasado;
			else
				x-=x_defasado;
		}
		void AjustarY()
		{
			if(passoy==0)
				passoy=1;
			int y_defasado=y%passoy;
			if(y_defasado>(passoy/2))
				y+=y_defasado;
			else
				y-=y_defasado;
		}
		void Mover()
		{
			setTrocaSprites(true);
			AjustarX();
			AjustarY();
			switch(movimento) {
			case LEFT:
				x-=passox;
				if(X_MATRIZ()<=0)
				{
					SetCentro_X(LARGURA_FUNDO);
				}
				break;
			case RIGHT:
				x+=passox;
				if(X_MATRIZ()>=COLUNAS_MAPA)
				{
					SetCentro_X(0);
				}
				break;
			case UP:
				y-=passoy;
				if(Y_MATRIZ()<=0)
				{
					SetCentro_Y(ALTURA_PAINELSUPERIOR+ALTURA_FUNDO);
				}
				break;
			case DOWN:
				y+=passoy;
				if(Y_MATRIZ()>=LINHAS_MAPA)
				{
					SetCentro_Y(0);
				}
				break;
			}
		}
		virtual void AnimacaoMorte()
		{
			anim_dead.Desenhar(X_Imagem(),Y_Imagem());
		}
		virtual void Desenhar()
		{
			if(comportamento==FEAR)
			{
				anim_fear.Desenhar(X_Imagem(),Y_Imagem());
			}
			else if(comportamento==ENDFEAR)
			{
				anim_endfear.Desenhar(X_Imagem(),Y_Imagem());
			}
			else if(comportamento==SCATTER||comportamento==CHASE)
			{
				switch(movimento){
					case UP:
						anim_up.Desenhar(X_Imagem(),Y_Imagem());
						break;
					case DOWN:
						anim_down.Desenhar(X_Imagem(),Y_Imagem());
						break;
					case LEFT:
						anim_left.Desenhar(X_Imagem(),Y_Imagem());
						break;
					case RIGHT:
						anim_right.Desenhar(X_Imagem(),Y_Imagem());
						break;
					case NONE:
						anim_none.Desenhar(X_Imagem(),Y_Imagem());
						break;
				}
			}
			else if(comportamento==DEAD)
			{
				AnimacaoMorte();
			}
			if(Debug)
			{
				ExibeDebug();
			}
		}
		int SetCentro_X(int valor)
		{
			x=valor;
		}
		int SetCentro_Y(int valor)
		{
			y=valor;
		}
		int Centro_X()
		{
			return x;
		}
		int Centro_Y()
		{
			return y;
		}
		int X_MATRIZ(int p_x)
		{
			return (p_x-Mapa::x0)/TAMANHO_CELULA;
		}
		int X_MATRIZ()
		{
			return X_MATRIZ(this->x);
		}
		int Y_MATRIZ(int p_y)
		{
			return (p_y-Mapa::y0)/TAMANHO_CELULA;
		}
		int Y_MATRIZ()
		{
			return Y_MATRIZ(this->y);
		}
		int X_TELA(int x_matriz)
		{
			return (x_matriz*TAMANHO_CELULA)+Mapa::x0;
		}
		int Y_TELA(int y_matriz)
		{
			return (y_matriz*TAMANHO_CELULA)+Mapa::y0;
		}
		int PixelsRestantes_X(int p_x)
		{
			return (p_x-MEIA_CELULA)%TAMANHO_CELULA;
		}
		int PixelsRestantes_X()
		{
			return PixelsRestantes_X(this->x);
		}
		int PixelsRestantes_Y(int p_y)
		{
			return (p_y-MEIA_CELULA)%TAMANHO_CELULA;
		}
		int PixelsRestantes_Y()
		{
			return PixelsRestantes_Y(this->y);
		}
		int X_Arredondado(int p_x)
		{
			return (p_x-PixelsRestantes_X(p_x)-MEIA_CELULA);
		}
		int X_Arredondado()
		{
			return X_Arredondado(this->x);
		}
		int Y_Arredondado(int p_y)
		{
			return (p_y-PixelsRestantes_Y(p_y)-MEIA_CELULA);
		}
		int Y_Arredondado()
		{
			return Y_Arredondado(this->y);
		}
		virtual void SetPassoDEAD()
		{
			passox=4*DEFAULT_PASSO;
			passoy=4*DEFAULT_PASSO;
		}
		virtual void MudaComportamento(comportamentos comp,bool forcar=false)
		{
			if(comp!=comportamento)//Reforçar a mudança de comportamento dá erro
			{
				
				if(comp==SCATTER||comp==CHASE)
				{
					passox=DEFAULT_PASSO;
					passoy=DEFAULT_PASSO;
				}
				else if(comp==FEAR||comp==ENDFEAR)
				{
					passox=DEFAULT_PASSO/2;
					passoy=DEFAULT_PASSO/2;
				}
				else if(comp==DEAD)
				{
					SetPassoDEAD();
				}
				comportamento = comp;
				if(forcar&&AI)
					DecidirProximoPasso(forcar);
			}
		}
		bool EmFear()
		{
			return comportamento==FEAR||comportamento==ENDFEAR;
		}
		char EstaSobre(Mapa m)
		{
			return m.Posicao(X_MATRIZ(),Y_MATRIZ());
		}
		bool EstaNoMesmoTile(Personagem per)
		{
			return (per.comportamento!=DEAD)&&
				(per.X_MATRIZ()==this->X_MATRIZ()
				&&per.Y_MATRIZ()==this->Y_MATRIZ());
		}
		char CharProximaCasa(movimentos mov)
		{
			if(mov==UP)
				return mapa_path.Posicao(X_MATRIZ(),(Y_MATRIZ()-1+LINHAS_MAPA)%LINHAS_MAPA);
			else if(mov==RIGHT)
				return mapa_path.Posicao((X_MATRIZ()+1)%COLUNAS_MAPA,Y_MATRIZ());
			else if(mov==DOWN)
				return mapa_path.Posicao(X_MATRIZ(),(Y_MATRIZ()+1)%LINHAS_MAPA);
			else if(mov==LEFT)
				return mapa_path.Posicao((X_MATRIZ()-1+COLUNAS_MAPA)%COLUNAS_MAPA,Y_MATRIZ());
			else
				return mapa_path.Posicao(X_MATRIZ(),Y_MATRIZ());
		}
		char CharProximaCasa()
		{
			return CharProximaCasa(movimento);
		}
		void FazCurva()
		{
			//http://stackoverflow.com/a/261986
			int mov = ((int)movimento+2)%4;//Começa faceando pra trás
			int count_opcoes=0;
			while(count_opcoes<4)
			{
				mov=(mov+1)%4;
				switch(mov){
					case UP:
						if(Mapa::matriz_base[this->Y_MATRIZ()-1][this->X_MATRIZ()]!=char_parede)
						{
							movimento = UP;
							return;
						}
						count_opcoes++;
						break;
					case RIGHT:
						if(Mapa::matriz_base[this->Y_MATRIZ()][this->X_MATRIZ()+1]!=char_parede)
						{
							movimento = RIGHT;
							return;
						}
						count_opcoes++;
						break;
					case DOWN:
						if(Mapa::matriz_base[this->Y_MATRIZ()+1][this->X_MATRIZ()]!=char_parede)
						{
							movimento = DOWN;
							return;
						}
						count_opcoes++;
						break;
					case LEFT:
						if(Mapa::matriz_base[this->Y_MATRIZ()][this->X_MATRIZ()-1]!=char_parede)
						{
							movimento = LEFT;
							return;
						}
						count_opcoes++;
						break;
				}
			}
			movimento = NONE;
		}
		virtual void DecidirProximoPasso(bool forcar=false)
		{
			if(comportamento==FEAR||comportamento==ENDFEAR)
			{
				bool calculou=false;
				int escolha=-1;
				if(EstaSobre(mapa)==char_parede)
				{
					movimento=NONE;
					return;
				}
				while(!calculou)
				{
					escolha=rand()%4;
					switch(escolha){
						case UP:
							movimento=UP;
							if(CharProximaCasa()!=char_parede)
								calculou=true;
							break;
						case RIGHT:
							movimento=RIGHT;
							if(CharProximaCasa()!=char_parede)
								calculou=true;
							break;
						case DOWN:
							movimento=DOWN;
							if(CharProximaCasa()!=char_parede)
								calculou=true;
							break;
						case LEFT:
							movimento=LEFT;
							if(CharProximaCasa()!=char_parede)
								calculou=true;
							break;
							
					}
				}
			}
			else
			{
				double d_left = 999;
				double d_right = 999;
				double d_up = 999;
				double d_down = 999;
				if(comportamento==SCATTER)
				{
					x_target=x_scatter;
					y_target=y_scatter;
				}
				else if(comportamento==CHASE||comportamento==DEAD)
				{
					DefineAlvo();
				}
				//No caso de mudança de estado, é possível reverter a trajetória
				//if I go left?
				if(CharProximaCasa(LEFT)!=char_parede
				&&PixelsRestantes_Y()==0
				&&(movimento!=RIGHT||forcar)
				)
				{
					d_left=CalculaDistanciaReta(X_MATRIZ()-1,Y_MATRIZ(),X_MATRIZ(x_target),Y_MATRIZ(y_target));
				}
				//if I go right?
				if(CharProximaCasa(RIGHT)!=char_parede
				&&PixelsRestantes_Y()==0
				&&(movimento!=LEFT||forcar)
				)
				{
					d_right=CalculaDistanciaReta(X_MATRIZ()+1,Y_MATRIZ(),X_MATRIZ(x_target),Y_MATRIZ(y_target));
				}
				//if I go up?
				if(CharProximaCasa(UP)!=char_parede
				&&PixelsRestantes_X()==0
				&&(movimento!=DOWN||forcar)
				)
				{
					d_up=CalculaDistanciaReta(X_MATRIZ(),Y_MATRIZ()-1,X_MATRIZ(x_target),Y_MATRIZ(y_target));
				}
				//if I go down?
				if(CharProximaCasa(DOWN)!=char_parede
				&&PixelsRestantes_X()==0
				&&(movimento!=UP||forcar)
				)
				{
					d_down=CalculaDistanciaReta(X_MATRIZ(),Y_MATRIZ()+1,X_MATRIZ(x_target),Y_MATRIZ(y_target));
				}
				
				//Ordem de prioridades no caso de resultados semelhantes: UP>LEFT>DOWN
				if(d_up<=d_left&&d_up<=d_right&&d_up<=d_down)
				{
					movimento=UP;
				}
				else if(d_left<=d_up&&d_left<=d_right&&d_left<=d_down)
				{
					movimento=LEFT;
				}
				else if(d_down<=d_left&&d_down<=d_up&&d_down<=d_right)
				{
					movimento=DOWN;
				}
				else if(d_right<=d_left&&d_right<=d_up&&d_right<=d_down)
				{
					movimento=RIGHT;
				}
				else//Impossível, mas vai que...
				{
					movimento=NONE;
				}
			}
		}
		bool ProximaCasaLivre(movimentos mov)
		{
			switch(mov){
				case LEFT:
					return CharProximaCasa(mov)!=char_parede;
					break;
				case RIGHT:
					return CharProximaCasa(mov)!=char_parede;
					break;
				case UP:
					return CharProximaCasa(mov)!=char_parede;
					break;
				case DOWN:
					return CharProximaCasa(mov)!=char_parede;
					break;
			}
		}
		bool ProximaCasaLivre()
		{
			return ProximaCasaLivre(movimento);
		}
		virtual void LogicaMover()
		{
			/*
			São as situações:
			- Personagem controlado por AI com PixelsRestantes_X()>0 e próxima casa = vazio			Mover();	
			- Personagem controlado por AI com PixelsRestantes_X()>0 e próxima casa = parede		Mover();
			- Personagem controlado por AI com PixelsRestantes_X()=0 e próxima casa = vazio			Mover();
			- Personagem controlado por AI com PixelsRestantes_X()=0 e próxima casa = parede		FazCurva() ou DecidirProximoPasso();
			
			- Personagem controlado manualmente com PixelsRestantes_X()>0 e próxima casa = vazio	Mover();
			- Personagem controlado manualmente com PixelsRestantes_X()>0 e próxima casa = parede	Mover();
			- Personagem controlado manualmente com PixelsRestantes_X()=0 e próxima casa = vazio	Mover();
			- Personagem controlado manualmente com PixelsRestantes_X()=0 e próxima casa = parede	Não se mexe
			*/
			switch(movimento) {
				case NONE:
					break;
				case LEFT:
					if(ProximaCasaLivre()||PixelsRestantes_X()!=0)
					{
						if(AI&&EstaSobre(mapa_path)==char_interseccao&&PixelsRestantes_X()==0)
							DecidirProximoPasso();
						Mover();
					}
					else if(AI)
					{
						if(EstaSobre(mapa_path)==char_vazio)
							FazCurva();
						else if(EstaSobre(mapa_path)==char_interseccao)
							DecidirProximoPasso();
						Mover();
					}
					else
					{
						setTrocaSprites(false);
					}
					break;
				case RIGHT:
					if(ProximaCasaLivre()||PixelsRestantes_X()!=0)
					{
						if(AI&&EstaSobre(mapa_path)==char_interseccao&&PixelsRestantes_X()==0)
							DecidirProximoPasso();
						Mover();
					}
					else if(AI)
					{
						if(EstaSobre(mapa_path)==char_vazio)
							FazCurva();
						else if(EstaSobre(mapa_path)==char_interseccao)
							DecidirProximoPasso();
						Mover();
					}
					else
					{
						setTrocaSprites(false);
					}
					break;
				case UP:
					if(ProximaCasaLivre()||PixelsRestantes_Y()!=0)
					{
						if(AI&&EstaSobre(mapa_path)==char_interseccao&&PixelsRestantes_Y()==0)
							DecidirProximoPasso();
						Mover();
					}
					else if(AI)
					{
						if(EstaSobre(mapa_path)==char_vazio)
							FazCurva();
						else if(EstaSobre(mapa_path)==char_interseccao)
							DecidirProximoPasso();
						Mover();
					}
					else
					{
						setTrocaSprites(false);
					}
					break;
				case DOWN:
					if(ProximaCasaLivre()||PixelsRestantes_Y()!=0)
					{
						if(AI&&EstaSobre(mapa_path)==char_interseccao&&PixelsRestantes_Y()==0)
							DecidirProximoPasso();
						Mover();
					}
					else if(AI)
					{
						if(EstaSobre(mapa_path)==char_vazio)
							FazCurva();
						else if(EstaSobre(mapa_path)==char_interseccao)
							DecidirProximoPasso();
						Mover();
					}
					else
					{
						setTrocaSprites(false);
					}
					break;
			}
		}
};
void Personagem::ExibeDebug()
{
	setcolor(GREEN);
	//Ponto central
	line(X_Imagem(),Y_Imagem(),X_Imagem()+Tiles(1),Y_Imagem()+Tiles(1));
	line(X_Imagem(),Y_Imagem()+Tiles(1),X_Imagem()+Tiles(1),Y_Imagem());
	
	//Círculo de colisão
	line(Centro_X()-MEIA_CELULA,Centro_Y(),Centro_X()+MEIA_CELULA,Centro_Y());
	line(Centro_X(),Centro_Y()-MEIA_CELULA,Centro_X(),Centro_Y()+MEIA_CELULA);
	circle(Centro_X(),Centro_Y(),r_colisao);
}
#endif
