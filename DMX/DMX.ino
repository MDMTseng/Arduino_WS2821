
#define UBYTE char

UBYTE opin = _BV(0);
#define NOP_DELAY() __asm__ __volatile__ ("nop\n\t");
#define X19(d) d;d;d;d;d;d;d;d;d;d;d;d;d;d;d;d;d;d;d;

void setup() {
  // put your setup code here, to run once:
  DDRB = 0xFF;
  PORTB = 0xFF;
}
//UBYTE ss[] = {0x00, 0xFF, 0xFF,0x00,       0x11, 0x00,0xFF,     0x01, 0x00,0x00   ,0x00, 0x00,0x1  ,0x00, 0x00,0x1,0x00, 0x00,0x1  ,0x00, 0x00,0x1 };
UBYTE ss[] = {0x00,  0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2};


void SendDMX(UBYTE* arr,unsigned int arrL)
{
    unsigned int i;
  // put your main code here, to run repeatedly:
  PORTB ^= opin; //0
  delayMicroseconds(87);
  noInterrupts();
  PORTB ^= opin; //1
  delayMicroseconds(12);
  //delay(100);
  /*dATA sEC
  */
  UBYTE tmp;
  
  UBYTE j = 0;
  for (i = 0; i < arrL; i++)
  {
    tmp = arr[i];

    delayMicroseconds(1);
    PORTB ^= opin; //0 stop
    delayMicroseconds(1);
    for (j = 8; j; j--) {

      if (tmp & 1) PORTB = PORTB | opin;
      else      PORTB = (PORTB & ~opin);
      tmp >>= 1;
      X19(NOP_DELAY())
    }

    PORTB = PORTB | opin;

  }
  
  interrupts();
  delay(330);
}


void SendDMX_WAddr(UBYTE* arr,unsigned int arrL)
{
    unsigned int i;
  // put your main code here, to run repeatedly:
  PORTB ^= opin; //0
  //delayMicroseconds(87);
  delay(500);
  noInterrupts();
  PORTB ^= opin; //1
  delayMicroseconds(12);
  //delay(100);
  /*dATA sEC
  */
  UBYTE tmp;
  
  UBYTE j = 0;
  for (i = 0; i < arrL; i++)
  {
    tmp = arr[i];

    delayMicroseconds(1);
    PORTB ^= opin; //0 stop
    delayMicroseconds(1);
    for (j = 8; j; j--) {

      if (tmp & 0x80) PORTB = PORTB | opin;
      else      PORTB = (PORTB & ~opin);
      tmp <<= 1;
      X19(NOP_DELAY())
    }

    PORTB = PORTB | opin;

  }
  
  interrupts();
  delay(10300);
}
void loop() {
   SendDMX_WAddr(ss,sizeof(ss));
}
