prefix = /usr/local
 
barebones: src/bb.c
	gcc -o bin/barebones src/bb.c

install: bin/barebones
	install -m 0755 bin/barebones $(prefix)/bin
