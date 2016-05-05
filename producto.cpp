#include "producto.hpp"

producto::producto():
product_id_(),
precio_(),
valoracion_(),
descripcion_(),
n_comparaciones_(),
stock_(){

}

producto::producto(char nombre_archivo[]):
product_id_(),
precio_(),
valoracion_(),
descripcion_(),
n_comparaciones_(){
    std::ifstream textfile;
    textfile.open(nombre_archivo);
    if(textfile.is_open()){
        textfile>>product_id_>>precio_>>valoracion_>>n_comparaciones_>>stock_;
        std::getline(textfile,name_,':');
        std::getline(textfile, descripcion_,':');
        textfile.ignore();
        while(textfile.peek()==10)
          textfile.ignore();
    }
    else{
        std::cerr<<"Se ha producido un error al leer archivo"<<std::endl;
    }

}

producto::producto(std::ifstream& textfile){
    if(textfile.is_open()){
        textfile>>product_id_>>precio_>>valoracion_>>n_comparaciones_>>stock_;
        std::getline(textfile,name_,':');
        std::getline(textfile, descripcion_,':');
        textfile.ignore();
        while(textfile.peek()==10)
          textfile.ignore();
    }
    else{
        std::cerr<<"Se ha producido un error al leer archivo"<<std::endl;
    }
    std::cout<<product_id_<<" "<<precio_<<" "<<valoracion_<<" "<<n_comparaciones_<<" "<<stock_<<" "<<name_<<":"<<descripcion_<<":"<<std::endl;


}

producto::~producto(void){
  product_id_ = 0;
  precio_ = 0;
  valoracion_ = 0;
  n_comparaciones_ = 0;
  stock_=0;
  descripcion_.clear();
  name_.clear();
}

void producto::exportar_producto(std::ofstream& textfile){
    textfile<<product_id_<<":"<<precio_<<":"<<valoracion_<<":"<<n_comparaciones_<<":"<<stock_<<":"<<name_<<":"<<descripcion_<<":"<<std::endl;
}



unsigned& producto::get_precio(void){
  return precio_;
}

unsigned& producto::get_id(void){
  return product_id_;
}

unsigned& producto::get_valoracion(){
    return valoracion_;
}

unsigned& producto::get_stock(){
    return stock_;
}

std::string producto::get_name(){
    return name_;
}

std::string producto::get_descripcion(){
    return descripcion_;
}

bool producto::act_valoracion(unsigned val){
  unsigned dummy = valoracion_;
  valoracion_ = (valoracion_ + val) / (n_comparaciones_ + 1);

  if(valoracion_ != dummy){
    n_comparaciones_++;
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
  return true;
}

bool producto::act_name(std::string name){
  if(name.empty()){
    std::cout << "Introduzca el nuevo nombre del producto" << std::endl;
    std::cin >> name_;
  }
  else{
    name_ = name;
  }
  return true;
}
