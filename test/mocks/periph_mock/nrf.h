/*
 * Copyright (c) Nordic Semiconductor ASA. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor ASA.
 * The use, copying, transfer or disclosure of such information is prohibited except by
 * express written agreement with Nordic Semiconductor ASA.
 */

/****************************************************************************************************//**
 * @file     nrf.h
 *
 * @brief    A modified version of nrf.h to make the unit tests that depend on hardware registers
 *           compile and run on a PC.
 *******************************************************************************************************/

#ifndef NRF_H
#define NRF_H

#include <stdint.h>

/* Hack since Microsoft Visual Studio (MSVC) is not supported by the MDK header files.
 * In order to avoid #warning in nrf*.h we pretend that MSVC is a texas instruments compiler (TMS470).
 * This is harmless as the define is only used to check if anonymous unions are supported. */
#ifdef _MSC_VER
#define __TMS470__
#endif

/* Define NRF52_SERIES for common use in nRF52 series devices. Only if not previously defined. */
#if defined (NRF52805_XXAA) || defined (NRF52810_XXAA) || defined (NRF52811_XXAA) || defined (NRF52832_XXAA) || defined (NRF52832_XXAB) || defined (NRF52833_XXAA) || defined (NRF52840_XXAA)
#ifndef NRF52_SERIES
        #define NRF52_SERIES
    #endif
#endif

/* Define NRF53_SERIES for common use in nRF53 series devices. */
#if defined (NRF5340_XXAA_APPLICATION) || defined (NRF5340_XXAA_NETWORK)
#ifndef NRF53_SERIES
        #define NRF53_SERIES
    #endif
#endif

#if defined (NRF52840_XXAA)
    #include "nrf52840.h"
    #include "nrf52840_bitfields.h"
    #include "nrf51_to_nrf52840.h"
    #include "nrf52_to_nrf52840.h"
#elif defined (NRF52833_XXAA)
    #include "nrf52833.h"
    #include "nrf52833_bitfields.h"
#elif defined (NRF52832_XXAA) || defined (NRF52832_XXAB)
    #include "nrf52.h"
    #include "nrf52_bitfields.h"
    #include "nrf51_to_nrf52.h"
    #include "nrf52_name_change.h"
#elif defined (NRF52820_XXAA)
    #include "nrf52820.h"
    #include "nrf52820_bitfields.h"
#elif defined (NRF52811_XXAA)
    #include "nrf52811.h"
    #include "nrf52811_bitfields.h"
#elif defined (NRF52810_XXAA)
    #include "nrf52810.h"
    #include "nrf52810_bitfields.h"
    #include "nrf51_to_nrf52810.h"
    #include "nrf52_to_nrf52810.h"
#elif defined(NRF5340_XXAA_NETWORK)
    #include "nrf5340_network.h"
    #include "nrf5340_network_bitfields.h"
#else
    #error "Device must be defined."
#endif /* NRF52832_XXAA, NRF52810_XXAA, NRF52840_XXAA */

#ifdef _MSC_VER
#undef __TMS470__
#endif

#if defined(USE_MULTIHW_DEFINES)
#include "nrf_multihw_defines.h"
#endif

#define __STATIC_INLINE static inline
#define __ALIGN(n)      __attribute__((aligned(n)))
#define __ASM           __asm
#define __WEAK          __attribute__((weak))

extern char g_periph_mem[];

#if defined(NRF52840_XXAA) || \
    defined(NRF52833_XXAA) || \
    defined(NRF52820_XXAA) || \
    defined(NRF52811_XXAA)

#if defined(NRF_RADIO)
  #undef  NRF_RADIO
  #undef  NRF_RADIO_BASE
  #define NRF_RADIO_BASE              (g_periph_mem + 0x01000)
  #define NRF_RADIO                   ((NRF_RADIO_Type*)         NRF_RADIO_BASE)
#endif

#if defined(NRF_GPIOTE)
  #undef  NRF_GPIOTE
  #undef  NRF_GPIOTE_BASE
  #define NRF_GPIOTE_BASE             (g_periph_mem + 0x06000)
  #define NRF_GPIOTE                  ((NRF_GPIOTE_Type*)        NRF_GPIOTE_BASE)
#endif

#if defined(NRF_TIMER0)
  #undef  NRF_TIMER0
  #undef  NRF_TIMER0_BASE
  #define NRF_TIMER0_BASE             (g_periph_mem + 0x08000)
  #define NRF_TIMER0                  ((NRF_TIMER_Type*)         NRF_TIMER0_BASE)
#endif

#if defined(NRF_TIMER1)
  #undef  NRF_TIMER1
  #undef  NRF_TIMER1_BASE
  #define NRF_TIMER1_BASE             (g_periph_mem + 0x09000)
  #define NRF_TIMER1                  ((NRF_TIMER_Type*)         NRF_TIMER1_BASE)
#endif

#if defined(NRF_TIMER2)
  #undef  NRF_TIMER2
  #undef  NRF_TIMER2_BASE
  #define NRF_TIMER2_BASE             (g_periph_mem + 0x0A000)
  #define NRF_TIMER2                  ((NRF_TIMER_Type*)         NRF_TIMER2_BASE)
#endif

#if defined(NRF_EGU0)
  #undef  NRF_EGU0
  #undef  NRF_EGU0_BASE
  #define NRF_EGU0_BASE               (g_periph_mem + 0x14000)
  #define NRF_EGU0                    ((NRF_EGU_Type*)           NRF_EGU0_BASE)
#endif

#if defined(NRF_EGU1)
  #undef  NRF_EGU1
  #undef  NRF_EGU1_BASE
  #define NRF_EGU1_BASE               (g_periph_mem + 0x15000)
  #define NRF_EGU1                    ((NRF_EGU_Type*)           NRF_EGU1_BASE)
#endif

#if defined(NRF_EGU2)
  #undef  NRF_EGU2
  #undef  NRF_EGU2_BASE
  #define NRF_EGU2_BASE               (g_periph_mem + 0x16000)
  #define NRF_EGU2                    ((NRF_EGU_Type*)           NRF_EGU2_BASE)
#endif

#if defined(NRF_EGU3)
  #undef  NRF_EGU3
  #undef  NRF_EGU3_BASE
  #define NRF_EGU3_BASE               (g_periph_mem + 0x17000)
  #define NRF_EGU3                    ((NRF_EGU_Type*)           NRF_EGU3_BASE)
#endif

#if defined(NRF_EGU4)
  #undef  NRF_EGU4
  #undef  NRF_EGU4_BASE
  #define NRF_EGU4_BASE               (g_periph_mem + 0x18000)
  #define NRF_EGU4                    ((NRF_EGU_Type*)           NRF_EGU4_BASE)
#endif

#if defined(NRF_EGU5)
  #undef  NRF_EGU5
  #undef  NRF_EGU5_BASE
  #define NRF_EGU5_BASE               (g_periph_mem + 0x19000)
  #define NRF_EGU5                    ((NRF_EGU_Type*)           NRF_EGU5_BASE)
#endif

#if defined(NRF_TIMER3)
  #undef  NRF_TIMER3
  #undef  NRF_TIMER3_BASE
  #define NRF_TIMER3_BASE             (g_periph_mem + 0x1A000)
  #define NRF_TIMER3                  ((NRF_TIMER_Type*)         NRF_TIMER3_BASE)
#endif

#if defined(NRF_TIMER4)
  #undef  NRF_TIMER4
  #undef  NRF_TIMER4_BASE
  #define NRF_TIMER4_BASE             (g_periph_mem + 0x1B000)
  #define NRF_TIMER4                  ((NRF_TIMER_Type*)         NRF_TIMER4_BASE)
#endif

#if defined(NRF_PPI)
  #undef  NRF_PPI
  #undef  NRF_PPI_BASE
  #define NRF_PPI_BASE                (g_periph_mem + 0x1F000)
  #define NRF_PPI                     ((NRF_PPI_Type*)           NRF_PPI_BASE)
#endif

#elif defined(NRF5340_XXAA_NETWORK)

#if defined(NRF_RADIO_NS)
  #undef  NRF_RADIO_NS
  #undef  NRF_RADIO_NS_BASE
  #define NRF_RADIO_NS_BASE              (g_periph_mem + 0x08000)
  #define NRF_RADIO_NS                   ((NRF_RADIO_Type*)         NRF_RADIO_NS_BASE)
#endif

#if defined(NRF_GPIOTE_NS)
  #undef  NRF_GPIOTE_NS
  #undef  NRF_GPIOTE_NS_BASE
  #define NRF_GPIOTE_NS_BASE             (g_periph_mem + 0x0A000)
  #define NRF_GPIOTE_NS                  ((NRF_GPIOTE_Type*)        NRF_GPIOTE_NS_BASE)
#endif

#if defined(NRF_TIMER0_NS)
  #undef  NRF_TIMER0_NS
  #undef  NRF_TIMER0_NS_BASE
  #define NRF_TIMER0_NS_BASE             (g_periph_mem + 0x0C000)
  #define NRF_TIMER0_NS                  ((NRF_TIMER_Type*)         NRF_TIMER0_NS_BASE)
#endif

#if defined(NRF_DPPIC_NS)
  #undef  NRF_DPPIC_NS
  #undef  NRF_DPPIC_NS_BASE
  #define NRF_DPPIC_NS_BASE              (g_periph_mem + 0x0F000)
  #define NRF_DPPIC_NS                   ((NRF_DPPIC_Type*)         NRF_DPPIC_NS_BASE)
#endif

#if defined(NRF_EGU0_NS)
  #undef  NRF_EGU0_NS
  #undef  NRF_EGU0_NS_BASE
  #define NRF_EGU0_NS_BASE               (g_periph_mem + 0x14000)
  #define NRF_EGU0_NS                    ((NRF_EGU_Type*)           NRF_EGU0_NS_BASE)
#endif

#if defined(NRF_TIMER1_NS)
  #undef  NRF_TIMER1_NS
  #undef  NRF_TIMER1_NS_BASE
  #define NRF_TIMER1_NS_BASE             (g_periph_mem + 0x18000)
  #define NRF_TIMER1_NS                  ((NRF_TIMER_Type*)         NRF_TIMER1_NS_BASE)
#endif

#if defined(NRF_TIMER2_NS)
  #undef  NRF_TIMER2_NS
  #undef  NRF_TIMER2_NS_BASE
  #define NRF_TIMER2_NS_BASE             (g_periph_mem + 0x19000)
  #define NRF_TIMER2_NS                  ((NRF_TIMER_Type*)         NRF_TIMER2_NS_BASE)
#endif

#else
#error Cannot mock peripherals of unknown SoC
#endif

#endif /* NRF_H */

