# Archivos fuente
TASK1_1_SRC = $(SRC_DIR)/task1-1.c
TASK1_2_SRC = $(SRC_DIR)/task1-2.cpp
TASK2_SRC = $(SRC_DIR)/task2_openmp_examples.cpp
TASK3_SRC = $(SRC_DIR)/task3.cpp
TASK4_SRC = $(SRC_DIR)/task4.cpp
TASK5_1_SRC = $(SRC_DIR)/task5-1.cpp
TASK5_2_SRC = $(SRC_DIR)/task5-2.cpp

# Ejecutables
task1-1 = $(BIN_DIR)/task1-1
task1-2 = $(BIN_DIR)/task1-2
task2 = $(BIN_DIR)/task2
task3 = $(BIN_DIR)/task3
task4 = $(BIN_DIR)/task4
task5-1 = $(BIN_DIR)/task5-1


# Reglas principales
all: $(task1-1) $(task1-2) $(task2) $(task3) $(task4) $(task5-1) $(task5-2)

# Regla para Task 1.1: OpenMP pre-training
$(task1-1): $(TASK1_1_SRC)
	g++ -fopenmp -O2 -o task1-1 task1-1.cpp

# Regla para Task 1.2: std::async pre-training
$(task1-2): $(TASK1_2_SRC)
	g++ -fopenmp -O2 -o task1-2 task1-2.cpp

# Regla para Task 2: OpenMP examples
$(task2): $(TASK2_SRC)
	g++ -fopenmp -O2 -o task2 task2.cpp

# Regla para Task 3: Parallelization techniques
$(task3): $(TASK3_SRC)
	g++ -fopenmp -O2 -o task3 task3.cpp

# Regla para Task 4: Race conditions
$(task4): $(TASK4_SRC)
	g++ -fopenmp -O2 -o task4 task4.cpp

# Regla para Task 5: PI Calculation
$(task5-1): $(TASK5_1_SRC)
	g++ -fopenmp -O2 -o task5-1 task5-1.cpp

$(task5-2): $(TASK5_2_SRC)
	g++ -fopenmp -O2 -o task5-2 task5-2.cpp

# Limpieza
clean:
	rm -rf $(BIN_DIR)
