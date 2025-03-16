GEN_SOURCES = gen/parser.c gen/lexer.c
C_SOURCES = src/args.c src/ast.c src/main.c src/network.c src/node.c src/validate.c src/util.c src/postprocess.c

ALL_SOURCES = $(GEN_SOURCES) $(C_SOURCES)

BINDIR = bin
OBJECTS = $(patsubst %.c,$(BINDIR)/%.o,$(ALL_SOURCES))
TARGET = $(BINDIR)/ndl

CC = gcc
CFLAGS = -ggdb -Iinclude -Igen

.PHONY: all clean
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

gen/parser.c gen/parser.h: parser/parser.y | gen
	bison -Wcounterexamples -d -o gen/parser.c parser/parser.y

gen/lexer.c gen/lexer.h: parser/lexer.l gen/parser.h | gen
	flex --header-file=gen/lexer.h -o gen/lexer.c parser/lexer.l

bin/gen/parser.o: gen/parser.c gen/parser.h gen/lexer.h | $(BINDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c gen/parser.c -o bin/gen/parser.o

bin/gen/lexer.o: gen/lexer.c gen/parser.h gen/lexer.h | $(BINDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c gen/lexer.c -o bin/gen/lexer.o

$(BINDIR)/%.o: %.c | $(BINDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR) gen:
	@mkdir -p $@

clean:
	@rm -rf gen $(BINDIR)
	@echo Directories cleaned.

.PHONY: clean all
