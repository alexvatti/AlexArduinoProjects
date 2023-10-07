#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#include "qutyserial.h"

/** Tutorial 08

INTRODUCTION:

In this week's tutorial you will be working with the TCA0 and
ADC0 peripherals. You will use these to control the brightness
of the 7-segment display, produce a tone from the buzzer, and
read the position of the potentiometer.

Interfacing with these hardware devices on the QUTy is a core
requirement for Assessment 2.
*/

/** EX: 8.0

TASK: Write a function named "pwm_init" which will configure
TCA0 to produce a

    3X0 Hz, 1Y % duty cycle output on the DISP EN net.

Where XY are the last two digits of your student number.

Your function should take no arguments and return no values.

EXAMPLE: If your student number were n12345678 then
you should configure TCA0 to produce a

    370 Hz, 18 % duty cycle output.
*/

/**
 * pwm_init function initializes PWM (Pulse Width Modulation) settings,
 *  configuring a timer and its associated pins to generate a PWM signal.
 *  It sets the timer's frequency, duty cycle, and enables PWM output on specific pins.
*/

//my student number: n11507365 --> X=6, and Y=5. --->  360 Hz, 15 % duty cycle output on the DISP EN net.

/*
Formula for PWM Frequency:
--------------------------
f_PWM = 1 / (TOP * T_clk_timer)

Where:
- f_PWM is the desired PWM frequency in Hertz (Hz).
- TOP is the value to which the timer counts.
- T_clk_timer is the time period of the timer clock in seconds (s).

To set a PWM frequency of 360 Hz with a timer clock period of 3.3333e-6 s,
TOP should be calculated as follows:
TOP = 1 / (f_PWM * T_clk_timer)
    = 1 / (360 * 3.3333e-6)
    ≈ 8333    ---->  but I had to use 9250  <-----

Formula for PWM Duty Cycle:
---------------------------
CMPx = TOP * (duty_cycle / 100)

Where:
- CMPx is the compare match value.
- TOP is the value to which the timer counts.
- duty_cycle is the desired duty cycle in percentage (%).

To set a duty cycle of 15% with a TOP value of 9250,
CMPx should be calculated as follows:
CMPx = TOP * (duty_cycle / 100)
     = 9250 * (15 / 100)
     = 1387.5
*/

void pwm_init()
{
    // Enabling the Display: 
    PORTB.OUTSET = PIN1_bm; // Set the DISP EN (Display Enable) pin high to disable it.
    PORTB.DIRSET = PIN1_bm; // Configure DISP EN pin as an output.

    // Timer Configuration for PWM:
    TCA0.SPLIT.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc; // Configure the timer clock source with no prescaling.
    TCA0.SINGLE.CTRLB |= TCA_SINGLE_WGMODE_SINGLESLOPE_gc; // Set the timer waveform generation mode to single slope.
    TCA0.SINGLE.CTRLB |= TCA_SINGLE_CMP1EN_bm; // Enable the compare channel 1 (CMP1) for the timer,  DISP EN is connected to WO1, hence enabling compare for CMP1.

   // Frequency Configuration:
   TCA0.SINGLE.PER = 9250; // Set the timer period to achieve a PWM frequency of 360Hz.

  // Duty Cycle Configuration for CMP1:
  TCA0.SINGLE.CMP1 = 1387; // Set the compare value for CMP1 to achieve an 15% duty cycle.
  
  // Additional Timer Configuration:
  PORTB.DIRSET = PIN0_bm; // Configure PIN0 as an output.
  TCA0.SINGLE.CMP0 = 4761; // Set the compare value for CMP0.
  TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm; // Enabling the timer.
}
/** CODE: Write your code for Ex 8.0 above this line. */

/** EX: 8.1

TASK: Write a function named "adc_init" below which will configure
ADC0 in 8-bit single conversion mode.

The ADC should be configured to sample the voltage on the POT net,
be placed in free-running mode, and start sampling immediately.
*/

void adc_init()
{
    ADC0.CTRLA = ADC_ENABLE_bm;
    ADC0.CTRLB = ADC_PRESC_DIV2_gc;
    ADC0.CTRLC = ADC_TIMEBASE4_bm | ADC_REFSEL_VDD_gc;
    ADC0.CTRLE = 64; 
    ADC0.CTRLF = ADC_FREERUN_bm; 
    ADC0.CTRLF |= ADC_LEFTADJ_bm; 
    ADC0.MUXPOS = ADC_MUXPOS_AIN2_gc;
    ADC0.COMMAND |= ADC_MODE_SINGLE_8BIT_gc; 
    ADC0.COMMAND |= ADC_START_IMMEDIATE_gc; 
}   
/** CODE: Write your code for Ex 8.1 above this line. */

int main(void)
{
    // Variable to store the result of the ADC conversion
    uint8_t result;

    serial_init();
    PORTA.DIRSET = PIN1_bm;
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;
    _delay_ms(3000); // 3 second delay

    /** EX: 8.2

    TASK: Call the two initialisation functions you have written above
    such that the TCA0 and ADC0 are enabled and operational.

    On completion of this exercise, the 7-segment display should show
    an 8 on the RHS that is initially bright, but dims after 3 seconds.

    You can then test your ADC configuration via the serial terminal
    using the instructions below.
    */

    pwm_init();
    adc_init();
    /** CODE: Write your code for Ex 8.2 above this line. */

    printf("Turn the potentiometer R1 fully counter-clockwise, then press S4.\n");
    while (VPORTA.IN & PIN7_bm); result = ADC0.RESULT0; printf("Ex 8.2.0: result = 0x%02X, expected = 0x00\n", result);
    _delay_ms(1000); printf("Turn the potentiometer R1 fully clockwise, then press S4.\n");
    while (VPORTA.IN & PIN7_bm); result = ADC0.RESULT0; printf("Ex 8.2.1: result = 0x%02X, expected = 0xFF\n", result);
    _delay_ms(1000); printf("Turn the potentiometer R1 to the half-way position, then press S4.\n");
    while (VPORTA.IN & PIN7_bm); result = ADC0.RESULT0; printf("Ex 8.2.2: result = 0x%02X, expected = ~0x80\n", result);

    // Main loop
    while (1)
    {
        /** EX: 8.3

        TASK: Write code below such that the position of the potentiometer
        controls the brightness of the 7-segment display in reverse.

        The display should be:
        - fully bright when the potentiometer is turned fully counter-clockwise
        - fully dim when the potentiometer is turned fully clockwise

        NOTE: ADC0.RESULT yields a value of 0 when the potentiometer is turned
        fully counter-clockwise, and a value of 255 when turned fully clockwise.

        You will need to reverse this range of values using a mathematical
        expression to achieve the desired functionality.

        HINT:

        1. Scale the 8-bit value from ADC0.RESULT to a value between
           0 and the TOP value of TCA0.
        2. Reverse the direction of the potentiometer by subtracting the
           scaled value from the TOP value of TCA0.

        Alternatively,

        1. Reverse the direction of the potentiometer by subtracting the
           8-bit value from ADC0.RESULT from 255.
        2. Scale the reversed value to a value between 0 and the TOP
           value of TCA0.

        TIP: Avoid floating-point arithmetic by performing integer operations.
        To ensure that you do not encounter integer overflow and loss of precision,
        perform operations in an appropriate order.
        */

        //Reading ADC Value ( 0 to 255)
        result = ADC0.RESULT;
        //Converting into another Scale 255 to 0
        uint16_t reversed_result = 255 - result;

        // Define the TOP value for TCA0 (adjust this as needed) (360 Hz)
        uint16_t TOP_VALUE = 9250; // Example value, replace with your actual TOP value

        // Calculate the scaled and reversed brightness value
        uint16_t scaled_brightness = (reversed_result * TOP_VALUE) / 255;

        // Set the TCA0 compare register to control display brightness
        TCA0.SINGLE.CMP1 = scaled_brightness;

        /** CODE: Write your code for Ex 8.3 above this line. */

        /** EX: 8.4

        TASK: Write code below such that the buzzer produces a 360 Hz tone
        when the potentiometer position is between 87.5% and 100%, where
        0% is fully CCW and 100% is fully CW.

        When the pot position is outside of this range the buzzer should be silent.

        The buzzer should be driven with a
        - 50 % duty cycle square wave when active
        - 0 % duty cycle square wave when inactive

        TIP: You will need to modify the code in pwm_init() to achieve this functionality.

        NOTE: The frequency specified above is the same as for Ex 8.0.
        */

        if (result > 223 && result < 255) // -----> 223 is 87.5% of 255
        {
            TCA0.SINGLE.CTRLA |= TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
            TCA0.SINGLE.CTRLA |= TCA_SINGLE_CMP0_bm; // Enable PWM on pin connected to 
            // Set the PWM frequency for 360 Hz by adjusting PER
            TCA0.SINGLE.PER = 9250; // For a 360 Hz frequency
            // Set the duty cycle to 50% (half the period)
            TCA0.SINGLE.CMP0 = TCA0.SINGLE.PER / 2;
        } else 
        {
            TCA0.SINGLE.CTRLA &= ~TCA_SINGLE_CMP0_bm; // Disable PWM 
        }
        /** CODE: Write your code for Ex 8.4 above this line. */
    }
}
