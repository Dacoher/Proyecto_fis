#include "producto.hpp"

producto::producto():
product_id_(),
precio_(),
valoracion_(),
descripcion_(){

}

producto::producto(char nombre_archivo[]):
product_id_(),
precio_(),
valoracion_(),
descripcion_(){

}

producto::~producto(void){
  product_id_ = 0;
  precio_ = 0;
  valoracion_ = 0;
  descripcion_.clear();
}

void producto::cargar_producto(char nombre_archivo[]){
  std::ifstream file;
  unsigned id = 0;
  unsigned price_tag = 0;
  unsigned val_inicial = 0;
  std::string description = "none";

  file.open(nombre_archivo);

  if(file.is_open()){
    file >> (unsigned &) id;
    file.ignore();
    file >> (unsigned &) price_tag;
    file.ignore();
    file >> (unsigned &) val_inicial;
    file.ignore();
    file >> (std::string &) description;
    file.close();
  }
  else{
    std::cout << "Error en la apertura del fichero (no existe)" << std::endl;
  }

  get_id() = id;
  get_precio() = price_tag;
  act_valoracion(val_inicial);
  act_descripcion(description);
}



unsigned& producto::get_precio(void){
  return precio_;
}

unsigned& producto::get_id(void){
  return product_id_;
}

bool producto::act_valoracion(unsigned val){

  unsigned dummy = valoracion_;
  n_comparaciones_++;
  valoracion_ = (valoracion_ + val) / n_comparaciones_;
  if(valoracion_ != dummy){
    return true;
  }
  else{
    return false;
  }
}

bool producto::act_descripcion(std::string descripcion){
  if(descripcion.empty()){
    std::cout << "Introduzca la nueva descripcion del producto" << std::endl;
    std::cin >> descripcion_;
  }
  else{
    descripcion_ = descripcion;
  }
}
