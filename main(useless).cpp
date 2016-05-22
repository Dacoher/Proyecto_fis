#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

  unsigned procesar_cadena(std::vector<std::string>&,std::string&);

int main(int argc, char const *argv[]) {

  bool carrito_creado = false;
  bool user_logeado = false;
  bool checking_product = false;
  bool claim_created = false;

  std::string token;
  std::vector<std::string> tokens(5);


  std::cout << "\x1B[2J\x1B[1;1H";
  std::cout << std::setw(8) << " " << "Proyecto FIS. Plataforma de comercio electrónico " << std::endl;

  do{

    procesar_cadena(tokens,token);

    if(tokens[0] == "clear"){
      std::cout << "\x1B[2J\x1B[1;1H";
      std::cout << std::setw(8) << " " << "Proyecto FIS. Plataforma de comercio electrónico " << std::endl;
    }

    if(tokens[0] == "create"){
      if(tokens[1] == "cart"){
        std::cout << "Creando Carrito" << std::endl;
      }
      if(tokens[1] == "claim"){
        std::cout << "Creando reclamacion" << std::endl;
      }
      if(tokens[1] == "comment"){
        std::cout << "Publicando comentario" << std::endl;
      }
    }

    if(tokens[0] == "delete"){
      if(tokens[1] == "cart"){
        std::cout << "Eliminando Carrito" << std::endl;
      }
      if(tokens[1] == "claim"){
        std::cout << "Eliminando Reclamacion" << std::endl;
      }
      if(tokens[1] == "comment"){
        std::cout << "Eliminando Comentario" << std::endl;
      }
      if(tokens[1] == "product"){
        std::cout << "Eliminando Producto" << std::endl;
      }
    }

    if(tokens[0] == "check"){
      if(tokens[1] == "cart"){

      }
      if(tokens[1] == "claim"){

      }
      if(tokens[1] == "product"){

      }
    }

    if(tokens[0] == "list"){

    }

    if((tokens[0] == "log") && (tokens[0] == "in")){

    }

    if(tokens[0] == "add"){

    }

    if(tokens[0] == "back"){

    }

  }while((tokens[0] != "q") && ( tokens[0] != "quit"));
/*
  if(argc = 1){

  }
  else{

  }*/
  return 0;

}


unsigned procesar_cadena(std::vector<std::string> &tokens,std::string &token){

  tokens.clear();

  std::cout << "->  ";
  getline(std::cin,token);
  std::stringstream ss(token);

  token.clear();

  while(getline(ss, token, ' ')) {

      tokens.push_back(token);

  }
}

//Isaac Aiman, Daniel Acosta
