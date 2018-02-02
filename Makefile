include config.mk

SRC=main.c noteme.c
OBJ=$(SRC:.c=.o)

all: noteme

options:
	@echo "CFLAGS   = $(CFLAGS)"
	@echo "LDFLAGS  = $(LDFLAGS)"
	@echo "CC       = $(CC)"
	@echo "SRC      = $(SRC)"
	@echo "OBJ      = $(OBJ)"

$(OBJ): noteme.h

noteme: $(OBJ)

clean:
	$(RM) noteme $(OBJ)

install:
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f noteme $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/noteme

uninstall:
	$(RM) $(DESTDIR)$(PREFIX)/bin/noteme

.PHONY: all options clean install uninstall
