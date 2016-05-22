#include <iostream>
#include "producto.hpp"
#include "catalogo.hpp"
#include <thread>
#include <sys/types.h>   // Types used in sys/socket.h and netinet/in.h
#include <netinet/in.h>  // Internet domain address structures and functions
#include <sys/socket.h>  // Structures and functions used for socket API
#include <netdb.h>       // Used for domain/DNS hostname lookup
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <atomic>
#include <mutex>
#include "cliente.hpp"
#include "catalogo.hpp"
#include "string.h"
#include "common.h"
#include <signal.h>
#include "connection.hpp"

std::atomic<bool> parar (false);
catalogo products;
std::vector<cliente> clientes;
int n_clientes, handler;

#define COMMAND(cmd) strcmp(command, cmd)==0


void* run_client_connection(void *c){
    int sock=*(int*)c;
    bool parar_hilo=false;
    
    ClientConnection *connection = (ClientConnection *)c;
    connection->WaitForRequests( clientes, products);
    connection->stop();
  
    return NULL;
}

void guardar_clientes();

void sighandler(int signal, siginfo_t *info, void *ptr) {
    char algo[100];
    shutdown(handler, SHUT_WR);
    while(recv(handler,algo, 100, 0)>0){
        recv(handler,algo, 100, 0);
    }
    
    shutdown(handler, SHUT_RD);
    close(handler);
    
    guardar_clientes();
    products.save();
    
    exit(-1);
}


void crear_clientes(){
    std::ifstream file;
    file.open ("clientes.txt");
    n_clientes=0;
    while (!file.eof()){
        cliente aux(file);
        clientes.push_back(aux);
        n_clientes++;
    }
    file.close();
    
}

void guardar_clientes(){
    std::ofstream aux;
    aux.open("clientes2.txt");
    if (clientes.size()!=0){
        for (int i = 0; i<clientes.size(); i++){
            clientes[i].exportar_cliente(aux);
            aux<<std::endl;
        }
    }
    aux.close();
    system("rm clientes.txt");
    system("mv clientes2.txt clientes.txt");
}


int main (void){
    
    struct sigaction action;
    action.sa_sigaction = sighandler;
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &action , NULL);
    
    
    crear_clientes();
    products.create();
    struct sockaddr_in SocketAddress;
    int port=2026;
    
    handler = socket(AF_INET, SOCK_STREAM, 0);
    if(handler<0){
        errexit("No se puede crear el socket: %s\n", strerror(errno));
    }
   
    memset(&SocketAddress, 0, sizeof(SocketAddress));
    SocketAddress.sin_family=AF_INET;
    SocketAddress.sin_addr.s_addr=INADDR_ANY;
    SocketAddress.sin_port=htons(port);
   
    if(bind(handler, (struct sockaddr *)&SocketAddress, sizeof(SocketAddress))<0){
        errexit("No se puede hacer el bind con el puerto: %s\n", strerror(errno));
    }
    
    int on = 1;
    if (setsockopt(handler, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), &on, sizeof(on)) < 0)
        errexit("Fallo en el option: %s\n", strerror(errno));
        
    if(listen(handler, 5)<0){
        errexit("Fallo en el listen: %s\n", strerror(errno));
    }
    struct sockaddr_in fsin;
    int ssock;
    socklen_t alen=sizeof(fsin);
    
    
    while (!parar) {
        pthread_t thread;
        
        ssock = accept(handler, (struct sockaddr *)&fsin, &alen);
        if(ssock < 0)
            errexit("Fallo en el accept: %s\n", strerror(errno));
           
        ClientConnection *connection = new ClientConnection(ssock);
	
	    
	    pthread_create(&thread, NULL, run_client_connection, (void*)connection);
    }
    shutdown(handler, SHUT_RDWR);
    close(handler);
    
}