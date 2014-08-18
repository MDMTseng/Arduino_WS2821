#include "MTOOL.h"
#define UBYTE byte
#define UINT unsigned int
#define PORTX PORTB

UBYTE opin = 0xFF;
#define NOP_DELAY() __asm__ __volatile__ ("nop\n\t");
#define X2(d)  d;d
#define X3(d)  d;d;d
#define X4(d)  d;d;d;d
#define X16(d) d;d;d;d;d;d;d;d;d;d; d;d;d;d;d;d
#define X17(d) d;d;d;d;d;d;d;d;d;d; d;d;d;d;d;d;d
#define X18(d) d;d;d;d;d;d;d;d;d;d; d;d;d;d;d;d;d;d
#define X19(d) d;d;d;d;d;d;d;d;d;d; d;d;d;d;d;d;d;d;d
#define X20(d) d;d;d;d;d;d;d;d;d;d; d;d;d;d;d;d;d;d;d;d
#define X25(d) d;d;d;d;d;d;d;d;d;d; d;d;d;d;d;d;d;d;d;d; d;d;d;d;d;d;d;d;d;d

void setup() {
  // put your setup code here, to run once:
  DDRB = 0xFF;
  PORTX = 0xFF;
  Serial.begin(9600);
}


void SendDMX(UBYTE* arr, unsigned int arrL)
{
  unsigned int i;
  // put your main code here, to run repeatedly:
  PORTX = (PORTX & ~opin);//0
  delayMicroseconds(89);
  noInterrupts();
  PORTX ^= opin; //1
  delayMicroseconds(7);
  //delay(100);
  /*dATA sEC
  */
  UBYTE tmp;

  UBYTE j = 0;
  for (i = 0; i < arrL; i++)
  {
    tmp = arr[i];

    delayMicroseconds(4);
    PORTX ^= opin; //0 stop
    delayMicroseconds(1);
    for (j = 8; j; j--) {

      if (tmp & 1) {
        PORTX = PORTX | opin;
      }
      else      PORTX = (PORTX & ~opin);
      tmp >>= 1;
      //X17(NOP_DELAY());
      X4(X4(NOP_DELAY()););
    }
    X2(X4(NOP_DELAY()););

    PORTX = PORTX | opin;

  }

  interrupts();
}


void SendDMX_WAddr(UBYTE* arr, unsigned int arrL)
{
  unsigned int i;
  // put your main code here, to run repeatedly:
  PORTX ^= opin; //0
  //delayMicroseconds(87);
  delay(500);
  noInterrupts();
  PORTX ^= opin; //1
  delayMicroseconds(12);
  //delay(100);
  /*dATA sEC
  */
  UBYTE tmp;

  UBYTE j = 0;
  for (i = 0; i < arrL; i++)
  {
    tmp = arr[i];

    delayMicroseconds(4);
    PORTX ^= opin; //0 stop
    delayMicroseconds(1);
    for (j = 8; j; j--) {

      if (tmp & 0x80) {
        PORTX = PORTX | opin;
      }
      else      PORTX = (PORTX & ~opin);
      tmp <<= 1;
      //X17(NOP_DELAY());
      X4(X4(NOP_DELAY()););
    }
    X2(X4(NOP_DELAY()););

    PORTX = PORTX | opin;

  }

  interrupts();
  delay(10300);
}
UBYTE ssBuff[31];
//UBYTE ss[] = {0x00,    0x55, 0x55,0x55,       0x00, 0x00,0x00,       0x00, 0x00,0x00,       0x00, 0x00,0x00,       0x00, 0x00,0x00,       0x00, 0x00,0x00,      0x00, 0x00,0x00,      0x00, 0x00,0x00,      0x00, 0x00,0x00,      0x00, 0x00,0x00,      0x00, 0x00,0x00,      0x00, 0x00,0x00,      0x00, 0x00,0x00,      0x00, 0x00,0x00,      0x00, 0x00,0x00,      0x00, 0x00,0x00,     };
//UBYTE sswa[] = {0x00,  0x0,0xf0,0xd2 ,0x1,0xf0,0xd2 ,0x2,0xf0,0xd2 ,0x3,0xf0,0xd2 ,0x4,0xf0,0xd2 ,0x5,0xf0,0xd2 ,0x6,0xf0,0xd2 ,0x7,0xf0,0xd2 ,0x8,0xf0,0xd2 ,0x9,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2 ,0x0,0xf0,0xd2};

void loop() {
  wData();
  //wArr();
}

byte ssss[] = {
  100,
  102, 104, 107, 109, 112, 114, 117, 119, 121, 124, 126, 129, 131, 133, 136, 138, 140, 142, 145, 147,
  149, 151, 153, 155, 157, 159, 161, 163, 165, 167, 169, 170, 172, 174, 175, 177, 179, 180, 181, 183,
  184, 185, 187, 188, 189, 190, 191, 192, 193, 194, 195, 195, 196, 197, 197, 198, 198, 198, 199, 199,
  199, 199, 199, 199, 199, 199, 199, 199, 199, 198, 198, 197, 197, 196, 196, 195, 194, 193, 193, 192,
  191, 190, 188, 187, 186, 185, 184, 182, 181, 179, 178, 176, 175, 173, 171, 170, 168, 166, 164, 162,
  160, 158, 156, 154, 152, 150, 148, 146, 144, 141, 139, 137, 134, 132, 130, 127, 125, 123, 120, 118,
  115, 113, 111, 108, 106, 103, 101, 98, 96, 93, 91, 88, 86, 84, 81, 79, 76, 74, 72, 69,
  67, 65, 62, 60, 58, 55, 53, 51, 49, 47, 45, 43, 41, 39, 37, 35, 33, 31, 29, 28,
  26, 24, 23, 21, 20, 18, 17, 15, 14, 13, 12, 11, 9, 8, 7, 6, 6, 5, 4, 3,
  3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2,
  2, 3, 4, 4, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 18, 19, 20, 22, 24,
  25, 27, 29, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 57, 59, 61, 63,
  66, 68, 70, 73, 75, 78, 80, 82, 85, 87, 90, 92, 95, 97, 99
};
UBYTE acc = 127;
UBYTE Rev=0;
void wData() {
  /*if(acc==10){Rev=0;Serial.println("REV:0");}
  if(acc==250){Rev=1;Serial.println("REV:1");}
  if(Rev)
    acc--;
  else
    acc++;*/
 acc+=2;
  UBYTE *ssA = ssBuff + 1;
  unsigned int i = 0;
  for (i = 0; i < sizeof(ssBuff) - 1; i += 3, ssA += 3)
  {
    ssA[0] =
    ssA[1] = 
    ssA[2] = ssss[(byte)(acc+i*10)];
  }
  SendDMX(ssBuff, sizeof(ssBuff));
  Serial.println((byte)acc);
  delay(10);
  // SendDMX_WAddr(sswa,sizeof(sswa));
}
void wArr() {
  UBYTE *ssA = ssBuff + 1;
  unsigned int i = 0;


  unsigned int k = 1;
  for (i = 0; i < sizeof(ssBuff) - 1; i += 3, k += 3)
  {
    ssA[0] = k;
    ssA[1] = 0xf0;
    ssA[2] = 0xd2;
    ssA += 3;
  }
  SendDMX_WAddr(ssBuff, sizeof(ssBuff));
  // SendDMX_WAddr(sswa,sizeof(sswa));
}
