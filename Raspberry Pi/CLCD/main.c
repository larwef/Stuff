#include <stdio.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringSerial.h>

static volatile int counter;
int fd;

static volatile int keepRunning = 1;
void intHandler(int dummy) {
	keepRunning = 0;
	printf("Program stopped\n");
}

void interrupt(void){
	printf("Interrupt!\n");
	static int lastEncoded = 0;
	static int clockwise = 0;
	static int cclockwise = 0;
	static char buffer[4];

	int MSB = digitalRead(18);
	int LSB = digitalRead(16);

	int encoded = (MSB << 1) | LSB;
	int sum = (lastEncoded << 2) | encoded;

	if(sum == 13 || sum == 4 || sum == 2 || sum == 11){
		cclockwise++;
		clockwise = 0;
		if(cclockwise >= 4){
			cclockwise = 0;
			counter--;
			sprintf(buffer,"%i",counter);
			serialPutchar(fd,(char)254);
			serialPutchar(fd,(char)128);
			serialPrintf(fd,"    "); // Clears 4 characters
			serialPutchar(fd,(char)254);
			serialPutchar(fd,(char)128);
			serialPrintf(fd,buffer);
		}
	}
	if(sum == 14 || sum == 7 || sum == 1 || sum == 8 ){
		clockwise++;
		cclockwise = 0;
		if(clockwise >= 4){
			clockwise = 0;
			counter++;
			sprintf(buffer,"%i",counter);
			serialPutchar(fd,(char)254);
			serialPutchar(fd,(char)128);
			serialPrintf(fd,"    "); // Clears 4 characters
			serialPutchar(fd,(char)254);
			serialPutchar(fd,(char)128);
			serialPrintf(fd,buffer);
		}
	}

	lastEncoded = encoded;
}

int main(void) {
	wiringPiSetup ();
	wiringPiSetupPhys();
	pinMode(16,INPUT);
	pinMode(18,INPUT);
	pullUpDnControl(16,PUD_UP);
	pullUpDnControl(18,PUD_UP);

	wiringPiISR(16, INT_EDGE_BOTH, &interrupt);
	wiringPiISR(18, INT_EDGE_BOTH, &interrupt);

	if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0){
	printf("Error opening serial device\n");
		return 1 ;
	}

	counter = 0;
	// Clear screen
	serialPutchar(fd,(char)254); //Move cursor to beginning of first line
	serialPutchar(fd,(char)128);
	serialPrintf(fd,"                ");
	serialPrintf(fd,"                ");

	while(keepRunning){
		waitForInterrupt(18,-1);
	}
	return 0;
}