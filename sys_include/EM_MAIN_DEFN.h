#ifndef EM_MAIN_DEFN
#define EM_MAIN_DEFN

#include "EM_MAIN_DECL.h"
#ifndef EM_CHILD_MAIN
int child_main (int argc, char* argv[]) { return 0; }
void child_main_loop(void *main_loop_arg) {}
#endif

#endif