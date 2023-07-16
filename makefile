compiler = g++
options = --std=c++17
memoriaOut = MemoriaCompartida.hpp.gch
semaforoOut = Semaforo.hpp.gch
socketOut = Socket.hpp.gch

all: memoriaCompartida semaforo socket
.PHONY: all

memoriaCompartida:
	$(compiler) $(options) -lpthread -lrt --shared MemoriaCompartida.hpp -o $(memoriaOut)
	@du $(memoriaOut) --bytes --human-readable

semaforo:
	$(compiler) $(options) -lpthread --shared Semaforo.hpp -o $(semaforoOut)
	@du $(semaforoOut) --bytes --human-readable

socket:
	$(compiler) $(options) --shared Socket.hpp -o $(socketOut)
	@du $(socketOut) --bytes --human-readable

# Clean
.PHONY: clean cleanMemoria cleanSemaforo
clean: cleanMemoria cleanSemaforo
	
cleanMemoria:
	-rm $(memoriaOut)

cleanSemaforo:
	-rm $(semaforoOut)

cleanSocket:
	-rm $(socketOut)
	