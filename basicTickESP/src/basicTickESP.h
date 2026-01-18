#ifndef BASIC_TICK_ESP_H
#define BASIC_TICK_ESP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// API
void     basicTick_init(void);
uint32_t basicTick_get(void);
void     basicTick_reset(void);

#ifdef __cplusplus
}
#endif

#endif
