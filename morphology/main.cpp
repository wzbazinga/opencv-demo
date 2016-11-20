/*************************************************************************
	> File Name: main.cpp
	> Author: WangZhe
	> Mail: wangzhe140@163.com
	> Created Time: 2016年11月20日 星期日 12时19分39秒
	>
	> morphology operation
	> dilate & erode
	>
	> too slow
    > cando: 二维线段树加速最大最小值查询
 ************************************************************************/

#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

char name[]="../images/renge.png";
int iserode;
int kernel;
int step,chan;
Mat src=imread(name);

int getValue(int x1,int y1,int x2,int y2,int c){
    uchar ret;
    if(iserode==0)
        ret=255;
    else
        ret=0;
    uchar* p=src.data;
    for(int i=x1;i<=x2;i++){
        for(int j=y1;j<=y2;j++){
            if(iserode==0){
                ret=min(ret,p[(i-1)*step+(j-1)*chan+c]);
            }
            else{
                ret=max(ret,p[(i-1)*step+(j-1)*chan+c]);
            }
        }
    }
    cout<<ret<<endl;
    return ret;
}

void on_callback(int,void*){
    Mat dst=Mat(src.size(),src.type());
    int r=src.rows+1,c=src.cols+1;
    for(int t=0;t<chan;t++){
        for(int i=1;i<r;i++){
            for(int j=1;j<c;j++){
                int x1=max(1,i-kernel),y1=max(1,j-kernel),x2=min(r,i+kernel),y2=min(c,j+kernel);
                dst.data[(i-1)*step+(j-1)*chan+t]=getValue(x1,y1,x2,y2,t);
            }
        }
    }
    imshow("dilate erode",dst);
}

void on_callback1(int,void*){
    Mat dst=src.clone();
    Mat se=getStructuringElement(MORPH_RECT,Size(2*kernel+1,2*kernel+1));
    if(iserode==0)
        dilate(src,dst,se);
    else
        erode(src,dst,se);

    imshow("opencv d&e",dst);
}

int main(){ 
    chan=src.channels();
    step=src.step;

    iserode=0,kernel=0;

    namedWindow("dilate erode",1);
    createTrackbar("trigger","dilate erode",&iserode,1,on_callback);
    createTrackbar("kernels","dilate erode",&kernel,10,on_callback);

    namedWindow("opencv d&e",1);
    createTrackbar("trigger","opencv d&e",&iserode,1,on_callback1);
    createTrackbar("kernels","opencv d&e",&kernel,10,on_callback1);

    waitKey(0);
    return 0;
}

