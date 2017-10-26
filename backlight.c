#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
    FILE *file;
    int numbers;
    int maxLimit; 
    if((file=fopen("/sys/class/backlight/intel_backlight/brightness","r"))==NULL)
    {
        printf("Can't open brightness!");
        exit(1);
    }
    fscanf(file,"%d",&numbers);
    fclose(file);
    //printf("Now:%d\n",numbers);

    if((file=fopen("/sys/class/backlight/intel_backlight/max_brightness","r"))==NULL)
    {
        printf("Can't open max_brightness!");
        exit(1);
    }
    fscanf(file,"%d",&maxLimit);
    //printf("Top:%d\n",maxLimit);
    fclose(file);
    file=NULL;
    if(argc==2&&strcmp("+",argv[1]))
    {
        numbers-=500;
    }else if(argc==2&&strcmp("-",argv[1]))
    {
        numbers+=500;
    }else
    {
        printf("Wrong command,give me \"+\" or \"-\" !\n");
        exit(1);
    }

    if((file=fopen("/sys/class/backlight/intel_backlight/brightness","w"))==NULL)
    {
        printf("Write Wrong!\n");
        exit(1);
    }
    if(numbers>maxLimit)
        numbers=maxLimit;
    if(numbers<0)
        numbers=0;
    
    fprintf(file,"%d",numbers);
    fclose(file);
    file=NULL;

    return 0;

}