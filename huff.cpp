#include<iostream>
#include<cstdlib>
#include<stdint.h>
#include<iomanip>
#include<queue>
using namespace std;

struct node
{
    unsigned int data;
    unsigned int freq;
    node *left,*right;
}*ptr;

struct heap
{
    unsigned int size;
    struct node **array;
}*h;

node* create_node(unsigned int data,unsigned int freq)
{
    struct node *temp=new node;
    temp=new node;
    temp->data = data;
    temp->freq = freq;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}

void heapify(struct heap *h,int index)
{
    int a=index,b=index+1;

    int k=0,j;

    //cout<<h->array[a]->freq<<" "<<h->array[b]->freq<<"\n";

    //we add the 2 frequencies to store in the frequency sum
    int frequency_sum = h->array[a]->freq + h->array[b]->freq;

    struct node *m=create_node(0,frequency_sum); //after that we put the frequency sum in the new node  an it return address of the  node;

    m->left=h->array[a]; //make the first extracted  node as its left child
    m->right=h->array[b]; //make the second extracted  node as its right child;

    for(int i=index+2;i<h->size;i++)
    {
            if(h->array[i]->freq >= m->freq)  //we compare all the frequency with the frequency sum
            {
                for(int j=index+2;j<=i;j++)
                {
                    h->array[j-1]=h->array[j];
                }
                h->array[i]=m;
                k=1;
                break;
        	}
    }
    if(k==0)
    {
        for(j=index+2;j<h->size;j++)
        {
            h->array[j-1]=h->array[j];
        }
        h->array[j-1]=m;
    }
    //cout<<h->array[index]->data<<"\t"<<h->array[index]->freq<<endl;
}
struct node* tree()
{
    int l=0;
    for(l=0;l<(h->size)-1;l++)
    {
        heapify(h,l);
    }
    return h->array[h->size-1]; //root
}

