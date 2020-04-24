#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    BYTE byte[512];
    int j=0;
    char filename[8];
    char ch;
    int f=0;
    if(argc != 2)
    {
        printf("Usage : ./recover image \n");
        return 1;
    }
    FILE *file=fopen(argv[1],"r");

    if(!file)
    {
        printf("File cannot be opened for reading \n");
        return 1;
    }
    while(fread(byte,512,1,file)==1)
    {
        if(byte[0]==0xff && byte[1]==0xd8 && byte[2]==0xff && (byte[3] & 0xf0)==0xe0)
        {
            if(j==0)
            {
                sprintf(filename,"%03i.jpg",j);
                j=j+1;
                FILE *img=fopen(filename,"w");
                fwrite(byte,512,1,img);
                fclose(img);
                f=1;
            }
            else
            {
                sprintf(filename,"%03i.jpg",j);
                j=j+1;
                FILE *img=fopen(filename,"w");
                fwrite(byte,512,1,img);
                fclose(img);
                f=1;
            }
        }
        else
        {
            if(f==1)
            {
                sprintf(filename,"%03i.jpg",j-1);
                FILE *img=fopen(filename,"a");
                fwrite(byte,512,1,img);
                fclose(img);
            }
        }
    }
    fclose(file);
    return 0;
}