.PHONY: demos libs clean smoke smoke-baseline

DEMOS_DIR = demos
DEMOS = arena bounce buttonfly cedit ep-1988 ep-1989 ep-1994-ogl-decomp ep-1994-ogl-reversed flight-1988 flight-1994 gview ideas insect jello logo newave twilight

LIBS_DIR = libs
LIBS = libgl libdemo

LOG_DIR = logs

# Build one target ($2) in one subdir ($1/$3), tee to a log file, and
# remember the exit code. Always returns 0 from the outer command so
# the for loop continues past failures; failures are surfaced in the
# summary by reading the .rc file.
#
# $1 = subdir family (demos or libs)
# $2 = make target (empty, native, browser, clean)
# $3 = item name (e.g. cedit, libgl)
define build_one
    mkdir -p $(LOG_DIR) ; \
    LOG=$(LOG_DIR)/$(3).log ; \
    echo "" ; echo "BUILDING: $(3)" ; echo "" ; \
    ( make $(2) -C $(1)/$(3) 2>&1 ; echo $$? > $(LOG_DIR)/$(3).rc ) | tee $$LOG ;
endef

# Summarize all .log/.rc files in $(LOG_DIR). Counts error and
# warning lines per file; reports overall pass/fail.
define summarize
    @echo "" ; \
    echo "==================== BUILD SUMMARY ===========================" ; \
    printf "%-22s %12s %12s %13s\n" "TARGET" "ERRORS" "WARNINGS" "STATUS" ; \
    fail=0 ; \
    for item in $(1) ; do \
        log=$(LOG_DIR)/$$item.log ; \
        rc_file=$(LOG_DIR)/$$item.rc ; \
        if [ -f $$log ] ; then \
            errs=$$(grep -c 'error:' $$log 2>/dev/null) ; errs=$${errs:-0} ; \
            warns=$$(grep -c 'warning:' $$log 2>/dev/null) ; warns=$${warns:-0} ; \
        else \
            errs=? ; warns=? ; \
        fi ; \
        if [ -f $$rc_file ] ; then \
            rc=$$(cat $$rc_file) ; \
        else \
            rc=? ; \
        fi ; \
        if [ "$$rc" != "0" ] ; then fail=1 ; fi ; \
        printf "%-22s %12s %12s %13s\n" $$item $$errs $$warns $$rc ; \
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
	@rm -rf $(LOG_DIR)
	@for lib in $(LIBS) ; do $(call build_one,$(LIBS_DIR),,$$lib) done
	@for demo in $(DEMOS) ; do $(call build_one,$(DEMOS_DIR),,$$demo) done
	$(call summarize,$(LIBS))
	$(call summarize,$(DEMOS))

native:
	@rm -rf $(LOG_DIR)
	@for demo in $(DEMOS) ; do $(call build_one,$(DEMOS_DIR),native,$$demo) done
	$(call summarize,$(DEMOS))

browser:
	@rm -rf $(LOG_DIR)
	@for demo in $(DEMOS) ; do $(call build_one,$(DEMOS_DIR),browser,$$demo) done
	$(call summarize,$(DEMOS))

libs:
	@rm -rf $(LOG_DIR)
	@for lib in $(LIBS) ; do $(call build_one,$(LIBS_DIR),,$$lib) done
	$(call summarize,$(LIBS))

libs-native:
	@rm -rf $(LOG_DIR)
	@for lib in $(LIBS) ; do $(call build_one,$(LIBS_DIR),native,$$lib) done
	$(call summarize,$(LIBS))

libs-browser:
	@rm -rf $(LOG_DIR)
	@for lib in $(LIBS) ; do $(call build_one,$(LIBS_DIR),browser,$$lib) done
	$(call summarize,$(LIBS))

clean:
	for demo in $(DEMOS) ; do echo "" ; echo "CLEANING: $$demo" ; echo "" ; make clean -C $(DEMOS_DIR)/$$demo ; done
	for lib in $(LIBS) ; do echo "" ; echo "CLEANING: $$lib" ; echo "" ; make clean -C $(LIBS_DIR)/$$lib ; done
	rm -rf $(LOG_DIR)

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
