/*
#ifndef RESOURCES_H
#define RESOURCES_H
#include "sprite.h"
#include <string>
#define QUANTIDADE_IMAGENS 61
#define CHAR_DELIMITADOR '|'
#define QUANTIDADE_SONS 20
enum ID_IMAGENS{
	ID_NENHUM,
	
	ID_BACKGROUND,
	ID_BACKGROUNDEND,
	
	ID_TITLESCREEN,
	
	ID_CUTSCENE_OPENING,
	ID_CUTSCENE_ENDING,
	
	ID_CHAR1_IDLE,
	ID_CHAR1_LEFT,
	ID_CHAR1_RIGHT,
	ID_CHAR1_DOWN,
	ID_CHAR1_UP,
	
	ID_CHAR2_IDLE,
	ID_CHAR2_LEFT,
	ID_CHAR2_RIGHT,
	ID_CHAR2_DOWN,
	ID_CHAR2_UP,
	
	ID_CHAR3_IDLE,
	ID_CHAR3_LEFT,
	ID_CHAR3_RIGHT,
	ID_CHAR3_DOWN,
	ID_CHAR3_UP,
	
	ID_CHAR4_IDLE,
	ID_CHAR4_LEFT,
	ID_CHAR4_RIGHT,
	ID_CHAR4_DOWN,
	ID_CHAR4_UP,
	
	ID_PACMAN_LEFT,
	ID_PACMAN_RIGHT,
	ID_PACMAN_DOWN,
	ID_PACMAN_UP,
	ID_PACMAN_FULL,
	
	ID_PACMAN_FEAR,
	ID_PACMAN_FEAR_WHITE,
	ID_PACMAN_DEATH1,	
	ID_PACMAN_DEATH2,
	ID_PACMAN_DEATH3,
	ID_PACMAN_DEATH4,
	
	ID_PACBIT,
	ID_PELLET,
	
	ID_GHOSTRED_LEFT,
	ID_GHOSTRED_RIGHT,
	ID_GHOSTRED_DOWN,
	ID_GHOSTRED_UP,
	
	ID_GHOSTBLUE_LEFT,
	ID_GHOSTBLUE_RIGHT,
	ID_GHOSTBLUE_DOWN,
	ID_GHOSTBLUE_UP,
	
	ID_GHOSTPINK_LEFT,
	ID_GHOSTPINK_RIGHT,
	ID_GHOSTPINK_DOWN,
	ID_GHOSTPINK_UP,
	
	ID_GHOSTORANGE_LEFT,
	ID_GHOSTORANGE_RIGHT,
	ID_GHOSTORANGE_DOWN,
	ID_GHOSTORANGE_UP,
	
	ID_GHOSTFEAR,
	ID_GHOSTFEAR_WHITE,
	
	ID_GHOSTEYE_LEFT,
	ID_GHOSTEYE_RIGHT,
	ID_GHOSTEYE_DOWN,
	ID_GHOSTEYE_UP
	//61
};
enum ID_SONS{
	ID_SOMINICIOJOGO,
	ID_SOMBACKGROUND1,
	ID_SOMBACKGROUND2,
	ID_SOMCOMEPACBIT,
	ID_SOMCOMEPELLET,
	ID_SOMCOMEFRUTA,
	ID_SOMGHOSTFEAR,
	ID_SOMCOMEGHOST,
	ID_SOMPACMANDEATH,
	ID_SOMFIMJOGO,
	//10
};
Sprite imagens[QUANTIDADE_IMAGENS];
char caminhos[QUANTIDADE_IMAGENS][2][TAMANHO_CAMINHO];
char sons[QUANTIDADE_SONS][TAMANHO_CAMINHO];
#include <iostream>
#include <fstream>
using namespace std;
void CarregaCaminhos()
{
//	ifstream arquivo("images/caminhos.txt");
//	string linha;//[2*TAMANHO_TEXTO];
//	int i=0;
////	arquivo.open
//	if(!arquivo.is_open())
//		cout<<"Erro ao abrir arquivo caminhos.txt"<<endl;
//	while(getline(arquivo,linha)
//	{
//		if(i==QUANTIDADE_IMAGENS)
//			break;
//		strcpy(caminhos[i][0],"");
//		strcpy(caminhos[i][1],"");
//		int pos = linha.find(CHAR_DELIMITADOR);
//		int nulo = linha.find('\0');
//		if(pos>=0)
//		{
//			if(pos>0)
//				strcpy(caminhos[i][0],linha.substr(0,pos-1).c_str());//Máscara
//			if(nulo>pos)
//				strcpy(caminhos[i][1],linha.substr(pos+1).c_str());//Bitmap
//		}
//		i++;
//	}
//	arquivo.close();
	strcpy(caminhos[ID_NENHUM][0],			"");
	strcpy(caminhos[ID_NENHUM][1],			"");
	
	strcpy(caminhos[ID_BACKGROUND][0],		"images/pacman_background_mask.bmp");
	strcpy(caminhos[ID_BACKGROUND][1],		"images/pacman_background2.bmp");
	strcpy(caminhos[ID_BACKGROUNDEND][0],	"images/pacman_background_mask.bmp");
	strcpy(caminhos[ID_BACKGROUNDEND][1],	"images/pacman_background_endgame2.bmp");
	
	strcpy(caminhos[ID_TITLESCREEN][0],		"");
	strcpy(caminhos[ID_TITLESCREEN][1],		"");
	
	strcpy(caminhos[ID_CUTSCENE_OPENING][0],"");
	strcpy(caminhos[ID_CUTSCENE_OPENING][1],"");
	strcpy(caminhos[ID_CUTSCENE_ENDING][0],	"");
	strcpy(caminhos[ID_CUTSCENE_ENDING][1],	"");
	
	strcpy(caminhos[ID_CHAR1_IDLE][0],		"");
	strcpy(caminhos[ID_CHAR1_IDLE][0],		"");
	strcpy(caminhos[ID_CHAR1_LEFT][1],		"");
	strcpy(caminhos[ID_CHAR1_LEFT][0],		"");
	strcpy(caminhos[ID_CHAR1_RIGHT][1],		"");
	strcpy(caminhos[ID_CHAR1_RIGHT][1],		"");
	strcpy(caminhos[ID_CHAR1_DOWN][0],		"");
	strcpy(caminhos[ID_CHAR1_DOWN][1],		"");
	strcpy(caminhos[ID_CHAR1_UP][0],		"");
	strcpy(caminhos[ID_CHAR1_UP][1],		"");
	
	strcpy(caminhos[ID_CHAR2_IDLE][0],		"");
	strcpy(caminhos[ID_CHAR2_IDLE][0],		"");
	strcpy(caminhos[ID_CHAR2_LEFT][1],		"");
	strcpy(caminhos[ID_CHAR2_LEFT][0],		"");
	strcpy(caminhos[ID_CHAR2_RIGHT][1],		"");
	strcpy(caminhos[ID_CHAR2_RIGHT][1],		"");
	strcpy(caminhos[ID_CHAR2_DOWN][0],		"");
	strcpy(caminhos[ID_CHAR2_DOWN][1],		"");
	strcpy(caminhos[ID_CHAR2_UP][0],		"");
	strcpy(caminhos[ID_CHAR2_UP][1],		"");
	
	strcpy(caminhos[ID_CHAR3_IDLE][0],		"");
	strcpy(caminhos[ID_CHAR3_IDLE][0],		"");
	strcpy(caminhos[ID_CHAR3_LEFT][1],		"");
	strcpy(caminhos[ID_CHAR3_LEFT][0],		"");
	strcpy(caminhos[ID_CHAR3_RIGHT][1],		"");
	strcpy(caminhos[ID_CHAR3_RIGHT][1],		"");
	strcpy(caminhos[ID_CHAR3_DOWN][0],		"");
	strcpy(caminhos[ID_CHAR3_DOWN][1],		"");
	strcpy(caminhos[ID_CHAR3_UP][0],		"");
	strcpy(caminhos[ID_CHAR3_UP][1],		"");
	
	strcpy(caminhos[ID_CHAR4_IDLE][0],		"");
	strcpy(caminhos[ID_CHAR4_IDLE][0],		"");
	strcpy(caminhos[ID_CHAR4_LEFT][1],		"");
	strcpy(caminhos[ID_CHAR4_LEFT][0],		"");
	strcpy(caminhos[ID_CHAR4_RIGHT][1],		"");
	strcpy(caminhos[ID_CHAR4_RIGHT][1],		"");
	strcpy(caminhos[ID_CHAR4_DOWN][0],		"");
	strcpy(caminhos[ID_CHAR4_DOWN][1],		"");
	strcpy(caminhos[ID_CHAR4_UP][0],		"");
	strcpy(caminhos[ID_CHAR4_UP][1],		"");
	
	strcpy(caminhos[ID_PACMAN_LEFT][0],		"");
	strcpy(caminhos[ID_PACMAN_LEFT][1],		"");
	strcpy(caminhos[ID_PACMAN_RIGHT][0],	"");
	strcpy(caminhos[ID_PACMAN_RIGHT][1],	"");
	strcpy(caminhos[ID_PACMAN_DOWN][0],		"");
	strcpy(caminhos[ID_PACMAN_DOWN][1],		"");
	strcpy(caminhos[ID_PACMAN_UP][0],		"");
	strcpy(caminhos[ID_PACMAN_UP][1],		"");
	strcpy(caminhos[ID_PACMAN_FULL][0],		"");
	strcpy(caminhos[ID_PACMAN_FULL][1],		"");
	
	strcpy(caminhos[ID_PACMAN_FEAR][0],		"");
	strcpy(caminhos[ID_PACMAN_FEAR][1],		"");
	strcpy(caminhos[ID_PACMAN_FEAR_WHITE][0],"");
	strcpy(caminhos[ID_PACMAN_FEAR_WHITE][1],"");
	strcpy(caminhos[ID_PACMAN_DEATH1][0],	"");
	strcpy(caminhos[ID_PACMAN_DEATH1][1],	"");
	strcpy(caminhos[ID_PACMAN_DEATH2][0],	"");
	strcpy(caminhos[ID_PACMAN_DEATH2][1],	"");
	strcpy(caminhos[ID_PACMAN_DEATH3][0],	"");
	strcpy(caminhos[ID_PACMAN_DEATH3][1],	"");
	strcpy(caminhos[ID_PACMAN_DEATH4][0],	"");
	strcpy(caminhos[ID_PACMAN_DEATH4][1],	"");
	
	strcpy(caminhos[ID_PACBIT][0],			"");
	strcpy(caminhos[ID_PACBIT][1],			"");
	strcpy(caminhos[ID_PELLET][0],			"");
	strcpy(caminhos[ID_PELLET][1],"");
	
	strcpy(caminhos[ID_GHOSTRED_LEFT][0],	"");
	strcpy(caminhos[ID_GHOSTRED_LEFT][1],	"");
	strcpy(caminhos[ID_GHOSTRED_RIGHT][0],	"");
	strcpy(caminhos[ID_GHOSTRED_RIGHT][1],	"");
	strcpy(caminhos[ID_GHOSTRED_DOWN][0],	"");
	strcpy(caminhos[ID_GHOSTRED_DOWN][1],	"");
	strcpy(caminhos[ID_GHOSTRED_UP][0],		"");
	strcpy(caminhos[ID_GHOSTRED_UP][1],		"");
	
	strcpy(caminhos[ID_GHOSTBLUE_LEFT][0],	"");
	strcpy(caminhos[ID_GHOSTBLUE_LEFT][1],	"");
	strcpy(caminhos[ID_GHOSTBLUE_RIGHT][0],	"");
	strcpy(caminhos[ID_GHOSTBLUE_RIGHT][1],	"");
	strcpy(caminhos[ID_GHOSTBLUE_DOWN][0],	"");
	strcpy(caminhos[ID_GHOSTBLUE_DOWN][1],	"");
	strcpy(caminhos[ID_GHOSTBLUE_UP][0],	"");
	strcpy(caminhos[ID_GHOSTBLUE_UP][1],	"");
	
	strcpy(caminhos[ID_GHOSTPINK_LEFT][0],	"");
	strcpy(caminhos[ID_GHOSTPINK_LEFT][1],	"");
	strcpy(caminhos[ID_GHOSTPINK_RIGHT][0],	"");
	strcpy(caminhos[ID_GHOSTPINK_RIGHT][1],	"");
	strcpy(caminhos[ID_GHOSTPINK_DOWN][0],	"");
	strcpy(caminhos[ID_GHOSTPINK_DOWN][1],	"");
	strcpy(caminhos[ID_GHOSTPINK_UP][0],	"");
	strcpy(caminhos[ID_GHOSTPINK_UP][1],	"");
	
	strcpy(caminhos[ID_GHOSTORANGE_LEFT][0],"");
	strcpy(caminhos[ID_GHOSTORANGE_LEFT][1],"");
	strcpy(caminhos[ID_GHOSTORANGE_RIGHT][0],"");
	strcpy(caminhos[ID_GHOSTORANGE_RIGHT][1],"");
	strcpy(caminhos[ID_GHOSTORANGE_DOWN][0],"");
	strcpy(caminhos[ID_GHOSTORANGE_DOWN][1],"");
	strcpy(caminhos[ID_GHOSTORANGE_UP][0],	"");
	strcpy(caminhos[ID_GHOSTORANGE_UP][1],	"");
	
	strcpy(caminhos[ID_GHOSTFEAR][0],		"");
	strcpy(caminhos[ID_GHOSTFEAR][1],		"");
	strcpy(caminhos[ID_GHOSTFEAR_WHITE][0],	"");
	strcpy(caminhos[ID_GHOSTFEAR_WHITE][1],	"");
	
	strcpy(caminhos[ID_GHOSTEYE_LEFT][0],	"");
	strcpy(caminhos[ID_GHOSTEYE_LEFT][1],	"");
	strcpy(caminhos[ID_GHOSTEYE_RIGHT][0],	"");
	strcpy(caminhos[ID_GHOSTEYE_RIGHT][1],	"");
	strcpy(caminhos[ID_GHOSTEYE_DOWN][0],	"");
	strcpy(caminhos[ID_GHOSTEYE_DOWN][1],	"");
	strcpy(caminhos[ID_GHOSTEYE_UP][0],		"");
	strcpy(caminhos[ID_GHOSTEYE_UP][1],		"");
}
void LeBMP(char caminho[TAMANHO_CAMINHO], int left, int top, int right, int bottom)
{
	readimagefile(caminho,left,top,right,bottom);
}
void LeBMP(char caminho[TAMANHO_CAMINHO], int largura, int altura)
{
	LeBMP(caminho,0,0,largura-1,altura-1);
}
void CarregaSprites()
{
	//Existe um jeito mais inteligente de se fazer isso, colocando os valores de largura e altura nas linhas do .txt
	
	/*
	Molde para facilitar visualização:
	
	imagens[ID_GHOSTRED_LEFT] =		Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,0			,Tiles(2)	,Tiles(1)-1		,Tiles(3)-1);
	*/
	
	imagens[ID_NENHUM] =  			Sprite(0,0,0,0,caminhos[ID_NENHUM][0],caminhos[ID_NENHUM][1]);
	
	imagens[ID_BACKGROUND] = 		Sprite(LARGURA_FUNDO,ALTURA_FUNDO,caminhos[ID_BACKGROUND][0],caminhos[ID_BACKGROUND][1]);
	imagens[ID_BACKGROUNDEND] = 	Sprite(LARGURA_FUNDO,ALTURA_FUNDO,caminhos[ID_BACKGROUNDEND][0],caminhos[ID_BACKGROUNDEND][1]);
	
	imagens[ID_TITLESCREEN] = 		Sprite(0,0,LARGURA_TELA-1,ALTURA_TELA-1,caminhos[ID_TITLESCREEN][0],caminhos[ID_TITLESCREEN][1]);
	
	imagens[ID_CUTSCENE_OPENING] = 	Sprite(0,0,LARGURA_TELA-1,ALTURA_TELA-1,caminhos[ID_CUTSCENE_OPENING][0],caminhos[ID_CUTSCENE_OPENING][1]);
	imagens[ID_CUTSCENE_ENDING] = 	Sprite(0,0,LARGURA_TELA-1,ALTURA_TELA-1,caminhos[ID_CUTSCENE_ENDING][0],caminhos[ID_CUTSCENE_ENDING][1]);
	
//	imagens[ID_CHAR1_IDLE] = 		Sprite(0,0,15,15,caminhos[ID_CHAR1_IDLE][0],caminhos[ID_CHAR1_IDLE][1]);
//	imagens[ID_CHAR1_LEFT] = 		Sprite(0,0,15,15,caminhos[ID_CHAR1_LEFT][0],caminhos[ID_CHAR1_LEFT][1]);
//	imagens[ID_CHAR1_RIGHT] = 		Sprite(0,0,15,15,caminhos[ID_CHAR1_RIGHT][0],caminhos[ID_CHAR1_RIGHT][1]);
//	imagens[ID_CHAR1_DOWN] = 		Sprite(0,0,15,15,caminhos[ID_CHAR1_DOWN][0],caminhos[ID_CHAR1_DOWN][1]);
//	imagens[ID_CHAR1_UP] = 			Sprite(0,0,15,15,caminhos[ID_CHAR1_UP][0],caminhos[ID_CHAR1_UP][1]);
//	
//	imagens[ID_CHAR2_IDLE] = 		Sprite(0,0,15,15,caminhos[ID_CHAR2_IDLE][0],caminhos[ID_CHAR2_IDLE][1]);
//	imagens[ID_CHAR2_LEFT] = 		Sprite(0,0,15,15,caminhos[ID_CHAR2_LEFT][0],caminhos[ID_CHAR2_LEFT][1]);
//	imagens[ID_CHAR2_RIGHT] = 		Sprite(0,0,15,15,caminhos[ID_CHAR2_RIGHT][0],caminhos[ID_CHAR2_RIGHT][1]);
//	imagens[ID_CHAR2_DOWN] = 		Sprite(0,0,15,15,caminhos[ID_CHAR2_DOWN][0],caminhos[ID_CHAR2_DOWN][1]);
//	imagens[ID_CHAR2_UP] = 			Sprite(0,0,15,15,caminhos[ID_CHAR2_UP][0],caminhos[ID_CHAR2_UP][1]);
//	
//	imagens[ID_CHAR3_IDLE] = 		Sprite(0,0,15,15,caminhos[ID_CHAR3_IDLE][0],caminhos[ID_CHAR3_IDLE][1]);
//	imagens[ID_CHAR3_LEFT] = 		Sprite(0,0,15,15,caminhos[ID_CHAR3_LEFT][0],caminhos[ID_CHAR3_LEFT][1]);
//	imagens[ID_CHAR3_RIGHT] = 		Sprite(0,0,15,15,caminhos[ID_CHAR3_RIGHT][0],caminhos[ID_CHAR3_RIGHT][1]);
//	imagens[ID_CHAR3_DOWN] = 		Sprite(0,0,15,15,caminhos[ID_CHAR3_DOWN][0],caminhos[ID_CHAR3_DOWN][1]);
//	imagens[ID_CHAR3_UP] = 			Sprite(0,0,15,15,caminhos[ID_CHAR3_UP][0],caminhos[ID_CHAR3_UP][1]);
//	
//	imagens[ID_CHAR4_IDLE] = 		Sprite(0,0,15,15,caminhos[ID_CHAR4_IDLE][0],caminhos[ID_CHAR4_IDLE][1]);
//	imagens[ID_CHAR4_LEFT] = 		Sprite(0,0,15,15,caminhos[ID_CHAR4_LEFT][0],caminhos[ID_CHAR4_LEFT][1]);
//	imagens[ID_CHAR4_RIGHT] = 		Sprite(0,0,15,15,caminhos[ID_CHAR4_RIGHT][0],caminhos[ID_CHAR4_RIGHT][1]);
//	imagens[ID_CHAR4_DOWN] = 		Sprite(0,0,15,15,caminhos[ID_CHAR4_DOWN][0],caminhos[ID_CHAR4_DOWN][1]);
//	imagens[ID_CHAR4_UP] = 			Sprite(0,0,15,15,caminhos[ID_CHAR4_UP][0],caminhos[ID_CHAR4_UP][1]);
	
	LeBMP("images/chars/pacman/masks.bmp",Tiles(5),Tiles(2));
	LeBMP("images/chars/pacman/bitmaps.bmp",0,Tiles(2),Tiles(5)-1,Tiles(4)-1);
//	SetPaginaVisual();
	imagens[ID_PACMAN_LEFT] = 		Sprite(0		,0			,Tiles(1)-1	,Tiles(1)-1
									      ,0		,Tiles(2)	,Tiles(1)-1	,Tiles(3)-1);
	imagens[ID_PACMAN_RIGHT] = 		Sprite(Tiles(1)	,0			,Tiles(2)-1	,Tiles(1)-1
									      ,Tiles(1)	,Tiles(2)	,Tiles(2)-1	,Tiles(3)-1);
	imagens[ID_PACMAN_DOWN] = 		Sprite(Tiles(2)	,0			,Tiles(3)-1	,Tiles(1)-1
									      ,Tiles(2)	,Tiles(2)	,Tiles(3)-1	,Tiles(3)-1);
	imagens[ID_PACMAN_UP] = 		Sprite(Tiles(3)	,0			,Tiles(4)-1	,Tiles(1)-1
									      ,Tiles(3)	,Tiles(2)	,Tiles(4)-1	,Tiles(3)-1);
	imagens[ID_PACMAN_FULL] = 		Sprite(Tiles(4)	,0			,Tiles(5)-1	,Tiles(1)-1
									      ,Tiles(4)	,Tiles(2)	,Tiles(5)-1	,Tiles(3)-1);
//	imagens[ID_PACMAN_LEFT] = 		Sprite(0,0,15,15,caminhos[ID_PACMAN_LEFT][0],caminhos[ID_PACMAN_LEFT][1]);
//	imagens[ID_PACMAN_RIGHT] = 		Sprite(0,0,15,15,caminhos[ID_PACMAN_RIGHT][0],caminhos[ID_PACMAN_RIGHT][1]);
//	imagens[ID_PACMAN_DOWN] = 		Sprite(0,0,15,15,caminhos[ID_PACMAN_DOWN][0],caminhos[ID_PACMAN_DOWN][1]);
//	imagens[ID_PACMAN_UP] = 		Sprite(0,0,15,15,caminhos[ID_PACMAN_UP][0],caminhos[ID_PACMAN_UP][1]);
//	imagens[ID_PACMAN_FULL] = 		Sprite(0,0,15,15,caminhos[ID_PACMAN_FULL][0],caminhos[ID_PACMAN_FULL][1]);
	
//	imagens[ID_PACMAN_FEAR] = 		Sprite(0,0,15,15,caminhos[ID_PACMAN_FEAR][0],caminhos[ID_PACMAN_FEAR][1]);
//	imagens[ID_PACMAN_FEAR_WHITE] = Sprite(0,0,15,15,caminhos[ID_PACMAN_FEAR_WHITE][0],caminhos[ID_PACMAN_FEAR_WHITE][1]);
//	imagens[ID_PACMAN_DEATH1] = 	Sprite(0,0,15,15,caminhos[ID_PACMAN_DEATH1][0],caminhos[ID_PACMAN_DEATH1][1]);
//	imagens[ID_PACMAN_DEATH2] = 	Sprite(0,0,15,15,caminhos[ID_PACMAN_DEATH2][0],caminhos[ID_PACMAN_DEATH2][1]);
//	imagens[ID_PACMAN_DEATH3] = 	Sprite(0,0,15,15,caminhos[ID_PACMAN_DEATH3][0],caminhos[ID_PACMAN_DEATH3][1]);
//	imagens[ID_PACMAN_DEATH4] = 	Sprite(0,0,15,15,caminhos[ID_PACMAN_DEATH4][0],caminhos[ID_PACMAN_DEATH4][1]);
	
	LeBMP("images/chars/PacDot_PelletMasks.bmp",Tiles8(2),Tiles8(1));
	LeBMP("images/chars/PacDot_PelletBitmaps.bmp",0,Tiles8(1),Tiles8(2)-1,Tiles8(2)-1);
//	SetPaginaVisual();
	imagens[ID_PELLET] = 			Sprite(0			,0			,Tiles8(1)-1	,Tiles8(1)-1
							   			  ,0			,Tiles8(1)	,Tiles8(1)-1	,Tiles8(2)-1);
	imagens[ID_PACBIT] = 			Sprite(Tiles8(1)	,0			,Tiles8(2)-1	,Tiles8(1)-1
										  ,Tiles8(1)	,Tiles8(1)	,Tiles8(2)-1	,Tiles8(2)-1);
	
	//Para fantasmas, já que eles compartilham da mesma máscara, fica fácil simplesmente desenhar o bitmap de um em cima do bitmap do anterior, assim dá pra usar as mesmas coordenadas
	
	LeBMP("images/chars/ghosts/masks.bmp",Tiles(5),Tiles(2));
	LeBMP("images/chars/ghosts/redghost.bmp",0,Tiles(2),Tiles(4)-1,Tiles(4)-1);
	
	imagens[ID_GHOSTRED_LEFT] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,0			,Tiles(2)	,Tiles(1)-1		,Tiles(3)-1);
	imagens[ID_GHOSTRED_RIGHT] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,Tiles(1)		,Tiles(2)	,Tiles(2)-1		,Tiles(3)-1);
	imagens[ID_GHOSTRED_DOWN] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,Tiles(2)		,Tiles(2)	,Tiles(3)-1		,Tiles(3)-1);
	imagens[ID_GHOSTRED_UP] = 		Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,Tiles(3)		,Tiles(2)	,Tiles(4)-1		,Tiles(3)-1);
	
	LeBMP("images/chars/ghosts/blueghost.bmp",0,Tiles(2),Tiles(4)-1,Tiles(4)-1);
	imagens[ID_GHOSTBLUE_LEFT] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,0			,Tiles(2)	,Tiles(1)-1		,Tiles(3)-1);
	imagens[ID_GHOSTBLUE_RIGHT] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,Tiles(1)		,Tiles(2)	,Tiles(2)-1		,Tiles(3)-1);
	imagens[ID_GHOSTBLUE_DOWN] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,Tiles(2)		,Tiles(2)	,Tiles(3)-1		,Tiles(3)-1);
	imagens[ID_GHOSTBLUE_UP] = 		Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,Tiles(3)		,Tiles(2)	,Tiles(4)-1		,Tiles(3)-1);

	LeBMP("images/chars/ghosts/pinkghost.bmp",0,Tiles(2),Tiles(4)-1,Tiles(4)-1);
	imagens[ID_GHOSTPINK_LEFT] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,0			,Tiles(2)	,Tiles(1)-1		,Tiles(3)-1);
	imagens[ID_GHOSTPINK_RIGHT] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,Tiles(1)		,Tiles(2)	,Tiles(2)-1		,Tiles(3)-1);
	imagens[ID_GHOSTPINK_DOWN] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,Tiles(2)		,Tiles(2)	,Tiles(3)-1		,Tiles(3)-1);
	imagens[ID_GHOSTPINK_UP] = 		Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,Tiles(3)		,Tiles(2)	,Tiles(4)-1		,Tiles(3)-1);

	LeBMP("images/chars/ghosts/orangeghost.bmp",0,Tiles(2),Tiles(4)-1,Tiles(4)-1);
	imagens[ID_GHOSTORANGE_LEFT] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,0			,Tiles(2)	,Tiles(1)-1		,Tiles(3)-1);
	imagens[ID_GHOSTORANGE_RIGHT] = Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,Tiles(1)		,Tiles(2)	,Tiles(2)-1		,Tiles(3)-1);
	imagens[ID_GHOSTORANGE_DOWN] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,Tiles(2)		,Tiles(2)	,Tiles(3)-1		,Tiles(3)-1);
	imagens[ID_GHOSTORANGE_UP] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,Tiles(3)		,Tiles(2)	,Tiles(4)-1		,Tiles(3)-1);
	
	LeBMP("images/chars/ghosts/ghostfear.bmp",0,Tiles(2),Tiles(2)-1,Tiles(4)-1);
	
	imagens[ID_GHOSTFEAR] = 		Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,0			,Tiles(2)	,Tiles(1)-1		,Tiles(3)-1);
	imagens[ID_GHOSTFEAR_WHITE] = 	Sprite(0			,0			,Tiles(1)-1		,Tiles(1)-1
										  ,0			,Tiles(3)	,Tiles(1)-1		,Tiles(4)-1);
//	imagens[ID_GHOSTFEAR] = 		Sprite(0,0,15,15,caminhos[ID_GHOSTFEAR][0],caminhos[ID_GHOSTFEAR][1]);
//	imagens[ID_GHOSTFEAR_WHITE] = 	Sprite(0,0,15,15,caminhos[ID_GHOSTFEAR_WHITE][0],caminhos[ID_GHOSTFEAR_WHITE][1]);
	
	
	LeBMP("images/chars/ghosts/ghosteyes.bmp",Tiles(1),Tiles(2),Tiles(5)-1,Tiles(3)-1);
	
	imagens[ID_GHOSTEYE_LEFT] = 	Sprite(Tiles(1)		,0			,Tiles(2)-1		,Tiles(1)-1
										  ,Tiles(1)		,Tiles(2)	,Tiles(2)-1		,Tiles(3)-1);
	imagens[ID_GHOSTEYE_RIGHT] = 	Sprite(Tiles(2)		,0			,Tiles(3)-1		,Tiles(1)-1
										  ,Tiles(2)		,Tiles(2)	,Tiles(3)-1		,Tiles(3)-1);
	imagens[ID_GHOSTEYE_DOWN] = 	Sprite(Tiles(3)		,0			,Tiles(4)-1		,Tiles(1)-1
										  ,Tiles(3)		,Tiles(2)	,Tiles(4)-1		,Tiles(3)-1);
	imagens[ID_GHOSTEYE_UP] = 		Sprite(Tiles(4)		,0			,Tiles(5)-1		,Tiles(1)-1
										  ,Tiles(4)		,Tiles(2)	,Tiles(5)-1		,Tiles(3)-1);
	
//	imagens[ID_GHOSTEYE_LEFT] = 	Sprite(0,0,15,15,caminhos[ID_GHOSTEYE_LEFT][0],caminhos[ID_GHOSTEYE_LEFT][1]);
//	imagens[ID_GHOSTEYE_RIGHT] = 	Sprite(0,0,15,15,caminhos[ID_GHOSTEYE_RIGHT][0],caminhos[ID_GHOSTEYE_RIGHT][1]);
//	imagens[ID_GHOSTEYE_DOWN] = 	Sprite(0,0,15,15,caminhos[ID_GHOSTEYE_DOWN][0],caminhos[ID_GHOSTEYE_DOWN][1]);
//	imagens[ID_GHOSTEYE_UP] = 		Sprite(0,0,15,15,caminhos[ID_GHOSTEYE_UP][0],caminhos[ID_GHOSTEYE_UP][1]);
}
bool requestsom=false;
void TocaSom(char som[TAMANHO_CAMINHO],bool async=true,bool loop=false,bool nostop=false,bool prioridade=false)
{
	int modos=0;
	if(async)
		modos=modos|SND_ASYNC;
	if(loop)
		modos=modos|SND_LOOP;
	if(nostop)
		modos=modos|SND_NOSTOP;
	if(!requestsom||prioridade)
	{
		requestsom=true;
		PlaySound(som,NULL,modos);
	}
}
void CarregaSons()
{
	strcpy(sons[ID_SOMINICIOJOGO],	"sounds/pacman/pacman_song1.wav");
	strcpy(sons[ID_SOMBACKGROUND1],	"sounds/pacman/pacman_background1.wav");
	strcpy(sons[ID_SOMBACKGROUND2],	"sounds/pacman/pacman_background2.wav");
	strcpy(sons[ID_SOMCOMEPACBIT],	"sounds/pacman/pacman_coinin.wav");
	strcpy(sons[ID_SOMCOMEPELLET],	"sounds/pacman/pacman_power1.wav");
	strcpy(sons[ID_SOMCOMEFRUTA],	"sounds/pacman_eatfruit.wav");
	strcpy(sons[ID_SOMGHOSTFEAR],	"sounds/pacman/pacman_power1.wav");
	strcpy(sons[ID_SOMCOMEGHOST],	"sounds/pacman/pacman_getghost.wav");
	strcpy(sons[ID_SOMPACMANDEATH], "sounds/pacman/pacman_death.wav");
	strcpy(sons[ID_SOMFIMJOGO], 	"sounds/pacman/pacman_song2.wav");
}
void CarregarResources()
{
	CarregaCaminhos();
	CarregaSprites();
	CarregaSons();
}
#endif
