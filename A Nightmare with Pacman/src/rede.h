#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define PACKET_MAX_SIZE 1440

// Estrutura com dados relativos a conex�o
struct Rede{
	

	// Vari�veis
	
	// Identifca o tipo de elemento da rede
	char* clienteOuServidor; 
	
	// Vari�veis utilizada pela biblioteca WinSock
	WSADATA wsaData;	
	
	// Socket para o servidor
    SOCKET ListenSocket; 
	
	// Socket para o cliente	
	SOCKET ConnectSocket;  
	
	// Socket para envio de mensagens 
	//(servidor utiliza-o)
	SOCKET AcceptSocket;   
	
	// Endere�o do cliente						
	sockaddr_in addrClient;
	
	// Endere�o do servidor
	sockaddr_in addrServer;
	
	// Vari�vel que recebe dados enviados pela rede
	char pacote[PACKET_MAX_SIZE]; 

	
	
	// Flags
	bool servidorInit; 	// Indica se o servidor foi inicializado
	
	bool clienteConectado;// Indica se o cliente est� 
							//conectado ao servidor
	
	bool clienteInit;		// Indica se o cliente 
							//foi inicializado
	
	bool clienteOk;			//Indica se o cliente est� pronto
							// para jogar
		
	bool servOk;			// Indica se o servidor est� pronto
							// para jogar

	// Fun��es
	bool WinSockInit();
	void EncerraWinSock();
	void FlagsInit();
	bool ServerInit(int portaServidor);
	bool ClientInit(char *ipServidor,int portaServidor);
	bool RecebeDoClient();
	bool EnviaParaOClient(char pacote[PACKET_MAX_SIZE]);
	bool EnviaParaOServer(char pacote[PACKET_MAX_SIZE]);
	bool RecebeDoServer();
	bool AceitaConexaoClient();
	bool ConectaServer();
	bool FechaConexaoClient();
	void FechaSocketClient();
	void FechaSocketServer();
//--Adi��es: Ricardo Petr�re
	bool IsCliente();
	bool RecebePacote();
	bool EnviarPacote(char pacote[PACKET_MAX_SIZE]);
	
	//================================================
	/*DICA: segure CTRL e d� um click no nome da fun��o
	para ir, automaticamente, na declara��o dela*/
	//================================================
};



//=============================================================
// Inicializa a biblioteca para conex�o em rede
bool Rede::WinSockInit(){
    int iResult;
    
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %ld\n", iResult);
        return false;
    }
    return true;
}


//============================================================
// Encerra a utiliza��o da biblioteca para conex�o em rede
void Rede::EncerraWinSock(){
	WSACleanup();
}

//==============================================================
// Inicializa as flags
void Rede::FlagsInit(){
	servidorInit = false;
	clienteInit = false;
	clienteConectado = false;
	clienteOk = false;
	servOk = false;
}


//===============================================================================
// Envia um pacote para o server
bool Rede::EnviaParaOServer(char pacote[PACKET_MAX_SIZE]){
	
	int bytesEnviados;
	
	bytesEnviados = send(ConnectSocket ,pacote,strlen(pacote),0);
	
	if(bytesEnviados != SOCKET_ERROR && bytesEnviados != 0 )
		return true;
	else
		return false;
}


//==============================================================================
// Envia um pacote para o cliente
bool Rede::EnviaParaOClient(char pacote[PACKET_MAX_SIZE]){
	
	int bytesEnviados;
	
	bytesEnviados = send(AcceptSocket,pacote,strlen(pacote),0);

	if(bytesEnviados != SOCKET_ERROR && bytesEnviados != 0 )
		return true;
	else
		return false;
}


// Conecta-se ao servidor
bool Rede::ConectaServer(){

	int iResult;

	iResult = connect( ConnectSocket, (SOCKADDR*) &addrServer, sizeof(addrServer) );
    
	if ( iResult == SOCKET_ERROR) {
        closesocket (ConnectSocket);
        printf("N�o foi poss�vel se conectar ao servidor. Erro: %ld\n", WSAGetLastError());
        WSACleanup();
        clienteConectado = false;
    }
	else
		clienteConectado = true;
		
	return clienteConectado;
	
}


// Inicializa o cliente
bool Rede::ClientInit(char *ipServidor,int portaServidor){
	
	// Indica que a struct est� configurada no modo cliente
	clienteOuServidor = "cliente";
	
	// Limpa o pacote
	strcpy(pacote,"");
	
    //----------------------
    // Cria um socket para se conectar ao servidor
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
       	WSACleanup();
        clienteInit = false;
        return false;
    }
    
    //----------------------
    // A estrutura sockaddr_in  especifica o endere�o da familia,
    // o endere�o IP, e a porta que o socket est� se conectando
    addrServer.sin_family = AF_INET;
    addrServer.sin_addr.s_addr = inet_addr( ipServidor );
    addrServer.sin_port = htons(portaServidor);   
	
	
	clienteInit = true;
    return true;   
}

//=========================================================
// Aceite o pedido de conex�o e retorna uma nova conex�o de soquete
bool Rede::AceitaConexaoClient(){
	
	int len;
	
	// Calcula o tamanho da estrutura SOCKADDR
	len= sizeof(SOCKADDR);
	
	// Aceita a conex�o do cliente
	AcceptSocket=accept(ListenSocket,(SOCKADDR*)&addrClient,&len);
	
		
	if(AcceptSocket  == INVALID_SOCKET)
		clienteConectado = false;
	else
		clienteConectado = true;
	
	return clienteConectado;
}


//================================================
//Fecha o socket para comunicacao com o client
bool Rede::FechaConexaoClient(){
	closesocket(AcceptSocket);
}


//========================================================
// Configura��o Inicial do Servidor
bool Rede::ServerInit(int portaServidor){
	
	// Indica que a struct rede est� sendo usada no modo servidor
	clienteOuServidor = "servidor";
	
	// Limpa o pacote
	strcpy(pacote,"");
	
    //----------------------
    // Cria um socket para ouvir
    // poss�veis requisi��es de conex�es
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        servidorInit = false;
        return false;
    }
    //----------------------
    // A estrutura sockaddr_in especifica a famil�a de endere�os
    // o endere�o IP, e a porta aonde o socket est� sendo utilizado
    addrServer.sin_family = AF_INET;
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY); 
    addrServer.sin_port = htons(portaServidor);


	// Vincula o socket
    if (bind(ListenSocket,(SOCKADDR *) & addrServer, sizeof (addrServer)) == SOCKET_ERROR) {
        wprintf(L"bind failed with error: %ld\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        servidorInit = false;
        return false;
    }


	//----------------------
    // Fica escutando poss�veis requsi��es de conex�o
    // no socket criado
    if (listen(ListenSocket, 1) == SOCKET_ERROR) {
        wprintf(L"listen failed with error: %ld\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        servidorInit = false;
        return false;
    }
	
	// Se chegou aqui, o servidor foi inicializado corretamente
	servidorInit = true;	
	return true;
}

//===================================================
// Recebe dados do cliente
bool Rede::RecebeDoClient(){
	
	int bytesRecebi;
	
	// Recebe e quantifica bytes recebidos
	bytesRecebi =recv(AcceptSocket ,pacote,PACKET_MAX_SIZE,0);
	
	// Acresenta o caracter de "fim de string"
	pacote[bytesRecebi] = '\0';
	
	//std::cout <<"BytesRecebi =" << bytesRecebi;
	
	if(bytesRecebi != 0 && bytesRecebi != SOCKET_ERROR)
		return true;
	else
		return false;
}

//===================================================
// Recebe dados do servidor
bool Rede::RecebeDoServer(){
	
	int bytesRecebi;
	
	// Recebe e quantifica bytes recebidos
	bytesRecebi =recv(ConnectSocket ,pacote,PACKET_MAX_SIZE,0);
	
	// Acresenta o caracter de "fim de string"
	pacote[bytesRecebi] = '\0';
		
	if(bytesRecebi != 0 && bytesRecebi != SOCKET_ERROR)
		return true;
	else
		return false;
}
//====================================================
// Fecha o socket do cliente
void Rede::FechaSocketClient(){
	closesocket(ConnectSocket);
}

//===================================================
// Fecha o socket do server
void Rede::FechaSocketServer(){
	closesocket(ListenSocket);
}

//-----------------Adi��es: Ricardo Petr�re
//===================================================
//Verifica se a aplica��o est� como cliente ou servidor
bool Rede::IsCliente()
{
	return strcmp(clienteOuServidor,"cliente")==0;
}

bool Rede::RecebePacote()
{
	if(IsCliente())
		return RecebeDoServer();
	else
		return RecebeDoClient();
}

bool Rede::EnviarPacote(char pacote[PACKET_MAX_SIZE])
{
	if(IsCliente())
		return EnviaParaOServer(pacote);
	else
		return EnviaParaOClient(pacote);
}

