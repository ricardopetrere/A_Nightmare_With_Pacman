#ifndef MAPA_H
#define MAPA_H

#define LADO_CELULA 20
#define LINHAS 31
#define COLUNAS 28
#define LARGURA_MENU 200

#define char_parede 'X'
#define char_vazio '0'
#define char_ghost1 '1'
#define char_ghost2 '2'
#define char_ghost3 '3'
#define char_ghost4 '4'
#define char_pacman 'C'
#define char_fruit 'F'
#define char_pellet 'P'
#define char_bit 'B'
class Mapa {
	public:
		char matriz[LINHAS,COLUNAS];
		
};

#endif
