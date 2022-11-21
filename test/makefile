CC=gcc

IDIR +=. ..
CFLAGS +=$(addprefix -I,$(IDIR)) -g -Wall -W -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable
LIBS +=

ODIR = obj
TARGETS = $(wildcard ../*.c)
TESTS = $(wildcard *.c)
OBJ = $(addprefix $(ODIR)/,$(TARGETS:../%.c=%.o)) $(addprefix $(ODIR)/,$(TESTS:.c=.o))

.PRECIOUS:  $(TESTS:%.c=../$(REFSTRING_OUTDIR)/%.exe)

all: $(OBJ) $(TESTS:%.c=../$(REFSTRING_OUTDIR)/%.exe)

../$(REFSTRING_OUTDIR)/%.exe: $(ODIR)/%.o
	@$(CC) -o $@ $< $(TARGETS:../%.c=$(ODIR)/%.o) $(CFLAGS) $(LIBS)
ifeq ($(shell uname),Linux)
	valgrind --leak-check=full --track-origins=yes $@
else
	$@
endif

$(OBJ): | $(ODIR)

$(ODIR):
	mkdir $(ODIR)

$(ODIR)/%.o: %.c
	@$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: ../%.c
	@$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	$(RM) $(ODIR)
