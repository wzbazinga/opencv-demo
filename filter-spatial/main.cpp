/************************************************************************
	> Author: WangZhe
	> Mail: wangzhe140@163.com
	> Created Time: 2016年11月19日 星期六 22时40分29秒
	>
	> filters gallery
 ************************************************************************/

#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;


void mean_filter(Mat& src,Mat& dst,int size=3){//mean filter, convolution kernel is ones(size)
    assert(size&1);
    int r=src.rows+1,c=src.cols+1,chan=src.channels();
    int step=src.step;
    uchar* p=src.data;
    int** s=new int*[r];
    for(int i=0;i<r;i++)
        s[i]=new int[c];

    for(int t=0;t<chan;t++){
        for(int i=1;i<r;i++){
            for(int j=1;j<c;j++){
                s[i][j]=p[(i-1)*step+(j-1)*chan+t]+s[i-1][j]+s[i][j-1]-s[i-1][j-1];
            }
        }
        for(int i=1;i<r;i++){
            for(int j=1;j<c;j++){
                int x1=max(1,i-size/2),y1=max(1,j-size/2),x2=min(r-1,i+size/2),y2=min(c-1,j+size/2);
                int count=(x2-x1+1)*(y2-y1+1);
                dst.data[(i-1)*step+(j-1)*chan+t]=(s[x2][y2]-s[x2][y1-1]-s[x1-1][y2]+s[x1-1][y1-1])/count;
            }
        }
    }
}

int main(){
    char name[]="../renge.png";
    Mat in=imread(name,1);
    imshow("origin",in);
    
    Mat dst=in.clone();
    mean_filter(in,dst,3);
    imshow("mean",dst);

    Mat dst1=in.clone();
    boxFilter(in,dst1,in.depth(),Size(3,3));
    //blur(in,dst1,Size(3,3));
    imshow("cv-boxFilter",dst1);

    Mat dst2=in.clone();
    GaussianBlur(in,dst2,Size(0,0),2,2);
    imshow("gaussian",dst2);

    Mat dst3=in.clone();
    medianBlur(in,dst3,7);
    imshow("median",dst3);

    Mat dst4=in.clone();
    bilateralFilter(in,dst4,45,100,45/2);
    imshow("bilateral",dst4);

    waitKey(0);

    return 0;
}

