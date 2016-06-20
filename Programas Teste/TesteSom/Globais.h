#ifndef GLOBAIS_H_
#define GLOBAIS_H_
#include <windows.h>
//Variáveis globais
bool LBClicked=false;
bool ESCClicked=false;
HWND MainWindow;
POINT P;

//Constantes globais

//Métodos globais
bool BASE_OcorreuClick(int VKey, bool &KeyClicked)
{
	if(GetKeyState(VKey)&0x80)
	{
		if(!KeyClicked)
		{
			KeyClicked=true;
		}
	}
	else if(!(GetKeyState(VKey)&0x80))
	{
		if(KeyClicked)
		{
			KeyClicked=false;
			if(GetForegroundWindow()==MainWindow)
			{
				if (ScreenToClient(MainWindow, &P))
				{
					return true;
				}
			}
		}
		KeyClicked=false;
	}
	return false;
}
bool OcorreuClickLButton()
{
	return BASE_OcorreuClick(VK_LBUTTON,LBClicked);
}
bool OcorreuClickESC()
{
	return BASE_OcorreuClick(VK_ESCAPE,ESCClicked);
}
#endif
