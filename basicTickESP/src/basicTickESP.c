#include "basicTickESP.h"
#include "driver/gptimer.h" // ESP32 General Purpose Timer sürücüsü
#include "esp_attr.h"       // IRAM_ATTR için

static volatile uint32_t __tick_count = 0;
static gptimer_handle_t timer_handle = NULL;

// ISR: Bu fonksiyon RAM üzerinde çalışır, inanılmaz hızlıdır.
static bool IRAM_ATTR on_timer_alarm_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx) {
    __tick_count++;
    return false; // Yield gerekmiyor
}

void basicTick_init(void) {
    // 1. Zamanlayıcı Yapılandırması (1 tick = 1 microsecond için 1MHz)
    gptimer_config_t timer_config = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000, // 1MHz
    };
    gptimer_new_timer(&timer_config, &timer_handle);

    // 2. Alarm Ayarı: Her 1000 microsecond'da (1ms) bir tetiklen
    gptimer_alarm_config_t alarm_config = {
        .reload_count = 0,
        .alarm_count = 1000, 
        .flags.auto_reload_on_alarm = true,
    };
    gptimer_set_alarm_action(timer_handle, &alarm_config);

    // 3. Callback (Kesme) Bağlantısı
    gptimer_event_callbacks_t cbs = {
        .on_alarm = on_timer_alarm_cb,
    };
    gptimer_register_event_callbacks(timer_handle, &cbs, NULL);

    // 4. Zamanlayıcıyı Başlat
    gptimer_enable(timer_handle);
    gptimer_start(timer_handle);
}

uint32_t basicTick_get(void) {
    // ESP32 32-bit olduğu için bu okuma donanımsal olarak atomiktir.
    return __tick_count + 1;
}

void basicTick_reset(void) {
    __tick_count = 0;
}
