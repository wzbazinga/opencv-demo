/*************************************************************************
	> File Name: main.cpp
	> Author: WangZhe
	> Mail: wangzhe140@163.com
	> Created Time: 2016年11月16日 星期三 22时51分29秒
	>
    > function: histogram match
 ************************************************************************/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

double df1[256],df2[256];

void init(){
    for(int i=0;i<256;i++){
        df1[i]=0,df2[i]=0;
    }
}

int main(){
    char name1[20]="../lena.jpg";
    char name2[20]="../renge.png";
    
    Mat in1=imread(name1,1);
    Mat in2=imread(name2,1);

    int pixels1=in1.rows*in1.cols,pixels2=in2.rows*in2.cols;
    int lut[256];//look up table

    imshow("in1-origin",in1);
    imshow("in2-origin",in2);
    

    int all;
    for(int i=0;i<3;i++){
        init();
        uchar* p=in1.data+i;
        for(int j=0;j<pixels1;j++){
            df1[*p]++;
            p+=3;
        }
        all=0;
        for(int j=0;j<256;j++){
            all+=df1[j];
            df1[j]=(double)all/pixels1;
        }
        
        p=in2.data+i;
        for(int j=0;j<pixels2;j++){
            df2[*p]++;
            p+=3;
        }
        all=0;
        for(int j=0;j<256;j++){
            all+=df2[j];
            df2[j]=(double)all/pixels2;
        }
        
        int a=0,b=0;
        while(true){
            if(a>255)break;
            while(a<256&&df2[b]>=df1[a]){
                lut[a]=b;
                a++;
            }
            b++;
        }
        
        p=in1.data+i;
        for(int j=0;j<pixels1;j++){
            *p=lut[*p];
            p+=3;
        }
    }

    imshow("in1-matched",in1);
    waitKey(0);

    return 0;
}

