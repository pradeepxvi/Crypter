CC = gcc
SRC = src/*.c
CFLAGS = include
OUTPUT = crtpter

.PHONY: build run clean help // avoid conflict with files same named as command

build:
	$(CC) $(SRC) -I$(CFLAGS) -o $(OUTPUT) -lm

run : build
	./$(OUTPUT)

clean:
	rm $(OUTPUT) 

help:
	@echo ""
	@echo "build  -  make build"
	@echo "run    -  make run"
	@echo "clean  -  make clean"
	@echo "help   -  make help"