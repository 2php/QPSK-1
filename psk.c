#include <stdint.h>
#include "inc/tm4c123gh6pge.h"
#include "inc/psk.h"

uint16_t SineWave[400] = {
			//fs=11400,fc=3500, alpha=0.5
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



//double SRRCResponse[51]={
//0.000023840131229942981, 0.000017133294737257204, 0.000024451503775899547, -0.000054472334456739562, -0.0000046940386206365412, 
//-0.000071311550915307591, 0.000089769043895260365, 0.0000019219737665863648, 0.00012773241118815512, -0.00010236044598800937, 
//-0.000049386756619929671, -0.00017295295221387986, 0.000021146839610528682, 0.00024583326375143653, 0.00016817510732315317, 
//0.00035766360076294024, -0.00087097330480897617, -0.000063892350693559957, -0.0018619476909842252, 0.0030957277147839403, 
//0.00018131862933297164, 0.011792833282013264, -0.020436437871943457, -0.072096485928656973, 0.27263950455200381, 
//0.61403508771929827, 0.27263950455200381, -0.072096485928656973, -0.020436437871943457, 0.011792833282013264, 
//0.00018131862933297164, 0.0030957277147839403, -0.0018619476909842252, -0.000063892350693559957, -0.00087097330480897617, 
//0.00035766360076294024, 0.00016817510732315317, 0.00024583326375143653, 0.000021146839610528682, -0.00017295295221387986, 
//-0.000049386756619929671, -0.00010236044598800937, 0.00012773241118815512, 0.0000019219737665863648, 0.000089769043895260365, 
//-0.000071311550915307591, -0.0000046940386206365412, -0.000054472334456739562, 0.000024451503775899547, 0.000017133294737257204, 
//0.000023840131229942981};


//fs=11400,fc=500, alpha=0.5
//double SRRCResponse[51]={0.0017092678297250393, 0.0011694647180873798, 0.00023563202108147017, -0.0011008383282433275, -0.0027984028409699215, 
//-0.0047582641844375771, -0.0068224473360397929, -0.0087780493653416801, -0.010368074275208304, -0.01130857081585949, 
//-0.011311060094354598, -0.010108553562566574, -0.0074829038463707686, -0.0032908749063816031, 0.0025137805317370573, 
//0.0098647606868454921, 0.018576224715102785, 0.028345706524949419, 0.038767363384545034, 0.049354993915788944, 
//0.059573273421853749, 0.068874784045543883, 0.076739760247254679, 0.082715103129396145, 0.086449186916044182, 
//0.08771929824561403, 0.086449186916044182, 0.082715103129396145, 0.076739760247254679, 0.068874784045543883, 
//0.059573273421853749, 0.049354993915788944, 0.038767363384545034, 0.028345706524949419, 0.018576224715102785, 
//0.0098647606868454921, 0.0025137805317370573, -0.0032908749063816031, -0.0074829038463707686, -0.010108553562566574, 
//-0.011311060094354598, -0.01130857081585949, -0.010368074275208304, -0.0087780493653416801, -0.0068224473360397929, 
//-0.0047582641844375771, -0.0027984028409699215, -0.0011008383282433275, 0.00023563202108147017, 0.0011694647180873798, 
//0.0017092678297250393};

//fs=1500,fc=500, alpha=0.5
//double SRRCResponse[51]={-0.000018730476813682615, 0.000000000000000000096299554478672303, 0.000024301297441278967, 0.000027903602390437059, -0.00000000000000000012763182016110939, 
//-0.000037486906057812389, -0.00004391851491004476, 0.00000000000000000017606708340097195, 0.000061847442960409962, 0.000074500048453563327, 
//-0.00000000000000000025680584809251634, -0.00011216774062870021, -0.00014072651034565523, 0.0000000000000000004067635931025513, 0.00023463616066676657, 
//0.00031419105401233092, -0.00000000000000000073668671919477983, -0.00062388727303135777, -0.00094316357507786294, 0.0000000000000000017264762484015129, 
//0.002719744377002798, 0.0056298433606074613, -0.0000000000000000086550433149216947, -0.088572053784103072, 0.24807393806742789, 
//0.66666666666666663, 0.24807393806742789, -0.088572053784103072, -0.0000000000000000086550433149216947, 0.0056298433606074613, 
//0.002719744377002798, 0.0000000000000000017264762484015129, -0.00094316357507786294, -0.00062388727303135777, -0.00000000000000000073668671919477983, 
//0.00031419105401233092, 0.00023463616066676657, 0.0000000000000000004067635931025513, -0.00014072651034565523, -0.00011216774062870021, 
//-0.00000000000000000025680584809251634, 0.000074500048453563327, 0.000061847442960409962, 0.00000000000000000017606708340097195, -0.00004391851491004476, 
//-0.000037486906057812389, -0.00000000000000000012763182016110939, 0.000027903602390437059, 0.000024301297441278967, 0.000000000000000000096299554478672303, 
//-0.000018730476813682615};

//low pass, fs=11400, fc=800
//double SRRCResponse[51]={ 0.010639563217545441, 0.012120042520289342, 0.012359769741471334, 0.011209005141414791, 0.0086522663861859795, 
//0.0048221931856325022, -0.0000000000000000038437368154999013, -0.005398338120367387, -0.01084968717401779, -0.015763319432263934, 
//-0.019529394623475652, -0.021572329669847949, -0.021404396680572233, -0.018674674923197639, -0.013208720621738166, 
//-0.0050349988833367229, 0.0056048079280440564, 0.018263132954724381, 0.032311472188291349, 0.046981340933217451, 
//0.061418167412606299, 0.074743836263799643, 0.086122747706970468, 0.094825863237667979, 0.1002873077718683, 
//0.10214868707817611, 0.1002873077718683, 0.094825863237667979, 0.086122747706970468, 0.074743836263799643, 
//0.061418167412606299, 0.046981340933217451, 0.032311472188291349, 0.018263132954724381, 0.0056048079280440564, 
//-0.0050349988833367229, -0.013208720621738166, -0.018674674923197639, -0.021404396680572233, -0.021572329669847949, 
//-0.019529394623475652, -0.015763319432263934, -0.01084968717401779, -0.005398338120367387, -0.0000000000000000038437368154999013, 
//0.0048221931856325022, 0.0086522663861859795, 0.011209005141414791, 0.012359769741471334, 0.012120042520289342, 
//0.010639563217545441};


//SRRC fs=11400, fc=800
double SRRCResponse[51]={0.00075837225766460612, 0.0006067144991254073, 0.00032117345862267625, 0.000060425417276347663, 0.000025667637351361229, 
0.00037840237611758181, 0.0011458739799257084, 0.0021485224460251356, 0.0029852089825032628, 0.0031006975187211658, 
0.0019372369872882988, -0.0008564302874355872, -0.0052112359766417838, -0.010486007675623315, -0.01544053462264354, 
-0.018371968711038588, -0.017412826811967336, -0.01094252300671299, 0.0019751583327495348, 0.021236537133375099, 
0.045525391226505868, 0.072389041653319622, 0.098572978158041363, 0.1205604873701526, 0.13520971896006431, 
0.14035087719298245, 0.13520971896006431, 0.1205604873701526, 0.098572978158041363, 0.072389041653319622, 
0.045525391226505868, 0.021236537133375099, 0.0019751583327495348, -0.01094252300671299, -0.017412826811967336, 
-0.018371968711038588, -0.01544053462264354, -0.010486007675623315, -0.0052112359766417838, -0.0008564302874355872, 
0.0019372369872882988, 0.0031006975187211658, 0.0029852089825032628, 0.0021485224460251356, 0.0011458739799257084, 
0.00037840237611758181, 0.000025667637351361229, 0.000060425417276347663, 0.00032117345862267625, 0.0006067144991254073, 
0.00075837225766460612};


int symbolsTable[4][2]={{-1,-1},{-1,1} ,{1,-1}, {1,1}};

double Symbols[1000][2];
int totalSymbols = 0;	
int currentSymbol=0, curIndex=0;
int xi, xq, xdac, cosxi, cosxq, cosxqamp;
bool isSampleAvail, isSampleSent;



void psk_init(){ 
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

}



int bitFuser(char ch, int x)
{
	int num;
	switch(x)
	{
		case 0:
		{
			num = ch & 0x03;
			break;
		}	
		case 2:
		{
			num = (ch & 0x0C)>>2;
			break;
		}
		case 4:
		{
			num= (ch & 0x30)>>4;
			break;
		}
		case 6:
		{
			num=(ch & 0xC0)>>6;
			break;
		}
	}
	return num;
}



void symbolLookUp(int SYM,int SYMARRAY[])
{
	SYMARRAY[0]= symbolsTable[SYM][0];
	SYMARRAY[1]= symbolsTable[SYM][1];
}


void symbolsReplicate(int SYMARRAY[])
{
	for (int i=0; i<replicatingFactor; i++)
	{
		Symbols[totalSymbols][0]= SYMARRAY[0];
		Symbols[totalSymbols][1]= SYMARRAY[1];
		totalSymbols++;
	}
}



void upSampling(int SYMARRAY[],int UPSAMPLED[][2])
{
	UPSAMPLED[totalSymbols][0]= SYMARRAY[0];
	UPSAMPLED[totalSymbols][1]= SYMARRAY[1];
	totalSymbols++;
	for (int i=0;i<upSampleFactor-1; i++)
	{
		UPSAMPLED[totalSymbols][0]= 0;
		UPSAMPLED[totalSymbols][1]= 0;
		totalSymbols++;
	}
}



void SRRCFilter(int UPSAMPLED[][2])
{

  int SignalLen=totalSymbols;
  int SRRCLen=ELEMENT_COUNT(SRRCResponse);

  totalSymbols=totalSymbols + SRRCLen - 1;

  for (int n = 0; n < totalSymbols; n++)
  {
    int kmin, kmax, k;

    Symbols[n][0]= Symbols[n][1] = 0;

    kmin = (n >= SRRCLen - 1) ? n - (SRRCLen - 1) : 0;
    kmax = (n < SignalLen - 1) ? n : SignalLen - 1;

    for (k = kmin; k <= kmax; k++)
    {
      Symbols[n][0] += UPSAMPLED[k][0] * SRRCResponse[n - k];
      Symbols[n][1] += UPSAMPLED[k][1] * SRRCResponse[n - k];
    }
	  }
	
}


void stringToSymbols(char* str)
{
			totalSymbols = 0;
		currentSymbol=0;
		curIndex=0;
	int upSampled[1000][2];
	int symArray[2], i=0, sym;
	for (i=0; str[i]!=0; i++)
	{
		for (int index=0; index<8; index+=2)
		{
			sym= bitFuser(str[i],index);
			symbolLookUp(sym, symArray);
			
			if (!isUpSampling)
				symbolsReplicate( symArray);
			else
				upSampling(symArray,upSampled);
			
		}
	}
	if (isUpSampling)
		SRRCFilter(upSampled);
}

int getNextSample()
{
	//static 
	if (currentSymbol<=totalSymbols)
	{
		cosxi=(cosine(curIndex%SIN_SAMPLES) );
		cosxq=(cosine((curIndex+SIN_SAMPLES/4)%SIN_SAMPLES));
		cosxqamp=(curIndex+SIN_SAMPLES/4)%SIN_SAMPLES;
		xi=Symbols[currentSymbol][0] * (cosine(curIndex%SIN_SAMPLES));
		xq=Symbols[currentSymbol][1] * (cosine((curIndex+SIN_SAMPLES/4)%SIN_SAMPLES));
		xdac=( xi-xq+4096-1200)/1.414;
		
		if (isUpSampling)
			
			xdac=((xdac-2048)*2048/352)+ 2048;
//		if (xdac<0)
//			xdac=0;
		
  	currentSymbol++;
		curIndex+=jumpSize;
 		isSampleAvail=true;
	}
	else
		isSampleAvail=false;
	return xdac;
}


int cosine(int x)
{
	int s;
	if (x>SIN_SAMPLES/2)
	{
		x=x-SIN_SAMPLES/2;
		s=-1;
	}
	else
		s=1;
	return (x<SIN_SAMPLES/4)? s*SineWave[x] : s*SineWave[SIN_SAMPLES/2 -1 - x];
	
}



