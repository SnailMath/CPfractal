#include "calc.hpp"

#ifndef PC
	APP_NAME("CPfactals")
	APP_DESCRIPTION("Fractals. Use num/arrow keys, 7+9 change selecction, 1+3 change step width, 5 toggle, '.' draw more.")
	APP_AUTHOR("SnailMath")
	APP_VERSION("1.0.0")
#endif

#define MAXS 4

//#define Y(y) (height-((height-width)/2)-y)
#define Y(y) (height-y)

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
	float x = 160;
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
	//uint8_t p[S]={	 63,	 127,	 191,	 255	};
	
	//void init(){
		//x = 160; //If the first point is already in the fractal, there are no ugly points outside the fractal
		//y = 0;
		//amount=40000; //the amount of pixels required
	//}

	//use a random equation
	void step(){
		int s=0;
		int r = nextRand() & 0xff;
		
		while ( r > p[s] ) s++;
		calc(s,x,y,&x,&y);
		setPixel((int)x, Y((int)y), color(0,0,0) );
	}
	//use a specific equation
	void calc(int s,float x,float y, float* outx, float* outy){
		float u = (a[s]*x) + (b[s]*y) + (e[s]*width);
		float v = (c[s]*x) + (d[s]*y) + (f[s]*width);
		*outx = u; *outy = v;

	}

};

//The acutal main
void main2(){
	
	//Create the fractal object
      Fractal fractal;

	//Use the fractal object to draw a fractal
	
	//iniyialize variables
	bool keyPressed=false; //if a key is currently being held down
	uint8_t es = 0 ; //edit s (which square is selected?)
	uint8_t ev = 2 ; //edit value (which value is selected)
	bool redraw=true;//do we need to start from scratch?
	long amount = 40000; //the amount that still needs to be drawn
	float keystep = 0.001; //the step with each keypress
	bool visible = true; //if boxes are visible

	//repeat until a key is pressed
	while(true){
	
		//Clear the screen
		if(redraw){
			fillScreen(color(255,255,255));
			randomInt = 1; //Reset the RNG
			amount = 40000;
			redraw=false;
			//fractal.init();
		}
		
		//calculate 1000 points
		if(amount){ //if the fractal is not fully drawn yet
			for(long i=0; i<1000; i++)
				fractal.step();
			amount-=1000;
		}
			
		//draw boxes to show the equations
		if(visible)
			for (int s=0; s<MAXS; s++){
				float x0,y0,x1,y1,x2,y2,x3,y3;
				fractal.calc(s,    0,     0,&x0,&y0);
				fractal.calc(s,width,     0,&x1,&y1);
				fractal.calc(s,width,height,&x2,&y2);
				fractal.calc(s,    0,height,&x3,&y3);
				#define sel color(255,0,0)
				#define uns color(255,192,192)
				line(x0,Y(y0),x1,Y(y1),(es!=s)?uns:(ev!=1?sel:uns));
				line(x1,Y(y1),x2,Y(y2),(es!=s)?uns:(ev==2?sel:uns));
				line(x2,Y(y2),x3,Y(y3),(es!=s)?uns:(ev==2?sel:uns));
				line(x3,Y(y3),x0,Y(y0),(es!=s)?uns:(ev!=0?sel:uns));
			}
		//Update the screen
		LCD_Refresh();

      		uint32_t key1, key2;
      		getKey(&key1, &key2);
      		if(key1||key2){
			if(!keyPressed){
				//If the key was pressed, not held
				if(testKey(key1, key2, KEY_7)){
					es++; if(es==MAXS) es=0;
				}
				if(testKey(key1, key2, KEY_9)){
					ev++; if(ev==3) ev=0;
				}
				if(testKey(key1, key2, KEY_1)){
					keystep *=.5;
				}
				if(testKey(key1, key2, KEY_3)){
					keystep *=2;
				}
				if(testKey(key1, key2, KEY_DOT)){
					amount = 40000;
				}
				if(testKey(key1, key2, KEY_5)){
					if (visible){
						visible = false;
						redraw = true;
					} else {
						visible = true;
					}
				}
			}
			//Pressed or held down
			//up (y++) or key 8
			if(testKey(key1, key2, KEY_8)
			|| testKey(key1, key2, KEY_UP)){
				if(ev==0) fractal.c[es]=fractal.c[es]+keystep;
				if(ev==1) fractal.d[es]=fractal.d[es]+keystep;
				if(ev==2) fractal.f[es]=fractal.f[es]+keystep;
				redraw=true;
			}
			//down (y--) or key 2
			if(testKey(key1, key2, KEY_2)
			|| testKey(key1, key2, KEY_DOWN)){
				if(ev==0) fractal.c[es]=fractal.c[es]-keystep;
				if(ev==1) fractal.d[es]=fractal.d[es]-keystep;
				if(ev==2) fractal.f[es]=fractal.f[es]-keystep;
				redraw=true;
			}
			//left (x--) or key 4
			if(testKey(key1, key2, KEY_4)
			|| testKey(key1, key2, KEY_LEFT)){
				if(ev==0) fractal.a[es]=fractal.a[es]-keystep;
				if(ev==1) fractal.b[es]=fractal.b[es]-keystep;
				if(ev==2) fractal.e[es]=fractal.e[es]-keystep;
				redraw=true;
			}
			//left (x++) or key 6
			if(testKey(key1, key2, KEY_6)
			|| testKey(key1, key2, KEY_RIGHT)){
				if(ev==0) fractal.a[es]=fractal.a[es]+keystep;
				if(ev==1) fractal.b[es]=fractal.b[es]+keystep;
				if(ev==2) fractal.e[es]=fractal.e[es]+keystep;
				redraw=true;
			}

			//if(testKey(key1, key2, KEY_3)){
			//	fractal.f[0]=fractal.f[0]-.01;
			//	redraw=true;
			//}
			//if(testKey(key1, key2, KEY_4)){
			//	fractal.f[0]=fractal.f[0]+.01;
			//	redraw=true;
			//}
			if(testKey(key1, key2, KEY_CLEAR)){
				break;
			}
			if(testKey(key1, key2, KEY_EXE)){
				break;
			}
			keyPressed=true;
		}else{
			keyPressed=false;
		}
	}
}
