#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i,j,av;
    float average;
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            average=(image[i][j].rgbtBlue+image[i][j].rgbtGreen+image[i][j].rgbtRed)/3;
            av=ceil(average);
            image[i][j].rgbtBlue=av;
            image[i][j].rgbtGreen=av;
            image[i][j].rgbtRed=av;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int i,j,ab,ag,ar;
    float avb,avg,avr;
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            avr=.393*image[i][j].rgbtRed+.769*image[i][j].rgbtGreen+.189*image[i][j].rgbtBlue;
            ar=round(avr);
            if(ar>255)
            {
                ar=255;
            }
            image[i][j].rgbtRed=ar;
            avg=.349*image[i][j].rgbtRed+.686*image[i][j].rgbtGreen+.168*image[i][j].rgbtBlue;
            ag=round(avg);
            if(ag>255)
            {
                ag=255;
            }
            image[i][j].rgbtGreen=ag;
            avb=.272*image[i][j].rgbtRed+.534*image[i][j].rgbtGreen+.131*image[i][j].rgbtBlue;
            ab=round(avb);
            if(ab>255)
            {
                ab=255;
            }
            image[i][j].rgbtBlue=ab;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i,j,k,h;
    RGBTRIPLE a[height][1];
    for(h=0;h<height;h++)
    {
        i=0;
        k=width-1;
        while(i<k)
        {
            a[h][0].rgbtBlue=image[h][i].rgbtBlue;
            a[h][0].rgbtGreen=image[h][i].rgbtGreen;
            a[h][0].rgbtRed=image[h][i].rgbtRed;
            image[h][i].rgbtBlue=image[h][k].rgbtBlue;
            image[h][i].rgbtGreen=image[h][k].rgbtGreen;
            image[h][i].rgbtRed=image[h][k].rgbtRed;
            image[h][k].rgbtBlue=a[h][0].rgbtBlue;
            image[h][k].rgbtGreen=a[h][0].rgbtGreen;
            image[h][k].rgbtRed=a[h][0].rgbtRed;
            i=i+1;
            k=k-1;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i,j,k,h,a,f,e,s;
    float av;
    i=0;
    j=0;
    while(i<height)
    {
        s=0;
        if(i==0)
        {
            k=i;
            while(j<width)
            {
                s=0;
                if(j==0)
                {
                     h=j;
                     for(f=k;f<=k+1;f++)
                     {
                           for(e=h;e<=h+2;e++)
                           {
                                  s=s+image[f][e].rgbtBlue+image[f][e].rgbtGreen+image[f][e].rgbtRed;
                           }
                     }
                }
                else
                {
                     h=j-1;
                     for(f=k;f<=k+1;f++)
                     {
                            while(e<=width-1&&e<=h+2)
                            {
                                 s=s+image[f][e].rgbtBlue+image[f][e].rgbtGreen+image[f][e].rgbtRed;
                                 e=e+1;
                            }
                     }
                }
                av=s/27;
                a=round(av);
                image[i][j].rgbtBlue=a;
                image[i][j].rgbtGreen=a;
                image[i][j].rgbtRed=a;
                j=j+1;
            }
        }
        else
        {
            k=i-1;
            while(j<width)
            {
                s=0;
                if(j==0)
                {
                     h=j;
                     while(f<=height-1&&f<=k+2)
                     {
                           for(e=h;e<=h+1;e++)
                           {
                                  s=s+image[f][e].rgbtBlue+image[f][e].rgbtGreen+image[f][e].rgbtRed;
                           }
                           f=f+1;
                     }
                }
                else
                {
                     h=j-1;
                     while(f<=height-1&&f<=k+2)
                     {
                            while(e<=width-1&&e<=h+2)
                           {
                            s=s+image[f][e].rgbtBlue+image[f][e].rgbtGreen+image[f][e].rgbtRed;
                            e=e+1;
                           }
                           f=k+1;
                     }
                }
                av=s/27;
                a=round(av);
                image[i][j].rgbtBlue=a;
                image[i][j].rgbtGreen=a;
                image[i][j].rgbtRed=a;
                j=j+1;
            }
        }
        i=i+1;
    }
    return;
}
