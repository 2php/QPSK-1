#include <stdint.h>
#include "inc/tm4c123gh6pge.h"
#include "inc/fsk.h"

uint16_t SineWave[400] = {
0,8,16,24,32,40,48,56,64,72
,80,88,96,104,112,120,128,136,145,153
,161,169,177,185,193,201,209,217,225,233
,241,249,257,265,273,281,289,297,305,313
,321,329,337,345,352,360,368,376,384,392
,400,408,416,424,432,439,447,455,463,471
,479,487,494,502,510,518,526,533,541,549
,557,565,572,580,588,595,603,611,619,626
,634,642,649,657,664,672,680,687,695,702
,710,718,725,733,740,748,755,763,770,778
,785,793,800,807,815,822,830,837,844,852
,859,866,874,881,888,895,903,910,917,924
,931,939,946,953,960,967,974,981,988,995
,1002,1010,1017,1023,1030,1037,1044,1051,1058,1065
,1072,1079,1086,1093,1099,1106,1113,1120,1126,1133
,1140,1147,1153,1160,1166,1173,1180,1186,1193,1199
,1206,1212,1219,1225,1232,1238,1245,1251,1257,1264
,1270,1276,1283,1289,1295,1301,1308,1314,1320,1326
,1332,1338,1345,1351,1357,1363,1369,1375,1381,1387
,1392,1398,1404,1410,1416,1422,1428,1433,1439,1445
,1451,1456,1462,1467,1473,1479,1484,1490,1495,1501
,1506,1512,1517,1523,1528,1533,1539,1544,1549,1554
,1560,1565,1570,1575,1580,1585,1591,1596,1601,1606
,1611,1616,1621,1626,1630,1635,1640,1645,1650,1654
,1659,1664,1669,1673,1678,1683,1687,1692,1696,1701
,1705,1710,1714,1718,1723,1727,1731,1736,1740,1744
,1748,1753,1757,1761,1765,1769,1773,1777,1781,1785
,1789,1793,1797,1801,1804,1808,1812,1816,1819,1823
,1827,1830,1834,1838,1841,1845,1848,1852,1855,1858
,1862,1865,1868,1872,1875,1878,1881,1885,1888,1891
,1894,1897,1900,1903,1906,1909,1912,1915,1917,1920
,1923,1926,1929,1931,1934,1937,1939,1942,1944,1947
,1949,1952,1954,1957,1959,1961,1964,1966,1968,1970
,1972,1975,1977,1979,1981,1983,1985,1987,1989,1991
,1993,1994,1996,1998,2000,2001,2003,2005,2006,2008
,2010,2011,2013,2014,2015,2017,2018,2020,2021,2022
,2023,2025,2026,2027,2028,2029,2030,2031,2032,2033
,2034,2035,2036,2037,2038,2038,2039,2040,2041,2041
,2042,2042,2043,2043,2044,2044,2045,2045,2046,2046
,2046,2046,2047,2047,2047,2047,2047,2047,2047,2048};








void fsk_init(){
	
	//--------------------------------------------
	///	.:One-Shot/Periodic Timer Mode [pg.742]:.
	//--------------------------------------------
  
	///		.:TIMER0 INIT:.
  
  //Enable and provide a clock to 16/32-bit general purpose timer module 0 in Run mode (enable timer0)
  SYSCTL_RCGCTIMER_R |= (1<<0); //0b0000 0001
  
  //1. Ensure the time is disabled (the TnEN bit in the GPTMCTL register is cleared) before making any changes
  TIMER0_CTL_R &= ~(1<<0);
  
  //2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000
  TIMER0_CFG_R = 0x00000000;	//32-bit timer
  
  //3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR)
  TIMER0_TAMR_R |= (0x2<<0);	//periodic mode
	//TIMER0_TAMR_R |= (0x1<<5);	//GPTMTAMATCHR interrupt enable
	
  
  //4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
  TIMER0_TAMR_R &= ~(1<<4);		//Count Down Timer
  
  //5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR)
  TIMER0_TAILR_R = RELOAD_VALUE;
  
  //6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register (GPTMIMR).
  TIMER0_IMR_R |= (1<<0); //Timeout Enabled Interrupt
	//TIMER0_IMR_R |= (1<<4); // Match Enabled Interrupt
  NVIC_EN0_R |= (1<<19);	//TIMER0A Interrupt Handler# 19. EN0 for handlers 0-31
	
  //7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
  //TIMER0_CTL_R |= (1<<0);			//enable timer
	//TIMER0_TAMATCHR_R = 0x00000001;	//Match value
	
	//---------------------------------------------------------
	
	
	///		.:TIMER1 INIT:.
  
  //Enable and provide a clock to 16/32-bit general purpose timer module 0 in Run mode (enable timer0)
  SYSCTL_RCGCTIMER_R |= (1<<1); //0b0000 0010
  
  //1. Ensure the time is disabled (the TnEN bit in the GPTMCTL register is cleared) before making any changes
  TIMER1_CTL_R &= ~(1<<0);
  
  //2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000
  TIMER1_CFG_R = 0x00000000;	//32-bit timer
  
  //3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR)
  TIMER1_TAMR_R |= (0x2<<0);	//periodic mode
	//TIMER1_TAMR_R |= (0x1<<5);	//GPTMTAMATCHR interrupt enable
	
  
  //4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
  TIMER1_TAMR_R &= ~(1<<4);		//Count Down Timer
  
  //5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR)
  TIMER1_TAILR_R = SAMPLING_RELOAD;
  
  //6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register (GPTMIMR).
  TIMER1_IMR_R |= (1<<0); //Timeout Enabled Interrupt
	//TIMER1_IMR_R |= (1<<4); // Match Enabled Interrupt
  NVIC_EN0_R |= (1<<21);	//TIMER1A Interrupt Handler# 21. EN0 for handlers 0-31
	
  //7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
  //TIMER1_CTL_R |= (1<<0);			//enable timer
	//TIMER1_TAMATCHR_R = 0x00000001;	//Match value
	

}

