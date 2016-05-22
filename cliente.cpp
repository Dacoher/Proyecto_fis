#include "cliente.hpp"

cliente::cliente(void){
    
}

cliente::cliente(std::ifstream& textfile){
    if(textfile.is_open()){
        textfile>>admin;
        textfile>>id;
        std::getline(textfile,username,':');
        std::getline(textfile, password,':');
        std::getline(textfile, direccion,':');
        while(textfile.peek()!=':'){
            carrito_item aux;
            textfile>>aux.id_producto>>aux.cantidad;
            carrito.push_back(aux);
            textfile.ignore();
        }
        while(textfile.peek()!=';'){
            while(textfile.peek()!=':'){
                pedidos_item aux;
                int aux1, aux2;
                textfile>>aux1>>aux2;
                aux.id_producto.push_back(aux1);
                aux.cantidad.push_back(aux2);
                pedidos.push_back(aux);
            }
            textfile.ignore();
        }
        textfile.ignore();
        while(textfile.peek()==10)
          textfile.ignore();
    }
    else{
        std::cerr<<"Se ha producido un error al leer archivo"<<std::endl;
    }
}


cliente::~cliente(){
    id=0;
    username.clear();
    direccion.clear();
    password.clear();
    pedidos.clear();
    carrito.clear();
}

void cliente::exportar_cliente(ofstream& textfile){
    textfile<<admin<<" "<<id<<username<<":"<<password<<":"<<direccion<<":";
    for(int i=0;i<carrito.size();i++){
        textfile<<carrito[i].id_producto<<" "<<carrito[i].cantidad<<" ";
    }
    textfile<<":";
    for(int i=0;i<pedidos.size();i++){
        for(int j=0; j<pedidos[i].id_producto.size();j++){
            textfile<<pedidos[i].id_producto[j]<<" "<<pedidos[i].cantidad[j];
        }
        textfile<<":";
    }
    textfile<<";";
}

int cliente::get_id(){
    return id;
}

void cliente::set_id(int id){
    this->id=id;
}

std::string cliente::get_password(){
    return password;
}

std::string cliente::get_direccion(){
    return direccion;
}

std::string cliente::get_name(){
    return username;
}

std::vector<pedidos_item>& cliente::get_pedidos(){
    return pedidos;
}

std::vector<carrito_item>& cliente::get_carrito(){
    return carrito;
}

void cliente::change_name(std::string aux){
    username=aux;
}

void cliente::change_dir(std::string aux){
    direccion=aux;
}

void cliente::change_passwd(std::string aux){
    password=aux;
}

void cliente::add_item_carrito(int id_producto, int cantidad){
    carrito_item aux={id_producto, cantidad};
    carrito.push_back(aux);
}

void cliente::add_pedido(std::vector<int> id_producto, std::vector<int> cantidad){
    pedidos_item aux={id_producto, cantidad};
    pedidos.push_back(aux);
}

void cliente::set_admin(bool admin){
    this->admin=admin;
}

bool cliente::is_admin(){
    return admin;
}