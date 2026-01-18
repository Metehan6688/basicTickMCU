# basicTickESP 🚀

**basicTickESP** is a professional, high-precision hardware tick counter library for the **ESP32**. It provides a lightweight 1ms time base by utilizing the **ESP-IDF GPTimer (General Purpose Timer)** engine and **IRAM-optimized ISRs**.

This library is designed for developers who need a rock-solid monotonic time source for embedded kernels, task schedulers, or real-time systems without the overhead or jitter of standard `millis()`.

---

## 🌟 Key Features

- **Hardware-Driven:** Uses the dedicated ESP32 GPTimer peripheral for absolute timing.
- **IRAM Optimized:** The Interrupt Service Routine (ISR) is placed in Instruction RAM, preventing delays during Flash/SPI operations.
- **Microsecond Engine:** Runs on a 1MHz hardware resolution for maximum precision.
- **Zero Jitter:** Unlike software timers, this uses a hardware-level alarm system.
- **Pure C Engine:** Minimal footprint, high speed, and compatible with both Arduino and ESP-IDF.

---

## 🛠 Project Architecture

- **Core**: Handles the 32-bit tick counter and public API.
- **Engine**: ESP-IDF GPTimer driver (the modern replacement for legacy timers).
- **ISR**: High-priority `IRAM_ATTR` handler for zero-latency increments.



---

## 🚀 Installation

1. Download the repository as a `.zip` file.
2. In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library...**.
3. Select the downloaded file.

---

## 💻 API Reference

### `void basicTick_init(void)`
Initializes the GPTimer, sets the interval to 1ms, and starts the background ISR. Call this in `setup()`.

### `uint32_t basicTick_get(void)`
Returns the current tick count in milliseconds. This read is **natively atomic** on ESP32's 32-bit architecture.

### `void basicTick_reset(void)`
Resets the tick counter back to zero.

---

## 📝 Simple Example

```cpp
#include <basicTickESP.h>

void setup() {
    Serial.begin(115200);
    basicTick_init(); // Initialize hardware timer
}

void loop() {
    static uint32_t lastPrint = 0;
    uint32_t now = basicTick_get();

    if (now - lastPrint >= 1000) {
        Serial.printf("System Uptime: %u ms\n", now);
        lastPrint = now;
    }
}
