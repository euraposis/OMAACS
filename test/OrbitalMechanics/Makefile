
C_COMPILER =clang

UNITY_ROOT=../../Unity/src
OMAACS_ORBITAL_MECHANICS_ROOT=../src/OrbitalMechanics
OMAACS_NUMERICS_ROOT=../../libs/OMAACS_NUM/OMAACS_NUM/src

C_FLAGS=-std=c17
C_FLAGS += -Wall
C_FLAGS += -Wextra
C_FLAGS += -Wpointer-arith
C_FLAGS += -Wcast-align
C_FLAGS += -Wwrite-strings
C_FLAGS += -Wswitch-default
C_FLAGS += -Wunreachable-code
C_FLAGS += -Winit-self
C_FLAGS += -Wmissing-field-initializers
C_FLAGS += -Wno-unknown-pragmas
C_FLAGS += -Wstrict-prototypes
C_FLAGS += -Wundef
C_FLAGS += -Wold-style-definition

TARGET_BASE=test_orbital_mechanics
TARGET1 = $(TARGET_BASE).out
SRC_FILES1=$(TARGET_BASE).c $(UNITY_ROOT)/unity.c
INC_DIRS=-I. -I.. -I$(UNITY_ROOT) -I$(OMAACS_GEOMETRY_ROOT)  -I$(OMAACS_ORBITAL_MECHANICS_ROOT)
UNITY_INCLUDE_CONFIG = -D UNITY_INCLUDE_CONFIG_H
LINKER_FLAGS=-lm

BIN_DIR=../build

all: name_test clean build run

name_test:
	@echo "\nRunning $(TARGET_BASE) Test\n"

clean:
	@rm -f $(BIN_DIR)/$(TARGET1)

build:
#check if BIN_DIR exists, if not create it
	@mkdir -p $(BIN_DIR)
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SRC_FILES1) $(UNITY_INCLUDE_CONFIG) $(LINKER_FLAGS) -o $(BIN_DIR)/$(TARGET1) 

run:
	@$(BIN_DIR)/$(TARGET1)