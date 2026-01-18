# basicTick

basicTick is a low-level, hardware-based tick counter library for Arduino AVR platforms.  
It provides a lightweight time base similar to `millis()`, implemented using a hardware timer and ISR, with a port-based architecture.

This library is designed as a foundation for embedded kernels, schedulers, and timing-critical systems.

---

## Features

- Hardware timer based tick counter
- ISR-driven timekeeping
- No dependency on `millis()`, `delay()`, or Arduino timing APIs
- Port-based architecture (core + hardware port separation)
- Suitable for kernel / RTOS groundwork
- Written with C and AVR Assembly

---

## What It Does

- Initializes a hardware timer
- Increments a global tick counter inside an ISR
- Provides atomic access to the tick counter
- Acts as a monotonic time source

---

## What It Does NOT Do

- No delays
- No callbacks
- No software timers
- No scheduler
- No power management

Those belong to higher layers.

---

## Supported Platforms

Currently supported:

- ATmega328P (Arduino Uno / Nano)

Planned:

- Other AVR MCUs
- ESP32
- STM32 (SysTick based port)

---

## Architecture Overview

- **Core**: contains the tick counter logic and public API  
- **Port**: handles timer configuration, ISR, and atomic sections  
- **ISR**: increments the tick counter only

---

## Tick Resolution

Default configuration:

- Timer: Timer1
- Mode: CTC
- Prescaler: 64
- Tick frequency: **1000 Hz**
- Resolution: **1 tick = 1 ms**

Tick counter type: `uint32_t`  
Overflow time: ~49.7 days

---

## Public API

```c
void     basicTick_init(void);
uint32_t basicTick_get(void);
void     basicTick_reset(void);

