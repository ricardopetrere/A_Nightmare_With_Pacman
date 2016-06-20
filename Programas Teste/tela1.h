#ifndef TELA1_H
#define TELA1_H
#include "telabase.h"
#include "botao.h"
#include "cutscenetextoplano.h"

class Tela1:public TelaBase {
	public:
		Botao b1;
		CutsceneTextoPlano cut1;
		Tela1(int delay)
			:TelaBase(delay)
		{
		}
		Tela1()
			:Tela1(DELAY)
		{
		}
		void InitializeComponents()
		{
			b1 = Botao(LARGURA_TELA-150,300,100,20,LIGHTGRAY,"Voltar");
			elementos.push_back(&b1);
			cut1 = CutsceneTextoPlano(5000,600,600,"solitaire.jpg","Texto exemplo");
			elementos.push_back(&cut1);
		}
		void Loop()
		{
			if(cut1.fimexecucao)
			{
				exibindo=false;
			}
		}
		void Eventos_Click()
		{
			if(OcorreuClickLButton())
			{
				if(b1.CursorEstaEmCima())
				{
					exibindo=false;
				}
			}
		}
		void OnClosed()
		{
			cut1.ResetaExecucao();
		}
};

#endif
