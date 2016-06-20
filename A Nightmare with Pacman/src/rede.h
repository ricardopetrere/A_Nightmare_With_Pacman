#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define PACKET_MAX_SIZE 1440

// Estrutura com dados relativos a conexão
struct Rede{
	

	// Variáveis
	
	// Identifca o tipo de elemento da rede
	char* clienteOuServidor; 
	
	// Variáveis utilizada pela biblioteca WinSock
	WSADATA wsaData;	
	
	// Socket para o servidor
    SOCKET ListenSocket; 
	
	// Socket para o cliente	
	SOCKET ConnectSocket;  
	
	// Socket para envio de mensagens 
	//(servidor utiliza-o)
	SOCKET AcceptSocket;   
	
	// Endereço do cliente						
	sockaddr_in addrClient;
	
	// Endereço do servidor
	sockaddr_in addrServer;
	
	// Variável que recebe dados enviados pela rede
	char pacote[PACKET_MAX_SIZE]; 

	
	
	// Flags
	bool servidorInit; 	// Indica se o servidor foi inicializado
	
	bool clienteConectado;// Indica se o cliente está 
							//conectado ao servidor
	
	bool clienteInit;		// Indica se o cliente 
							//foi inicializado
	
	bool clienteOk;			//Indica se o cliente está pronto
							// para jogar
		
	bool servOk;			// Indica se o servidor está pronto
							// para jogar

	// Funções
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
//--Adições: Ricardo Petrére
	bool IsCliente();
	bool RecebePacote();
	bool EnviarPacote(char pacote[PACKET_MAX_SIZE]);
	
	//================================================
	/*DICA: segure CTRL e dê um click no nome da função
	para ir, automaticamente, na declaração dela*/
	//================================================
};



//=============================================================
// Inicializa a biblioteca para conexão em rede
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
// Encerra a utilização da biblioteca para conexão em rede
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
        printf("Não foi possível se conectar ao servidor. Erro: %ld\n", WSAGetLastError());
        WSACleanup();
        clienteConectado = false;
    }
	else
		clienteConectado = true;
		
	return clienteConectado;
	
}


// Inicializa o cliente
bool Rede::ClientInit(char *ipServidor,int portaServidor){
	
	// Indica que a struct está configurada no modo cliente
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
    // A estrutura sockaddr_in  especifica o endereço da familia,
    // o endereço IP, e a porta que o socket está se conectando
    addrServer.sin_family = AF_INET;
    addrServer.sin_addr.s_addr = inet_addr( ipServidor );
    addrServer.sin_port = htons(portaServidor);   
	
	
	clienteInit = true;
    return true;   
}

//=========================================================
// Aceite o pedido de conexão e retorna uma nova conexão de soquete
bool Rede::AceitaConexaoClient(){
	
	int len;
	
	// Calcula o tamanho da estrutura SOCKADDR
	len= sizeof(SOCKADDR);
	
	// Aceita a conexão do cliente
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
// Configuração Inicial do Servidor
bool Rede::ServerInit(int portaServidor){
	
	// Indica que a struct rede está sendo usada no modo servidor
	clienteOuServidor = "servidor";
	
	// Limpa o pacote
	strcpy(pacote,"");
	
    //----------------------
    // Cria um socket para ouvir
    // possíveis requisições de conexões
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        servidorInit = false;
        return false;
    }
    //----------------------
    // A estrutura sockaddr_in especifica a familía de endereços
    // o endereço IP, e a porta aonde o socket está sendo utilizado
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
    // Fica escutando possíveis requsições de conexão
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

//-----------------Adições: Ricardo Petrére
//===================================================
//Verifica se a aplicação está como cliente ou servidor
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

