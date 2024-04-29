# Pong
This is a simple remake of pong using [SDL2](https://github.com/libsdl-org/SDL/tree/SDL2)[^1].

---

## Pre-Requisites
If you for whatever reason do not have listed prerequisites, and do not wish to download them via the provided links, you can also downloaded them via your preferred package manager, which is recommended.

- [gcc](https://github.com/gcc-mirror/gcc)
- [make](https://ftp.gnu.org/gnu/make/)

---

## Running
1) Clone this repository or otherwise download the `SDL_pong` directory
2) Navigate to the `SDL_pong` directory
3) Run `make`
4) Run `./pong` 

---

## Use 
Use the `w` and `s` as well as the "uparrow" and "downarrow" keys to move the left and right paddles up and down, respectively. The process will end once either score reaches 100; this is expected behavior.

---

### Notes
- Run `make clean` in the `SDL_pong` directory to clean it of the executable and object file created by the `make` command
- This project is not windows compatible, sorry.


[^1]: Downloading [SDL2](https://github.com/libsdl-org/SDL/tree/SDL2), is entirely unnecessary for this project to function.


