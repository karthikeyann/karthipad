#include<stdio.h>
#include<string.h>
main()
{
char k;
do{
//single letter command
k=getchar(); //instead of getchar, gets can also be used for entering multi-letter command.
//pass only allowed commands
if(k=='q') //quit
	printf("%c\n",k);
}while(k!='q');
}
