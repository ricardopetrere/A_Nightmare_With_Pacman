#ifndef RESOURCES_H
#define RESOURCES_H
#include "sprite.h"
#include <string>
#define QUANTIDADE_IMAGENS 100
#define QUANTIDADE_SONS 20
enum ID_THUMBNAILS{
	ID_THUMB_CHAR1,
	ID_THUMB_CHAR2,
	ID_THUMB_CHAR3,
	ID_THUMB_CHAR4
	//4
};
enum ID_IMAGENSPLAYERS{
	ID_CHAR1_LEFT1,
	ID_CHAR1_LEFT2,
	ID_CHAR1_LEFT3,
	ID_CHAR1_LEFT4,
	ID_CHAR1_RIGHT1,
	ID_CHAR1_RIGHT2,
	ID_CHAR1_RIGHT3,
	ID_CHAR1_RIGHT4,
	
	ID_CHAR2_LEFT1,
	ID_CHAR2_LEFT2,
	ID_CHAR2_LEFT3,
	ID_CHAR2_LEFT4,
	ID_CHAR2_RIGHT1,
	ID_CHAR2_RIGHT2,
	ID_CHAR2_RIGHT3,
	ID_CHAR2_RIGHT4,
	
	ID_CHAR3_LEFT1,
	ID_CHAR3_LEFT2,
	ID_CHAR3_LEFT3,
	ID_CHAR3_LEFT4,
	ID_CHAR3_RIGHT1,
	ID_CHAR3_RIGHT2,
	ID_CHAR3_RIGHT3,
	ID_CHAR3_RIGHT4,
	
	ID_CHAR4_LEFT1,
	ID_CHAR4_LEFT2,
	ID_CHAR4_LEFT3,
	ID_CHAR4_LEFT4,
	ID_CHAR4_RIGHT1,
	ID_CHAR4_RIGHT2,
	ID_CHAR4_RIGHT3,
	ID_CHAR4_RIGHT4
	//32
};

enum ID_IMAGENS{
	ID_NENHUM,
	
	ID_BACKGROUND,
	ID_BACKGROUNDEND,
	
	ID_TITLESCREEN,
	
	ID_CUTSCENE_OPENING,
	ID_CUTSCENE_ENDING,
	
	ID_PACMAN_RIGHT,
	ID_PACMAN_LEFT,
	ID_PACMAN_UP,
	ID_PACMAN_DOWN,
	ID_PACMAN_FULL,
	
	ID_PACMAN_FEAR,
	ID_PACMAN_FEAR_WHITE,
	ID_PACMAN_DEATH1,	
	ID_PACMAN_DEATH2,
	ID_PACMAN_DEATH3,
	ID_PACMAN_DEATH4,
	
	ID_PELLET,
	ID_PACBIT,
	
	ID_GHOSTRED_RIGHT,
	ID_GHOSTRED_LEFT,
	ID_GHOSTRED_UP,
	ID_GHOSTRED_DOWN,
	
	ID_GHOSTBLUE_RIGHT,
	ID_GHOSTBLUE_LEFT,
	ID_GHOSTBLUE_UP,
	ID_GHOSTBLUE_DOWN,
	
	ID_GHOSTPINK_RIGHT,
	ID_GHOSTPINK_LEFT,
	ID_GHOSTPINK_UP,
	ID_GHOSTPINK_DOWN,
	
	ID_GHOSTORANGE_RIGHT,
	ID_GHOSTORANGE_LEFT,
	ID_GHOSTORANGE_UP,
	ID_GHOSTORANGE_DOWN,
	
	ID_GHOSTFEAR,
	ID_GHOSTFEAR_WHITE,
	
	ID_GHOSTEYE_RIGHT,
	ID_GHOSTEYE_LEFT,
	ID_GHOSTEYE_UP,
	ID_GHOSTEYE_DOWN,
	//41
	
	ID_PACMAN_RIGHT2,
	ID_PACMAN_LEFT2,
	ID_PACMAN_UP2,
	ID_PACMAN_DOWN2,
	
	ID_PACMAN_DEATH5,
	ID_PACMAN_DEATH6,
	ID_PACMAN_DEATH7,
	ID_PACMAN_DEATH8,
	ID_PACMAN_DEATH9,
	ID_PACMAN_DEATH10,
	ID_PACMAN_DEATH11,
	
	ID_GHOSTRED_RIGHT2,
	ID_GHOSTRED_LEFT2,
	ID_GHOSTRED_UP2,
	ID_GHOSTRED_DOWN2,
	
	ID_GHOSTBLUE_RIGHT2,
	ID_GHOSTBLUE_LEFT2,
	ID_GHOSTBLUE_UP2,
	ID_GHOSTBLUE_DOWN2,
	
	ID_GHOSTPINK_RIGHT2,
	ID_GHOSTPINK_LEFT2,
	ID_GHOSTPINK_UP2,
	ID_GHOSTPINK_DOWN2,
	
	ID_GHOSTORANGE_RIGHT2,
	ID_GHOSTORANGE_LEFT2,
	ID_GHOSTORANGE_UP2,
	ID_GHOSTORANGE_DOWN2,
	
	ID_GHOSTFEAR2,
	ID_GHOSTFEAR_WHITE2,
	//70
	
	ID_PACMAN_LIVES,
	//71
	ID_BIGPACMAN_RIGHT1,
	ID_BIGPACMAN_RIGHT2,
	ID_BIGPACMAN_FULL
	//74
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
	ID_SOMGHOSTMORTO,
	ID_SOMPACMANDEATH,
	ID_SOMFIMJOGO,
	//11
};
Sprite thumbs[4];
Sprite imagensplayers[32];
Sprite imagens[QUANTIDADE_IMAGENS];
char sons[QUANTIDADE_SONS][TAMANHO_CAMINHO];
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
	int id_mainwindow=getcurrentwindow();
	initwindow(3*LARGURA_FUNDO,ALTURA_FUNDO);
	int id_windowsprites=getcurrentwindow();
	
	int i100=100;//As thumbnails são pra tela de pré-jogo. tem 100px cada
	LeBMP("images/playerthumbnails.bmp",4*i100,2*i100);
	thumbs[ID_THUMB_CHAR1] = 		Sprite(0*i100,0*i100,1*i100-1,1*i100-1
										  ,0*i100,1*i100,1*i100-1,2*i100-1);
	
	thumbs[ID_THUMB_CHAR2] = 		Sprite(1*i100,0*i100,2*i100-1,1*i100-1
										  ,1*i100,1*i100,2*i100-1,2*i100-1);
	
	thumbs[ID_THUMB_CHAR3] = 		Sprite(2*i100,0*i100,3*i100-1,1*i100-1
										  ,2*i100,1*i100,3*i100-1,2*i100-1);
	
	thumbs[ID_THUMB_CHAR4] = 		Sprite(3*i100,0*i100,4*i100-1,1*i100-1
										  ,3*i100,1*i100,4*i100-1,2*i100-1);	
	
	LeBMP("images/background.bmp",3*LARGURA_FUNDO,ALTURA_FUNDO);
	imagens[ID_BACKGROUND] = 		Sprite(0				,0				,LARGURA_FUNDO-1		,ALTURA_FUNDO-1
										  ,LARGURA_FUNDO	,0				,2*LARGURA_FUNDO-1		,ALTURA_FUNDO-1);
	imagens[ID_BACKGROUNDEND] = 	Sprite(0				,0				,LARGURA_FUNDO-1		,ALTURA_FUNDO-1
										  ,2*LARGURA_FUNDO	,0				,3*LARGURA_FUNDO-1		,ALTURA_FUNDO-1);
//	imagens[ID_TITLESCREEN] = 		Sprite(
//	
//	imagens[ID_CUTSCENE_OPENING] = 	Sprite(
//	imagens[ID_CUTSCENE_ENDING] = 	Sprite(
	
	//Char1
	LeBMP("images/players.bmp",Tiles(8),Tiles(8));
	imagensplayers[ID_CHAR1_LEFT1] = Sprite(0,0,0,Tiles(1));
	imagensplayers[ID_CHAR1_LEFT2] = Sprite(Tiles(1),0,Tiles(1),Tiles(1));
	imagensplayers[ID_CHAR1_LEFT3] = Sprite(Tiles(2),0,Tiles(2),Tiles(1));
	imagensplayers[ID_CHAR1_LEFT4] = Sprite(Tiles(3),0,Tiles(3),Tiles(1));
	
	imagensplayers[ID_CHAR1_RIGHT1] = Sprite(Tiles(4),0,Tiles(4),Tiles(1));
	imagensplayers[ID_CHAR1_RIGHT2] = Sprite(Tiles(5),0,Tiles(5),Tiles(1));
	imagensplayers[ID_CHAR1_RIGHT3] = Sprite(Tiles(6),0,Tiles(6),Tiles(1));
	imagensplayers[ID_CHAR1_RIGHT4] = Sprite(Tiles(7),0,Tiles(7),Tiles(1));
	
	//Char2
	imagensplayers[ID_CHAR2_LEFT1] = Sprite(0,Tiles(2),0,Tiles(3));
	imagensplayers[ID_CHAR2_LEFT2] = Sprite(Tiles(1),Tiles(2),Tiles(1),Tiles(3));
	imagensplayers[ID_CHAR2_LEFT3] = Sprite(Tiles(2),Tiles(2),Tiles(2),Tiles(3));
	imagensplayers[ID_CHAR2_LEFT4] = Sprite(Tiles(3),Tiles(2),Tiles(3),Tiles(3));
	                                 
	imagensplayers[ID_CHAR2_RIGHT1] = Sprite(Tiles(4),Tiles(2),Tiles(4),Tiles(3));
	imagensplayers[ID_CHAR2_RIGHT2] = Sprite(Tiles(5),Tiles(2),Tiles(5),Tiles(3));
	imagensplayers[ID_CHAR2_RIGHT3] = Sprite(Tiles(6),Tiles(2),Tiles(6),Tiles(3));
	imagensplayers[ID_CHAR2_RIGHT4] = Sprite(Tiles(7),Tiles(2),Tiles(7),Tiles(3));
	
	//Char3
	imagensplayers[ID_CHAR3_LEFT1] = Sprite(0,Tiles(4),0,Tiles(5));
	imagensplayers[ID_CHAR3_LEFT2] = Sprite(Tiles(1),Tiles(4),Tiles(1),Tiles(5));
	imagensplayers[ID_CHAR3_LEFT3] = Sprite(Tiles(2),Tiles(4),Tiles(2),Tiles(5));
	imagensplayers[ID_CHAR3_LEFT4] = Sprite(Tiles(3),Tiles(4),Tiles(3),Tiles(5));
	                                 
	imagensplayers[ID_CHAR3_RIGHT1] = Sprite(Tiles(4),Tiles(4),Tiles(4),Tiles(5));
	imagensplayers[ID_CHAR3_RIGHT2] = Sprite(Tiles(5),Tiles(4),Tiles(5),Tiles(5));
	imagensplayers[ID_CHAR3_RIGHT3] = Sprite(Tiles(6),Tiles(4),Tiles(6),Tiles(5));
	imagensplayers[ID_CHAR3_RIGHT4] = Sprite(Tiles(7),Tiles(4),Tiles(7),Tiles(5));
	
	//Char4
	imagensplayers[ID_CHAR4_LEFT1] = Sprite(0,Tiles(6),0,Tiles(7));
	imagensplayers[ID_CHAR4_LEFT2] = Sprite(Tiles(1),Tiles(6),Tiles(1),Tiles(7));
	imagensplayers[ID_CHAR4_LEFT3] = Sprite(Tiles(2),Tiles(6),Tiles(2),Tiles(7));
	imagensplayers[ID_CHAR4_LEFT4] = Sprite(Tiles(3),Tiles(6),Tiles(3),Tiles(7));
	                                 
	imagensplayers[ID_CHAR4_RIGHT1] = Sprite(Tiles(4),Tiles(6),Tiles(4),Tiles(7));
	imagensplayers[ID_CHAR4_RIGHT2] = Sprite(Tiles(5),Tiles(6),Tiles(5),Tiles(7));
	imagensplayers[ID_CHAR4_RIGHT3] = Sprite(Tiles(6),Tiles(6),Tiles(6),Tiles(7));
	imagensplayers[ID_CHAR4_RIGHT4] = Sprite(Tiles(7),Tiles(6),Tiles(7),Tiles(7));
	
	LeBMP("images/chars_m.bmp",0,0,LARGURA_FUNDO-1,Tiles(10)-1);
	LeBMP("images/chars_b.bmp",LARGURA_FUNDO,0,2*LARGURA_FUNDO-1,Tiles(10)-1);
	imagens[ID_PACMAN_RIGHT] = 		Sprite(Tiles(1)	,0			);
	imagens[ID_PACMAN_LEFT] = 		Sprite(Tiles(1)	,Tiles(1)	);
	imagens[ID_PACMAN_UP] = 		Sprite(Tiles(1)	,Tiles(2)	);
	imagens[ID_PACMAN_DOWN] = 		Sprite(Tiles(1)	,Tiles(3)	);
	
	imagens[ID_PACMAN_RIGHT2] =		Sprite(0		,0			);
	imagens[ID_PACMAN_LEFT2] = 		Sprite(0		,Tiles(1)	);
	imagens[ID_PACMAN_UP2] = 		Sprite(0		,Tiles(2)	);
	imagens[ID_PACMAN_DOWN2] = 		Sprite(0		,Tiles(3)	);
	
	imagens[ID_PACMAN_FULL] = 		Sprite(Tiles(2)	,0			);
	
	imagens[ID_PACMAN_FEAR] =		Sprite(Tiles(8)	,Tiles(2)	);
	imagens[ID_PACMAN_FEAR_WHITE] = Sprite(Tiles(9)	,Tiles(2)	);
	
	//Animação de morte é composta por: ID_PACMAN_FULL, ID_PACMAN_UP e as abaixo
	imagens[ID_PACMAN_DEATH1] = 	Sprite(Tiles(3)	,0			);
	imagens[ID_PACMAN_DEATH2] = 	Sprite(Tiles(4)	,0			);
	imagens[ID_PACMAN_DEATH3] = 	Sprite(Tiles(5)	,0			);
	imagens[ID_PACMAN_DEATH4] = 	Sprite(Tiles(6)	,0			);
	imagens[ID_PACMAN_DEATH5] = 	Sprite(Tiles(7)	,0			);
	imagens[ID_PACMAN_DEATH6] = 	Sprite(Tiles(8)	,0			);
	imagens[ID_PACMAN_DEATH7] = 	Sprite(Tiles(9)	,0			);
	imagens[ID_PACMAN_DEATH8] = 	Sprite(Tiles(10),0			);
	imagens[ID_PACMAN_DEATH9] = 	Sprite(Tiles(11),0			);
	imagens[ID_PACMAN_DEATH10] = 	Sprite(Tiles(12),0			);
	imagens[ID_PACMAN_DEATH11] = 	Sprite(Tiles(13),0			);
	
	imagens[ID_PACMAN_LIVES] = 		Sprite(Tiles(8)	,Tiles(1)	);
	
	imagens[ID_PELLET] = 			Sprite(Tiles(10),Tiles(3)		,1);
	imagens[ID_PACBIT] = 			Sprite(Tiles(10)+TAMANHO_CELULA	,Tiles(3),1);
	
	imagens[ID_GHOSTRED_RIGHT] = 	Sprite(0		,Tiles(4)	);
	imagens[ID_GHOSTRED_RIGHT2] = 	Sprite(Tiles(1)	,Tiles(4)	);
	imagens[ID_GHOSTRED_LEFT] = 	Sprite(Tiles(2)	,Tiles(4)	);
	imagens[ID_GHOSTRED_LEFT2] = 	Sprite(Tiles(3)	,Tiles(4)	);
	imagens[ID_GHOSTRED_UP] = 		Sprite(Tiles(4)	,Tiles(4)	);
	imagens[ID_GHOSTRED_UP2] = 		Sprite(Tiles(5)	,Tiles(4)	);
	imagens[ID_GHOSTRED_DOWN] = 	Sprite(Tiles(6)	,Tiles(4)	);
	imagens[ID_GHOSTRED_DOWN2] = 	Sprite(Tiles(7)	,Tiles(4)	);

	imagens[ID_GHOSTPINK_RIGHT] = 	Sprite(0		,Tiles(5)	);
	imagens[ID_GHOSTPINK_RIGHT2] = 	Sprite(Tiles(1)	,Tiles(5)	);
	imagens[ID_GHOSTPINK_LEFT] = 	Sprite(Tiles(2)	,Tiles(5)	);
	imagens[ID_GHOSTPINK_LEFT2] = 	Sprite(Tiles(3)	,Tiles(5)	);
	imagens[ID_GHOSTPINK_UP] = 		Sprite(Tiles(4)	,Tiles(5)	);
	imagens[ID_GHOSTPINK_UP2] = 	Sprite(Tiles(5)	,Tiles(5)	);
	imagens[ID_GHOSTPINK_DOWN] = 	Sprite(Tiles(6)	,Tiles(5)	);
	imagens[ID_GHOSTPINK_DOWN2] = 	Sprite(Tiles(7)	,Tiles(5)	);
	
	imagens[ID_GHOSTBLUE_RIGHT] = 	Sprite(0		,Tiles(6)	);
	imagens[ID_GHOSTBLUE_RIGHT2] = 	Sprite(Tiles(1)	,Tiles(6)	);
	imagens[ID_GHOSTBLUE_LEFT] = 	Sprite(Tiles(2)	,Tiles(6)	);
	imagens[ID_GHOSTBLUE_LEFT2] = 	Sprite(Tiles(3)	,Tiles(6)	);
	imagens[ID_GHOSTBLUE_UP] = 		Sprite(Tiles(4)	,Tiles(6)	);
	imagens[ID_GHOSTBLUE_UP2] = 	Sprite(Tiles(5)	,Tiles(6)	);
	imagens[ID_GHOSTBLUE_DOWN] = 	Sprite(Tiles(6)	,Tiles(6)	);
	imagens[ID_GHOSTBLUE_DOWN2] = 	Sprite(Tiles(7)	,Tiles(6)	);

	imagens[ID_GHOSTORANGE_RIGHT] = Sprite(0		,Tiles(7)	);
	imagens[ID_GHOSTORANGE_RIGHT2] =Sprite(Tiles(1)	,Tiles(7)	);
	imagens[ID_GHOSTORANGE_LEFT] = 	Sprite(Tiles(2)	,Tiles(7)	);
	imagens[ID_GHOSTORANGE_LEFT2] = Sprite(Tiles(3)	,Tiles(7)	);
	imagens[ID_GHOSTORANGE_UP] = 	Sprite(Tiles(4)	,Tiles(7)	);
	imagens[ID_GHOSTORANGE_UP2] = 	Sprite(Tiles(5)	,Tiles(7)	);
	imagens[ID_GHOSTORANGE_DOWN] = 	Sprite(Tiles(6)	,Tiles(7)	);
	imagens[ID_GHOSTORANGE_DOWN2] = Sprite(Tiles(7)	,Tiles(7)	);
	
	
	imagens[ID_GHOSTFEAR] = 		Sprite(Tiles(8)	,Tiles(4)	);
	imagens[ID_GHOSTFEAR2] = 		Sprite(Tiles(9)	,Tiles(4)	);
	imagens[ID_GHOSTFEAR_WHITE] = 	Sprite(Tiles(10),Tiles(4)	);
	imagens[ID_GHOSTFEAR_WHITE2] = 	Sprite(Tiles(11),Tiles(4)	);
	
	
	imagens[ID_GHOSTEYE_RIGHT] = 	Sprite(Tiles(8)	,Tiles(5)	);
	imagens[ID_GHOSTEYE_LEFT] = 	Sprite(Tiles(9)	,Tiles(5)	);
	imagens[ID_GHOSTEYE_UP] = 		Sprite(Tiles(10),Tiles(5)	);
	imagens[ID_GHOSTEYE_DOWN] = 	Sprite(Tiles(11),Tiles(5)	);
	
	imagens[ID_BIGPACMAN_RIGHT1] = 	Sprite(Tiles(2)	,Tiles(1)	,4);
	imagens[ID_BIGPACMAN_RIGHT2] = 	Sprite(Tiles(4)	,Tiles(1)	,4);
	imagens[ID_BIGPACMAN_FULL] = 	Sprite(Tiles(6)	,Tiles(1)	,4);
	
	closegraph(id_windowsprites);
	setcurrentwindow(id_mainwindow);
//	VerificaUI();
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
void InterrompeSom()
{
	TocaSom(NULL,false,false,false,true);
}
void CarregaSons()
{
	strcpy(sons[ID_SOMINICIOJOGO],	"sounds/pacman_song1.wav");
	strcpy(sons[ID_SOMBACKGROUND1],	"sounds/pacman_background1.wav");
	strcpy(sons[ID_SOMBACKGROUND2],	"sounds/pacman_background2.wav");
	strcpy(sons[ID_SOMCOMEPACBIT],	"sounds/pacman_coinin.wav");
	strcpy(sons[ID_SOMCOMEPELLET],	"sounds/pacman_power1.wav");
	strcpy(sons[ID_SOMCOMEFRUTA],	"sounds/pacman_eatfruit.wav");
	strcpy(sons[ID_SOMGHOSTFEAR],	"sounds/pacman_power1.wav");
	strcpy(sons[ID_SOMCOMEGHOST],	"sounds/pacman_getghost.wav");
	strcpy(sons[ID_SOMGHOSTMORTO],	"sounds/pacman_alarm1.wav");
	strcpy(sons[ID_SOMPACMANDEATH], "sounds/pacman_death.wav");
	strcpy(sons[ID_SOMFIMJOGO], 	"sounds/pacman_song2.wav");
}
void CarregarResources()
{
	CarregaSprites();
	CarregaSons();
}
#endif
