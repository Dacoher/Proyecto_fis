
all: Server_Demon Cliente_Demon


Server_Demon: Server_Demon.cpp connection.cpp catalogo.cpp cliente.cpp producto.cpp
	g++ -g -std=c++11  Server_Demon.cpp connection.cpp catalogo.cpp producto.cpp cliente.cpp -o Server_Demon -lpthread

Cliente_Demon: Cliente_Demon.cpp
	g++ -g -std=c++11  Cliente_Demon.cpp -o Cliente_Demon -lpthread


clean:
	$(RM) Server_Demon *~
