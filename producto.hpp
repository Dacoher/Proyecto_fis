#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//smelg   000webhost

class producto{
  private:
    unsigned product_id_;
    unsigned precio_;
    unsigned valoracion_;
    unsigned n_comparaciones_;
    unsigned stock_;
    std::string descripcion_;
    std::string name_;

  public:
    producto(void);
    producto(char []);
    producto(std::ifstream& textfile);
    ~producto(void);

    void exportar_producto(std::ofstream & textfile);
    unsigned& get_stock();
    unsigned& get_precio(void);
    unsigned& get_id(void);
    unsigned& get_valoracion();
    unsigned get_valoracion_final();
    std::string get_name();
    std::string get_descripcion();
    bool act_valoracion(unsigned);
    bool act_descripcion(std::string);
    bool act_name(std::string);
};

#endif
