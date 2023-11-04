/*
 * QUTy-UART-Example.cpp
 * Baud Rate 9600-8N-1
 * Clock: 3.3MHZ
 * Baud rate = (64*3.333333MHZ)/(9600*16)
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t rxbuf[256];             //Rx buffer
volatile uint8_t pWrite = 0;    //Index into Rx buffer
uint8_t pRead = 0;              //Index into Rx buffer

// Function: uart_recv_char
// Description: Waits for and retrieves a character from USART0.
// Arguments: None
// Returns: The received character.
int uart_recv_char() {
	//Wait for buffer is empty or not
	while(!(pWrite-pRead));
	//Return character in buffer
	return rxbuf[pRead++];
}

// Function: uart_send_char
// Description: Sends a character over USART0.
// Arguments: c - The character to send.
// Returns: None
int uart_send_char(char c) {
	//Wait while UART Tx busy
	while (!(USART0.STATUS & USART_DREIF_bm));
	//put char to Tx buffer
	USART0.TXDATAL = c;
	return c;
}

// Function: uart_init
// Description: Initialize UART (Universal Asynchronous Receiver/Transmitter) hardware for communication.
void uart_init(void)
{

	// Set Tx pin as output
	PORTB.DIRSET = PIN2_bm;
	// Set the baud rate to 9600 for serial communication
	USART0.BAUD = 1389; //for 9600 baud rate = (64*3.333333MHZ)/(9600*16)
	// Enable receive complete interrupt to handle incoming data
	USART0.CTRLA = USART_RXCIE_bm;
	// Enable receiver and transmitter for UART communication
	USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
}
	

//USART - Rx ISR function
ISR(USART0_RXC_vect) {
	//push char to Rx buffer
	uint8_t ch = USART0.RXDATAL;
	rxbuf[pWrite++] = ch;
}

//main
int main(void)
{
	char ch;
	cli();          // Disable interrupts
	uart_init();
	sei();  
    /* Replace with your application code */
    while (1) 
    {
		ch=uart_recv_char();
		uart_send_char(ch);
    }
}
