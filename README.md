# Asteroids-c
An asteroids game written in c + raylib https://www.raylib.com/. 

Move with arrow keys and shoot with space, collect red, green and blue powerups which spawn when you get hit by an asteroid.

Red powerup gives health, Blue increases bullets size and Green increases bullets speed.

# Start screen
![start-game](https://cdn.hackclub.com/01a009cf-1736-7ab5-bcfd-20d148e581de/screenshot_20260815_233105.png)

# Game screen

**The Green circles on the screen are powerups there can be green,blue and red powerups which spawn when you get hit by an asteroid.**

![game-screen](https://cdn.hackclub.com/01a009fb-656a-76ad-b33f-fc979d325dba/screenshot_20260816_145001.png)

# End screen
![end-game](https://cdn.hackclub.com/01a009cf-1110-79f0-b591-654525bc4411/screenshot_20260815_233612.png)

# How to run locally

Install raylib on your system using this wiki https://github.com/raysan5/raylib/wiki

Install make.

Clone this repo and run 
```
make main
./main
```

## How to Compile AppImage

Install appimagetool https://github.com/AppImage/appimagetool

Run 
```
./appimagetool-x86_64.AppImage AppDir
```

**Tested on ubuntu 20,22,24 and fedora 43**

### AI DISCLOSURE
**No LLM/AI was used in the making of this project.**

<!--emcc -o index.html raygui.c main.c asteroids.c debug.c game_asteroids.c player.c projectile.c game_projectiles.c game_score.c game_player.c game_ui.c game.c powerup.c game_powerup.c -Os -Wall -I /home/sbj/Downloads/programming/c/emsdk/upstream/emscripten/cache/sysroot/include -L /home/sbj/Downloads/programming/c/emsdk/upstream/emscripten/cache/sysroot/lib/libraylib.a -s USE_GLFW=3 -s ASYNCIFY --preload-file /home/sbj/Downloads/programming/c/asteroids-c/assets/asteroid.png --preload-file /home/sbj/Downloads/programming/c/asteroids-c/assets/ship.png  -DPLATFORM_WEB /home/sbj/Downloads/programming/c/emsdk/upstream/emscripten/cache/sysroot/lib/libraylib.a-->
