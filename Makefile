CC=gcc

main: main.c
	$(CC) raygui.c main.c asteroids.c debug.c game_asteroids.c player.c projectile.c game_projectiles.c game_score.c game_player.c game_ui.c game.c powerup.c game_powerup.c -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run: main
	./main

clean:
	rm main

a:
	make clean && make main && make run

main-safe: main.c
	$(CC) -fsanitize=address -g raygui.c main.c asteroids.c debug.c game_asteroids.c player.c projectile.c game_projectiles.c game_score.c game_player.c game_ui.c game.c powerup.c game_powerup.c -o main-safe -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run-safe: main-safe
	./main-safe

clean-safe:
	rm main-safe

b:
	make clean-safe && make main-safe && make run-safe
