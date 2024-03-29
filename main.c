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

inline void temp_sensor_init(void);

inline void io_init(void);

int putchar(int c);

inline void render_time(void);

volatile uint8_t h, m, s;
volatile uint32_t uptime;

int16_t temp_sensor_get_temp(void);

inline void timer_init(void);

int main(void){
	io_init();
	spi_init();
	lcd_init();
	temp_sensor_init();
	timer_init();

	h = m = s = 0;
	uptime = 0;

	render_time();




	IE2 = 0xff;
	IE1 = 0xff;

	__bis_SR_register( LPM3_bits +  GIE);        // enter LPM0 with interrrupt enable
	
	return 0;
}

inline void timer_init(){
	TA0CTL = TASSEL0 + TACLR;              // TA0CLK (ext xtal), reset timer
	TA0CCTL0 = CCIE;                         // CCR0 interrupt enabled
	TA0CTL |= MC_1;                         // Start Timer_A in up mode (counts to TACCR0 and resets to 0)
	// f = 1Hz
	TA0CCR0 = 32768;
//	TA0CCR0 =100;
	
}

int16_t temp_sensor_get_temp(){
//	int32_t temp = ADC10MEM;	
//	return ADC10MEM;
}

inline void io_init(void){
	WDTCTL = WDTPW + WDTHOLD;
	P1DIR |= BIT5 | BIT6 | BIT7; //RST, D/C, ENABLE
 	P1DIR |= BIT0;	
	
	P1OUT &= ~BIT0;
	P1OUT &= ~BIT6;
}

inline void temp_sensor_init(void){
	ADC10CTL1 = INCH_10 | ADC10DIV_3; // temp sensor, clock div 3
	ADC10CTL0 = SREF_1 | ADC10SHT_3 | REFON | ADC10ON | ADC10IE; //
}

int putchar(int c){
	/* the font is incomplete so all workarounds are implemented here */
	if(c >= '0' && c <= '9'){
		c = c - '0' +1;
	}
	else if(c >= 'A' && c < 'a'){
		c = c - '0' - 1;
	}
	else if(c >= 'a'){
		c = c - '0' - 8;
	}
	else if(c > '9'){
		c = c - '0' + 1 ;
	}
	if(c == ' '){
		c=0; 
	}
	lcd_render_char(c);
	return 0;
}

inline void render_time(void){
	ADC10CTL0 |= ENC + ADC10SC;
	lcd_clear();

	lcd_move_cursor(27, 0);	
	printf("%02d:%02d", h,m);

	lcd_move_cursor(0,1);
	printf("temp: %d",  (((ADC10MEM - 673) * 423) / 1024) - 11);

	ADC10CTL1 = INCH_11 | ADC10DIV_3; //bat mon, clk div 3
	ADC10CTL0 |= ENC + ADC10SC; //sample
	lcd_move_cursor(0,2);
	printf("Vbat: %d", ADC10MEM);

	lcd_move_cursor(0,3);
	printf("uptime: %d", uptime);

}

//interrupt (TIMERA0_VECTOR) IntServiceRoutine(void){
__attribute__((interrupt(TIMER0_A0_VECTOR))) void timer_isr(void){
	//executed at 1Hz
	if(s < 59){
		s = s + 1;
	}
	else{
		s = 0;
		m++;
		uptime++;
		render_time();
	}
	if(m >= 60){
		m = 0;
		h++;
	}
	if(h >= 24){
		h = 0;
	}
//	P1OUT ^= BIT0;
//	TACCR0 += 50;
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

