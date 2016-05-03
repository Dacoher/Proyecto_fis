#pragma once
#include <iostream>
#include <vector>
#include "producto.hpp"

class catalogo{
  private:
    unsigned n_productos;
    vector<producto> listado_productos_;
  public:
    catalogo(bool);
    ~catalogo(bool);
    bool agregar_producto(producto);
    bool eliminar_producto(unsigned);
    unsigned chequear_existencias(unsigned);
};
