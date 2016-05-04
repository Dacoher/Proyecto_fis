#include <iostream>
#include "producto.hpp"
#include "catalogo.hpp"

int main (void){

  catalogo c;
  producto p("prod.txt");
  c.eliminar_producto(3);

}
