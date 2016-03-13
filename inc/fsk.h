////============================================
///	Code by: Muneeb Abid
//	Dated: 1 Jul 2015
///	Details: FSK Basic Functions
////============================================


#define RELOAD_VALUE 200			//0x03F940AA		//66,666,666 = 1 sec //0x02FAF080		//50,000,000 = 1 sec
#define SAMPLING_RELOAD 0x000031E0

#define TIMER0_ENABLE TIMER0_CTL_R|=0x1			//enable timer
#define TIMER1_ENABLE TIMER1_CTL_R|=0x1			//enable timer
#define TIMER0_DISABLE TIMER0_CTL_R&=~0x00000001			//disable timer
#define TIMER1_DISABLE TIMER1_CTL_R&=~0x00000001			//disable timer

#define FLAG_INACTIVE 0x00000000
#define FLAG_ACTIVE 0x00000001

#define SIN_SAMPLES 1600
#define FREQ_MOD_KHZ 25
#define FREQ_SEP_KHZ 2
#define SAMPLES_PER_SYMBOL	1000

void fsk_init(void);

extern uint16_t SineWave[400];
