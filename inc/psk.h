#include <stdint.h>
#include <stdbool.h>


#define SAMPLING_RELOAD 0x000031E0
#define TIMER0_ENABLE TIMER0_CTL_R|=0x1			//enable timer
#define TIMER1_ENABLE TIMER1_CTL_R|=0x1			//enable timer
#define TIMER0_DISABLE TIMER0_CTL_R&=~0x00000001			//disable timer
#define TIMER1_DISABLE TIMER1_CTL_R&=~0x00000001			//disable timer

#define FLAG_INACTIVE 0x00000000
#define FLAG_ACTIVE 0x00000001

#define RELOAD_VALUE 200			//0x03F940AA		//66,666,666 = 1 sec //0x02FAF080		//50,000,000 = 1 sec

#define SIN_SAMPLES 1600
#define replicatingFactor 20
#define jumpSize 					80
#define upSampleFactor    8
#define isUpSampling			true

#define ELEMENT_COUNT(X) (sizeof(X) / sizeof((X)[0]))


void psk_init(void);
void stringToSymbols(char*);
int bitFuser(char, int);
int getNextSample(void);
int cosine(int);
void symbolLookUp(int,int[]);
void symbolsReplicate(int[]);
void upSampling(int[], int[][2]);
void SRRCFilter(int[][2]);


extern uint16_t SineWave[400];
extern double SRRCResponse[51];
extern bool isSampleAvail, isSampleSent;


