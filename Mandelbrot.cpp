#include "./Mandelbrot.hpp"

Mandelbrot::Mandelbrot(
    int width,
    int height,
    float xmin,
    float xmax,
    float ymin,
    float ymax,
    int max_iterations
){
	this->width = width;
	this->height = height;
	this->xmin = xmin;
	this->xmax = xmax;
	this->ymin = ymin;
	this->ymax = ymax;
	this->max_iterations = max_iterations;
}

std::vector<unsigned char> Mandelbrot::drawLine(int lineNumber){
	std::vector<unsigned char> linePixels = std::vector<unsigned char>(this->width * 4,0);
	int y = lineNumber;
	float zoomX = this->width/((float) this->xmax - this->xmin);
	float zoomY = this->height/((float) this->ymax - this->ymin);

	for(int x = 0; x < this->width; x++){
		float c_r = x / zoomX + this->xmin;
		float c_i = y / zoomY + this->ymin;
		float z_r = 0;
		float z_i = 0;
		int i = 0;

		do {
			float tmp = z_r;
			z_r = z_r*z_r - z_i*z_i + c_r;
			z_i = 2*z_i*tmp + c_i;
			i++;
		}while(z_r*z_r + z_i*z_i < 4 && i < this->max_iterations);
		if(i == this->max_iterations){

		}
		else{
			linePixels[x * 4 + 2] = ((float) i)/((float)this->max_iterations)*(float) 255;
		}
	}
	
	return linePixels;
}