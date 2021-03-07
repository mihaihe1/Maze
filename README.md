# Maze

Simple C++ maze game. Can you beat it in 35 seconds?

## Implemented using the Simple DirectMedia Layer 2.0(SDL 2) library
SDL provides support for 2D pixel operations, sound, file access, event handling, timing and threading.

### Installation
```
sudo apt install libsdl2-dev
sudo apt install libsdl2-image-dev
```
In order to compile SDL 2 code, we have to tell the compiler to link against the libraries.
![linker](https://user-images.githubusercontent.com/44977942/110235525-22e18300-7f39-11eb-9a1e-2c9621d33c80.png)


## Game

* The game uses a stack for the states of the game
* The possible states of the stack are: *QUIT*, *MENU*, *ENDING*, *PAUSE*
* It starts with *MENU* at the top.
* It stops when *QUIT* is at the top.

![game](https://user-images.githubusercontent.com/44977942/110235791-a5b70d80-7f3a-11eb-9ad6-c24188838cd2.png)

***More levels coming soon!!!***
