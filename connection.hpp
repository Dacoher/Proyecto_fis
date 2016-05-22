#if !defined ClientConnection_H
#define ClientConnection_H

#include <pthread.h>
#include <unistd.h>

#include <iomanip>
#include <cstdio>
#include <cstdint>
#include <sys/socket.h>
#include <string>
#include <sstream>
#include <cstring>
#include <iostream>
#include "cliente.hpp"
#include "catalogo.hpp"
#include <vector>
#include <signal.h>

const int MAX_BUFF=1000;

class ClientConnection {
public:
    ClientConnection(int s);
    ~ClientConnection();
    
    void WaitForRequests(std::vector<cliente>& clientes, catalogo& products);
    void stop();

    
private:  
    bool ok;  
   
    
    char command[MAX_BUFF];  // Buffer for saving the command.
    
    int control_socket;      // Control socket descriptor;
    
    bool parar_;
    
    int id_user;
};

#endif