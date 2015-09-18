#include "main.H"
#include "timeout.H"

// Function prototypes
void delay_50micros(void); 
void delay_500micros(void); 
void delay_1ms(void); 
void delay_5ms(void); 
void delay_10ms(void); 
void delay_15ms(void); 
void delay_20ms(void); 
void delay_50ms(void); 

// TIMEOUT code variable & TIMEOUT code (dummy here)
#define TIMEOUT 0xFF

void delay_50micros(void)
{
	// Configure Timer 0 as a 16-bit timer 
	TMOD &= 0xF0; // Clear all T0 bits (T1 left unchanged)
	TMOD |= 0x01; // Set required T0 bits (T1 left unchanged) 
	ET0 = 0;      // No interrupts
	// Simple timeout feature – approx 50 µs
	TH0 = T_50micros_H;
	TL0 = T_50micros_L;//T_50micros_L;
	TF0 = 0; // Clear flag
	TR0 = 1; // Start timer
	while (!TF0);
	TR0 = 0; 
}

void delay_500micros(void)
{
	// Configure Timer 0 as a 16-bit timer 
	TMOD &= 0xF0; // Clear all T0 bits (T1 left unchanged)
	TMOD |= 0x01; // Set required T0 bits (T1 left unchanged) 
	ET0 = 0;      // No interrupts
	// Simple timeout feature – approx 50 µs
	TH0 = T_500micros_H;
	TL0 = T_500micros_L;//T_50micros_L;
	TF0 = 0; // Clear flag
	TR0 = 1; // Start timer
	while (!TF0);
	TR0 = 0; 
}

void delay_5ms(void)
{
	// Configure Timer 0 as a 16-bit timer 
	TMOD &= 0xF0; // Clear all T0 bits (T1 left unchanged)
	TMOD |= 0x01; // Set required T0 bits (T1 left unchanged) 
	ET0 = 0;      // No interrupts
	// Simple timeout feature – approx 50 µs
	TH0 = T_05ms_H;
	TL0 = T_05ms_L;//T_50micros_L;
	TF0 = 0; // Clear flag
	TR0 = 1; // Start timer
	while (!TF0);
	TR0 = 0; 
}

void delay_1ms(void)
{
	// Configure Timer 0 as a 16-bit timer 
	TMOD &= 0xF0; // Clear all T0 bits (T1 left unchanged)
	TMOD |= 0x01; // Set required T0 bits (T1 left unchanged) 
	ET0 = 0;      // No interrupts
	// Simple timeout feature – approx 50 µs
	TH0 = T_01ms_H;
	TL0 = T_01ms_L;//T_50micros_L;
	TF0 = 0; // Clear flag
	TR0 = 1; // Start timer
	while (!TF0);
	TR0 = 0; 
}

void delay_10ms(void)
{
	// Configure Timer 0 as a 16-bit timer 
	TMOD &= 0xF0; // Clear all T0 bits (T1 left unchanged)
	TMOD |= 0x01; // Set required T0 bits (T1 left unchanged) 
	ET0 = 0;      // No interrupts
	// Simple timeout feature – approx 50 µs
	TH0 = T_10ms_H;
	TL0 = T_10ms_L;//T_50micros_L;
	TF0 = 0; // Clear flag
	TR0 = 1; // Start timer
	while (!TF0);
	TR0 = 0; 
}

void delay_15ms(void)
{
	// Configure Timer 0 as a 16-bit timer 
	TMOD &= 0xF0; // Clear all T0 bits (T1 left unchanged)
	TMOD |= 0x01; // Set required T0 bits (T1 left unchanged) 
	ET0 = 0;      // No interrupts
	// Simple timeout feature – approx 50 µs
	TH0 = T_15ms_H;
	TL0 = T_15ms_L;//T_50micros_L;
	TF0 = 0; // Clear flag
	TR0 = 1; // Start timer
	while (!TF0);
	TR0 = 0; 
}

void delay_20ms(void)
{
	// Configure Timer 0 as a 16-bit timer 
	TMOD &= 0xF0; // Clear all T0 bits (T1 left unchanged)
	TMOD |= 0x01; // Set required T0 bits (T1 left unchanged) 
	ET0 = 0;      // No interrupts
	// Simple timeout feature – approx 50 µs
	TH0 = T_20ms_H;
	TL0 = T_20ms_L;//T_50micros_L;
	TF0 = 0; // Clear flag
	TR0 = 1; // Start timer
	while (!TF0);
	TR0 = 0; 
}

void delay_50ms(void)
{
	// Configure Timer 0 as a 16-bit timer 
	TMOD &= 0xF0; // Clear all T0 bits (T1 left unchanged)
	TMOD |= 0x01; // Set required T0 bits (T1 left unchanged) 
	ET0 = 0;      // No interrupts
	// Simple timeout feature – approx 50 µs
	TH0 = T_50ms_H;
	TL0 = T_50ms_L;//T_50micros_L;
	TF0 = 0; // Clear flag
	TR0 = 1; // Start timer
	while (!TF0);
	TR0 = 0; 

}
