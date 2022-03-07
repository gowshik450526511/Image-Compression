#include<iostream>
using namespace std;
void sorting_freq(int **frequency,int size)
    {
        int temp;
        for(int i=0;i<size-1;i++)
        {
            for(int j=0;j<size;j++)
            {
                    if(frequency[i][1]>frequency[j][1])
                    {
                        temp=frequency[i][1];
                        frequency[i][1]=frequency[j][1];
                        frequency[j][1]=temp;
                        temp=frequency[i][0];
                        frequency[i][0]=frequency[j][0];
                        frequency[j][0]=temp;
                    }

            }
        }
        /*for(int i=0;i<size;i++)
        {
            cout<<setw(10)<<frequency[i][0]<<"\t\t"<<frequency[i][1]<<"\n";
        }*/
    }
