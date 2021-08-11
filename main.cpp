#include "calc.hpp"

#ifndef PC
	APP_NAME("CPfactals")
	APP_DESCRIPTION("A short description of my app")
	APP_AUTHOR("ThatLolaSnail")
	APP_VERSION("0.0.0")
#endif

//RNG inspired by https://github.com/Qqwy/SimpleRNG/blob/master/c/simple_rng.c
//class RNG {
//public:
	int randomInt = 1;
	uint32_t nextRand(){
		randomInt^=randomInt<<13;
		randomInt^=randomInt>>17;
		randomInt^=randomInt<< 5;
		return randomInt;
	}
//};

class Fractal {
public:
	float x = 160; //If the first point is already in the fractal, there are no ugly points outside the fractal
	float y =   0;
	float a[4] = {	 0.849,	 0.197,	-0.150,	 0.000	};
	float b[4] = {	 0.037,	-0.226,	 0.283,	 0.000	};
	float c[4] = {	-0.037,	 0.226,	 0.260,	 0.000	};
	float d[4] = {	 0.849,	 0.197,	 0.237,	 0.160	};
	float e[4] = {	 0.075,	 0.400,	 0.575,  0.500	};
	float f[4] = {	 0.183,	 0.049,	-0.084,  0.000	};
	//		  70%	  13%	  15%	   2%	//percentage for each thing
	//		  70%	  83%	  98%	 100%	//percentage added
	uint8_t p[4]={	 179,	 212,	 251,	 255	};
	//uint8_t p[4]={	 63,	 127,	 191,	 255	};
	
	void step(){
		int s=0;
		int r = nextRand() & 0xff;
		
		while ( r > p[s] ) s++;
		//println("r=%d s=%d",(int)r,(int)s);

		float u = (a[s]*x) + (b[s]*y) + (e[s]*width);
		float v = (c[s]*x) + (d[s]*y) + (f[s]*width);
		x=u; y=v;
		setPixel((int)x, height-((height-width)/2)-(int)y, color(0,0,0) );
		//println("x=%d y=%d",(int)x,(int)y);

	}

};

//The acutal main
void main2(){
	
	//Clear the screen
	fillScreen(color(255,255,255));
	LCD_Refresh();

	//Create the fractal object
	Fractal fractal;

	//Use the fractal object to draw a fractal

	//repeat until a key is pressed
	int drawing = 400; //The amount of points divided by 100
	while(true){
		
		if (drawing){
			//calculate 100 points
			for(long i=0; i<100; i++)
				fractal.step();
			//Update the screen
			LCD_Refresh();
			drawing--;
		}

		uint32_t key1, key2;
		getKey(&key1, &key2);
		if(testKey(key1, key2, KEY_CLEAR)){
			break;
		}
		if(testKey(key1, key2, KEY_EXE)){
			break;
		}
	}

}
