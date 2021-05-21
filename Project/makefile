
# Name of the project
PROJ_NAME=TOP_GRASP_TS_PR

# wildcard pega todos os arquivos com .cpp
CPP_SOURCE=$(wildcard *.cpp)

# wildcard pega todos os arquivos com .h
H_SOURCE=$(wildcard *.h)

# É copiado todos os nomes da variável C_SOURCE para OBJ,
# mas com a substituição da extensão .cpp para .o. 
# Fazemos isso pois inicialmente os arquivos-objeto não existem,
# então a função wildcard seria ineficiente nesse caso.
OBJ=$(CPP_SOURCE:.cpp=.o)

# Compiler
CC=g++

# Flags for compiler
CC_FLAGS=-c -W -Wall

all:$(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
#	@ echo "CPP $(CPP_SOURCE)"
#	@ echo "H $(H_SOURCE)"
#	@ echo "OBJ $(OBJ)"
	$(CC) -o $@ $^
	
# o simbolo '%' pega o nome do arquivo
# $@ pega o nome o target
# $< pega o nome do pré-requisito 
%.o: %.cpp %.h
	$(CC) -o $@ $< $(CC_FLAGS)

# Esse é caso especial para main.c
main.o: main.cpp $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

clean:
	rm -rf *.o $(PROJ_NAME) *~
