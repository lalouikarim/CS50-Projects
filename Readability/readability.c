#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
int main(void)
{
    string text=get_string("text: ");
    int nl,nw,ns;
    nl=0;
    nw=0;
    ns=0;
    for(int i=0,n=strlen(text);i<n;i++)
    {
        if(((int)text[i]>=65&&(int)text[i]<=90)||((int)text[i]>=97&&(int)text[i]<=122))
        {
            nl=nl+1;
        }
        if((int)text[i]==32)
        {
            nw=nw+1;
        }
        if((int)text[i]==46||(int)text[i]==33||(int)text[i]==63)
        {
            ns=ns+1;
            if(ns>=2)
            {
                nw=nw-1;
            }
        }
    }
    nw=nw+ns;
    float L=(nl*100)/nw;
    float S=(ns*100)/nw;
    float x=0.0588*L-0.296*S-15.8;
    int x1=round(x);
    printf("nl= %i\n",nl);
    printf("nw= %i\n",nw);
    printf("ns= %i\n",ns);
    if(x1<1)
    {
        printf("Before Grade 1\n");
    }
    else if(x1>=16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n",x1);
    }
}