#ifndef TELAENDGAME_H
#define TELAENDGAME_H
#include "telabase.h"
//Talvez implementar em uma tela pr�pria, ou como cutscene
class TelaEndGame:public TelaBase {
	public:
		TelaEndGame(int delay)
			:TelaBase(delay)
		{
		}
		TelaEndGame()
			:TelaEndGame(DELAY)
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
