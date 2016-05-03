#pragma once
#include <iostream>
#include <fstream>

//smelg   000webhost
//prueba
class producto{
  private:
    unsigned product_id_;
    unsigned precio_;
    unsigned valoracion_;
    unsigned n_comparaciones_;
    std::string descripcion_;
  public:
    producto(void);
    producto(char []);
    ~producto(void);

    void cargar_producto(char []);

    unsigned& get_precio(void);
    unsigned& get_id(void);
    bool act_valoracion(unsigned);
    bool act_descripcion(std::string);
};
