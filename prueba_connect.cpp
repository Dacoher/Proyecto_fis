#include <iostream>
#include <thread>
#include <sys/types.h>   // Types used in sys/socket.h and netinet/in.h
#include <netinet/in.h>  // Internet domain address structures and functions
#include <sys/socket.h>  // Structures and functions used for socket API
#include <netdb.h>       // Used for domain/DNS hostname lookup
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include <atomic>
#include <mutex>
#include "string.h"
#include "common.h"
#include <sstream>
#include <iomanip>


 
 
int main (void){
    std::string username;
    std::string password;
    bool logged = false;
    bool admin = false;
    struct sockaddr_in SocketAddress, SocketDestiny;
    int port=2027;
    int handler;
    bool control_bucle_principal = true;

    handler = socket(AF_INET, SOCK_STREAM, 0);
    
    int on=1;
    if(handler<0){
        errexit("No se puede crear el socket: %s\n", strerror(errno));
    }
   
    memset(&SocketAddress, 0, sizeof(SocketAddress));
    SocketAddress.sin_family=AF_INET;
    SocketAddress.sin_addr.s_addr=INADDR_ANY;
    SocketAddress.sin_port=htons(port);
    
    SocketDestiny.sin_family=AF_INET;
    inet_aton("127.0.0.1", &SocketDestiny.sin_addr);
    SocketDestiny.sin_port=htons(2026);
   
    if(bind(handler, (struct sockaddr *)&SocketAddress, sizeof(SocketAddress))<0){
        errexit("No se puede hacer el bind con el puerto: %s\n", strerror(errno));
    }
    
    if (setsockopt(handler, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), &on, sizeof(on)) < 0)
        errexit("Fallo en el option: %s\n", strerror(errno));
   
    if (connect(handler, (struct sockaddr *)&SocketDestiny, sizeof(SocketDestiny)) < 0){
        errexit("No se puede conectar con el servidor.\n", strerror(errno));
    }
    
    
    
   
    char buf[1000];

    std::string receive;
    std::stringstream stream;
    std::string aux;
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";              //<3
        std::cin >> password;
        snprintf(buf, 1000, "CONNECT %s %s", username.c_str(), password.c_str());
        send(handler, buf, sizeof(buf), 0);
        std::cin.get();

        recv(handler, buf, 1000, 0);
        receive = std::string(buf);
        stream.clear();
        stream.str(receive);
        std::getline(stream, aux, ' ');
        if (aux == "OK"){
            std::cout << "Usuario y contraseña correctos" << std::endl;
            logged = true;
            bool dummy;
            stream>>dummy;
            if (dummy)
                admin =true;
        }
        else{
            std::cout << "Usuario y/o contraseña incorrectos" << std::endl;
        }
}