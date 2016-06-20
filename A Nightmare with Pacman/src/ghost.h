#ifndef GHOST_H
#define GHOST_H
#include "personagem.h"
#include "pacman.h"
class Ghost:public Personagem {
	public:
		static int x_begin;
		static int y_begin;
		
		int estagios_respawn;
		int contador_sair;
		int limite_sair;
		bool saindo;
		
		static Pacman* pac;
		Ghost()
			:Personagem()
		{
		}
		void Init()
		{
			estagios_respawn=0;
			contador_sair=0;
			limite_sair=0;
			saindo=false;
			AI=true;
			anim_up.delay = Timer(1000/4);
			anim_down=Animacao(1000/4);
			anim_left=Animacao(1000/4);
			anim_right=Animacao(1000/4);
			anim_none=Animacao(1000/4);
			anim_fear=Animacao(1000/2);
			anim_endfear=Animacao(1000/4);
			
			anim_fear.InsereSprite(imagens[ID_GHOSTFEAR]);
			anim_fear.InsereSprite(imagens[ID_GHOSTFEAR2]);
			anim_endfear.InsereSprite(imagens[ID_GHOSTFEAR2]);
			anim_endfear.InsereSprite(imagens[ID_GHOSTFEAR]);
			anim_endfear.InsereSprite(imagens[ID_GHOSTFEAR_WHITE2]);
			anim_endfear.InsereSprite(imagens[ID_GHOSTFEAR_WHITE]);
			anim_dead.InsereSprite(imagens[ID_GHOSTEYE_UP]);
			anim_dead.InsereSprite(imagens[ID_GHOSTEYE_RIGHT]);
			anim_dead.InsereSprite(imagens[ID_GHOSTEYE_DOWN]);
			anim_dead.InsereSprite(imagens[ID_GHOSTEYE_LEFT]);
			anim_dead.trocaspriteautomatico=false;
		}
		static void AmarrarPacman(Pacman &pacman)
		{
			Ghost::pac = &pacman;
		}
		void ExibeDebug()
		{
			Personagem::ExibeDebug();
			
			//Exibe o ponto-alvo (scatter e chase)
			setfillstyle(SOLID_FILL,RED);
			bar(X_Arredondado(x_target+MEIA_CELULA),Y_Arredondado(y_target+MEIA_CELULA)
				,X_Arredondado(x_target+MEIA_CELULA)+TAMANHO_CELULA-1,Y_Arredondado(y_target+MEIA_CELULA)+TAMANHO_CELULA-1);
		}
		void setTrocaSprites(bool valor)
		{
			Personagem::setTrocaSprites(valor);
			anim_dead.trocaspriteautomatico=valor;
		}
		virtual void DefineAlvo()
		{
			if(comportamento==DEAD)
			{
				x_target=x_begin;
				y_target=y_begin;
			}
		}
		void SetPassoDEAD()
		{
			passox=4*DEFAULT_PASSO;
			passoy=4*DEFAULT_PASSO;
		}
		bool EstaNaGhostHouse(int p_x, int p_y)
		{
			return (p_x>X_TELA(9)+MEIA_CELULA&&p_x<X_TELA(18)-MEIA_CELULA
				&&p_y>Y_TELA(11)+MEIA_CELULA&&p_y<Y_TELA(17)-MEIA_CELULA)
				||saindo;
		}
		bool EstaNaGhostHouse()
		{
			return EstaNaGhostHouse(x,y);
		}
		void ForcaRenascimento()
		{
			if(comportamento==DEAD)
			{
				comportamento=SCATTER;
				passox=DEFAULT_PASSO;
				passoy=DEFAULT_PASSO;
				saindo=false;
				estagios_respawn=0;
			}
		}
		void MudaComportamento(comportamentos comp,bool forcar=false)
		{
			if(comportamento!=DEAD&&!EstaNaGhostHouse(x,y))//Morto só muda comportamento pelo método de cima
				Personagem::MudaComportamento(comp,forcar);
		}
		void LogicaMover()
		{
			if(estagios_respawn>0)//Em processo de respawn
			{
				if(estagios_respawn==1)//Indo até o centro da ghost house
				{
					movimento=DOWN;
					passox=DEFAULT_PASSO/4;
					passoy=DEFAULT_PASSO/4;
					if(y-MEIA_CELULA==Y_TELA(14))//Chegou no meio da ghost house, troca de estágio
					{
						estagios_respawn=2;
						comportamento = SCATTER;
					}
				}
				else if(estagios_respawn==2)//Saindo
				{
					movimento=UP;
					if(y-MEIA_CELULA==Y_TELA(11))//Voltou à entrada da ghost house
					{
						estagios_respawn=0;//Terminou o processo de respawn
						passox=DEFAULT_PASSO;
						passoy=DEFAULT_PASSO;
						movimento=LEFT;
						saindo=false;
					}
				}
				Mover();
			}
			else if(comportamento==DEAD&&X_MATRIZ()==14&&Y_MATRIZ()==11)//Entrada da ghost house
			{
				x=X_TELA(14);//Pra garantir que entre no meio da casa
				estagios_respawn=1;
			}
			else if(saindo)
			{
				if(x==X_TELA(14)&&y>Y_TELA(11)+MEIA_CELULA)
				{
					movimento=UP;
					passox=DEFAULT_PASSO/4;
					passoy=DEFAULT_PASSO/4;
				}
				else if(x>X_TELA(14))
				{
					movimento=LEFT;
					passox=DEFAULT_PASSO/4;
					passoy=DEFAULT_PASSO/4;
				}
				else if(x<X_TELA(14))
				{
					movimento=RIGHT;
					passox=DEFAULT_PASSO/4;
					passoy=DEFAULT_PASSO/4;
				}
				else
				{
					passox=DEFAULT_PASSO;
					passoy=DEFAULT_PASSO;
					movimento=LEFT;
					saindo=false;
				}
				Mover();
			}
			else
				Personagem::LogicaMover();
		}
		void AnimacaoMorte()
		{
			anim_dead.Desenhar(x+offsetimagem_x,y+offsetimagem_y,(int)movimento);
		}
		void Sair()
		{
			if(EstaNaGhostHouse()&&!saindo)
				saindo=true;
		}
};
Pacman* Ghost::pac;
int Ghost::x_begin=TAMANHO_CELULA*14;
int Ghost::y_begin=MEIA_CELULA+ ALTURA_PAINELSUPERIOR+(TAMANHO_CELULA*14);
#endif
