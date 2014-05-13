/**************** AUTHOR ****************/
/* Karthikeyan.N			*/
/* email:karthi.amrita.cbe@gmail.com 	*/
/****************************************/
/*
 Description:
 Draws a image file from synclient output until it sees a letter 'q'
 synclient -m 10 gives the touchpad status every 10 ms.
*/
#include<stdio.h>
#include<string.h>
#include "bmpfile.c"
int contains(char* str, char val);
inline bool draw_pixel(bmpfile_t *bmp, uint32_t x, uint32_t y, rgb_pixel_t pixel);
int main(int argc, char **argv)
{
  char* b;
  char a[200];
  float time;
  int x, y, z, f, w, l, r, u, d, m, multi;
  int prev_x,prev_y,prev_z,prev_f,x1,x2,y1,y2,i,j;
  bmpfile_t *bmp;
  rgb_pixel_t pixel = {128, 64, 0, 0};

  if( argc == 5 )
	printf("Output File: %s\n", argv[1]);
  else if( argc < 5 )
  {
	printf("Usage: %s filename width height depth.\n", argv[0]);
	return 1;
  }
  else
	printf("Too many arguments supplied.\n");

  if ((bmp = bmp_create(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]))) == NULL) {
	printf("Invalid depth value: %s.\n", argv[4]);
	return 1;
  }

  prev_x=-1;  prev_y=-1;  prev_z=-1;  prev_f=0;
  f=0;
  while(1)
  {
	b=gets(a);
	if(contains(a,'q'))
		break;
	if(contains(a,'t')==0)
	{
		//time     x    y    z f  w  l r u d m     multi  gl gm gr gdx gdy
		//0.000   539  532   0 0  0  0 0 0 0 0  00000000
		sscanf(a,"%f %d %d %d %d %d %d %d %d %d %d %d", &time, &x, &y, &z, &f, &w, &l, &r, &u, &d, &m, &multi);
/*TODO Pixel value change according to pressure*/
/*		pixel.red=z;
		pixel.green++;
		pixel.blue++;
*/
/*Draw line between consecutive points on moving (use 'f' value to check finger is continuously moving or not)*/
/*TODO curve (second order interpolation) So, smoother drawing*/
		//Setting Pixels around the touching point
		if(f==1)
		{
			draw_pixel(bmp, x, y, pixel);
			//Draw line if you move finger without removing from surface.
			if(prev_f==1)
			{
				if( abs(prev_x-x) > abs(prev_y-y) )
				{
					if(x>prev_x) { x2=x; x1=prev_x; y2=y; y1=prev_y;}
					else {x2=prev_x; x1=x; y2=prev_y; y1=y; }
					// Line drawing between two points (x versus y)
					for(i=x1;i<x2;i++)
					{
					j= y1 + (((y2-y1)*(i-x1))/(x2-x1));
					draw_pixel(bmp, i, j, pixel);
					}
				}
				else
				{
					if(y>prev_y) { x2=x; x1=prev_x; y2=y; y1=prev_y;}
					else {x2=prev_x; x1=x; y2=prev_y; y1=y; }
					// Line drawing between two points (y versus x)
					for(j=y1;j<y2;j++)
					{
					i= x1 + (((x2-x1)*(j-y1))/(y2-y1));
					draw_pixel(bmp, i, j, pixel);
					}
				}
			}
		}
		prev_x=x;  prev_y=y;  prev_z=z;  prev_f=f;
//Debug		printf("%d. %f %d %d %d %d %d %d %d %d %d %d %d\n",i++,time,x, y, z, f, w, l, r, u, d, m, multi);
	}
  }
  bmp_save(bmp, argv[1]);
  bmp_destroy(bmp);
  printf("Drawing Finished\n");
  return 0;
}

int contains(char* str, char val)
{
  int j,len;
  len=strlen(str);
  for(j=0;j<len;j++)
  {
	if(str[j]==val)
	return 1;
  }
  return 0;
}

inline bool draw_pixel(bmpfile_t *bmp, uint32_t x, uint32_t y, rgb_pixel_t pixel)
{
	/*For more thickness, adjacent pixels are also set.*/
	bmp_set_pixel(bmp, x+1, y, pixel);
	bmp_set_pixel(bmp, x, y+1, pixel);
	bmp_set_pixel(bmp, x-1, y, pixel);
	bmp_set_pixel(bmp, x, y-1, pixel);
	bmp_set_pixel(bmp, x-1, y-1, pixel);
	bmp_set_pixel(bmp, x+1, y+1, pixel);
	/*For thinner lines, remove above lines in this function*/	
	return bmp_set_pixel(bmp, x, y, pixel);
}
