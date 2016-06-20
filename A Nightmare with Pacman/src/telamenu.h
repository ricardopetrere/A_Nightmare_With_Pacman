#ifndef TELAMENU_H
#define TELAMENU_H
#include "telabase.h"

class TelaMenu:public TelaBase {
	public:
		TelaMenu(int delay)
			:TelaBase(delay)
		{
		}
		TelaMenu()
			:TelaMenu(DELAY)
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
