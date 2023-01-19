/* Redefine main() to demo_main() because Emscripten is driving the bus */
#define main main (argc, argv) \
             int argc; char *argv[]; { demo_main(argc, argv); } \
             int demo_main
