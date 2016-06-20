#ifndef TELABASE_H
#define TELABASE_H
#include "globais.h"
class TelaBase {
	public:
		bool exibindo;
		int delay_tela;
		TelaBase()
		{
			TelaBase(DELAY);
		}
		TelaBase(int delay)
		{
			delay_tela=delay;
		}
		virtual void Loop(){}
		virtual void DesenharObjetos(){}
		virtual void Eventos_Click(){}
		void Exibir()
		{
			exibindo=true;
			while(exibindo)
			{
				TrocaPaginaAtiva();
				cleardevice();
				Loop();
				DesenharObjetos();
				Eventos_Click();
				SetPaginaVisual();
				delay(delay_tela);
			}
			
		}
};
#endif
