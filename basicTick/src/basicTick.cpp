#include "basicTick.h"

// Değişkeni C bağlantısı ile tanımlıyoruz (Assembly'den erişim için)
extern "C" {
    volatile uint32_t __basicTick_count = 0;
}

void basicTick_reset(void) {
    __basicTick_atomic_enter();
    __basicTick_count = 0;
    __basicTick_atomic_exit();
}

uint32_t basicTick_get(void) {
    uint32_t raw_count;
    
    // Ham veriyi atomik (kesintisiz) olarak oku
    __basicTick_atomic_enter();
    raw_count = __basicTick_count;
    __basicTick_atomic_exit();
    
    /* Kalibrasyon: Her 5 saniyede 1ms sapma için telafi */
    int32_t adjustment = (int32_t)(raw_count / BASICTICK_CALIBRATION_INTERVAL) * BASICTICK_DRIFT_DIRECTION;
    
    return (uint32_t)(raw_count + adjustment);
}
