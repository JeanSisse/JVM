all: build clean

build: leitor.o exibidor.o interface.o decoder.o instructions.o main.o
	@echo "Criando executavel...Pronto!"
	@gcc leitor.o exibidor.o interface.o main.o instructions.o -ansi -std=c99 -lcunit -o jvm -Wall -g -lm

main.o: main.c
	@echo "Compilando..."
	@gcc -c -ansi -Wall -std=c99 main.c -lcunit -g

instructions.o: instructions.c
	@gcc -c -ansi -Wall -std=c99 instructions.c -lcunit -g

decoder.o: decoder.c
	@gcc -c -ansi -Wall -std=c99 decoder.c -lcunit -g

leitor.o: leitor.c
	@gcc -c -ansi -Wall -std=c99 leitor.c -lcunit -g

exibidor.o: exibidor.c
	@gcc -c -ansi -Wall -std=c99 exibidor.c -lcunit -g

interface.o: interface.c
	@gcc -c -ansi -Wall -std=c99 interface.c -lcunit -g

clean:
	@rm *.o