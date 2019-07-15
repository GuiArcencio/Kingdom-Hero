buttonqueue.o: buttonqueue.c ./header/buttonqueue.h
	gcc -c buttonqueue.c -o buttonqueue.o

audio.o: audio.c ./header/audio.h
	gcc -c audio.c -o audio.o

knight.o: knight.c ./header/knight.h
	gcc -c knight.c -o knight.o

main.o: main.c
	gcc -c main.c -o main.o 

funcoes.o: funcoes.c ./header/funcoes.h
	gcc -c funcoes.c -o funcoes.o

menu.o: menu.c ./header/menu.h
	gcc -c menu.c -o menu.o

comojogar.o: comojogar.c ./header/comojogar.h
	gcc -c comojogar.c -o comojogar.o

all: main.o knight.o audio.o buttonqueue.o funcoes.o menu.o comojogar.o
	gcc knight.o main.o audio.o menu.o funcoes.o buttonqueue.o comojogar.o -o ../Kingdom-Hero_linux `pkg-config allegro-static-5 allegro_image-static-5 allegro_audio-static-5 allegro_acodec-static-5 allegro_font-static-5 allegro_ttf-static-5 allegro_primitives-static-5 --libs --static`