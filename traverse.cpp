#include<iostream>
#include<string.h>
#include<iomanip>
using namespace std;
int sum=0;
char str[256][15];
void binaryfying(int **image,char *binary,int height,int width);

int traverse(struct node *root,int z)
{
    //Static variables are used because during recursion value should not be changed
    static int a[15],k=0,f=0;
    char tmp[15];                           //z=0 as it should not take any value(0 or 1) for the first time
    if(root == NULL)
        return 0;
    if(f!=0)
    {
        a[k]=z;
        k++;
    }
    else
    {
        f++;
    }

    traverse(root->left,0);   //0 for left node
    traverse(root->right,1);  //1 for right node

    //Breaking the Array and storing the encoded value in a string and going back by one step
    if(root->left == NULL && root->right == NULL)
    {
        int i=0;
        cout<<setw(6)<<root->data<<"\t"<<setw(6)<<root->freq<<"\t"<<setw(6);
        for(int i=0;i<k;i++)
            cout<<a[i];           //binary
        cout<<endl;

        for(i=0;i<k;i++)
        {
            tmp[i]=a[i]+48;              //here
                                        //Converting integer into char
        }
        tmp[i]='\0';
        strcpy(str[root->data],tmp);
        //cout<<str[root->data]<<"\n";
        //Calculating the Total number of bits
        //sum=sum+((root->freq)*k);
        k--;

        return 0;
    }
    k--;
    return 0;
}

void binaryfying(int **image,char *binary,int height,int width)
{
    int i,j;
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            strcat(binary,str[image[i][j]]);     //here we storing the encoded value in a string
        }
    }
}

