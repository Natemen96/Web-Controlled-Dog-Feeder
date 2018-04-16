#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "soc_cv_av/socal/socal.h"
#include "soc_cv_av/socal/hps.h"
#include "soc_cv_av/socal/alt_gpio.h"
#include "hps_0.h"
#include <stdbool.h>
#include <string.h>
#include "fpga.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

#define DOG_FEED_HEADER	"Dog Bowl,Dog Feeder"

#define DOG_FEED_PATH	"dog_feeder.csv"	// Path to Output File for Dog Feeder ADC values

#define DOG_BOWL_ADDR	0				// ADC Channel for Dog Bowl
#define DOG_FEED_ADDR	1				// ADC Channel for Dog Feeder

// Local Function Declarations
static bool initialize_hardware(void);

int main(int argc, char *argv[])
{
	FILE* csv_file;
	uint32_t dog_bowl_val, dog_feed_val, pwm_sel;

	if(0 == FPGAInit())
	{
		printf("Error Initializing FPGA\n");
		return 0;
	}

	if(0 == initialize_hardware())
	{
		printf("Error Initializing Custom Hardware\n");
		return 0;
	}

	if(access(DOG_FEED_PATH, F_OK ) == -1 )
	{
    		if( (csv_file = fopen(DOG_FEED_PATH, "w")) == NULL)
		{
			perror("Error Opening CSV File");
			return 0;
		}

		fprintf(csv_file, "%s\n", DOG_FEED_HEADER);
	}
	else
	{
		if( (csv_file = fopen(DOG_FEED_PATH, "a+")) == NULL)
		{
			perror("Error Opening CSV File");
			return 0;
		}
	}

	while(true)
	{
		ReadADC(&dog_bowl_val, DOG_BOWL_ADDR);	// Get Dog Bowl Weight
		ReadADC(&dog_feed_val, DOG_FEED_ADDR);	// Get Dog Feeder Weight

		// TODO Log ADC Readings, Check if servo should be adjusted
		char dog_bowl_str[5], dog_feed_str[5];
		sprintf(dog_bowl_str, "%4d", dog_bowl_val);
		sprintf(dog_feed_str, "%4d", dog_feed_val);

		char csv_str[10];
		csv_str[0] = dog_bowl_str[0];
		csv_str[1] = dog_bowl_str[1];
		csv_str[2] = dog_bowl_str[2];
		csv_str[3] = dog_bowl_str[3];
		csv_str[4] = ',';
		csv_str[5] = dog_feed_str[0];
		csv_str[6] = dog_feed_str[1];
		csv_str[7] = dog_feed_str[2];
		csv_str[8] = dog_feed_str[3];
		csv_str[9] = '\0';

		printf("Dog Bowl: %d\n", dog_bowl_val);

		fprintf(csv_file, "%s\n", csv_str);
		fflush(csv_file);

		usleep(1000*1000);			// Sleep for One Second 
	}

	fclose(csv_file);

	return 1;
}

static bool initialize_hardware(void)
{
	if(!WriteADC(1, DOG_BOWL_ADDR)) return false;	// Initialize Dog Bowl ADC
	if(!WriteADC(1, DOG_FEED_ADDR)) return false;	// Initialize Dog Feeder ADC
	// TODO Add Other Custom Hardware Inits

	return true;
}
