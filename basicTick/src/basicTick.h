#ifndef BASIC_TICK_H
#define BASIC_TICK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Kalibrasyon Ayarları */
#define BASICTICK_CALIBRATION_INTERVAL 5000 
#define BASICTICK_DRIFT_DIRECTION      1    

void     basicTick_init(void);
uint32_t basicTick_get(void);
void     basicTick_reset(void);

extern volatile uint32_t __basicTick_count;

void __basicTick_atomic_enter(void);
void __basicTick_atomic_exit(void);

#ifdef __cplusplus
}
#endif

#endif
