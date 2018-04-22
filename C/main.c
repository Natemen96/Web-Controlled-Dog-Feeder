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

#define DOG_BOWL_HEADER "Dog Bowl"			// Header for Dog Bowl CSV File
#define DOG_FEED_HEADER	"Dog Feeder"			// Header for Dog Feeder CSV File

#define DOG_BOWL_PATH	"dog_bowl.csv"			// Path to Output File for Dog Bowl ADC Values
#define DOG_FEED_PATH	"dog_feeder.csv"		// Path to Output File for Dog Feeder ADC values
#define CNTRL_PATH	"../Python/feedme.txt"		// Path to File to Determine when to move Feeder (Servo)

#define DOG_BOWL_ADDR	0				// ADC Channel for Dog Bowl
#define DOG_FEED_ADDR	1				// ADC Channel for Dog Feeder

// Local Function Declarations
static bool initialize_hardware(void);
static int countlines(char* file_path);

int bowl_index, feed_index;

int main(int argc, char *argv[])
{
	FILE* bowl_file = NULL;
	FILE* feed_file = NULL;
	FILE* cntrl_file = NULL;
	uint32_t dog_bowl_val, dog_feed_val;

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

	/*if( (0 == open_file(bowl_file, DOG_BOWL_PATH)) || (0 == open_file(feed_file, DOG_FEED_PATH)) )
	{
		return 0;
	}*/

	if(access(DOG_BOWL_PATH, F_OK ) == -1 )
	{
    		if( (bowl_file = fopen(DOG_BOWL_PATH, "w")) == NULL)
		{
			perror("Error Opening CSV File");
			return 0;
		}
	}
	else
	{
		if( (bowl_file = fopen(DOG_BOWL_PATH, "a+")) == NULL)
		{
			perror("Error Opening CSV File");
			return 0;
		}
	}

	if(access(DOG_FEED_PATH, F_OK ) == -1 )
	{
    		if( (feed_file = fopen(DOG_FEED_PATH, "w")) == NULL)
		{
			perror("Error Opening CSV File");
			return 0;
		}
	}
	else
	{
		if( (feed_file = fopen(DOG_FEED_PATH, "a+")) == NULL)
		{
			perror("Error Opening CSV File");
			return 0;
		}
	}

	while(true)
	{
		ReadADC(&dog_bowl_val, DOG_BOWL_ADDR);	// Get Dog Bowl Weight
		ReadADC(&dog_feed_val, DOG_FEED_ADDR);	// Get Dog Feeder Weight

		printf("Reading From ADC...\n");
		printf("Dog Bowl ADC Code: %d\n", dog_bowl_val);

		/*if(dog_bowl_val < 3000)
		{
			printf("Writing 110\n");
			WritePWM(6);
		}
		else
		{
			printf("Writing 100\n");
			WritePWM(5);
		}*/

		char dog_bowl_str[5], dog_feed_str[5];
		sprintf(dog_bowl_str, "%4d", dog_bowl_val);
		sprintf(dog_feed_str, "%4d", dog_feed_val);

		fprintf(bowl_file, "%d,%s\n", bowl_index, dog_bowl_str);
		fprintf(feed_file, "%d,%s\n", feed_index, dog_feed_str);

		fflush(bowl_file);
		fflush(feed_file);

		bowl_index++;
		feed_index++;

		// Check if servo should be adjusted
		printf("Checking whether to feed Dog\n");
		if( (cntrl_file = fopen(CNTRL_PATH, "r")) == NULL)
		{
			perror("Error Opening File");
			return 0;
		}

		char a = fgetc(cntrl_file);
		if(a == '1')
		{
			printf("Feeding\n");
			WritePWM(3 << 1);		// Rotate CW
			fclose(cntrl_file);
			cntrl_file = fopen(CNTRL_PATH, "w");
			fputc('0', cntrl_file);
		}
		else
		{
			printf("Don't Feed\n");
			WritePWM(0);			// Stop Servo Motor
		}

		fclose(cntrl_file);

		usleep(1000*1000);			// Sleep for One Second 
	}

	fclose(bowl_file);
	fclose(feed_file);

	return 1;
}

static bool initialize_hardware(void)
{
	if(!WriteADC(1, DOG_BOWL_ADDR)) return false;	// Initialize Dog Bowl ADC
	if(!WriteADC(1, DOG_FEED_ADDR)) return false;	// Initialize Dog Feeder ADC
	bowl_index = countlines(DOG_BOWL_PATH);		// Initialize Dog Dowl Index (used in CSV)
	feed_index = countlines(DOG_FEED_PATH);		// Initialize Dog Feeder Index (used in CSV)

	// TODO Add Other Custom Hardware Inits

	return true;
}

static int countlines(char* file_path)
{                                  
	int ch=0;
  	int lines=0;
  	FILE *f;

	if( (f = fopen(file_path,"r")) == NULL)
		return 0;
	
  	lines++;
  	while( (ch = fgetc(f)) != EOF)
    	{
      		if(ch == '\n')
    			lines++;
    	}
  	fclose(f);
  	return lines;
}

