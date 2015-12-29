// Code for RGB Rotary encoder https://www.sparkfun.com/products/10982
// Encoder has 4 states per tick

#include <stdio.h>
#include <signal.h>
#include <wiringPi.h>

static volatile int counter;

static volatile int keepRunning = 1;
void intHandler(int dummy) {
	keepRunning = 0;
	printf("Program stopped\n");
}

void interrupt(void){
	static int lastEncoded = 0;
	static int clockwise = 0;
	static int cclockwise = 0;

	int MSB = digitalRead(18);
	int LSB = digitalRead(16);

	int encoded = (MSB << 1) | LSB;
	int sum = (lastEncoded << 2) | encoded;

	// ++ clockwise, -- counter clockwise
	if(sum == 13 || sum == 4 || sum == 2 || sum == 11){
		cclockwise++;
		clockwise = 0;
		if(cclockwise >= 4){
			cclockwise = 0;
			counter--;
			printf("%i\n", counter);
		}
	}
	if(sum == 14 || sum == 7 || sum == 1 || sum == 8 ){
		clockwise++;
		cclockwise = 0;
		if(clockwise >= 4){
			clockwise = 0;
			counter++;
			printf("%i\n", counter);
		}
	}

	lastEncoded = encoded;
}

int main(void) {
	wiringPiSetup ();
	wiringPiSetupPhys();
	pinMode(16,INPUT) ;
	pinMode(18,INPUT);
	pullUpDnControl(16,PUD_UP);
	pullUpDnControl(18,PUD_UP);

	wiringPiISR(16, INT_EDGE_BOTH, &interrupt);
	wiringPiISR(18, INT_EDGE_BOTH, &interrupt);

	counter = 0;

	while(keepRunning){
		delay(10000);
	}
	return 0;
}