CC = gcc
FLAGS = flags
SRC = src/*.c
OUTPUT = crypter

.PHONY: build run clean help

build:
	$(CC) $(SRC) -I$(FLAGS) -o $(OUTPUT) -lm
run:build
	./$(OUTPUT)
clean:
	rm $(OUTPUT)
help:
	@echo ""
	@echo "build  -  make build"
	@echo "run    -  make run"
	@echo "clean  -  make clean"
	@echo "help   -  make help"