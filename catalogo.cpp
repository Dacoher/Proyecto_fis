#include "catalogo.hpp"



catalogo::catalogo(void){
  file = "catalogo.txt";
  std::cout << file << std::endl;
  std::ifstream catalog;
  catalog.open (file.c_str());
  while (!catalog.eof()){
    producto aux(catalog);
    listado_productos_.push_back(aux);
  }
  catalog.close();
}
catalogo::catalogo(bool n){


}

catalogo::~catalogo(){

  std::ofstream catalog;
  catalog.open("catalogo2.txt");
  if (listado_productos_.size()!=0){
    for (int i = 0; i<listado_productos_.size(); i++){
      listado_productos_[i].exportar_producto(catalog);
    }
  }
  catalog.close();
  //system("rm catalogo.txt");
  //system("mv catalogo2.txt catalogo.txt");

}

bool catalogo::agregar_producto(producto prod) {

  listado_productos_.push_back(prod);
  return true;
}

bool catalogo::eliminar_producto(unsigned n){

  //busqueda del id del producto
for (int i = 0; i<listado_productos_.size(); i++)
  if (listado_productos_[i].get_id()==n){
    listado_productos_.erase (listado_productos_.begin()+i);
    return true;
  }
  return false;
}

unsigned catalogo::chequear_existencias(unsigned n){
  //a que se refiere?? ver el numero de veces que un producto se repite?
  return -1;
}
