#include <iostream>
#include <math.h>
#include <cmath>
void writepx(int x, int y){
	std::cout <<x<<","<<y<<std::endl;
}

int rd(double y){
	return std::floor(0.5+y);
}

void dda(int x0,int y0, int x1, int y1){
	double y= y0;
	double dy = y1-y0;
	double dx = x1-x0;
	double m = dy/dx;
	for(int x=x0;x<=x1;x++){
		writepx(x,rd(y));
		y=y+m;
	}
}

int bresenham(int x0, int y0, int x1, int y1){
	int dy = y1-y0;
	int dx = x1-x0;
	int y = y0;
	int x =  x0;
	int d = 2*dy-dx;
	int deltaE = 2*dy;
	int deltaNE = 2* (dy-dx);
		writepx(x,y);
	while(x<x1){
		if(d<=0){
			x+=1;
			d+=deltaE;
			std::cout<<"ne"<<std::endl;
		}else{
			x+=1;
			y+=1;
			d+=deltaNE;
			std::cout<<"e"<<std::endl;
		}
		writepx(x,y);
	}
	return 0;
}

int main(){
	std::cout<<"BRESENHAM"<<std::endl;
	bresenham(1,2,4,7);
	std::cout<<"DDA"<<std::endl;
	dda(1,1,6,4);
return 0;
}
