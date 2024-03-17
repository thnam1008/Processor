#include<htc.h>

__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_OFF & CP_OFF & BOREN_ON & LVP_OFF & CPD_OFF & WRT_OFF & DEBUG_OFF);
 
#define SOUND RD0

#define rs RC0
#define rw RC1
#define en RC2
#define delay for(i=0;i<1000;i++)

int i;

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);

 
void main()
{
    TRISB=TRISC0=TRISC1=TRISC2=0;
    TRISD=0xff;
    lcd_init();
    cmd(0x80);
    show("Nhom 3 - RAI K63");
    while(1) {
        if(SOUND) {
            cmd(0xc0);
            show("Sound Detected");
            delay;delay;
        } else {
            cmd(0xc0);
            show("                ");
        }
    }
}

void lcd_init()
{
    cmd(0x38);
    cmd(0x0c);
    cmd(0x06);
    cmd(0x80);
}

void cmd(unsigned char a)
{
    PORTB=a;
    rs=0;
    rw=0;
    en=1;
    delay;
    en=0;
}

void dat(unsigned char b)
{
    PORTB=b;
    rs=1;
    rw=0;
    en=1;
    delay;
    en=0;
}

void show(unsigned char *s)
{
    while(*s)
    {
        dat(*s++);
    }
}