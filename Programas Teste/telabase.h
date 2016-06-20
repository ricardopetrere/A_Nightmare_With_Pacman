#ifndef TELABASE_H
#define TELABASE_H
#include "elementografico.h"
#include <vector>

class TelaBase {
	public:
		bool exibindo;
		int delay_tela;
		int i;
		//http://www.cplusplus.com/forum/general/17754/
		std::vector<ElementoGrafico *> elementos;
		TelaBase()
			:TelaBase(DELAY)
		{
		}
		TelaBase(int delay)
		{
			elementos.clear();
			delay_tela=delay;
		}
		virtual void InitializeComponents()//Método responsável por inicializar os objetos da tela
		{}
		virtual void Loop()//Método responsável pela lógica da tela
		{}
		virtual void DesenharObjetos()//Método responsável por desenhar os elementos da tela
		{
			for(i=0;i<elementos.size();i++)
			{
				elementos[i]->Desenhar();
				outtextxy(elementos[i]->x-10,elementos[i]->y,"i");
			}
		}
		virtual void Eventos_Click()//Método que inclui as entradas do usuário (cliques e teclas pressionadas. O nome foi puramente sugestivo)
		{
			if(OcorreuClickLButton())
				exibindo=false;
		}
		virtual void OnClosed()//Método executado ao fechar a tela, para resetar o que for preciso
		{}
		void Exibir()//Método em loop, que exibe a tela enquanto for para ela ser exibida
		{
			exibindo=true;
			InitializeComponents();
			while(exibindo)
			{
				TrocaPaginaAtiva();
				cleardevice();
				Loop();
				Eventos_Click();
				DesenharObjetos();
				SetPaginaVisual();
				delay(delay_tela);
			}
			OnClosed();
		}
		void Exibir(telas_cutscenes tela_pai)//Sobrecarga para caso seja uma tela-filho
		{
			TelaBase::Exibir();
			telamostrando=tela_pai;
		}
};
#endif
