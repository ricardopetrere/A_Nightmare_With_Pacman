#ifndef CUTSCENEBASE_H
#define CUTSCENEBASE_H
#include "telabase.h"
class CutsceneBase:public TelaBase{
	public:
		Timer t_start;
//		int delay_ms;
		bool PulaComESC;
//		clock_t timer_start;
		
		CutsceneBase()
			:TelaBase(DELAY)
		{
		}
		CutsceneBase(int delay_ms,bool PulaComESC)
		{
//			this->delay_ms=delay_ms;
			t_start=Timer(delay_ms);
			this->PulaComESC=PulaComESC;
		}
		void Loop()//M�todo respons�vel pela l�gica da tela
		{
			if(t_start.CheckTimeout())
				exibindo=false;
//			if(CheckTimeout(timer_start,delay_ms))
//			{
//				exibindo=false;
//			}
		}
		void Eventos_Click()//M�todo que inclui as entradas do usu�rio (cliques e teclas pressionadas. O nome foi puramente sugestivo)
		{
			if(PulaComESC&&OcorreuClickESC())
				exibindo=false;
		}
		void Start()
		{
//			timer_start = clock();
			t_start.Start();
			TelaBase::Exibir();
		}
};
#endif
