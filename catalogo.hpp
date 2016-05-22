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
    void create (void);
    bool agregar_producto(producto);
    bool eliminar_producto(unsigned);
    unsigned chequear_existencias(unsigned);
    unsigned size(void);
    producto& get_producto(int id);
    producto& get_producto_secuencial(int i);
    void export_to_stream(std::stringstream&);
    void save();
};
