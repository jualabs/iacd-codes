struct measdata { 
	long ts;
	float temperature;
	float humidity;
};

struct measdata measurements [100];

struct measdata { 
	long ts;
	float temperature;
	float humidity;
} measurements[100], single_meas;

temperature_value = measurements[46].temperature;


#define MAXMEAS 100

struct measdata measurements [MAXMEAS];
int stop_meas = 0;
int i = 0;

while (!stop_meas) {
	measurements[i].ts = (long) time(NULL);
	measurements[i].temperature = GetMeas(TEMP);
	measurements[i].humidity = GetMeas(HUM);
	i++;
	if (i >= MAXMEAS) {
		stop_meas = 1;
	}
}

typedef struct measdata { 
	long ts;
	float temperature;
	float humidity;
} measure;

typedef struct { 
	long ts;
	float temperature;
	float humidity;
} measure;

measure single_measure;
measure measurements[100];


#include <stdio.h>
#include <stdlib.h>

typedef struct { 
	long ts;
	float temperature;
	float humidity;
} measure;

int i;

measure *measurements[10];

int main(void) {
	for (i = 0; i < 10; i++) {
		measurements[i] = (measure *) malloc(sizeof(measure));
		measurements[i]->ts = (long) time(NULL);
		measurements[i]->temperature = GetMeas(TEMP);
		measurements[i]->humidity = GetMeas(HUM);
		delay(1000);
	}
	for (i = 0; i < 10; i++) {
		printf("%l, %f, %f\n", measurements[i]->ts, measurements[i]->temperature, measurements[i]->humidity);
	}
	for (i = 9; i >= 0; i--) {
		free(measurements[i]); }
	}
}
	