include ../build/platform.mk

LIB=$(BIN_DIR)/$(LIBNAME).a
EMLIBNAME=$(WEB_DIR)/$(LIBNAME)
EMLIB=$(EMLIBNAME).a
SRC = $(wildcard *.c)
HDRS = $(wildcard *.h)
OBJS = $(patsubst %.c,$(BIN_DIR)/%.o,$(SRC))
EMOBJS = $(patsubst %.c,$(WEB_DIR)/%.o,$(SRC))

all: $(LIB) $(EMLIB)

ifeq ($(IS_OLD_CODE),yes)
PATCH_SRC = $(patsubst %.c,$(PATCH_DIR)/%.c,$(SRC))
SRC_DIR = $(PATCH_DIR)
LIB_CC = $(OLD_CODE_CC) $(OPT) $(OLD_CODE_WARN_OFF)
LIB_EMCC = $(OLD_CODE_EMCC) $(EM_OPT) $(EM_OLD_CODE_WARN_OFF)
else
PATCH_SRC =
SRC_DIR = .
LIB_CC = $(CC) $(OPT)
LIB_EMCC = $(EMCC) $(EM_OPT)
endif

$(PATCH_DIR): $(SRC) $(HDRS)
	mkdir -p $@
	cp $(SRC) $(HDRS) $@

$(PATCH_SRC): $(PATCH_DIR)

$(BIN_DIR): $(PATCH_SRC)
	mkdir -p $@
	echo *.o > $@/.gitignore
	echo *.a > $@/.gitignore

$(WEB_DIR): $(PATCH_SRC)
	mkdir -p $@
	echo *.o > $@/.gitignore
	echo *.a > $@/.gitignore

$(OBJS): $(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(LIB_CC) $(LIBGL_INC) $(LIBDEMO_INC) $(LIBDEFS) $< -c -o $@

$(LIB): $(OBJS)
	$(AR) $@ $(OBJS)
	@echo
	@echo BUILT: $@
	@echo

$(EMOBJS): $(WEB_DIR)/%.o: $(SRC_DIR)/%.c | $(WEB_DIR) 
	$(LIB_EMCC) $(LIBGL_INC) $(LIBDEMO_INC) $< -c -o $@

$(EMLIB): $(EMOBJS)
	$(EMAR) $@ $(EMOBJS)
	@echo
	@echo BUILT: $@
	@echo

.PHONY: clean

clean:
	rm -f $(LIB) $(OBJS)
	rm -f $(EMLIB) $(EMOBJS)
	rm -rf $(PATCH_DIR)
