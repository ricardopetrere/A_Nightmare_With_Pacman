#ifndef CONTROLEBASE_H
#define CONTROLEBASE_H
#include "globais.h"
enum EnumTiposControles {
	KEYBOARD_MOUSE=0,JOYSTICK_XINPUT=1
};
INPUT in_mouse,in_keyboard;
size_t in_size=sizeof(INPUT);

class ControleBase {
	EnumTiposControles tipo=KEYBOARD_MOUSE;
	public:
		ControleBase()
		{
		}
		ControleBase(EnumTiposControles tipo)
		{
			this->tipo=tipo;
		}
		~ControleBase()
		{
		}
		virtual bool ComandoParaCima(bool consideraAnalogico=true);
		virtual bool ComandoParaDireita(bool consideraAnalogico=true);
		virtual bool ComandoParaBaixo(bool consideraAnalogico=true);
		virtual bool ComandoParaEsquerda(bool consideraAnalogico=true);
		virtual bool ComandoSelecionar();
		virtual bool ComandoVoltar();
//		virtual void MoverMouse();
		int tecla_cima=0;
		int tecla_direita=0;
		int tecla_baixo=0;
		int tecla_esquerda=0;
		int tecla_selecionar=0;
		int tecla_voltar=0;
		
		void BASE_SendInput(INPUT _in);
		void BASE_SendInputKeyboard(int _VKey, int _KEYEVENTF);
		void BASE_SendInputMouse(int _MOUSEEVENTF, int _dx, int _dy, int _mouseData);
		void BASE_SendInputKeyboardKey(int _VKey, bool &_KeyPressed, bool _KeyValue, int _KEYEVENTF);
		void BASE_SendInputMouseButton(bool &_ButtonPressed, bool _ButtonValue, int _MOUSEEVENTF);
//		bool BASE_PressKey(int _VKey, bool &_KeyPressed);
};
void ControleBase::BASE_SendInput(INPUT _in)
{
	SendInput(1,&_in,in_size);
}
void ControleBase::BASE_SendInputKeyboard(int _VKey, int _KEYEVENTF)
{
	ZeroMemory(&in_keyboard,in_size);
	in_keyboard.type = INPUT_KEYBOARD;
	in_keyboard.ki.wScan=0;
	in_keyboard.ki.time=0;
	in_keyboard.ki.dwExtraInfo=0;
	in_keyboard.ki.wVk=_VKey;
	in_keyboard.ki.dwFlags=_KEYEVENTF;
	BASE_SendInput(in_keyboard);
}
void ControleBase::BASE_SendInputMouse(int _MOUSEEVENTF, int _dx, int _dy, int _mouseData)
{
	ZeroMemory(&in_mouse,in_size);
	in_mouse.type  = INPUT_MOUSE;
	in_mouse.mi.dwFlags = _MOUSEEVENTF;
	in_mouse.mi.dx = _dx;
	in_mouse.mi.dy = _dy;
	in_mouse.mi.mouseData=_mouseData;
	BASE_SendInput(in_mouse);
}
void ControleBase::BASE_SendInputKeyboardKey(int _VKey, bool &_KeyPressed, bool _KeyValue, int _KEYEVENTF)
{
	//https://batchloaf.wordpress.com/2012/04/17/simulating-a-keystroke-in-win32-c-or-c-using-sendinput/
	_KeyPressed=_KeyValue;
	BASE_SendInputKeyboard(_VKey,_KEYEVENTF);
}
void ControleBase::BASE_SendInputMouseButton(bool &_ButtonPressed, bool _ButtonValue, int _MOUSEEVENTF)
{
	//http://forums.codeguru.com/showthread.php?377394-Windows-SDK-User-Interface-How-can-I-emulate-mouse-events-in-an-application
	_ButtonPressed=_ButtonValue;
	BASE_SendInputMouse(_MOUSEEVENTF,0,0,0);
}
//bool ControleBase::BASE_PressKey(int _VKey, bool &_KeyPressed)
//{
//	if(GetKeyState(_VKey)&0x80)
//	{
//		_KeyPressed=true;
//	}
//	else
//	{
//		if(_KeyPressed)
//		{
//			_KeyPressed=false;
//			return true;
//		}
//		_KeyPressed=false;
//	}
//	return false;
//}
#endif
