#pragma once
#include <iostream>
#include <vector>
#include "producto.hpp"

class catalogo{
  private:
    unsigned n_productos;
    std::vector<producto> listado_productos_;
    std::string file;
  public:
    catalogo(bool n);
    catalogo (void);
    ~catalogo();
    bool agregar_producto(producto);
    bool eliminar_producto(unsigned);
    unsigned chequear_existencias(unsigned);
};
