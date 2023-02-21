/* Redefine main() to child_main() because Emscripten is driving the bus */
#define main child_main
