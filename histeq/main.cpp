/*************************************************************************
	> File Name: main.cpp
	> Author: WangZhe
	> Mail: wangzhe140@163.com
	> Created Time: 2016年11月16日 星期三 22时15分07秒
	> 
    > function: image histgram euqalization
 ************************************************************************/

#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    Mat in=imread("../lena.jpg",0);
    imshow("lena-origin",in);
    
    int counts[256];//calculate the pixel amount of a particular gray level
    int cdf[256];//cumulative distribution function
    memset(counts,0,sizeof(counts));
    memset(cdf,0,sizeof(cdf));
    int pixels=in.rows*in.cols;

    uchar* p=in.data;
    for(int i=0;i<pixels;i++){
        counts[*p++]++;
    }
    for(int i=0;i<256;i++){
        cdf[i]=counts[i]+(i==0?0:cdf[i-1]);
    }

    p=in.data;
    for(int i=0;i<pixels;i++){
        *p=uchar((double)cdf[*p]/pixels*255);
        p++;
    }

    imshow("lena-equalized",in);
    waitKey(0);
    return 0;
}

