CC = gcc
VERSION = 0.1.0
prefix =/usr/local
main: bmpfile.c bmpfile.h wpad.c passcmds.c
	@gcc passcmds.c -o passcmds
	@gcc wpad.c -lm -o wpad
	@echo "Compilation complete."
install: main
	@install -m 0755 passcmds $(prefix)/bin
	@install -m 0755 wpad $(prefix)/bin
	@install -m 0755 karthipad $(prefix)/bin
	@echo "karthipad: Installation complete."
uninstall:
	@rm -f $(prefix)/bin/passcmds $(prefix)/bin/wpad $(prefix)/bin/karthipad
	@echo "karthipad: Un-install complete."
reinstall: clean main install
clean:
	@rm -f passcmds wpad
	@echo "clean complete."
