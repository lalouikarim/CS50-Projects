#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include <stdlib.h>
int main(int argc,string argv[])
{
    bool e=false;
    int h;
    if(argc==2)
    {
        for(int i=0, n=strlen(argv[1]);i<n;i++)
        {
            if(argv[1][i]=='0'||argv[1][i]=='1'||argv[1][i]=='2'||argv[1][i]=='3'
            ||argv[1][i]=='4'||argv[1][i]=='5'||argv[1][i]=='6'||argv[1][i]=='7'
            ||argv[1][i]=='8'||argv[1][i]=='9')
            {
                int k=atoi(argv[1]);
                if(k>0)
                {
                    e=true;
                }
                else
                {
                    e=false;
                }
            }
            else
            {
                e=false;
            }
        }
        if(e==true)
        {
            string plaintext=get_string("plaintext: ");
            int k=atoi(argv[1]);
            printf("ciphertext: ");
            for(int i=0,n=strlen(plaintext);i<n;i++)
            {
                if((int)plaintext[i]>=65&&(int)plaintext[i]<=90)
                {
                    h=((int)plaintext[i]+k);
                    if(h>90)
                    {
                        h=h-26;
                    }
                }
                else if((int)plaintext[i]>=97&&(int)plaintext[i]<=122)
                {
                    h=(int)plaintext[i]+k;
                    if(h>122)
                    {
                        h=h-26;
                    }
                }
                else
                {
                    h=(int)plaintext[i];
                }
                char c=(char)h;
                printf("%c",c);
                if(i==n-1)
                {
                    printf("\n");
                }
            }
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    return 0;
}