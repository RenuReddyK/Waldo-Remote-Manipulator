
/* Name: main.c
 * Project: Q 3.2
 * Author: Kasala Renu Reddy
 */


#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include "m_usb.h"
#define PRINTNUM(x); m_usb_tx_uint(x); m_usb_tx_char(10); m_usb_tx_char(13) // char 10 and 13 are carriage return and line feed

// Function for setting up an arbitrary ADC port
void setup_ADC_port(uint8_t channel) {
    
    // 1. Setting the VCC for V_reference
    set(ADMUX, REFS0);
    
    // 2. Setting the prescaler to /128
    set(ADCSRA, ADPS0);
    set(ADCSRA, ADPS1);
    set(ADCSRA, ADPS2);
    
    // 3. Disabling the digital input for the specified channel
    set(DIDR0, channel);
    
    // 5. Choose which channel to use
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
}

// Function for reading the setup ADC port
int read_ADC_port() {
    
    // 6. Enable ADC
    set(ADCSRA, ADEN);
    
    // 7. Start conversion
    set(ADCSRA, ADSC);
    
    // 8. Wait for the conversion to finish
    while (!bit_is_set(ADCSRA, ADIF));
    
    // Read the result (16-bit register)
    float adc_value = ADC;
    
    // 9. Use value - print (ADC) to USB
    // m_usb_tx_uint(adc_value);
    
    // Print angle value
//    float angle = adc_value * (270.0/1023.0);
    
    // 10. Clear the conversion complete flag
    set(ADCSRA, ADIF);
    
    return adc_value;
}

void servo_control(int adc_value, int channel)
{
    // Calculate the servo control value based on ADC reading and set the corresponding COM bit for the timer
    // 16000000/(256) --> 62,500
    // At 25Hz frequency --> 62,500/(2*25) --> 1250
    int max_servo = 25;
    int min_servo = 225;
    int max_potentiometer = 1023;
    int min_potentiometer = 0;
    int compare_value =  adc_value * (max_servo - min_servo) / (max_potentiometer - min_potentiometer) + min_servo;
    
    // Setting timer 3A: clear at OCR3A, set at rollover   [C6]
    // 16 bit timer
    if (channel == 5) {
        
        // Timer register for 3A:  (mode 7) UP to 0x03FF (10-bit), PWM mode
        set(TCCR3A,WGM30);
        set(TCCR3A,WGM31);
        set(TCCR3B,WGM32);
        clear(TCCR3B,WGM33);
        // Timer 3 prescaler set to /256
        set(TCCR3B,CS32);
        clear(TCCR3B,CS31);
        clear(TCCR3B,CS30);
       
        // Setting PWM duty cycle
        OCR3A = compare_value;
        // Set polarity for output compare: clear at OCR3A, set at rollover
        set(TCCR3A, COM3A1);
        clear(TCCR3A,COM3A0);
    }
    
    // Setting timer 1B: clear at OCR1B, set at rollover   [B6]
    // 16 bit timer
    else if (channel == 10) {
        
        // Timer register for 1B:  (mode 7) UP to 0x03FF (10-bit), PWM mode
        set(TCCR1A,WGM10);
        set(TCCR1A,WGM11);
        set(TCCR1B,WGM12);
        clear(TCCR1B,WGM13);
        // Timer 1 prescaler set to /256
        set(TCCR1B,CS12);
        clear(TCCR1B,CS11);
        clear(TCCR1B,CS10);
        
        // Setting PWM duty cycle
        OCR1B = compare_value;
        // Set polarity for output compare: clear at OCR1B, set at rollover
        set(TCCR1A, COM1B1);
        clear(TCCR1A,COM1B0);
    }
    
    // Setting timer 0A: clear at OCR0A, set at 0xFF       [B7]
    // 8 bit timer
    else {
        
        // Timer register for 0A
        set(TCCR0A,WGM00);
        set(TCCR0A,WGM01);
        set(TCCR0B,WGM02);
        // Timer 0 prescaler set to /256
        set(TCCR0B,CS02);
        clear(TCCR0B,CS01);
        clear(TCCR0B,CS00);
        
        // Setting PWM duty cycle
        OCR0A = compare_value;
        // Set polarity for output compare
        set(TCCR0A, COM0A1);
        clear(TCCR0A, COM0A0);
    }
}

int main() {
    // Initialize the USB communication
    m_usb_init();

    set(DDRC, 6);
    set(DDRB, 6);
    set(DDRB, 7);
    
    while (1) {
        
        // Initializing the ADC channels by calling the subroutine 1
        setup_ADC_port(4);
        // Read from the ADC channels by calling the subroutine 2
        m_usb_tx_string("ADC 1: ");
        // Printing the sensor values to the USB serial port
        int adc_val1 = read_ADC_port();
        m_usb_tx_uint(adc_val1);
        // Controlling the servo motor 1
        servo_control(adc_val1, 5);

        // Similarly initialising for the second sensor
        setup_ADC_port(1);
        m_usb_tx_string(", ADC 2: ");
        int adc_val2 = read_ADC_port();
        m_usb_tx_uint(adc_val2);
        // Controlling the servo motor 2
        servo_control(adc_val2, 10);
        
        // Similarly initialising for the third sensor
        setup_ADC_port(0);
        m_usb_tx_string(", ADC 3: ");
        int adc_val3 = read_ADC_port();
        m_usb_tx_uint(adc_val3);
        // Controlling the servo motor 3
        servo_control(adc_val3, 11);

        m_usb_tx_string("\r\n");

    }
    return 0;
}
