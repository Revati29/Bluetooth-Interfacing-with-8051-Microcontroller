#include <reg52.h> 
void Uart_Init(); 
void delay(unsigned int itime); 
void send_str (unsigned char *str); 
void send_char (unsigned char chr); 
sbit Relay1 = P2^0; sbit Relay2 = P2^1; 
char temp; char incoming_com =0; 
void main() { 
Uart_Init(); 
P2=0xFF; 
while(1) 
{ while(!RI); 
incoming_com=SBUF; 
temp = incoming_com; 
RI=0; if(temp =='A') 
{ 
  Relay1=0; 
  send_str("Relay1 ON"); 
 delay(100); 
}
else if(temp == 'B') 
{ Relay1=1; 
 send_str("Relay1 OFF");
 delay(100); 
}
else if(temp =='C') 
{ 
Relay2=0; 
send_str("Relay2 ON"); 
  delay(100); 
}
else if(temp == 'D') 
{ 
Relay2=1; 
send_str("Relay2 OFF"); 
delay(100);
}
 temp=0; 
} 
}
void delay(unsigned int itime)
{
  unsigned int i,j; 
  for(i=0;i<itime;i++) 
    for(j=0;j<120;j++); 
}
void Uart_Init()
{
SCON = 0x50; // SCON: mode 1, 8-bit UART, enable receive
TMOD |= 0x20; // TMOD: timer 1, mode 2, 8-bit TH1 = 0xFD; // 
TH1: for 9600 baud 
TR1 = 1; //TR1: timer 1 run 
}
void send_str (unsigned char *str)
{ 
  while(*str)
    {
       send_char(*str++); 
              } 
  send_char(0x0D); 
}
void send_char (unsigned char chr) 
{
SBUF = chr; 
while (TI==0); //Wait until the character is completely sent 
TI=0; //Reset the Transmit Interrupt flag
}




