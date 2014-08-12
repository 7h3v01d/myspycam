CC=gcc
CFLAGS=-c -Wall -Wextra -std=gnu99 -ggdb
LDFLAGS=
LIBS=
SOURCES=config.c myspycamd.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=myspycamd

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o$@ $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $< -o$@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run:
	./$(EXECUTABLE) $(EXECUTABLE).conf

stop:
	killall -15 $(EXECUTABLE)

kill:
	killall -9 $(EXECUTABLE)

show:
	@ps aux | grep $(EXECUTABLE) | grep -v grep

commit:
	git commit -a --allow-empty-message

tail:
	@tail -n2 -f /var/log/syslog

distclean: clean

valgrind:
	cat /dev/null > $(EXECUTABLE).valgrind
	valgrind --trace-children=yes --log-file=$(EXECUTABLE).valgrind --leak-check=full --show-reachable=yes -v ./$(EXECUTABLE)
	tail -f -n9999 $(EXECUTABLE).valgrind

demo: clean all run show tail

tags:
	ctags *.c *.h

test: distclean all valgrind
