# Snake
A OpenGL implementation of the good old Nokia phone's game.
## Building
The instructions below have only been tested in Ubuntu 22.04.03 LTS.
### Installing GLFW
Follow the instructions in [https://www.glfw.org/docs/latest/compile.html](https://www.glfw.org/docs/latest/compile.html) to compile the library.

To compile the game, run the following command:
```
gcc -o snake src/main.c src/glad.c -Iinclude -lGL -lglfw3 -lX11 -lpthread -lXrandr -lXi -ldl -lm
```