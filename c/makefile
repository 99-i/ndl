GEN_SOURCES = gen/parser.c gen/lexer.c
C_SOURCES = src/main.c src/program.c

ALL_SOURCES = $(GEN_SOURCES) $(C_SOURCES)

OUTBIN = bin/ndl

$(OUTBIN): $(ALL_SOURCES) | bin
	mkdir -p $(dir $@)
	gcc -ggdb -Iinclude -Igen $(ALL_SOURCES) -o $(OUTBIN)

bin:
	@mkdir -p bin

gen:
	@mkdir -p gen

gen/parser.c: parser/parser.y | gen
	bison -d -o $@ $<

gen/lexer.c: parser/lexer.l | gen
	flex -o $@ $<

.PHONY: clean
clean:
	@rm -rf gen
	@rm -f $(OUTBIN)
	@rm -rf bin
