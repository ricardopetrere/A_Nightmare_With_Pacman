#ifndef TELABASE_H
#define TELABASE_H
/*
Sempre que for gerar uma nova tela, baseada nesta, usar esse bloco de código:

#ifndef TELAJOGO_H
#define TELAJOGO_H
#include "telabase.h"

class TelaJogo:public TelaBase {
	public:
		TelaJogo(int delay)
			:TelaBase(delay)
		{
		}
		TelaJogo()
			:TelaJogo(DELAY)
		{
		}
		void InitializeComponents()
		{
		}
		void Loop()
		{
		}
		void Eventos_Click()
		{
		}
		void OnClosed()
		{
		}
};

#endif
*/
#include "botao.h"
#include "texto.h"
#include "radiobutton.h"
#include "controlejogo.h"

class TelaBase{
	public:
		bool exibindo;
//		int delay_tela;
		Timer t_delay_tela;
		TelaBase(int delay=DELAY)
		{
			t_delay_tela=Timer(delay);
//			delay_tela=delay;
		}
		virtual void InitializeComponents()//1- Método responsável por inicializar os objetos da tela
		{}
		virtual void Loop()//2- Método responsável pela lógica da tela
		{}
		virtual void DesenharObjetos()//3- Método responsável por desenhar os elementos da tela
		{
		}
		virtual void Eventos_Click()//4- Método que inclui as entradas do usuário (cliques e teclas pressionadas. O nome foi puramente sugestivo)
		{
			if(OcorreuClickLButton())
				exibindo=false;
		}
		virtual void OnClosed()//5- Método executado ao fechar a tela, para resetar o que for preciso
		{
			InterrompeSom();
		}
		void Exibir()//Método em loop, que exibe a tela enquanto for para ela ser exibida
		{
			exibindo=true;
			InitializeComponents();
			while(exibindo)
			{
				#ifdef __TESTE__ //Colocar -D__TESTE__ nos parâmetros do compilador C++
				EscreveEmConsole("Teste");
				#elif defined __DEBUG__
				EscreveEmConsole("Modo Debug");
				#else
				EscreveEmConsole("Modo Release");
				#endif
				TrocaPaginaAtiva();
				cleardevice();
				Loop();
				DesenharObjetos();
				Eventos_Click();
				while(!t_delay_tela.CheckTimeout());
				t_delay_tela.Start();
				SetPaginaVisual();
//				Delay_Ms(delay_tela);
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
