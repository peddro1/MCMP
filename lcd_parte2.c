#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include "util/delay.h"

#define F_CPU 160000000UL
#define Barramento_lcd PORTB

#define RS PC0
#define RW PC1
#define E PC2

void inicializa_lcd(){
	
	
	_delay_ms(20);
	envia_comando_lcd(0x38);
	envia_comando_lcd(0x38);
	envia_comando_lcd(0x06);
	envia_comando_lcd(0x0E);
	envia_comando_lcd(0x01);
}


void envia_comando_lcd(unsigned char dado){
	PORTC=0x00;
	PORTC=0x00;
	PORTC=0x00;
	Barramento_lcd=dado;
	PORTC=0b00000100;
	PORTC=0x00;
	_delay_ms(20);
	
}

void envia_dado_lcd(unsigned char dado){
	PORTC=0x00;
	PORTC=0b00000001;
	PORTC=0b00000001;
	Barramento_lcd=dado;
	PORTC=0b00000101;
	PORTC=0b00000001;
	_delay_ms(20);
}

void envia_num_lcd(int dado){
	char a = (char)dado;
	PORTC=0x00;
	PORTC=0b00000001;
	PORTC=0b00000001;
	Barramento_lcd=dado;
	PORTC=0b00000101;
	PORTC=0b00000001;
	_delay_ms(20);
}

void relogio(){
	int a,b,c,d,e,f;
	
	while(1){
		for(a=0;a<3;a++){
			
			envia_comando_lcd(0xC4);
			envia_num_lcd(a);
			for(b=0;b<4;b++){
				
				envia_comando_lcd(0xC5);
				envia_num_lcd(b);
				envia_comando_lcd(0xC6);
				envia_dado_lcd(':');
				for(c=0;c<6;c++){
					
					envia_comando_lcd(0xC7);
					envia_num_lcd(c);
					for(d=0;d<10;d++){
						
						envia_comando_lcd(0xC8);
						envia_num_lcd(d);
						envia_comando_lcd(0xC9);
						envia_dado_lcd(':');
						for(e=0;e<6;e++){
							
							envia_comando_lcd(0xCA);
							envia_num_lcd(e);
							for(f=0;f<10;f++){
								
								envia_comando_lcd(0xCB);
								envia_num_lcd(f);
								_delay_ms(1000);	
							}
						}
					}
				}	
			}
		}
	}
	
	
	
}

int main(void)
{
    DDRB = 0b00000000;
	DDRC = 0b00000111;
	inicializa_lcd();
	
    while (1) 
    {
		envia_comando_lcd(0x82);
		envia_dado_lcd('T');
		envia_dado_lcd('E');
		envia_dado_lcd('S');
		envia_dado_lcd('T');
		envia_dado_lcd('E');
		envia_dado_lcd(' ');
		envia_dado_lcd('D');
		envia_dado_lcd('O');
		envia_dado_lcd(' ');
		envia_dado_lcd('L');
		envia_dado_lcd('C');
		envia_dado_lcd('D');
		
		
		relogio();
		
		_delay_ms(1000000);
		envia_comando_lcd(0x01);
		
    }
}

