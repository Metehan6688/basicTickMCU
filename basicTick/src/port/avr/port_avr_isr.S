#define __SFR_OFFSET 0
#include <avr/io.h>

    .extern __basicTick_count
    .global __vector_7

__vector_7:
    push r0
    in   r0, SREG
    push r0
    push r1
    clr  r1
    push r24
    push r25
    push r26
    push r27

    lds r24, __basicTick_count
    lds r25, __basicTick_count+1
    lds r26, __basicTick_count+2
    lds r27, __basicTick_count+3

    adiw r24, 1
    adc  r26, r1
    adc  r27, r1

    sts __basicTick_count,   r24
    sts __basicTick_count+1, r25
    sts __basicTick_count+2, r26
    sts __basicTick_count+3, r27

    pop r27
    pop r26
    pop r25
    pop r24
    pop r1
    pop r0
    out SREG, r0
    pop r0
    reti
