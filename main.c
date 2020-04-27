
                      /*Main program*/
#include<lpc214x.h>
#include<string.h>
#include"timer.h"
#include"lcd.h"
#include"keypad.h"
#define bit(x) (1<<x)
char flag=0;
char pwd[]="3333";
char buffer[16];    // buffer for temp storage of string
void lock(void);
int main(void)
{
    char key[5];
    int con=0;
    lcd_init();
    lcd_cmd(0x01);
    lcd_string("press 1 to cha-");
    lcd_cmd(0x01);
    lcd_string("new password");
    flag=get_key();
    if(flag=='1')
    { 
        lcd_cmd(0x01);
        lcd_string("New pwd : ");
        for(con=0;con<4;con++){
  	        pwd[con]=get_key();
  	        lcd_string("*");
        }
            pwd[con]=0;
    }
    while(1){
        lcd_cmd(0x01);
        lcd_string("password:");
        //lcd_cmd(0xc0);
        for(con=0;con<4;con++){
            key[con]=get_key();
            lcd_string("*");
        }
        key[con]=0;
        if(strcmp(key,pwd)!=0){
            lcd_cmd(0x20);
            lcd_cmd(0x01);
            lcd_string("Wrong password");
        }
        else {
            lock();
            // Account transaction
            int acc_balance = 5;
            lcd_cmd(0x01);
            sprintf(buffer, "accbal %d. Debit",acc_balance);
            lcd_string(buffer);
            char a = get_key();
            int x = (int)a -48; // Convert to integer
            if(x<=5){
                acc_balance = acc_balance - x;
                lcd_cmd(0x01);
                sprintf(buffer,"final accbal %d. Thnks",acc_balance);
                lcd_string(buffer);
                timemdel(200);
              	lcd_cmd(0x01);
    						lcd_string("exiting");
              	timemdel(200);
            }    

        }
    }
}

void lock(void)
{   
    IO0DIR|=bit(19)|bit(20);
    lcd_cmd(0x01);
    lcd_string("processing");
    IO0SET|=bit(19);
    timemdel(50);
    IO0CLR|=bit(19);
    timemdel(100);
    IO0SET|=bit(20);
    timemdel(50);
    IO0CLR|=bit(20);
}