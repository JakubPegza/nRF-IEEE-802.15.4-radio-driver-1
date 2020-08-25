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
/* Undefine all hardware peripherals provided by MDK so that they can be mocked later */

extern char g_periph_mem[];

#if defined(NRF_RADIO)
  #undef  NRF_RADIO
  #undef  NRF_RADIO_BASE
  #define NRF_RADIO_BASE              (g_periph_mem + 0x01000)
  #define NRF_RADIO                   ((NRF_RADIO_Type*)         NRF_RADIO_BASE)
#endif

#endif /* NRF_H */

