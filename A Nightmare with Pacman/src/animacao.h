#ifndef ANIMACAO_H
#define ANIMACAO_H
#include <vector>
#include "sprite.h"

using namespace std;

class Animacao {
	public:
		vector<Sprite> vetor;
		int counter=0;
		bool trocaspriteautomatico=true;
		Timer delay=Timer(100);
		Animacao()
		{
			vetor.clear();
		}
		Animacao(int delay)
			:Animacao()
		{
			this->delay.timeout_ms=delay;
		}
		Animacao(bool trocaautomatica)
			:Animacao()
		{
			trocaspriteautomatico=trocaautomatica;
		}
		Animacao(int delay, bool trocaautomatica)
			:Animacao()
		{
			this->delay.timeout_ms=delay;
			trocaspriteautomatico=trocaautomatica;
		}
		bool InsereSprite(Sprite s)
		{
			vetor.push_back(s);
		}
		int TotalSprites()
		{
			return vetor.size();
		}
		void Desenhar(int x, int y, int id=-1)//Informar um valor para "id" significa não usar a troca automática de sprites
		{
			if(id>=0)
			{
				vetor[id].Desenhar(x,y);
			}
			else
			{
				if(counter>=0&&counter<vetor.size())
				{
					vetor[counter].Desenhar(x,y);
					if(trocaspriteautomatico&&delay.CheckTimeout())
					{
						counter=(counter+1)%vetor.size();
						delay.Start();
					}
				}
			}
		}
};

#endif
