compiler = g++
options = --std=c++17

all: socket # semShm
	@du *.out --bytes --human-readable
.PHONY: all

socket:
	$(compiler) $(options) -o cliente.out socketCliente.cpp
	$(compiler) $(options) -o servidor.out socketServidor.cpp

# No está compilando. Comentado solo para que no rompa el código comiteado, hay que arreglarlo.
# semShm:
# 	$(compiler) $(options) -lrt -lpthread -o semShmProductor.out semShmProductor.cpp
# 	$(compiler) $(options) -lrt -lpthread -o semShmConsumidor.out semShmConsumidor.cpp
