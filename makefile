CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC_DIR = temas
OUT_DIR = bin

EJ := $(word 2, $(MAKECMDGOALS))

SRC = $(wildcard $(SRC_DIR)/$(EJ)/*.cpp)
OUT = $(OUT_DIR)/$(EJ)
run:
	@if [ -z "$(EJ)" ]; then \
		echo "Debes indicar el ejercicio"; \
		echo "Uso: make run <nombre_ejercicio>"; \
		exit 1; \
	fi

	@if [ -z "$(SRC)" ]; then \
		echo "No se encontró ningún .cpp en $(SRC_DIR)/$(EJ)"; \
		exit 1; \
	fi

	@if [ $(words $(SRC)) -gt 1 ]; then \
		echo "Hay más de un .cpp en $(SRC_DIR)/$(EJ)"; \
		exit 1; \
	fi

	@mkdir -p $(OUT_DIR)

	@echo "Compilando $(SRC)..."
	@$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

	@echo "Ejecutando tests..."
	@./$(OUT)

	@rm -f $(OUT)

clean:
	rm -rf $(OUT_DIR)

# Esto evita que make intente ejecutar "00" como target
%:
	@:

.PHONY: run clean
