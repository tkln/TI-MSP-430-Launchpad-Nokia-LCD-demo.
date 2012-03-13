#include <msp430.h>
#include <stdio.h>
#include <stdint.h>
#include "font.h"

#define F_CPU 1000
#define BLINK_PORT
#define BLINK_PIN 0

#define LCD_ENABLE P1OUT  &= ~BIT7;
#define LCD_DISABLE P1OUT |= BIT7;

#define LCD_DATA_MODE P1OUT |= BIT6
#define LCD_COMMAND_MODE P1OUT &= ~BIT6

//PIN5 RST

inline void spi_init(void);
inline void spi_transmit(uint8_t data);
inline void delay(uint16_t time);
inline void blink(void);

inline void lcd_init(void);
inline void lcd_send_data(uint8_t data);
inline void lcd_send_command(uint8_t command);
inline void lcd_clear(void);
inline void lcd_move_cursor(uint8_t x, uint8_t y);

inline void lcd_render_char(char c);
inline void lcd_print_int(uint16_t val);

int putchar(int c);

uint8_t h, m;

int main(void){
	WDTCTL = WDTPW + WDTHOLD;
	P1DIR |= BIT5 | BIT6 | BIT7; //RST, D/C, ENABLE
 	P1DIR |= BIT0;	
	
	P1OUT &= ~BIT0;
	P1OUT &= ~BIT6;

	spi_init();
	lcd_init();

	ADC10CTL1 = INCH_10 | ADC10DIV_3; // temp sensor
	ADC10CTL0 = SREF_1 | ADC10SHT_3 | REFON | ADC10ON | ADC10IE;
	
//	printf("hello");
	
	IE1_;
//	LPM0;

//	_BIS_SR(LPM0_bits + GIE); //not low power mode and enable interrupts
	uint8_t i;
	
	lcd_clear();
	for(i=0; i < 10; i++){
		putchar('a'+i);

	}

	while(0){
		lcd_clear();

		lcd_move_cursor(32, 3);
		// really need to rethink the formula
		lcd_print_int(( ((((ADC10MEM -128) & 0xff)) * 23) / 40 ) - 45 )  ;
		ADC10CTL0 |= ENC | ADC10SC;
		delay(100);
	}
	return 0;
}

int putchar(int c){
	if(c >= '0' && c <= '9'){
		c = c - '0';//numes
	}
	else if(c >= 'a'){
		c = c - '0' + 10;
	}
	lcd_render_char(c);
}

//interrupt (TIMERA0_VECTOR) IntServiceRoutine(void){
__attribute__((interrupt(TIMER0_A1_VECTOR))) void timer_isr(void){
	P1OUT ^= BIT0;
	CCR0 += 50;
}

inline void lcd_print_int(uint16_t val){
	lcd_render_char((val/(100))%10);
	lcd_render_char((val/(10))%10);
	lcd_render_char(val%10);
}

inline void lcd_render_char(char c){
/*	if(c>96){
		c=c-29;
	}*/

	uint8_t i = 0;
	while(i<5){
		lcd_send_data(font[c][i]);
		i++;
	}
	lcd_send_data(0); // one vertical clean line between numbers
}

inline void lcd_move_cursor(uint8_t x, uint8_t y){
	lcd_send_command(0b10000000 + x);
	lcd_send_command(0b01000000 + y);
}

inline void lcd_clear(void){
	uint16_t i = 0;
	while(i<504){
		lcd_send_data(0);
		i++;
	}
}

inline void lcd_send_command(uint8_t command){
	LCD_ENABLE;
	LCD_COMMAND_MODE;
	spi_transmit(command);
	LCD_DISABLE;
}

inline void lcd_send_data(uint8_t data){
	LCD_ENABLE;
	LCD_DATA_MODE;
	spi_transmit(data);
	LCD_DISABLE;
}

inline void lcd_init(void){
	LCD_ENABLE;
	P1OUT |= BIT5;
	delay(10);
	P1OUT &= ~BIT5;
	delay(10);
	P1OUT |= BIT5;
	LCD_DISABLE;

	lcd_send_command(0x21);
	lcd_send_command(0xbb);
	lcd_send_command(0x04);
	lcd_send_command(0x14);
	lcd_send_command(0x20);
	lcd_send_command(0x0c);
}	

inline void spi_init(void){
	P1SEL = BIT2 + BIT4; //data out, clock
	P1SEL2 = BIT2 + BIT4; 
	UCA0CTL0 |= UCMST | UCSYNC | UCMSB /*+ UCCKPL*/; //
	UCA0CTL1 |= UCSSEL_2;
	UCA0BR0 = 0xff;
	UCA0BR0 = 0;
	UCA0MCTL = 0;
	UCA0CTL1 &= ~UCSWRST;
}

inline void spi_transmit(uint8_t data){
	UCA0TXBUF = data;
	while(UCA0STAT & UCBUSY){
	}

}

inline void blink(void){
	P1OUT |= (1<<BLINK_PIN);
	delay(50);
	P1OUT &= ~(1<<BLINK_PIN);
	delay(50);
}

inline void delay(uint16_t time){
	while(time--){
		__delay_cycles(F_CPU);
	}
}

