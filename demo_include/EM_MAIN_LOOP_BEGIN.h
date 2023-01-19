/*#define while mainLoop(dev, val, attached); \
              } \
              int mainLoop(dev, val, attached) \
              short dev; \
              short val; \
              Boolean attached; \
              { \
                  while (TRUE) \
                      if*/

/* redefine infinite loop to mainLoop() because Emscripten is driving the bus */
#define while \
    emscripten_set_main_loop_arg(&mainLoop, NULL, 0, 0); \
} \
\
void mainLoop() \
{ \
    static short dev; \
    static short val; \
    static Boolean attached; \
    if
