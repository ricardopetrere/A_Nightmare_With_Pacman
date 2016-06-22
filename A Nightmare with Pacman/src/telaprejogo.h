#ifndef TELAPREJOGO_H
#define TELAPREJOGO_H
#include "telabase.h"

class TelaPreJogo:public TelaBase {
	public:
		//RadioButtons para escolher modo de jogo (cliente ou servidor, talvez também pra singleplayer, singleplayer+IA,splitscreen)
		ElementoGrafico* ptr_elementoselecionado;
		Texto txtModoDeJogo;
		RadioButton rbSinglePlayer;
		RadioButton rbOnlineClient;
		RadioButton rbOnlineServer;
		RadioButton rbCoop;
		Texto txtIP;
		Texto txtPorta;
		Botao btnPortaMais;
		Botao btnPortaMenos;
		
		Botao btnProximo;
		Timer t_inputusuario;
		char buf_porta[TAM_BUF_INT];
		
		TelaPreJogo(int delay)
			:TelaBase(delay)
		{
		}
		TelaPreJogo()
			:TelaPreJogo(DELAY)
		{
		}
		void InitializeComponents()
		{
			setbkcolor(COLOR(20,0,50));
			ptr_elementoselecionado=0x0;
			txtModoDeJogo=Texto("Modo de Jogo:",50,50,GREEN);
			rbSinglePlayer = RadioButton(50,80,15,"Single Player",GREEN);
			rbOnlineClient = RadioButton(50,120,15,"Online (Client)",GREEN);
			rbOnlineServer = RadioButton(50,160,15,"Online (Server)",GREEN);
			rbCoop = RadioButton(50,200,15,"Coop",GREEN);
			txtIP = Texto("IP:",300,50,GREEN,100,50,PLANO);
			txtPorta = Texto("Porta: ",300,200,GREEN);
			btnPortaMais = Botao(500,225,50,20,LIGHTGRAY,"+");
			btnPortaMenos = Botao(500,250,50,20,LIGHTGRAY,"-");
			
			btnProximo=Botao(LARGURA_TELA/3,500,LARGURA_TELA/3,30,LIGHTGRAY,"Próximo");
			t_inputusuario=Timer(100);
		}
		void Loop()
		{
			rbSinglePlayer.Checked=false;
			rbOnlineClient.Checked=false;
			rbOnlineServer.Checked=false;
			rbCoop.Checked=false;
			switch(config.modo_atual)
			{
				case SINGLEPLAYER:
					rbSinglePlayer.Checked=true;
					break;
				case CLIENT:
					rbOnlineClient.Checked=true;
					break;
				case SERVER:
					rbOnlineServer.Checked=true;
					break;
				case COOP:
					rbCoop.Checked=true;
					break;
			}
			if(config.modo_atual!=CLIENT&&strcmp(config.ip,"127.0.0.1")!=0)
				strcpy(config.ip,"127.0.0.1");
			EscreveEmConsole(config.ip);
		}
		void DesenharObjetos()
		{
			txtModoDeJogo.Desenhar();
			rbSinglePlayer.Desenhar();
			rbOnlineClient.Desenhar();
			rbOnlineServer.Desenhar();
			rbCoop.Desenhar();
			btnProximo.Desenhar();
			
			if(config.TemOnline())
			{
				if(config.modo_atual==CLIENT)
				{
					txtIP.Desenhar();
					ExibeTextoPlano(300,80,BLACK,LIGHTGRAY,config.ip);
				}
				txtPorta.Desenhar();
				ExibeTextoPlano(300,225,BLACK,DARKGRAY,itoa(config.porta,buf_porta,10));
				btnPortaMais.Desenhar();
				btnPortaMenos.Desenhar();
				if(ptr_elementoselecionado==&txtIP)
				{
					setcolor(WHITE);
					rectangle(txtIP.x-5,txtIP.y-5,txtIP.Right()+5,txtIP.Bottom()+5);
				}
			}
		}
		void Eventos_Click()
		{
			if(OcorreuClickLButton())
			{
				if(txtIP.CursorEstaEmCima()&&config.modo_atual==CLIENT)
				{
					ptr_elementoselecionado=&txtIP;
				}
				else
					ptr_elementoselecionado=0x0;
				if(rbSinglePlayer.CursorEstaEmCima())
				{
					config.modo_atual=SINGLEPLAYER;
				}
				else if(rbOnlineClient.CursorEstaEmCima())
				{
					config.modo_atual=CLIENT;
				}
				else if(rbOnlineServer.CursorEstaEmCima())
				{
					config.modo_atual=SERVER;
				}
				else if(rbCoop.CursorEstaEmCima())
				{
					config.modo_atual=COOP;
				}
				else if(btnPortaMais.CursorEstaEmCima())
				{
					if(config.porta<USHRT_MAX)
						config.porta++;
				}
				else if(btnPortaMenos.CursorEstaEmCima())
				{
					if(config.porta>0)
						config.porta--;
				}
				else if(btnProximo.CursorEstaEmCima())
				{
					if(config.modo_atual!=NENHUM)
					{
						telamostrando=TELA_PREJOGO2;
						bool conectou=false;
						if(config.modo_atual==CLIENT)
						{
							comm.ClientInit(config.ip,config.porta);
							while(!conectou)
							{
								if(GetAsyncKeyState(VK_ESCAPE)&0x80)
									break;
								if(comm.ConectaServer())
									conectou=true;
								else
								{
									comm.WinSockInit();
									comm.ClientInit(config.ip,config.porta);
									delay(1000);
									cout<<"Tentando novamente...\n";
								}
							}
						}
						else if(config.modo_atual==SERVER)
						{
							cout << "Esperando outro jogador se conectar pela porta "<<config.porta<<"...\n";
							comm.ServerInit(config.porta);
							while(!conectou)
							{
								EscreveEmConsole(GetAsyncKeyState(VK_ESCAPE));
								if(GetAsyncKeyState(VK_ESCAPE))
									break;
								if(comm.AceitaConexaoClient())
									conectou=true;
							}
						}
						else
							conectou=true;
						if(conectou)
						{
							exibindo=false;
						}
					}
				}
			}
			
			fflush(stdin);
			if(!t_inputusuario.CheckTimeout())
				return;
//			//KeyDowns
			char tecla='\0';
			if(kbhit())
				tecla=getch();
			if(tecla!='\0')
			{
				if(ptr_elementoselecionado==&txtIP)
				{
					int n=0;
					if(tecla=='\b')//backspace
					{
						for(n=1;n<=16;n++)
						{
							if(config.ip[n]=='\0')
							{
								config.ip[n-1]='\0';
								break;
							}
						}
					}
					else if(CharIsNumber(tecla)||tecla=='.')
					{
						for(n=0;n<16;n++)
						{
							if(config.ip[n]=='\0')
							{
								config.ip[n]=tecla;
								config.ip[n+1]='\0';//Pra evitar mostrar informação "suja"
								break;
							}
						}
					}
				}
			}
			
//			char tecla;
//			if(PressionouNumeroBackspaceOuPonto(tecla))
//			{
//				if(CharIsNumber(tecla))
//				{
//					
//				}
//				if(tecla=='.')
//				{
//				}
//			}
			t_inputusuario.Start();
			
			if(OcorreuClickESC())
			{
				exibindo=false;
				telamostrando=TELA_INICIAL;
			}
		}
		void OnClosed()
		{
		}
};
#endif
