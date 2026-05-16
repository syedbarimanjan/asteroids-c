CC=gcc

main: main.c
	$(CC) raygui.c main.c asteroids.c -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run: main
	./main

clean:
	rm main