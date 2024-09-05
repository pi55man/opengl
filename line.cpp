#include <iostream>
#include <math.h>
#include <cmath>
void writepx(int x, int y){
	std::cout <<x<<","<<y<<std::endl;
}

int rd(double y){
	return std::floor(0.5+y);
}

int main(){
	int x0 = 2, y0 = 3; 
	int x1 = 6, y1 = 15;
	double y= y0;
	double dy = y1-y0;
	double dx = x1-x0;
	double m = dy/dx;
	for(int x=x0;x<=x1;x++){
		writepx(x,rd(y));
		y=y+m;
	} 

}
