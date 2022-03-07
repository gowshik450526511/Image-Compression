#include<bits/stdc++.h>
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iomanip>
#include "huff.cpp"
#include "sorting.cpp"
#include "traverse.cpp"
using namespace std;

int traverse(struct node *root,int z);

void binaryfying(int **image,char *binary,int height,int width);

int **frequency;

char binary[32000];

struct node *root;

void load_bmp(int& height,int& width)
{

    int max_pixel=256,length;
    char ch[200];
	FILE *file,*f,*bin_file;

    char filename[]="lenagray.bmp";
	int data,offset,hbytes;
	long bmpsize=0,bmpdataoff=0,bpp=0;
	int temp=0;
	int** image;
	FILE *image_file,*binary_file;
	image_file = fopen(filename,"rb");
	if(image_file==NULL)
	{
		printf("Error Opening File!!");
	}
	else
	{
		//Set file position of the stream to the beginning
		printf("Processing BMP Header...\n\n");

		offset = 0;

		fseek(image_file,offset,SEEK_SET); //it is used to traverse to the file depending on the no of bytes given

		printf("Getting file ID...\n\n");
		for(int i=0;i<2;i++)
		{
			fread(&data,1,1,image_file);  //read the file id
			printf("%c",data);
		}
		printf("\n\nGetting size of BMP File...\n\n");

		fread(&bmpsize,4,1,image_file); //size of the integer is 4

		printf("Size of the BMP File:: %ld bytes\n\n",bmpsize);

		printf("Getting offset where the pixel arrray starts...\n\n");

		offset = 10;  //purpose
                    // the offset, i.e starting address of the byte where bit map image data (pixel array) can be found

		fseek(image_file,offset,SEEK_SET);    //seek set is used to beginning of file.

		fread(&bmpdataoff,4,1,image_file);

		printf("Bitmap data offset:: %ld\n\n",bmpdataoff);

		printf("DIB Header\n\n");     //bitmap information header.


		fread(&hbytes,4,1,image_file);

		printf("Number of bytes in header:: %d\n\n",hbytes);

		fread(&width,4,1,image_file);
		fread(&height,4,1,image_file);

		printf("Width of Image: %d\n",width);
		printf("Height of image: %d\n\n",height);

		fseek(image_file,2,SEEK_CUR); //current position of file pointer
		fread(&bpp,2,1,image_file);

		printf("Number of bits per pixel: %ld\n\n",bpp);

    //"Setting offset to start of pixel data...
		fseek(image_file,bmpdataoff,SEEK_SET);

        image = (int **)malloc(height*sizeof(int *));  //creating image array

		for(int i=0;i<height;i++)
		{
            image[i] = (int *)malloc(width*sizeof(int));
		}
		//cout<<"The pixel intensities of image and their frequencies<<\n\n";
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                fread(&temp, 3, 1, image_file);

                // the Image is a
                // 24-bit BMP Image
                temp = temp & 0x0000FF;
              //cout<<temp;
                image[i][j] = temp;
               // cout<<image[i][j];
                //cout<<"\t";

            }
        }
        fclose(image_file);

        f = fopen("lenagray.bmp","rb");
        /*file = fopen("image_Header.txt","w");

		fgets(ch,bmpdataoff,f);
		fputs(ch,file);*/

		//cout<<ch<<endl<<endl<<"dfbdg"<<"\n\n";

        fclose(f);
	}
	frequency=new int*[256];  //dynamically allocating 256  because bitmap image has max pixel is 256


	for(int i=0;i<max_pixel;i++)
    {
        frequency[i]=new int[2];
    }

    //Assigning initially with 0.
    for(int i=0;i<max_pixel;i++)
    {
        frequency[i][1]=0;  //first we initialize all the frequencies is 0
        frequency[i][0]=i;
    }
     //cout<<"The pixel intensities of image and their frequencies<<\n\n";
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            frequency[image[i][j]][1]++;         //counting the pixel intensity frequencies
        }
    }


    sorting_freq(frequency,max_pixel);   //sorting


    for(int i=0;i<max_pixel;i++)
    {
        if(frequency[i][1]!=0)
        {
            cout<<frequency[i][0]<<"\t"<<frequency[i][1]<<"\n\n";
        }
    }
       //storing the frequency into the file for reuse:
    file=fopen("pixel_freq.c","w");

     fprintf(file,"PIXEL_VALUE");
     fprintf(file,"\t");
     fprintf(file,"PIXEL_FREQ");
     fprintf(file,"\n");

    for(int i=0;i<max_pixel;i++)
    {

        if(frequency[i][1]!=0)    //if pixel intensity value is not 0 then store it in the file.
        {
            fprintf(file,"%d",frequency[i][0]);
            fprintf(file,"\t\t");
            fprintf(file,"%d",frequency[i][1]);
            fprintf(file,"\n");

        }
    }

    fclose(file);

    h=new heap; //dynamically allocating heap;

    for(int i=0;i<max_pixel;i++)
    {
        if(frequency[i][1]!=0)
        {
            h->size++;   //if pixel intensity is not equal to 0 then size increases
        }
    }
    //cout<<"SIZE OF THE HEAP:"<<setw(15)<<h->size<<"\n";

    int o=0;
     //Allocating heap memory
    h->array = new node*[h->size];

   // cout<<h->array<<"\n";

    for(int i=0;i<max_pixel;i++)
    {
        if(frequency[i][1]!=0)
        {
            h->array[o]=create_node(frequency[i][0],frequency[i][1]); //here we create a node for each unique pixel intensity and
                                                                    //bulid a min heap of all leaf nodes.
            o++;
        }
    }
    //find1();
    //finding the root
    root=tree();


    cout<<setw(20)<<"TRAVERSE"<<"\n\n";
    traverse(root,0);

    cout<<"\n\n\n";

    binaryfying(image,binary,height,width);

    length=strlen(binary);


    //cout<<binary<<"\n\n";

    cout<<"\n\n"<<"LENGTH OF BINARY:"<<setw(15)<<length<<"\n";

    //cout<<"\n\n"<<"LENGTH OF BINARY /8:"<<setw(15)<<(length/8)<<"\n\n\n";


    file=fopen("Huffmann_encode.txt","wb");
    char ch1;
    int k=0;
    int l=0,m=0;

    for(int i=0;i<strlen(binary)/8;i++)
    {
        int sum=0;
        for(int j=0;j<8;j++)
        {
            sum+=((binary[k]-48)*pow(2,7-j));  //this is an encoding part
            k++;
        }
        ch1=(char)sum;
       // cout<<sum<<" "<<ch1<<"\n\n";
        putc(ch1,file);
        l++;
    }
    fclose(file);


    //cout<<endl<<l;
    l=0;


    file=fopen("Huffmann_encode.txt","rb");
    cout<<endl;
    cout<<"ENCODE:"<<"\n\n";
    //cout<<endl<<ch<<endl;
    while(!feof(file))
    {
        ch1=getc(file);
        cout<<ch1;
        l++;
    }
    l--;
    //cout<<"\n\n\n"<<sum/8;
    cout<<"\n\n\n"<<"AFTER COMPRESSING LENGTH OF BINARY:"<<l<<"\n\n";

}
int main()
{
     struct node *root;
     int height=0,width=0;
     load_bmp(height,width);
}

