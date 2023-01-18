RASTERIZER_SRCS = ../libgl/reference_rasterizer.c
EVENTS_SRCS = ../libgl/dummy_events.c
BIN_DIR = ../demo_bin
OPT_NONE = -O0
OPT_TWO = -DNDEBUG -O2
OPT_LEVEL = $(OPT_NONE)