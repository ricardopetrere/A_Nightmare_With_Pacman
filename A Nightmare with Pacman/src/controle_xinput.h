#ifndef CONTROLE_XINPUT_H
#define CONTROLE_XINPUT_H
#include <xinput.h>
#include "controlebase.h"
//Adicionar C:/Dev-Cpp/MinGW64/x86_64-w64-mingw32/lib32/libxinput1_4.a nos parâmetros do linker
#include <limits.h>
#define TAXA_MOV_MOUSE	50
class Controle_XINPUT : public ControleBase{
	int _numerocontrole;
	int _resultadoconexao;
	XINPUT_STATE _estadocontrole;
	XINPUT_BATTERY_INFORMATION _estadobateria;
	public:
		Controle_XINPUT(int numerocontrole);
		~Controle_XINPUT();
		bool ComandoParaCima(bool consideraAnalogico=true);
		bool ComandoParaDireita(bool consideraAnalogico=true);
		bool ComandoParaBaixo(bool consideraAnalogico=true);
		bool ComandoParaEsquerda(bool consideraAnalogico=true);
		bool ComandoSelecionar();
		bool ComandoVoltar();
		int NumeroControle();
		XINPUT_STATE GetState();
		bool IsConnected();
		void Vibrar(int Left=0, int Right=0);
		XINPUT_GAMEPAD GetGamepadState();
		int EstadoBotoes();
		
		//Este método precisa da versão 1.4 da libxinput.a. Vide https://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xinputgetbatteryinformation(v=vs.85).aspx
		int EstadoBateria();
		
		//Esses três métodos são apenas para remover a deadzone da visualização na tela
		int EstadoThumb(short sThumb, int _DEADZONE)
		{
			if(sThumb>_DEADZONE
				||sThumb<-_DEADZONE)
				return sThumb;
			else
				return 0;
		}
		int EstadoThumbL(bool IsX)
		{
			short _sThumbL;
			if(IsX)
				_sThumbL = _estadocontrole.Gamepad.sThumbLX;
			else
				_sThumbL = _estadocontrole.Gamepad.sThumbLY;
			return EstadoThumb(_sThumbL,XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		}
		int EstadoThumbR(bool IsX)
		{
			short _sThumbR;
			if(IsX)
				_sThumbR = _estadocontrole.Gamepad.sThumbRX;
			else
				_sThumbR = _estadocontrole.Gamepad.sThumbRY;
			return EstadoThumb(_sThumbR,XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		}
		int EstadoThumbLX()
		{
			return EstadoThumbL(true);
		}
		int EstadoThumbLY()
		{
			return EstadoThumbL(false);
		}
		int EstadoThumbRX()
		{
			return EstadoThumbR(true);
		}
		int EstadoThumbRY()
		{
			return EstadoThumbR(false);
		}
		
		bool BASE_ConverteClickGamepadtoKeyboardKey(int _XINPUT_MASK, int _VKey, bool &_KeyPressed)
		{
			if(EstadoBotoes()&_XINPUT_MASK)
			{
				BASE_SendInputKeyboardKey(_VKey,_KeyPressed,true,0);
			}
			else
			{
				if(_KeyPressed)
				{
					BASE_SendInputKeyboardKey(_VKey,_KeyPressed,false,KEYEVENTF_KEYUP);
					return true;
				}
				_KeyPressed=false;
			}
			return false;
		}
		bool BASE_ConverteClickGamepadtoMouseClick(int _XINPUT_MASK,bool &_ButtonPressed, int _MOUSEEVENTF_DOWN, int _MOUSEEVENTF_UP)
		{
			if(EstadoBotoes()&_XINPUT_MASK)
			{
				BASE_SendInputMouseButton(_ButtonPressed,true,_MOUSEEVENTF_DOWN);
			}
			else
			{
				if(_ButtonPressed)
				{
					BASE_SendInputMouseButton(_ButtonPressed,false,_MOUSEEVENTF_UP);
					return true;
				}
				_ButtonPressed=false;
			}
			return false;
		}
		void MoverMouse()
		{
			int lx=EstadoThumbLX();
			int ly=EstadoThumbLY();
			
			if(lx>0)
				lx-=XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			else if(lx<0)
				lx+=XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			if(ly>0)
				ly-=XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			else if(ly<0)
				ly+=XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			
			int dx=(lx/(double)SHRT_MAX)*TAXA_MOV_MOUSE;
			int dy=-(ly/(double)SHRT_MAX)*TAXA_MOV_MOUSE;
			
			BASE_SendInputMouse(MOUSEEVENTF_MOVE,dx,dy,0);
		}
};
Controle_XINPUT::Controle_XINPUT(int numerocontrole)
	:ControleBase(JOYSTICK_XINPUT)
{
	_numerocontrole=numerocontrole-1;
	//Default
	tecla_cima=XINPUT_GAMEPAD_DPAD_UP;
	tecla_direita=XINPUT_GAMEPAD_DPAD_RIGHT;
	tecla_baixo=XINPUT_GAMEPAD_DPAD_DOWN;
	tecla_esquerda=XINPUT_GAMEPAD_DPAD_LEFT;
	tecla_selecionar=XINPUT_GAMEPAD_A;
	tecla_voltar=XINPUT_GAMEPAD_B;
}
Controle_XINPUT::~Controle_XINPUT()
{
}
//É um pouco irritante, no caso de o LThumb estar sendo lido para mexer o mouse, se ele também for considerado para os comandos
bool Controle_XINPUT::ComandoParaCima(bool consideraAnalogico)
{
	int tmp=EstadoThumbLY();
	return EstadoBotoes()&tecla_cima||(consideraAnalogico&&(tmp>0&&abs(EstadoThumbLX())<tmp));
}
bool Controle_XINPUT::ComandoParaDireita(bool consideraAnalogico)
{
	int tmp=EstadoThumbLX();
	return EstadoBotoes()&tecla_direita||(consideraAnalogico&&(abs(EstadoThumbLY())<tmp&&tmp>0));
}
bool Controle_XINPUT::ComandoParaBaixo(bool consideraAnalogico)
{
	int tmp=EstadoThumbLY();
	return EstadoBotoes()&tecla_baixo||(consideraAnalogico&&(tmp<0&&abs(EstadoThumbLX())<-tmp));
}
bool Controle_XINPUT::ComandoParaEsquerda(bool consideraAnalogico)
{
	int tmp=EstadoThumbLX();
	return EstadoBotoes()&tecla_esquerda||(consideraAnalogico&&(abs(EstadoThumbLY())<-tmp&&tmp<0));
}
bool Controle_XINPUT::ComandoSelecionar()
{
	return BASE_ConverteClickGamepadtoMouseClick(tecla_selecionar,LBPressed,MOUSEEVENTF_LEFTDOWN,MOUSEEVENTF_LEFTUP);
}
bool Controle_XINPUT::ComandoVoltar()
{
	return BASE_ConverteClickGamepadtoKeyboardKey(tecla_voltar,VK_ESCAPE,ESCPressed);
}
int Controle_XINPUT::NumeroControle()
{
	return _numerocontrole+1;
}
XINPUT_STATE Controle_XINPUT::GetState()
{
	ZeroMemory(&_estadocontrole,sizeof(XINPUT_STATE));
	
	_resultadoconexao = XInputGetState(_numerocontrole,&_estadocontrole);
	
	return _estadocontrole;
}
bool Controle_XINPUT::IsConnected()
{
	return (_resultadoconexao==ERROR_SUCCESS);
}
void Controle_XINPUT::Vibrar(int Left, int Right)
{
	XINPUT_VIBRATION Vibration;
	ZeroMemory(&Vibration,sizeof(XINPUT_VIBRATION));
	Vibration.wLeftMotorSpeed=Left;
	Vibration.wRightMotorSpeed=Right;
	XInputSetState(_numerocontrole,&Vibration);
}
XINPUT_GAMEPAD Controle_XINPUT::GetGamepadState()
{
	return GetState().Gamepad;
}
int Controle_XINPUT::EstadoBotoes()
{
	return GetGamepadState().wButtons;
}
int Controle_XINPUT::EstadoBateria()
{
	XInputGetBatteryInformation(_numerocontrole,BATTERY_DEVTYPE_GAMEPAD,&_estadobateria);
	/*
	No caso de programas como ScpDriver, que emulam o controle de PS3 como de XBox 360, estes armazenam uma lista dos 4 últimos controles conectados, o que engana o XInput,
	fazendo-o acreditar que os controles ainda estão conectados
	O código abaixo seria um modo de declarar que eles não foram conectados nessa sessão do Windows, mas nada impede de eles terem sido conectados anteriormente
	Colocar uma função Sleep() seria errado, então também não foi utlilizada aqui
	
	if(_resultadoconexao!=0)
		return 0;
	*/
	return _estadobateria.BatteryLevel;
}
#endif
