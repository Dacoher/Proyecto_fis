#ifndef CLIENTE_H
#define CLIENTE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

struct carrito_item{
    int id_producto;
    int cantidad;
};

struct pedidos_item{
    std::vector<int> id_producto;
    std::vector<int> cantidad;
};


using namespace std;

class cliente{
    private:
        bool admin;
        int id;
        std::string username;
        std::string direccion;
        std::string password;
        std::vector<pedidos_item> pedidos;
        std::vector<carrito_item> carrito;
    public:
        cliente(void);
        cliente(std::ifstream& textfile);
        ~cliente(void);
        void exportar_cliente(ofstream& textfile);
        int get_id();
        bool is_admin();
        void set_admin(bool);
        std::string get_password();
        std::string get_direccion();
        std::string get_name();
        std::vector<pedidos_item>& get_pedidos();
        std::vector<carrito_item>& get_carrito();
        void set_id(int id);
        void change_name(std::string aux);
        void change_dir(std::string aux);
        void change_passwd(std::string aux);
        void add_item_carrito(int id_producto, int cantidad);
        void add_pedido(std::vector<int> id_producto, std::vector<int> cantidad);
};

#endif