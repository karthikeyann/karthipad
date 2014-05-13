karthipad
=========
karthipad is an application to turn your touchpad/trackpad into a writing pad.
Once you run karthipad, you can write on touchpad as if you are writing on a paper.
The content what you write will be saved to a bitmap file (.bmp)

**Dependencies :** synclient

Initial Setup
=============

1. Type the following command in terminal
		locate synaptics
	You will find a file like "50-synaptics.conf"
	 either in /etc/X11/xorg.conf.d/ or /usr/share/X11/xorg.conf.d/

2. Open the file using sudo
	    example: >sudo gedit /etc/X11/xorg.conf.d/50-synaptics.conf

3. Add the following line (with exact spaces- don't use tab) and save the file
	        Option         "SHMConfig" "on"

4. Restart the system.

5. Type the follwing command in terminal
	    synclient -m 100
	 Now, when you move your finger over touchpad, you can see the values printed in the terminal.
	 Press Ctrl+C to stop.

Compilation
===========

Extract the source files.
Compile using the following command

	make

Recompile:
		make clean
		make

Running Binary:

	./karthipad

Installation
============
Install using following command

	make
	sudo make install

Un-install using following command

		sudo make uninstall

Re-install using following command

		sudo make reinstall
Usage
=====
Following commands are supported.

		karthipad filename
		#(default size = 1000x1000)
		karthipad filename 980
		#(size = 980x980)
		karthipad filename 999 500
		#(size = 999x500)
		karthipad -h
		#(displays help information)
		karthipad -v
		#(displays version information)
To quit the command line application, type q.

Support Information
===================

Modules used:

- libbmp http://code.google.com/p/libbmp/
- synclient http://en.gentoo-wiki.com/wiki/Synaptics_Touchpad

About Author
============
Karthikeyan.N
- Email: karthi.amrita.cbe@gmail.com
- Website:techbird.wordpress.com
- Twitter: www.twitter.com/lxkarthi
