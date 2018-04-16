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
#include "fpga.h"

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

#define DOG_BOWL_PATH	"/ELE408/dog_bowl.csv"		// Path to Output File for Dog Bowl ADC values
#define DOG_FEED_PATH	"/ELE408/dog_feeder.csv"	// Path to Output File for Dog Feeder ADC values

#define DOG_BOWL_ADDR	0				// ADC Channel for Dog Bowl
#define DOG_FEED_ADDR	1				// ADC Channel for Dog Feeder

// Local Function Declarations
static bool initialize_hardware(void);

int main(int argc, char *argv[])
{
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

	while(true)
	{
		ReadADC(&dog_bowl_val, DOG_BOWL_ADDR);	// Get Dog Bowl Weight
		ReadADC(&dog_feed_val, DOG_FEED_ADDR);	// Get Dog Feeder Weight

		// TODO Log ADC Readings, Check if servo should be adjusted

		usleep(1000*1000);			// Sleep for One Second 
	}

	return 1;
}

static bool initialize_hardware(void)
{
	if(!WriteADC(1, DOG_BOWL_ADDR)) return false;	// Initialize Dog Bowl ADC
	if(!WriteADC(1, DOG_FEED_ADDR)) return false;	// Initialize Dog Feeder ADC
	// TODO Add Other Custom Hardware Inits

	return true;
}
