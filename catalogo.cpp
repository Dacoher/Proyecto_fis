#include "catalogo.hpp"



catalogo::catalogo(void){
  
}


void catalogo::create(void){
  file = "catalogo.txt";
  std::ifstream catalog;
  catalog.open (file.c_str());
  n_productos=0;
  while (!catalog.eof()){
    producto aux(catalog);
    listado_productos_.push_back(aux);
    n_productos++;
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
  system("rm catalogo.txt");
  system("mv catalogo2.txt catalogo.txt");

}

void catalogo::save(){
  std::ofstream catalog;
  catalog.open("catalogo2.txt");
  if (listado_productos_.size()!=0){
    for (int i = 0; i<listado_productos_.size(); i++){
      listado_productos_[i].exportar_producto(catalog);
    }
  }
  catalog.close();
  system("rm catalogo.txt");
  system("mv catalogo2.txt catalogo.txt");
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
 //devuelve el stock, del producto, en caso de no existir (devuleve -1)
  for (int i = 0; i<listado_productos_.size(); i++)
    if (listado_productos_[i].get_id()==n)
      return listado_productos_[i].get_stock();
  return -1;
}

unsigned catalogo::size(void){
  return listado_productos_.size();
}

void catalogo::export_to_stream(std::stringstream &stream){
  std::string algo;
  
  for(int i = 0; i < listado_productos_.size(); i++){
    std::string aux;
    std::ostringstream convert;
    convert << listado_productos_[i].get_precio();
    aux = convert.str();
    algo = listado_productos_[i].get_name() + ":" + aux;
    stream << algo;
  }
}

producto& catalogo::get_producto(int id){
  for(int i=0; i<listado_productos_.size();i++){
    if(listado_productos_[i].get_id()==id){
      return listado_productos_[i];
    }
  }
}

producto& catalogo::get_producto_secuencial(int i){
  return listado_productos_[i];
}