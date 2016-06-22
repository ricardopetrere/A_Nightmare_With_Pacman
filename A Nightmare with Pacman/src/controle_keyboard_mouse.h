#ifndef CONTROLE_KEYBOARD_MOUSE_H
#define CONTROLE_KEYBOARD_MOUSE_H
#include "controlebase.h"
class Controle_KeyboardMouse : public ControleBase{
	public:
		Controle_KeyboardMouse();
		~Controle_KeyboardMouse();
};
Controle_KeyboardMouse::Controle_KeyboardMouse()
	:ControleBase(KEYBOARD_MOUSE)
{
	//Default
	tecla_cima='W';					//Player 2: VK_UP
	tecla_direita='D';				//Player 2: VK_RIGHT
	tecla_baixo='S';				//Player 2: VK_DOWN
	tecla_esquerda='A';				//Player 2: VK_LEFT
	tecla_selecionar=VK_LBUTTON;
	tecla_voltar=VK_ESCAPE;
}
Controle_KeyboardMouse::~Controle_KeyboardMouse()
{
}
bool ControleBase::ComandoParaCima(bool consideraAnalogico)
{
	return BASE_OcorreuKeyDown(tecla_cima);
}
bool ControleBase::ComandoParaDireita(bool consideraAnalogico)
{
	return BASE_OcorreuKeyDown(tecla_direita);
}
bool ControleBase::ComandoParaBaixo(bool consideraAnalogico)
{
	return BASE_OcorreuKeyDown(tecla_baixo);
}
bool ControleBase::ComandoParaEsquerda(bool consideraAnalogico)
{
	return BASE_OcorreuKeyDown(tecla_esquerda);
}
bool ControleBase::ComandoSelecionar()
{
	return BASE_OcorreuClick(tecla_selecionar,LBPressed);
}
bool ControleBase::ComandoVoltar()
{
	return BASE_OcorreuClick(tecla_voltar,ESCPressed);
}
#endif
