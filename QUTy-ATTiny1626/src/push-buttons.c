/*
 * QUTy-push-buttons.c
 */ 
#define F_CPU 3333333
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

uint8_t rxbuf[256];             //Rx buffer
volatile uint8_t pWrite = 0;    //Index into Rx buffer
uint8_t pRead = 0;              //Index into Rx buffer

// Function: uart_recv_char
// Description: Waits for and retrieves a character from USART0.
// Arguments: None
// Returns: The received character.
int uart_recv_char(FILE *stream) {
	//Wait for buffer is empty or not
	while(!(pWrite-pRead));
	//Return character in buffer
	return rxbuf[pRead++];
}

// Function: uart_send_char
// Description: Sends a character over USART0.
// Arguments: c - The character to send.
// Returns: None
int uart_send_char(char c,FILE *stream) {
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
	FILE uart = FDEV_SETUP_STREAM(uart_send_char, uart_recv_char, _FDEV_SETUP_RW);
	stdout = &uart;
	stdin = &uart;
}


//USART - Rx ISR function
ISR(USART0_RXC_vect) {
	//push char to Rx buffer
	uint8_t ch = USART0.RXDATAL;
	rxbuf[pWrite++] = ch;
}

void buttons_init() {
  // Enable pull-up resistors for PA [4:7]
  PORTA.PIN4CTRL = PORT_PULLUPEN_bm;
  PORTA.PIN5CTRL = PORT_PULLUPEN_bm;
  PORTA.PIN6CTRL = PORT_PULLUPEN_bm;
  PORTA.PIN7CTRL = PORT_PULLUPEN_bm;
}

// Push button states
uint8_t btn_previous = 0xFF; // Previous state of push buttons
uint8_t btn_new = 0xFF;      // New state of push buttons
uint8_t btn_falling; // Flags for detecting falling  push buttons
uint8_t btn_rising; // Flags for detecting rising edges of push buttons
volatile uint8_t pb_state = 0xFF;   // Volatile variable to store push button state

// Function: push_buttons_debounce
// Description: Debounce push button inputs.
// Arguments: None
// Returns: None
void push_buttons_debounce(void)
{
    static uint8_t count0 = 0;
    static uint8_t count1 = 0;

    uint8_t pb_sample = PORTA.IN;
    uint8_t pb_changed = pb_state ^ pb_sample;

    // Vertical counter
    count1 = (count1 ^ count0) & pb_changed;
    count0 = ~count0 & pb_changed;

    // New debounced state
    // Update if PB high for three samples
    pb_state ^= (count1 & count0);
}
/*
 * Function: void scan_button_status()
 * Description: Scan the status of buttons. 
 * Arguments: None
 * Returns: None
 */
void scan_button_status()
{
    // Previous debounced state
	push_buttons_debounce();
    btn_previous = btn_new;
    btn_new = pb_state;

    // Compare edge & prev/new state
    btn_falling = (btn_previous ^ btn_new) & btn_previous; // pressed - failling edge
    btn_rising = (btn_previous ^ btn_new) & btn_new;       // released - rising edge
}

void my_delay_ms(int ms)
{
	while (ms > 0)
	{
		_delay_ms(1);
		--ms;
	}
}
//main
int main(void)
{
	cli();          // Disable interrupts
	uart_init();
	buttons_init();
	sei();
	/* Replace with your application code */
	while (1)
	{
		scan_button_status();
		printf("failing edge=%x\n",btn_falling);
		printf("raising edge=%x\n",btn_rising);
		my_delay_ms(500);
	}
}
