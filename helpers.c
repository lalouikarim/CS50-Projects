#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i,j,av,av_1;
    float average,difference,difference_1;
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            average=(float)(image[i][j].rgbtBlue+image[i][j].rgbtGreen+image[i][j].rgbtRed)/3;
            av=floor(average);
            av_1=ceil(average);
            difference=average - (float)av;
            difference_1=(float)av_1 - average;
            if(difference<difference_1)
            {
                av=floor(average);
            }
            else
            {
                av=ceil(average);
            }
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
    int i,j,ab,ag,ar,ab_1,ag_1;
    float avb,avg,avr,difference_g,difference_g_1,difference_b,difference_b_1;
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            //Red
            avr=.393*image[i][j].rgbtRed+.769*image[i][j].rgbtGreen+.189*image[i][j].rgbtBlue;
            ar=floor(avr);
            int ar_1=ceil(avr);
            float difference_r=avr - (float)ar;
            float difference_r_1=(float)ar_1 - avr;
            if(difference_r<difference_r_1)
            {
                ar=floor(avr);
            }
            else
            {
                ar=ceil(avr);
            }
            if(ar>255)
            {
                ar=255;
            }
            //Green
            avg=.349*image[i][j].rgbtRed+.686*image[i][j].rgbtGreen+.168*image[i][j].rgbtBlue;
            ag=floor(avg);
            ag_1=ceil(avg);
            difference_g=avg - (float)ag;
            difference_g_1=(float)ag_1 - avg;
            if(difference_g<difference_g_1)
            {
                ag=floor(avg);
            }
            else
            {
                ag=ceil(avg);
            }
            if(ag>255)
            {
                ag=255;
            }
            //Blue
            avb=.272*image[i][j].rgbtRed+.534*image[i][j].rgbtGreen+.131*image[i][j].rgbtBlue;
            ab=floor(avb);
            ab_1=ceil(avb);
            difference_b=avb - (float)ab;
            difference_b_1=(float)ab_1 - avb;
            if(difference_b<difference_b_1)
            {
                ab=floor(avb);
            }
            else
            {
                ab=ceil(avb);
            }
            if(ab>255)
            {
                ab=255;
            }
            image[i][j].rgbtRed=ar;
            image[i][j].rgbtGreen=ag;
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
   int i,j,k,h,f,c,g,e,av_r,av_r_1,av_g,av_g_1,av_b,av_b_1;
   float average_b,average_r,average_g,difference_r,difference_r_1,difference_g,difference_g_1,difference_b,difference_b_1;
   for(i=0;i<height;i++)
   {
       k=i;
       if(k+1<height)
       {
           f=k+1;
       }
       else
       {
           f=k;
       }
       if(k-1>=0)
       {
           g=k-1;
       }
       else
       {
           g=k;
       }
       for(j=0;j<width;j++)
       {
           h=j;
           int sum_r=0;
           int sum_g=0;
           int sum_b=0;
           int counter=0;
           if(h+1<width)
           {
               e=h+1;
           }
           else
           {
               e=h;
           }
           if(h-1>=0)
           {
               c=h-1;
           }
           else
           {
               c=h;
           }
           for(int x=g;x<=f;x++)
           {
               for(int n=c;n<=e;n++)
               {
                   counter++;
                   sum_r=sum_r+image[x][n].rgbtRed;
                   sum_g=sum_g+image[x][n].rgbtGreen;
                   sum_b=sum_b+image[x][n].rgbtBlue;
               }
           }
           //new blue
           average_b=(float) sum_b/counter;
           av_b=floor(average_b);
           av_b_1=ceil(average_b);
           difference_b=average_b - (float)av_b;
           difference_b_1=(float)av_b_1 - average_b;
           if(difference_b<difference_b_1)
           {
               av_b=floor(average_b);
           }
           else
           {
               av_b=ceil(average_b);
           }
           //new red
           average_r=(float)(sum_r)/counter;
           av_r=floor(average_r);
           av_r_1=ceil(average_r);
           difference_r=average_r - (float)av_r;
           difference_r_1=(float)av_r_1 - average_r;
           if(difference_r<difference_r_1)
           {
               av_r=floor(average_r);
           }
           else
           {
               av_r=ceil(average_r);
           }
           //new green
           average_g=(float) sum_g/counter;
           av_g=floor(average_g);
           av_g_1=ceil(average_g);
           difference_g=average_g - (float)av_g;
           difference_g_1=(float)av_g_1 - average_g;
           if(difference_g<difference_g_1)
           {
               av_g=floor(average_g);
           }
           else
           {
               av_g=ceil(average_g);
           }
           image[i][j].rgbtRed=av_r;
           image[i][j].rgbtGreen=av_g;
           image[i][j].rgbtBlue=av_b;
       }
   }
    return;
}
