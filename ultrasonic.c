/*
This one is to make ultrasonic working example.

Input:	GPIO8(pin24)
Output:	GPIO7(pin26)

3V3		5V
pin3:		5V
pin5:		GND
pin7: pifm	pin8:
GND		pin10:
pin11:		pin12: motor1
pin13: motor2	GND
pin15: motor3	pin16: motor4
3V3		pin18:
pin19:		GND
pin21:		pin22: OneWire(previous for DS18B20)
pin23:		pin24: ultrasonic trig1
GND		pin26: ultrasonic echo1


Outline:
Send a pulse to activate the sensor, and wait for a time to receive the signal.
use Distance = Speed_of_sound * timediff.


You need the wiringPi lib.

Compile: 
gcc -lwiringPi $(this).c

Run:
sudo ./$(this.out)


Thanks the following persons developed the libs which this project used.
wiringPi lib from:	Gordons Projects @ https://projects.drogon.net/raspberry-pi/wiringpi/

This project is created by @DaochenShi (shidaochen@live.com)

20150421 created.
*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>	// for SIG_IGN etc.
#include <errno.h>	// for errno

#define TRIG_GPIO_PIN	10
#define ECHO_GPIO_PIN	11

#define DEBUG

void break_program(int sig);
void myInterrupt(void);
static volatile int loopingStatus = 0;
static volatile struct timespec prevT;
static volatile struct timespec nowT;

int main(int argc, const char* argv[])
{
	int result = 1;
	// run this program in background when not in Debug mode
#ifndef DEBUG
	{
		pid_t pid, sid;
		pid = fork();
		if (pid < 0)
		{
			exit(EXIT_FAILURE);
		}
		if (pid > 0)
		{
			exit(EXIT_SUCCESS);
		}
		
		// change file mode mask
		umask(0);
		// open logs,,, but I did not record any logs
		
		// create SID for child process
		sid = setsid();
		if (sid < 0)
		{
			exit(EXIT_FAILURE);
		}
		
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		//close(STDERR_FILENO);
	}
#endif	
	signal(SIGINT, break_program);
	
	// First to setup wiringPi
	if (wiringPiSetup() < 0)
	{
		fprintf(stderr, "Unable to setup wiringPi: %s \n", strerror(errno));
		return 1;	//exit(1);
	}
	pinMode(TRIG_GPIO_PIN, OUTPUT);
	pinMode(ECHO_GPIO_PIN, INPUT);
	pullUpDnControl(ECHO_GPIO_PIN, PUD_DOWN);

	if (wiringPiISR (ECHO_GPIO_PIN, INT_EDGE_BOTH, &myInterrupt) < 0)
	{
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
		return 1 ;
	}


	
	loopingStatus = 1;
#ifdef DEBUG
	printf("All initialized...\n");
#endif
	while(loopingStatus)
	{
#ifdef DEBUG
	printf("waiting for signal...\n");
#endif
		digitalWrite(TRIG_GPIO_PIN, LOW);
		delayMicroseconds(10);
		digitalWrite(TRIG_GPIO_PIN, HIGH);
		usleep(10);
		digitalWrite(TRIG_GPIO_PIN, LOW);
		sleep(5);
	}
	
	return 0;
}


// Accept Ctrl+C command, this seems not work when main process is forked.
void break_program(int sig)
{
	signal(sig, SIG_IGN);
	loopingStatus = 0;
	printf("Program end.\n");
	signal(sig, SIG_DFL);
}

// Get the interrupt if we touched the button.
void myInterrupt()
{
	long long diffns = 0;
	gettimeofday(&nowT, NULL);
	diffns = nowT.tv_nsec - prevT.tv_nsec;
	diffns += (nowT.tv_sec - prevT.tv_sec)*1000000000;
	if ( !digitalRead(ECHO_GPIO_PIN) )
		printf("detected!%f m\n", diffns*340.0/2/1000000);
	prevT = nowT;
}
