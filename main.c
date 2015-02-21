#include <msp430.h> 

#define CS BIT0  //2.0 is SPI CS
#define MOSI BIT7  //1.7 is SPI MOSI
#define SCLK BIT5  //1.5 is SPI clock
#define LED1 BIT4  //1.5 is SPI clock
#define LED0 BIT5  //1.5 is SPI clock
#define switchright BIT2  //1.5 is SPI clock
#define switchcenter BIT3  //1.5 is SPI clock
#define switchleft BIT1  //1.5 is SPI clock
#define alarmPin BIT1  //1.5 is SPI clock
#define POT1 INCH_0

void Init_MAX7219(void);
void printmatrix(unsigned char one, unsigned char two, unsigned char three, unsigned char four, unsigned char five);
void setTime(void);
void updateNumber(void);
void setIntensity(void);
void SPI_Init(void); //SPI initialization
void SPI_Write(unsigned char);
void SPI_Write2(unsigned char, unsigned char);
void SPI_Write3(unsigned char, unsigned char, unsigned char);

int pot1value = 0;
int right=0;
int left=0;
int center=0;
unsigned int intensity =0;
unsigned char textBuffer[100];
unsigned char timeString[100];
unsigned char Length = 0;
int digits =30;
unsigned int a,b,c,d,e;
int j,i,ii;
unsigned int jj,jjj,jjjj,jjjjj,jjjjjj;
int days =15;
int hours =2;
int minutes =52;
int seconds =31;
int tenmilliseconds =2;
unsigned char daysfirst =2;
unsigned char dayssecond =3;
unsigned char hoursfirst =2;
unsigned char hourssecond =3;
unsigned char minutessfirst =2;
unsigned char minutessecond =3;
unsigned char secondsfirst =2;
unsigned char secondssecond =3;
int i =0;
int alarm =0;
int Colon =0;


unsigned const char dispFRONT[51][8]={
		{	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	}	,	//	null
		{	31	,	40	,	72	,	136	,	72	,	40	,	31	,	0	}	,	//	A
		{	255	,	145	,	145	,	145	,	145	,	145	,	110	,	0	}	,	//	B
		{	60	,	66	,	129	,	129	,	129	,	129	,	129	,	0	}	,	//	C
		{	255	,	129	,	129	,	129	,	66	,	60	,	0	,	0	}	,	//	D
		{	255	,	145	,	145	,	145	,	145	,	129	,	129	,	0	}	,	//	E
		{	255	,	144	,	144	,	144	,	144	,	128	,	128	,	0	}	,	//	F
		{	60	,	66	,	129	,	129	,	133	,	71	,	4	,	0	}	,	//	G
		{	255	,	8	,	8	,	8	,	8	,	8	,	255	,	0	}	,	//	H
		{	129	,	129	,	129	,	255	,	129	,	129	,	129	,	0	}	,	//	I
		{	130	,	129	,	129	,	129	,	255	,	128	,	128	,	0	}	,	//	J
		{	255	,	16	,	40	,	68	,	130	,	1	,	0	,	0	}	,	//	K
		{	255	,	1	,	1	,	1	,	1	,	1	,	1	,	0	}	,	//	L
		{	255	,	64	,	32	,	16	,	32	,	64	,	255	,	0	}	,	//	M
		{	255	,	64	,	32	,	16	,	8	,	4	,	255	,	0	}	,	//	N
		{	255	,	129	,	129	,	129	,	129	,	129	,	255	,	0	}	,	//	O
		{	255	,	144	,	144	,	144	,	144	,	144	,	96	,	0	}	,	//	P
		{	254	,	130	,	130	,	134	,	130	,	131	,	254	,	0	}	,	//	Q
		{	255	,	144	,	144	,	152	,	148	,	146	,	241	,	0	}	,	//	R
		{	241	,	145	,	145	,	145	,	145	,	145	,	159	,	0	}	,	//	S
		{	128	,	128	,	128	,	255	,	128	,	128	,	128	,	0	}	,	//	T
		{	254	,	1	,	1	,	1	,	1	,	1	,	254	,	0	}	,	//	U
		{	248	,	4	,	2	,	1	,	2	,	4	,	248	,	0	}	,	//	V
		{	255	,	1	,	2	,	4	,	2	,	1	,	255	,	0	}	,	//	W
		{	65	,	34	,	20	,	8	,	20	,	34	,	65	,	0	}	,	//	X
		{	128	,	64	,	32	,	31	,	32	,	64	,	128	,	0	}	,	//	Y
		{	0	,	131	,	133	,	137	,	145	,	161	,	193	,	0	}	,	//	Z
		{	0	,	126	,	129	,	129	,	129	,	126	,	0	,	0	}	,	//	0
		{	0	,	65	,	129	,	255	,	1	,	1	,	0	,	0	}	,	//	1
		{	0	,	67	,	133	,	137	,	113	,	0	,	0	,	0	}	,	//	2
		{	0	,	0	,	66	,	145	,	145	,	110	,	0	,	0	}	,	//	3
		{	0	,	120	,	8	,	8	,	255	,	8	,	0	,	0	}	,	//	4
		{	0	,	242	,	145	,	145	,	145	,	142	,	0	,	0	}	,	//	5
		{	0	,	56	,	70	,	137	,	137	,	73	,	6	,	0	}	,	//	6
		{	0	,	128	,	128	,	159	,	160	,	192	,	0	,	0	}	,	//	7
		{	0	,	0	,	110	,	145	,	145	,	110	,	0	,	0	}	,	//	8
		{	0	,	98	,	145	,	145	,	146	,	124	,	0	,	0	}	,	//	9
		{	112	,	136	,	68	,	34	,	68	,	136	,	112	,	0	}	,	//	heart
		{	0	,	0	,	112	,	249	,	112	,	0	,	0	,	0	}	,	//	!
		{	60	,	66	,	169	,	133	,	169	,	66	,	60	,	0	}	,	//	smilly
		{	12	,	18	,	18	,	28	,	16	,	16	,	56	,	16	}	,	//	boner1
		{	16	,	56	,	16	,	16	,	28	,	18	,	18	,	12	}	,	//	boner2
		{	112	,	136	,	168	,	112	,	136	,	168	,	112	,	0	}	,	//	eyes right
		{	112	,	168	,	168	,	112	,	168	,	168	,	112	,	0	}	,	//	eyes center
		{	112	,	168	,	136	,	112	,	168	,	136	,	112	,	0	}	,	//	eyes left
		{	112	,	152	,	136	,	112	,	152	,	136	,	112	,	0	}	,	//	eyes low left
		{	112	,	136	,	152	,	112	,	136	,	152	,	112	,	0	}	,	//	eyes low right
		{	112	,	200	,	136	,	112	,	200	,	136	,	112	,	0	}	,	//	eyes high left
		{	112	,	136	,	200	,	112	,	136	,	200	,	112	,	0	}	,	//	eyes high right
		{	0	,	0	,	0	,	102	,	102	,	0	,	0	,	0	}	,	//	:
		{	12	,	60	,	124	,	254	,	124	,	60	,	12	,	0	}	,	//	bell

};

void setTime(void)
{
	while(1)
	{
	for(ii = 30;ii>0;ii--)
	{
	  	if((P1IN & switchleft) != switchleft)
	  	{
	  		left++;
	  	}
	  	if((P1IN & switchright) != switchright)
	  	{
	  		right++;
	  	}
	  	if((P1IN & switchcenter) != switchcenter)
	  	{
	  		center++;
	  	}
	  	_delay_cycles(10);
	}
	if(left > 20)
	{
		alarm =0;
		days--;
		if(days < 0)
		{
			days =99;
		}
		updateNumber();
		printmatrix(0,(dayssecond - 21),(daysfirst-21),0,4);
		_delay_cycles(1000000);

	}

	if(right > 20)
	{
		alarm =0;
		minutes++;
		if(minutes >59)
		{
			minutes =0;
		}
		updateNumber();
		printmatrix(0,(minutessecond - 21),(minutessfirst-21),0,13);
		_delay_cycles(1000000);
	}

	if(center > 20)
	{
		alarm =0;
		hours++;
		if(hours > 12)
		{
			hours =1;
		}
		updateNumber();
		printmatrix(0,(hourssecond - 21),(hoursfirst-21),0,8);
		_delay_cycles(1000000);
	}
	if(right ==0 && left == 0 && center ==0)
	{
		break;
	}

	left=0;
	right=0;
	center=0;
	}
}

unsigned int analogRead(unsigned int pin) {
 ADC10CTL0 = ADC10ON + ADC10SHT_0 + SREF_0;
 ADC10CTL1 = ADC10SSEL_0 + pin;
 if (pin==INCH_0){
 ADC10AE0 = 0x01;
 }
 else if (pin==INCH_1){
 ADC10AE0 = 0x02;
 }
 else if (pin==INCH_2){
 ADC10AE0 = 0x04;
 }
 else if (pin==INCH_3){
  ADC10AE0 = 0x08;
  }
 else if (pin==INCH_4){
  ADC10AE0 = 0x10;
  }
 else if(pin==INCH_5){
 ADC10AE0 = 0x20;
 }
 else if(pin==INCH_6){
  ADC10AE0 = 0x40;
  }
 else if(pin==INCH_7){
  ADC10AE0 = 0x80;
  }
 ADC10CTL0 |= ENC + ADC10SC;
 //_delay_cycles(10);
 while (1) {
 if (((ADC10CTL0 & ADC10IFG)==ADC10IFG)) {
 ADC10CTL0 &= ~(ADC10IFG +ENC);
 break;
 }
 }
 return ADC10MEM;
 }

void printmatrix(unsigned char one, unsigned char two, unsigned char three, unsigned char four, unsigned char five) //SPI initialization
{
  int aa;

  setIntensity();

  for(aa=1;aa<9;aa++)
  {
    P2OUT &= ~CS;
    _delay_cycles(10);
    UCB0TXBUF = aa ;
    while (UCB0STAT & UCBUSY);
    UCB0TXBUF = dispFRONT[five][8-aa];
    while (UCB0STAT & UCBUSY);
    UCB0TXBUF = aa ;
    while (UCB0STAT & UCBUSY);
    UCB0TXBUF = dispFRONT[four][8-aa];
    while (UCB0STAT & UCBUSY);
    UCB0TXBUF = aa ;
    while (UCB0STAT & UCBUSY);
    UCB0TXBUF = dispFRONT[three][8-aa];
    while (UCB0STAT & UCBUSY);
    UCB0TXBUF = aa ;
    while (UCB0STAT & UCBUSY);
    UCB0TXBUF = dispFRONT[two][8-aa];
    while (UCB0STAT & UCBUSY);
    UCB0TXBUF = aa ;
    while (UCB0STAT & UCBUSY);
    UCB0TXBUF = dispFRONT[one][8-aa];
    while (UCB0STAT & UCBUSY);
    P2OUT |= CS;
  }

}

void updateNumber(void)
{
		daysfirst = (days%10) + 48;
	  dayssecond = (days/10) + 48;
	  hoursfirst = (hours%10) + 48;
	  hourssecond = (hours/10) + 48;
	  minutessfirst = (minutes%10) + 48;
	  minutessecond = (minutes/10) + 48;
	  secondsfirst = (seconds%10) + 48;
	  secondssecond = (seconds/10) + 48;
}

void setIntensity(void)
{
	pot1value = (analogRead(POT1)) >> 6;
	intensity = (0x0F & pot1value);
	P2OUT &= ~CS;
	    _delay_cycles(10);
	    UCB0TXBUF = 0x0A;
	    while (UCB0STAT & UCBUSY);
	    UCB0TXBUF = intensity;
	    while (UCB0STAT & UCBUSY);
	    UCB0TXBUF = 0x0A;
	    while (UCB0STAT & UCBUSY);
	    UCB0TXBUF = intensity;
	    while (UCB0STAT & UCBUSY);
	    UCB0TXBUF = 0x0A;
	    while (UCB0STAT & UCBUSY);
	    UCB0TXBUF = intensity;
	    while (UCB0STAT & UCBUSY);
	    UCB0TXBUF = 0x0A;
	    while (UCB0STAT & UCBUSY);
	    UCB0TXBUF = intensity;
	    while (UCB0STAT & UCBUSY);
	    UCB0TXBUF = 0x0A;
	    while (UCB0STAT & UCBUSY);
	    UCB0TXBUF = intensity;
	    while (UCB0STAT & UCBUSY);
	    P2OUT |= CS;
}

void setText(unsigned char *data)
{
  volatile int  ii,iii;

  Length =0;

  for(iii = strlen(data);iii >=0;iii--)
  {
    if(data[iii] != 0)
    {
      Length++;
    }
  }

  for(ii =99;ii>=0;ii--)
  {
    textBuffer[ii] = 0;
  }

  digits = Length + 5;

  while(Length--)
  {


    if(*data >= 65 && *data <= 90)//letters
    {
      textBuffer[i] = (*data) - 64; //Write the character at the location specified py the pointer
    }
    else if (*data >= 48 && *data <= 57) //numbers
    {
      textBuffer[i] = (*data) - 21;
    }
    else if (*data == 109) // heart m
    {
      textBuffer[i] = 37;
    }
    else if (*data == 33) //!
    {
      textBuffer[i] = 38;
    }
    else if (*data == 64) //@
    {
      textBuffer[i] = 39;
    }
    else if (*data == 41) //)
    {
      textBuffer[i] = 40;
    }
    else if (*data == 40) //(
    {
      textBuffer[i] = 41;
    }
    else if (*data == 62) //>
    {
      textBuffer[i] = 42;
    }
    else if (*data == 94) //^
    {
      textBuffer[i] = 43;
    }
    else if (*data == 60) //<
    {
      textBuffer[i] = 44;
    }
    else if (*data == 46) //. lower left
    {
      textBuffer[i] = 45;
    }
    else if (*data == 44) //, lower right
    {
      textBuffer[i] = 46;
    }
    else if (*data == 39) //' upper left
    {
      textBuffer[i] = 47;
    }
    else if (*data == 59) //; upper right
    {
      textBuffer[i] = 48;
    }
    else if (*data == 58) //: time thing
    {
      textBuffer[i] = 49;
    }
    else if (*data == 97) //a alarm
    {
      textBuffer[i] = 50;
    }
    else
    {
      textBuffer[i] = 0; //space

    }

    	//textBuffer[i] = (*data);
    data++; //Increment the TxString pointer to point to the next character
    i++;
  }
  i=0;

}

void SPI_Init(void) //SPI initialization
{
  P2DIR |= CS;
  P1SEL |= MOSI + SCLK;
  P1SEL2 |= MOSI + SCLK;
  UCB0CTL1 = UCSWRST;
  UCB0CTL0 |= UCMSB + UCMST + UCSYNC + UCCKPH; // 4-pin, 8-bit SPI master
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  UCB0BR0 = 10;                          // /2
  UCB0BR1 = 0;                              //
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

  __enable_interrupt(); // enable all interrupts
}

void SPI_Write2(unsigned char MSB, unsigned char LSB) //SPI write one byte
{

  P2OUT &= ~CS;
  _delay_cycles(50);
  UCB0TXBUF = MSB ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = LSB ;
  while (UCB0STAT & UCBUSY);
  P2OUT |= CS;
}
void SPI_Write1(unsigned char MSB) //SPI write one byte
{

  P2OUT &= ~CS;
  _delay_cycles(10);
  UCB0TXBUF = MSB ;
  while (UCB0STAT & UCBUSY);
  P2OUT |= CS;
}
void SPI_Write3(unsigned char MSB,unsigned char MMSB,unsigned char LSB ) //SPI write one byte
{

  P2OUT &= ~CS;
  _delay_cycles(10);
  UCB0TXBUF = MSB ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = MMSB ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = LSB ;
  while (UCB0STAT & UCBUSY);
  P2OUT |= CS;
}

void Matrix1(unsigned char address,unsigned char data ) //SPI write one byte
{

  P2OUT &= ~CS;
  _delay_cycles(10);
  UCB0TXBUF = address ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = data ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0x00 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0x00 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0x00 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0x00 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0x00 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0x00 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  P2OUT |= CS;
}
void Matrix2(unsigned char address,unsigned char data ) //SPI write one byte
{

  P2OUT &= ~CS;
  _delay_cycles(10);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = address ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = data ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  P2OUT |= CS;
}

void Matrix3(unsigned char address,unsigned char data ) //SPI write one byte
{

  P2OUT &= ~CS;
  _delay_cycles(10);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = address ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = data ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  P2OUT |= CS;
}

void Matrix4(unsigned char address,unsigned char data ) //SPI write one byte
{

  P2OUT &= ~CS;
  _delay_cycles(10);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = address ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = data ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  P2OUT |= CS;
}

void Matrix5(unsigned char address,unsigned char data ) //SPI write one byte
{

  P2OUT &= ~CS;
  _delay_cycles(10);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = 0 ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = address ;
  while (UCB0STAT & UCBUSY);
  UCB0TXBUF = data ;
  while (UCB0STAT & UCBUSY);
  P2OUT |= CS;
}



void Init_MAX7219(void)
{
  Matrix1(0x09, 0x00);       //
  Matrix1(0x0A, 0x0F);       //
  Matrix1(0x0B, 0x0F);       //
  Matrix1(0x0C, 0x01);       //
  Matrix1(0x0F, 0x0F);       //
  Matrix1(0x0F, 0x00);       //

  Matrix2(0x09, 0x00);       //
  Matrix2(0x0A, 0x0F);       //
  Matrix2(0x0B, 0x0F);       //
  Matrix2(0x0C, 0x01);       //
  Matrix2(0x0F, 0x0F);       //
  Matrix2(0x0F, 0x00);       //

  Matrix3(0x09, 0x00);       //
  Matrix3(0x0A, 0x0F);       //
  Matrix3(0x0B, 0x0F);       //
  Matrix3(0x0C, 0x01);       //
  Matrix3(0x0F, 0x0F);       //
  Matrix3(0x0F, 0x00);       //

  Matrix4(0x09, 0x00);       //
  Matrix4(0x0A, 0x0F);       //
  Matrix4(0x0B, 0x0F);       //
  Matrix4(0x0C, 0x01);       //
  Matrix4(0x0F, 0x0F);       //
  Matrix4(0x0F, 0x00);       //

  Matrix5(0x09, 0x00);       //
  Matrix5(0x0A, 0x0F);       //
  Matrix5(0x0B, 0x0F);       //
  Matrix5(0x0C, 0x01);       //
  Matrix5(0x0F, 0x0F);       //
  Matrix5(0x0F, 0x00);       //
}

int main(void)
{
	BCSCTL3 |= XCAP_3;
	TACCTL0 |= CCIE;          // xtal has 12.5 pF caps
    TACCR0 = (32767 -1);               // f_xtal / 2 - 1 gives 2 Hz
    TACTL = TASSEL_1 + MC_1 + TACLR + ID_0; // ACLK + Up Mode + Clear timer

    P1REN |= (switchright + switchcenter + switchleft);
    P1OUT |= (switchright + switchcenter + switchleft);

  P2DIR |= (LED1 + LED0 + alarmPin);
  P2OUT |= (LED1);
  P2OUT &= ~(LED0 + alarmPin);

  WDTCTL = WDTPW | WDTHOLD;

  SPI_Init();
  _delay_cycles(100000);
  Init_MAX7219();
  _delay_cycles(1000);
  __enable_interrupt(); // enable all interrupts

  setText(" ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789m!@)(>^<.,';:a");
  while(1)
  {

	  updateNumber();
	  _delay_cycles(10000);
	  setTime();
	  if(hours<10)
	  {
		  printmatrix(0,(hoursfirst + (27 - 48)),Colon,(minutessecond +(27 - 48)),(minutessfirst+(27 - 48)));
		  //printmatrix(0,(hoursfirst + (27 - 48)),Colon,(secondssecond +(27 - 48)),(secondsfirst+(27 - 48)));
	  }
	  else
	  {

		  printmatrix((hourssecond+ (27 - 48)),(hoursfirst + (27 - 48)),Colon,(minutessecond +(27 - 48)),(minutessfirst+(27 - 48)));
	  }


  }

}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void)
{

	P2OUT ^= LED0;
	seconds++;
	P2OUT ^= LED1;
	if(Colon == 0)
	{
		Colon =49;
	}
	else
	{
		Colon =0;
	}


	if(seconds >59)
	{
		seconds = 0;
		minutes++;
	}
	if(minutes >59)
	{
		minutes = 0;
		hours++;
	}
	if(hours >12)
	{
		hours = 1;
		if(days <99)
		{
		days++;
		}
	}
	if(days ==0 && hours == 0 && minutes == 0 && seconds == 0)
	{
		//TACCTL0 &= ~CCIE;
		//alarm =1;
	}

}




