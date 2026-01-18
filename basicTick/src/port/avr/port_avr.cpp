#include <avr/io.h>
#include <avr/interrupt.h>
#include "basicTick.h"
#include "port_avr.h"

#ifndef __AVR_ATmega328P__
#error "basicTick AVR port supports ATmega328P only"
#endif

static uint8_t sreg_cache;

extern "C" {

void __basicTick_atomic_enter(void) {
    sreg_cache = SREG;
    cli();
}

void __basicTick_atomic_exit(void) {
    SREG = sreg_cache;
}

void basicTick_init(void) {
    port_basicTick_timerInit();
}

void port_basicTick_timerInit(void) {
    __basicTick_atomic_enter();

    // Timer 2: CTC Modu, Prescaler 64
    TCCR2A = (1 << WGM21); 
    TCCR2B = (1 << CS22); 
    
    // 16MHz / 64 = 250kHz. 1ms için 250 adım (0-249).
    OCR2A  = 249; 
    
    // Kesmeyi aktif et
    TIMSK2 |= (1 << OCIE2A);

    __basicTick_atomic_exit();
}
}

