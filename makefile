# Optimisation Options
# export CFLAGS+=-O2 -mtune=native -march=native

export REFSTRING_OUTDIR = out

all: test

#utils
test: clean $(REFSTRING_OUTDIR)
	$(MAKE) -C test

test-sanitized: export CFLAGS+=-fsanitize=address,undefined
test-sanitized: export LIBS+=-static-libasan
test-sanitized: export DISABLE_VALGRIND=true
test-sanitized: clean $(REFSTRING_OUTDIR)
	$(MAKE) -C test

$(REFSTRING_OUTDIR):
	mkdir $(REFSTRING_OUTDIR)

.PHONY: clean

clean:
ifeq ($(findstring CYGWIN, $(shell uname)),CYGWIN)
	find . -type f -name '*.o' -exec rm -f -r -v {} \;
	find . -type f -name '*.a' -exec rm -f -r -v {} \;
	find . -type f -name '*.exe' -exec rm -f -r -v {} \;
	find . -type f -name '*.dll' -exec rm -f -r -v {} \;
	find . -type f -name '*.lib' -exec rm -f -r -v {} \;
	find . -type f -name '*.so' -exec rm -f -r -v {} \;
	find . -empty -type d -delete
else ifeq ($(shell uname),Linux)
	find . -type f -name '*.o' -exec rm -f -r -v {} \;
	find . -type f -name '*.a' -exec rm -f -r -v {} \;
	find . -type f -name '*.exe' -exec rm -f -r -v {} \;
	find . -type f -name '*.dll' -exec rm -f -r -v {} \;
	find . -type f -name '*.lib' -exec rm -f -r -v {} \;
	find . -type f -name '*.so' -exec rm -f -r -v {} \;
	rm -rf out
	find . -empty -type d -delete
else ifeq ($(OS),Windows_NT)
	$(RM) *.o *.a *.exe 
else ifeq ($(shell uname),Darwin)
	find . -type f -name '*.o' -exec rm -f -r -v {} \;
	find . -type f -name '*.a' -exec rm -f -r -v {} \;
	find . -type f -name '*.exe' -exec rm -f -r -v {} \;
	find . -type f -name '*.dll' -exec rm -f -r -v {} \;
	find . -type f -name '*.lib' -exec rm -f -r -v {} \;
	find . -type f -name '*.dylib' -exec rm -f -r -v {} \;
	find . -type f -name '*.so' -exec rm -f -r -v {} \;
	rm -rf out
	find . -empty -type d -delete
else
	@echo "Deletion failed - what platform is this?"
endif

rebuild: clean all
