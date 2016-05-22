#include "connection.hpp"

ClientConnection::ClientConnection(int s){
    control_socket=s;
    ok=true;
    parar_=false;
}

ClientConnection::~ClientConnection(){
    close(control_socket);
    ok=false;
}

void ClientConnection::stop() {
    close(control_socket);
    parar_ = true;
}

#define COMMAND(cmd) strcmp(command, cmd)==0

void ClientConnection::WaitForRequests(std::vector<cliente>& clientes, catalogo& products){
    if(!ok){
        return;
    }
    
    bool connected=false;
    char buffer[MAX_BUFF];
    
    
    while(!parar_){
        if(recv(control_socket,command,MAX_BUFF,0)==0)
            return;
        std::string comando(command);
        std::stringstream stream(comando);
        std::string aux;
        
        stream>>aux;
        
        if(aux=="CONNECT"){
            stream >> aux;
            for(int i=0; i<clientes.size();i++){
                if(aux==clientes[i].get_name()){
                    stream>>aux;
                    if(aux==clientes[i].get_password()){
                        connected=true;
                        id_user=i;
                        snprintf(buffer,MAX_BUFF,"OK %d", (int)clientes[i].is_admin());
                        if(-1==send(control_socket, buffer, sizeof(buffer), MSG_NOSIGNAL))
                            if(errno==EPIPE)
                                parar_=true;
                        break;
                    }
                }   
            }
            if(!connected){
                snprintf(buffer, MAX_BUFF, "BADLOGIN");
                if(-1==send(control_socket, buffer, sizeof(buffer), MSG_NOSIGNAL))
                    if(errno==EPIPE)
                        parar_=true;
            }
        }
        if(connected){
            if(aux=="SHUTDOWN"){
                parar_=true;
            }
            if(aux=="CHPASS"){
                stream>>aux;
                if(aux==clientes[id_user].get_password()){
                    stream.ignore();
                    std::getline(stream, aux);
                    clientes[id_user].change_passwd(aux);
                }
            }
            if(aux=="CHDIR"){
                stream>>aux;
                if(aux==clientes[id_user].get_password()){
                    stream.ignore();
                    std::getline(stream, aux);
                    clientes[id_user].change_dir(aux);
                }
            }
            if(aux=="GETCAT"){
                memset(buffer, 0, sizeof(buffer));
                snprintf(buffer,MAX_BUFF,"ID del producto               Nombre              Precio");
                send(control_socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
                for (int i = 0; i<products.size(); i++){
                    memset(buffer, 0, sizeof(buffer));
                    snprintf(buffer,MAX_BUFF,"%d                    %s                  %d", products.get_producto_secuencial(i).get_id(),
                    products.get_producto_secuencial(i).get_name().c_str(),
                    products.get_producto_secuencial(i).get_precio());
                    send(control_socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
                }
                memset(buffer, 0, sizeof(buffer));
                snprintf(buffer,MAX_BUFF,"END");
                send(control_socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
            }
            
            if(aux=="ADDCART"){
                stream>>aux;
                int id=stoi(aux,NULL);
                stream>>aux;
                int cantidad=stoi(aux,NULL);
                clientes[id_user].add_item_carrito(id,cantidad);
            }
            if(aux=="RM_CART"){
                clientes[id_user].get_carrito().clear();
            }
            if(aux=="CLOSE"){
                kill(getpid(),SIGINT);
            }
            if (aux == "SHOW_CART"){
                vector<carrito_item> cart = clientes[id_user].get_carrito();
                memset(buffer, 0, sizeof(buffer));
                snprintf(buffer,MAX_BUFF,"ID del producto                       Cantidad");
                send(control_socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
                for (int i = 0; i<cart.size(); i++){
                    memset(buffer, 0, sizeof(buffer));
                    snprintf(buffer,MAX_BUFF,"%d                %d", cart[i].id_producto, cart[i].cantidad);
                    send(control_socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
                }
                memset(buffer, 0, sizeof(buffer));
              //  std::cout << "END" << std::endl;
                snprintf(buffer,MAX_BUFF,"END");
                send(control_socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
                
            }
            if (aux == "SHOW_ORDER"){
                vector<pedidos_item> orders = clientes[id_user].get_pedidos();
                
                for (int i = 0; i<orders.size(); i++){
                    memset(buffer, 0, sizeof(buffer));
                    snprintf(buffer,MAX_BUFF,"Pedido");
                    send(control_socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
                    for (int j = 0 ; j<orders[i].id_producto.size(); j++){
                        memset(buffer, 0, sizeof(buffer));
                        snprintf(buffer, MAX_BUFF, "%d  %d",orders[i].id_producto[j],orders[i].cantidad[j] );
                        send(control_socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
                    }
                }
                memset(buffer, 0, sizeof(buffer));
                snprintf(buffer,MAX_BUFF,"END");
                send(control_socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
            }
            if(aux == "ORDER"){
                std::vector<carrito_item>& aux= clientes[id_user].get_carrito();
                std::vector<int> aux1, aux2;
                for(int i=0; i<aux.size(); i++){
                    aux1.push_back(aux[i].id_producto);
                    aux2.push_back(aux[i].cantidad);
                }
                clientes[id_user].add_pedido(aux1,aux2);
                clientes[id_user].get_carrito().clear();
            }
            if(aux =="RMVPROD"){
                int x;
                stream>>x;
                products.eliminar_producto(x);
            }
            if(aux=="GETPROD"){
                int id;
                stream>>id;
                producto X=products.get_producto(id);
                snprintf(buffer,MAX_BUFF,"%d %d %d %s %s",X.get_precio(),X.get_valoracion_final(),X.get_stock(),X.get_name().c_str(), X.get_descripcion().c_str() );
                send(control_socket, buffer, sizeof(buffer), MSG_NOSIGNAL);
            }
            if(aux=="VAL"){
                int id;
                stream>>id;
                int val;
                stream>>val;
                products.get_producto(id).act_valoracion(val);
            }
            
            if(aux=="ADDPROD"){
                producto aux_prod;
                int id, price, stock;
                std::string name, description;
                stream >> id;
                stream >> price;
                stream >> stock;
                stream >> name;
                stream.ignore();
                std::getline(stream, description);
                aux_prod.get_id() = id;
                aux_prod.get_stock() = stock;
                aux_prod.get_precio() = price;
                aux_prod.act_descripcion(description);
                aux_prod.act_name(name);
                
                //cout << products.size() << std::endl;
                products.agregar_producto(aux_prod);
                //cout << products.size() << std::endl;
            }
            if(aux=="EDITPROD"){
                int election;
                int id, price, stock;
                std::string name, description;
                stream >> election;
                stream >> id;
                stream >> price;
                stream >> stock;
                stream >> name;
                stream.ignore();
                std::getline(stream, description);
                switch(election){
                    case 0:
                        products.get_producto(id).get_stock() = stock;
                        products.get_producto(id).get_precio() = price;
                        products.get_producto(id).act_descripcion(description);
                        products.get_producto(id).act_name(name);
                    break;
                    case 1:
                        //std::cout << "hola" << std::endl;
                        products.get_producto(id).act_name(name);
                    break;
                    case 2:
                        products.get_producto(id).get_precio() = price;
                    break;
                    case 3:
                        products.get_producto(id).get_stock() = stock;
                    break;
                    case 4:
                        products.get_producto(id).act_descripcion(description);
                    break;
                    default:
                    std::cout << "ERROR" << std::endl;
                }
            }
        }   
    }
}

