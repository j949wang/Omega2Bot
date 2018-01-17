#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include <ugpio/ugpio.h>

using namespace std;

float sensor(const int trig, const int echo){
	int outputSensor = gpio_direction_output(trig,0);
	int inputSensor = gpio_direction_input(echo);
	int setSensor;
	float time;
	float distance ;
	setSensor = gpio_set_value(trig,0);
	sleep(5);
	setSensor = gpio_set_value(trig,1);
	sleep(10);
	setSensor = gpio_set_value(trig,0);
	
	clock_t begin = clock();
	inputSensor = gpio_direction_input(echo);
	clock_t end = clock();
	time = float(end-begin)/CLOCKS_PER_SEC;
	distance = (time/2)/29.1;

	return distance;
}

int main(int argc, char **argv, char **envp)
{	
	float distance;
	int timesleep;
	int trigPin = 3;
	int echoPin = 2;
	int gpioLLed = 18;
	int gpioRLed = 19;
	int gpioLMotor_c = 6;
	int gpioLMotor_ac = 7;
	int gpioRMotor_c= 0;
	int gpioRMotor_ac = 1;

	int valueLLed = 1;
	int valueRLed = 1;
	int valueLMotor_c = 1 ;
	int valueLMotor_ac = 0;
	int valueRMotor_c = 0;
	int valueRMotor_ac = 1;

	int outputLLed = gpio_direction_output(gpioLLed,0);
	int outputRLed = gpio_direction_output(gpioRLed,0);
	int outputLMotor_c = gpio_direction_output(gpioLMotor_c,0);
	int outputLMotor_ac = gpio_direction_output(gpioLMotor_ac,0);
	int outputRMotor_c = gpio_direction_output(gpioRMotor_c,0);
	int outputRMotor_ac = gpio_direction_output(gpioRMotor_ac,0);

	int setLLed;
	int setRLed;
	int setLMotor_c = gpio_set_value(gpioLMotor_c,valueLMotor_c);
	int setLMotor_ac = gpio_set_value(gpioLMotor_ac,valueLMotor_ac);
	int setRMotor_c = gpio_set_value(gpioRMotor_c,valueRMotor_c);
	int setRMotor_ac = gpio_set_value(gpioRMotor_ac,valueRMotor_ac);
	
	while (true){
		distance = sensor(trigPin, echoPin);
		if(distance <= 2){
			for (int i = 0; i<25;i++){
				valueLMotor_c = 0;
				setLMotor_c = gpio_set_value(gpioLMotor_c,valueLMotor_c);
				setLLed = gpio_set_value(gpioLLed,valueLLed);
				setRLed = gpio_set_value(gpioRLed,valueRLed);

				if (valueLLed == 1){
					valueLLed = 0;
				}
				else{
					valueLLed = 1;
				}

				if (valueRLed == 1){
					valueRLed = 0;
				}
				else{
					valueRLed = 1;
				}

				sleep(10);
			}
			timesleep = 0;

		}
		else{
			valueLMotor_c = 1;
			valueLLed = 0;
			valueRLed = 0;
			setLMotor_c = gpio_set_value(gpioLMotor_c,valueLMotor_c);
			setLLed = gpio_set_value(gpioLLed,valueLLed);
			setRLed = gpio_set_value(gpioRLed,valueRLed);
			timesleep = 250;
		}
		
		sleep(timesleep);
	}

	return 0;
}
