#!/usr/bin/python
import sys
import Tkinter as tk
import Image, ImageDraw
from threading import Thread
import time

width = 980/2
height = 720/2
#print 'Number of arguments:', len(sys.argv), 'arguments.'
print 'Argument List:', str(sys.argv)
args= sys.argv
width = int(args[2])
height= int(args[3])
filename= args[1]
center = height//2
white = (255, 255, 255)
green = (0,128,0)

class App():
    def __init__(self):
	self.root = tk.Tk()
	self.label = tk.Label(text="")
	self.label.pack()
	# Tkinter create a canvas to draw on
	self.cv = tk.Canvas(self.root, width=width/2, height=height/2, bg='white')
	self.cv.pack()

	# PIL create an empty image and draw object to draw on
	# memory only, not visible
	self.image1 = Image.new("RGB", (width, height), white)
	self.draw = ImageDraw.Draw(self.image1)

	# do the Tkinter canvas drawings (visible)
	#self.cv.create_line([0, center, width, center], fill='green')

	# do the PIL image/draw (in memory) drawings
	#self.draw.line([0, center, width, center], green)
	#self.draw.ellipse([50, 45, 55, 60], fill=green)

	#sync variable for thread loop
	self.goon=1
	try:
		Thread(target=self.listen ).start()
	except Exception, errtxt:
		print errtxt
	self.update_clock()
	self.root.protocol("WM_DELETE_WINDOW", self.handler)
	self.root.mainloop()

    def update_clock(self):
	now = time.strftime("%H:%M:%S")
	self.label.configure(text=now)
	self.root.after(1000, self.update_clock)

    def listen(self):
	#self.cv.create_line([50, center+50, width, center], fill='green')
	s=raw_input()
	while( ("q" not in s) and self.goon==1):
		if("time" not in s):
			coords=s.split()
			#   time     x    y   z f  w  l r u d m     multi  gl gm gr gdx gdy
			if(coords[4]=='1'):
				x=int(coords[1])
				y=int(coords[2])
				z=int(coords[3])
				#self.cv.create_line([x, y, x+1, y+1], fill='green')
				#self.cv.create_rectangle([x, y, x+z/4, y+z/4], outline='green', fill='green')
				self.cv.create_oval([x/2, y/2, x/2+z/8, y/2+z/8], outline='green', fill='green')
				self.draw.ellipse([x-z/8, y-z/8, x+z/8, y+z/8], fill=green)
				#print coords
		s=raw_input()

    def handler(self):
	self.goon=0
	print "Killed soon"
	# PIL image can be saved as .png .jpg .gif or .bmp file (among others)
	#filename = "my_drawing.jpg"
	self.image1.save(filename)
	self.root.quit()

app=App()
#app.mainloop()

