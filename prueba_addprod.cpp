#include <iostream>
#include "producto.hpp"
#include "catalogo.hpp"
#include <unistd.h>

int main (void){
    
    catalogo c;
    c.create();
    producto aux_prod;
    int id, price, stock;
    std::string name, description;
    std::cout << "id: ";
    std::cin >> id;
    std::cout << "price: ";
    std::cin >> price;
    std::cout << "stock: ";
    std::cin >> stock;
    std::cout << "name: ";
    std::cin >> name;
    std::cout << "descripción: ";
    std::getline(std::cin, description);
    aux_prod.get_id() = id;
    aux_prod.get_stock() = stock;
    aux_prod.get_precio() = price;
    aux_prod.act_descripcion(description);
    aux_prod.act_name(name);
    c.agregar_producto(aux_prod);
    c.save();
    
    
    
}