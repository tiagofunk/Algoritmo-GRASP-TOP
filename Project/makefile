
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

#INSTANCE=../instances/set_7_3/p7.3.t.txt
#PROGRAM_ARGS=--alpha 0.98 --iterations 4506 --path y --margin 1.42 --removeOperator w --removePercentage 0.56 --shuffleOperator e --addOperator b

# SEED=2143751518
INSTANCE=../instances/set_5_3/p5.3.v.txt
# PROGRAM_ARGS=--alpha 0.58 --iterations 2398 --path y --margin 0.78 --removeOperator w --removePercentage 0.17 --shuffleOperator e --addOperator b

# SEED=347357786
# INSTANCE=../instances/set_4_4/p4.4.l.txt
# PROGRAM_ARGS=--alpha 0.79 --iterations 2031 --path n --margin 1.11 --removeOperator w --removePercentage 0.39 --shuffleOperator e --addOperator b

# SEED=241161500
# INSTANCE=../instances/set_4_4/p4.4.l.txt
# PROGRAM_ARGS=--alpha 0.55 --iterations 3471 --path n --margin 0.97 --removeOperator w --removePercentage 0.21 --shuffleOperator e --addOperator r

SEED=1011742676
#INSTANCE=../instances/set_1_2/p1.2.h.txt
PROGRAM_ARGS=--alpha 0.9 --iterations 4500 --path y --margin 1.9 --removeOperator r --removePercentage 0.15 --shuffleOperator e --addOperator b


all: $(PROJ_NAME) run

build: clean $(PROJ_NAME)

test: clean_main $(PROJ_NAME) run_test

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^
	
# o simbolo '%' pega o nome do arquivo
# $@ pega o nome o target
# $< pega o nome do pré-requisito 
%.o: %.cpp %.h
	$(CC) -o $@ $< $(CC_FLAGS)

# Esse é caso especial para main.c
#main.o: main.cpp $(H_SOURCE)
#	$(CC) -o $@ $< $(CC_FLAGS)

clean_main:
	rm main.o

clean:
	rm -rf *.o $(PROJ_NAME) *~

run_test:
	./$(PROJ_NAME)

run:
	./$(PROJ_NAME) 1 1 $(SEED) $(INSTANCE) $(PROGRAM_ARGS)
