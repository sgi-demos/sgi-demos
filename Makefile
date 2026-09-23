.PHONY: all native browser libs clean list smoke smoke-baseline thumbs

# The one list of demos: every demos/<name>/ or demos/<name>/<variant>/ with a
# Makefile, except draft ports (placard.json "draft": true). The smoke tests,
# thumbnails, and README grid read it too, through `make list`.
DEMO_DIRS := $(patsubst %/Makefile,%,$(wildcard demos/*/Makefile demos/*/*/Makefile))
DRAFTS := $(patsubst %/placard.json,%,$(shell grep -l '"draft": *true' $(wildcard $(DEMO_DIRS:=/placard.json)) /dev/null))
DEMOS := $(sort $(patsubst demos/%,%,$(filter-out $(DRAFTS),$(DEMO_DIRS))))

LIBS = libgl libdemo
LIB_DIRS = $(LIBS:%=libs/%)

LOG_DIR = logs

# Build each directory in $2 with one make target ($1: empty for both native
# and browser, or native, or browser). Each item's output is teed to
# $(LOG_DIR)/<item>.log and its exit code kept in <item>.rc, so the loop runs
# past failures and the summary reports them. Items in a subdirectory
# (ep-1994/decomp) log as ep-1994-decomp.
define build
	@rm -rf $(LOG_DIR) ; mkdir -p $(LOG_DIR) ; \
	for item in $(2) ; do \
	    name=$$(echo $${item#*/} | tr / -) ; \
	    echo "" ; echo "BUILDING: $$name" ; echo "" ; \
	    ( $(MAKE) $(1) -C $$item 2>&1 ; echo $$? > $(LOG_DIR)/$$name.rc ) | tee $(LOG_DIR)/$$name.log ; \
	done
	@echo "" ; \
	echo "==================== BUILD SUMMARY ===========================" ; \
	printf "%-22s %12s %12s %13s\n" "TARGET" "ERRORS" "WARNINGS" "STATUS" ; \
	fail=0 ; \
	for item in $(2) ; do \
	    name=$$(echo $${item#*/} | tr / -) ; \
	    log=$(LOG_DIR)/$$name.log ; \
	    errs=$$(grep -c 'error:' $$log 2>/dev/null) ; \
	    warns=$$(grep -c 'warning:' $$log 2>/dev/null) ; \
	    rc=$$(cat $(LOG_DIR)/$$name.rc 2>/dev/null || echo '?') ; \
	    if [ "$$rc" != "0" ] ; then fail=1 ; fi ; \
	    printf "%-22s %12s %12s %13s\n" $$name $${errs:-?} $${warns:-?} $$rc ; \
	done ; \
	echo "==============================================================" ; \
	if [ $$fail -ne 0 ] ; then \
	    echo "BUILD FAILED: See $(LOG_DIR)/<target>.log for details." ; \
	    exit 1 ; \
	else \
	    echo "BUILD OK: All targets built." ; \
	fi
endef

all:
	$(call build,,$(LIB_DIRS) $(DEMOS:%=demos/%))

native browser:
	$(call build,$@,$(LIB_DIRS) $(DEMOS:%=demos/%))

# just the libs, native and browser: a quick compile check while editing one
libs:
	$(call build,,$(LIB_DIRS))

clean:
	@for item in $(DEMOS:%=demos/%) $(LIB_DIRS) ; do echo "" ; echo "CLEANING: $$item" ; $(MAKE) clean -C $$item ; done
	rm -rf $(LOG_DIR)

list:
	@for d in $(DEMOS) ; do echo $$d ; done

# ============================================================================
# Visual smoke tests (web targets) — see tests/smoke/README.md
#
# `make smoke` assumes the web targets are already built (`make browser`).
# Captures every demo in both rendering modes (CPU reference + gles2 GPU),
# fails on errors/blank frames, and writes the human-review gallery to
# tests/smoke/report/index.html. First run installs node deps + Chromium.
# ============================================================================

SMOKE_DIR = tests/smoke

$(SMOKE_DIR)/node_modules:
	cd $(SMOKE_DIR) && npm install
	cd $(SMOKE_DIR) && npx playwright install chromium

smoke: $(SMOKE_DIR)/node_modules
	cd $(SMOKE_DIR) && node smoke.mjs --repo ../..

# Promote the current captured frames to baseline/ (for the gallery's
# side-by-side eyeball view; not part of the pass/fail gate).
smoke-baseline: $(SMOKE_DIR)/node_modules
	cd $(SMOKE_DIR) && node smoke.mjs --repo ../.. --update-baseline

# Browse-page thumbnails: capture every demo's web build into media/<demo>.png
# (512x384) for sgi-demos.github.io/browse/. Recipes for the demos that need
# them (settle time, keys/mouse to get past splash screens) live in
# scripts/thumbs.json.
thumbs: $(SMOKE_DIR)/node_modules
	node scripts/thumbs.mjs
