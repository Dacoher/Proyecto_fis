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
    while (!logged){
        std::cout << "Bienvenido a CriCriCommerce (CCC)" << std::endl;
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
    bool fin_bucle=false;
    if(logged){
        int op;
        int aux;
        char caux[1000];
        
        if (admin){
            while (!fin_bucle){
                memset(buf, 0, sizeof(buf));
                std::cout << "1.Añadir producto\n2.Editar producto\n3.Eliminar producto\n4.Ver producto\n5.Mostrar catálogo\n6.Cambiar de dirección\n7.Cambiar contraseña\n8.Apagar servidor\n9.Cerrar\n-->";
                std::cin >> op;
                std::string saux;
                switch(op){
                    case 1:
                        {
                        int id, price, stock;
                        std::string description;
                        char name[1000];
                        std::cout << "Id producto: ";
                        std::cin >> id;
                        std::cout << "Precio: ";
                        std::cin >> price;
                        std::cout << "Stock: ";
                        std::cin >> stock;
                        std::cout << "Nombre: ";
                        std::cin >> name;
                        std::cin.get();
                        std::cout << "Descripcion: ";
                        std::getline(std::cin, description);
                       
                        snprintf(buf, 1000, "ADDPROD %d %d %d %s %s", id,  price, stock, name, description.c_str());
                        send(handler, buf, sizeof(buf), 0);
                        break;
                        }
                    case 2:
                        {
                        int select = 0;
                        bool control = false;
                        int id, price, stock;
                        std::string description;
                        char name[1000];
                        std::cout << "Id producto: ";
                        std::cin >> id;
                        std::cout << "Desea editar todo el producto? (1/0)" << std::endl;
                        std::cin >> control;
                        if(control){
                            std::cout << "Nombre: ";
                            std::cin >> name;
                            std::cout << "Precio: ";
                            std::cin >> price;
                            std::cout << "Stock: ";
                            std::cin >> stock;
                            std::cin.ignore();
                            std::cout << "Descripcion: ";
                            std::getline(std::cin, description);
                        }
                        else{
                                std::cout << "Elija el campo a modificar: 1.nombre   2.precio    3.stock     4.descripcion " << std::endl;
                                std::cin >> select;
                                if(select == 1){
                                    std::cin.ignore();
                                    std::cout << "Nombre: ";
                                    std::cin >> name;
                                }
                                if(select == 2){
                                    std::cout << "Precio: ";
                                    std::cin >> price;
                                }
                                if(select == 3){
                                    std::cout << "Stock: ";
                                    std::cin >> stock;
                                }
                                if(select == 4){
                                    std::cin.ignore();
                                    std::cout << "Descripcion: ";
                                    std::getline(std::cin, description);
                                }
                        }
                        snprintf(buf, 1000, "EDITPROD %d %d %d %d %s %s", select, id, price, stock, name, description.c_str());
                        send(handler, buf, sizeof(buf), 0);
                        break;
                        }
                        case 3:
                        std::cout << "Id producto: ";
                        std::cin >> aux;
                        snprintf(buf, 1000, "RMVPROD %d", aux);
                        send(handler, buf, sizeof(buf), 0);
                        break;
                    case 4:
                        {
                        int id, price, stock, val;
                        std::string description;
                        char name[1000];
                        std::cout << "Id producto: ";
                        std::cin >> aux;
                        snprintf(buf, 1000, "GETPROD %d", aux);
                        send(handler, buf, sizeof(buf), 0);
                        recv(handler, buf, 1000, 0);
                        std::string comando(buf);
                        std::stringstream stream_dummy(comando);
                        stream_dummy >> price;
                        stream_dummy >> val;
                        stream_dummy >> stock;
                        stream_dummy >> name;
                        std::getline(stream_dummy, description);
                        std::cout << "Nombre: " << name << std::endl;
                        std::cout << "Precio: " << price << std::endl;
                        std::cout << "Valoración: " << val << std::endl;
                        std::cout << "Stock: " << stock << std::endl;
                        std::cout << "Descripcion: " << description << std::endl;
                        }
                        break;
                    case 5:
                        snprintf(buf, 1000, "GETCAT");
                        send(handler, buf, sizeof(buf), 0);
                        while (1){
                            recv(handler, buf, 1000, 0);
                            std::string puf(buf);
                            receive = std::string(buf);
                            std::cout << std::setw(30) << puf << std::endl;
                            if (receive=="END")
                                break;
                        }
                        break;
                    case 6:
                        std::cout << "Nueva dirección: ";
                        std::cin.ignore();
                        std::getline(std::cin, saux);
                        std::cout << "Contraseña: ";
                        std::cin>> caux;
                        snprintf(buf, 1000, "CHDIR %s %s", caux ,saux.c_str());
                        send(handler, buf, sizeof(buf), 0);
                        break;
                    case 7:
                        std::cout << "Nueva contraseña: ";
                        std::cin.ignore();
                        std::getline(std::cin, saux);
                        std::cout << "Contraseña vieja: ";
                        std::cin>> caux;
                        snprintf(buf, 1000, "CHPASS %s %s", caux ,saux.c_str());
                        send(handler, buf, sizeof(buf), 0);
                        break;
                    case 8:
                        snprintf(buf, 1000, "CLOSE");
                        send(handler, buf, sizeof(buf), 0);
                        fin_bucle=true;
                        break;
                    case 9:
                        snprintf(buf, 1000, "SHUTDOWN");
                        send(handler, buf, sizeof(buf), 0);
                        fin_bucle=true;
                        break;
                    default:
                        std::cout << "Opción no válida. Vuelva a intentarlo." << std::endl;
                        break;
                }    
                std::cout << "\nPulse cualquier tecla para continuar." << std::endl;
                std::cin.get();
                std::cin.get();
                system ("clear");
            }
                
                
        }
        else{
            while (!fin_bucle){
                memset(buf, 0, sizeof(buf));
                std::cout << "1.Añadir producto a carrito\n2.Mostrar pedido\n3.Mostrar carrito\n4.Hacer pedido\n5.Borrar carrito\n6.Mostrar catálogo\n7.Cambiar de dirección\n8.Cambiar contraseña\n9.Ver producto\n10. Valorar producto\n11.Cerrar\n-->";
                std::cin >> op;
                std::string saux;
                switch(op){
                    case 1:
                    {
                        int prod, cantidad;
                        std::cin>>prod;
                        std::cin>>cantidad;
                        snprintf(buf,1000,"ADDCART %d %d",prod, cantidad);
                        send(handler, buf, sizeof(buf), 0);
                    }
                    case 2:
                        snprintf(buf, 1000, "SHOW_ORDER");
                        send(handler, buf, sizeof(buf), 0);
                        while (1){
                            recv(handler, buf, 1000, 0);
                            printf("%s", buf);
                            receive = std::string(buf);
                            std::cout<< std::endl;
                            if (receive=="END")
                                break;
                        }
                        break;
                    case 3:
                        snprintf(buf, 1000, "SHOW_CART");
                        send(handler, buf, sizeof(buf), 0);
                        while (1){
                            recv(handler, buf, 1000, 0);
                            printf("%s", buf);
                            receive = std::string(buf);
                            std::cout<< std::endl;
                            if (receive=="END")
                                break;
                        }
                        break;
                    case 4:
                        snprintf(buf, 1000, "ORDER");
                        send(handler, buf, sizeof(buf), 0);
                        break;
                    case 5:
                        snprintf(buf,1000, "RM_CART");
                        send(handler, buf, sizeof(buf), 0);
                        break;
                    case 6:
                        snprintf(buf, 1000, "GETCAT");
                        send(handler, buf, sizeof(buf), 0);
                        while (1){
                            recv(handler, buf, 1000, 0);
                            printf("%s", buf);
                            receive = std::string(buf);
                            std::cout<< std::endl;
                            if (receive=="END")
                                break;
                        }
                        break;
                    case 7:
                        std::cout << "Nueva dirección: ";
                        std::cin.ignore();
                        std::getline(std::cin, saux);
                        std::cout << "Contraseña: ";
                        std::cin>> caux;
                        snprintf(buf, 1000, "CHDIR %s %s", caux ,saux.c_str());
                        send(handler, buf, sizeof(buf), 0);
                        break;
                    case 8:
                        std::cout << "Nueva contraseña: ";
                        std::cin.ignore();
                        std::getline(std::cin, saux);
                        std::cout << "Contraseña vieja: ";
                        std::cin>> caux;
                        snprintf(buf, 1000, "CHDIR %s %s", caux ,saux.c_str());
                        send(handler, buf, sizeof(buf), 0);
                        break;
                    case 9:
                        std::cout << "Id producto: ";
                        std::cin >> aux;
                        snprintf(buf, 1000, "GETPROD %d", aux);
                        send(handler, buf, sizeof(buf), 0);
                        break;
                    case 10:{
                        int id,val;
                        std::cout<<"ID del producto a valorar: ";
                        std::cin>>id;
                        std::cout<<"Valoracion: ";
                        std::cin>>val;
                        snprintf(buf,1000,"VAL %d %d", id, val);
                        send(handler, buf, sizeof(buf), 0);
                        break;
                    }
                    case 11:
                        snprintf(buf, 1000, "SHUTDOWN");
                        send(handler, buf, sizeof(buf), 0);
                        fin_bucle=true;
                        break;
                    default:
                        std::cout << "Opción no válida. Vuelva a intentarlo." << std::endl;
                        break;
                }    
                std::cout << "\nPulse cualquier tecla para continuar." << std::endl;
                std::cin.get();
                std::cin.get();
                system ("clear");
            }    
        }
            
    }
    close(handler);
    shutdown(handler, SHUT_RDWR);
}







