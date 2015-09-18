
#ifndef _TIMEOUT_H
#define _TIMEOUT_H

// Define initial Timer 0 / Timer 1 values for ~50 µs delay
#define T_50micros (65536-(tWord)((OSC_FREQ / 26000)/(OSC_PER_INST)))
#define T_50micros_H (T_50micros / 256)
#define T_50micros_L (T_50micros % 256)

// Define initial Timer 0 / Timer 1 values for ~500 µs delay
#define T_500micros (65536-(tWord)((OSC_FREQ)/(OSC_PER_INST*2000)))
#define T_500micros_H (T_500micros / 256)
#define T_500micros_L (T_500micros % 256)

// Define initial Timer 0 / Timer 1 values for ~1 msec delay
#define T_01ms (65536-(tWord)((OSC_FREQ)/(OSC_PER_INST*1000))) 
#define T_01ms_H (T_01ms / 256)
#define T_01ms_L (T_01ms % 256)
//
// Define initial Timer 0 / Timer 1 values for ~5 msec delay
#define T_05ms (65536-(tWord)((OSC_FREQ)/(OSC_PER_INST*200))) 
#define T_05ms_H (T_05ms / 256)
#define T_05ms_L (T_05ms % 256)
//
// Define initial Timer 0 / Timer 1 values for ~10 msec delay
#define T_10ms (65536-(tWord)((OSC_FREQ)/(OSC_PER_INST*100))) 
#define T_10ms_H (T_10ms / 256)
#define T_10ms_L (T_10ms % 256)
//
// Define initial Timer 0 / Timer 1 values for ~15 msec delay
#define T_15ms (65536-(tWord)((OSC_FREQ)/(OSC_PER_INST*67))) 
#define T_15ms_H (T_15ms / 256)
#define T_15ms_L (T_15ms % 256)
//
// Define initial Timer 0 / Timer 1 values for ~20 msec delay
#define T_20ms (65536-(tWord)((OSC_FREQ)/(OSC_PER_INST*50))) 
#define T_20ms_H (T_20ms / 256)
#define T_20ms_L (T_20ms % 256)
//
// Define initial Timer 0 / Timer 1 values for ~50 msec delay


#define T_50ms (65536-(tWord)((OSC_FREQ)/(OSC_PER_INST*20))) 
#define T_50ms_H (T_50ms / 256)
#define T_50ms_L (T_50ms % 256)
#endif
