#include<htc.h>
#include<pic.h>


__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_OFF & CP_OFF & BOREN_ON & LVP_OFF & CPD_OFF & WRT_OFF & DEBUG_OFF);

// USART
void ser_int();
void tx(unsigned char);
unsigned char rx();
void txstr(unsigned char *);

// LCD
#define rs RC0
#define rw RC1
#define en RC2
#define delay for(j=0;j<1000;j++)

int j;

unsigned char rcvCh;

void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);

void main()
{
    unsigned int i;
    TRISD=TRISC0=TRISC1=TRISC2=0;
    TRISC6=0;   //Output (TX)
    TRISC7=1;   //Input (RX)
    ser_int();
    txstr("(Nhom 3 test USART): Nhap ky tu tu ban phim may tinh:)\n\r\r");
    
    lcd_init();
    cmd(0x80);
    show("Ky tu: ");
    
    while(1) {
        rcvCh = rx(); // receive character from UART
        tx(rcvCh); // echo back to UART terminal
        show(&rcvCh); // display on LCD
    }   
}   

void ser_int() // khoi tao USART
{
    TXSTA=0x20; //BRGH=0, TXEN = 1, Asynchronous Mode, 8-bit mode
    RCSTA=0b10010000; //Serial Port enabled,8-bit reception
    SPBRG=17;           //9600 baudrate for 11.0592Mhz
    TXIF=RCIF=0;
}
    
void tx(unsigned char a) // turyen tin di
{
    TXREG=a;
    while(!TXIF);
    TXIF = 0;
}

unsigned char rx() // nhan thong tin
{
    while(!RCIF);
    RCIF=0;
    return RCREG;
}

void lcd_init() // khoi tao LCD
{
    //Lenh 6: Khoi tao che do hoat dong
    cmd(0x38); // 0b00111000 - 8bit, 2 dong, co chu 5x7
    //Lenh 4: Khoi tao man hinh, con tro
    cmd(0x0d); // 0b00001101 - man hinh mo, vuong, nhay
    //Lenh 3: Xac dinh che do nhap du lieu
    cmd(0x06); // 0b00000110
    //Dinh dia chi trong vung RAM hien thi
    cmd(0x80); // 0b10000000
}

void cmd(unsigned char a) // gui lenh
{
    PORTD=a;
    rs=0;
    rw=0;
    en=1;
    delay;
    en=0;
}

void dat(unsigned char b) // gui du lieu
{
    PORTD=b;
    rs=1;
    rw=0;
    en=1;
    delay;
    en=0;
}

void txstr(unsigned char *s)
{
    while(*s) {
        tx(*s++);
    }
}

void show(unsigned char *s)
{
    while(*s) {
        dat(*s++);
    }
}