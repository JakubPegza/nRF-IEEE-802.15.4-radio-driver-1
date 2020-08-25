/*
 * Copyright (c) Nordic Semiconductor ASA. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor ASA.
 * The use, copying, transfer or disclosure of such information is prohibited except by
 * express written agreement with Nordic Semiconductor ASA.
 */

#include "nrf.h"

#include <string.h>

char g_periph_mem[0x20000];

void nrf_mock_reset(void)
{
    memset(g_periph_mem, 0, sizeof(g_periph_mem));
}

#if 0
#if defined(MOCK_NRF_FICR)
  NRF_FICR_Type m_NRF_FICR = {0};
  NRF_FICR_Type * NRF_FICR = &m_NRF_FICR;
#endif

#if defined(MOCK_NRF_UICR)
  NRF_UICR_Type m_NRF_UICR = {0};
  NRF_UICR_Type * NRF_UICR = &m_NRF_UICR;
#endif

#if defined(MOCK_NRF_BPROT)
  /* soc_nrf52 writes to out of bounds memory for ACL & BPROT. Make sure to allocate enough memory */
  typedef struct {
    __IM  NRF_BPROT_Type data;
    __IM  uint32_t  PADDING[512];
  } NRF_BPROT_Alloc_Type;

  NRF_BPROT_Alloc_Type m_NRF_BPROT = {0};
  NRF_BPROT_Type * NRF_BPROT = (NRF_BPROT_Type*) &m_NRF_BPROT;
#endif

#if defined(MOCK_NRF_POWER)
  NRF_POWER_Type m_NRF_POWER = {0};
  NRF_POWER_Type * NRF_POWER = &m_NRF_POWER;
#endif

#if defined(MOCK_NRF_CLOCK)
  NRF_CLOCK_Type m_NRF_CLOCK = {0};
  NRF_CLOCK_Type * NRF_CLOCK = &m_NRF_CLOCK;
#endif

#if defined(MOCK_NRF_RADIO)
  NRF_RADIO_Type m_NRF_RADIO = {0};
  NRF_RADIO_Type * NRF_RADIO = &m_NRF_RADIO;
#endif

#if defined(MOCK_NRF_UARTE0)
  NRF_UARTE_Type m_NRF_UARTE0 = {0};
  NRF_UARTE_Type * NRF_UARTE0 = &m_NRF_UARTE0;
#endif

#if defined(MOCK_NRF_UARTE1)
  NRF_UARTE_Type m_NRF_UARTE1 = {0};
  NRF_UARTE_Type * NRF_UARTE1 = &m_NRF_UARTE1;
#endif

#if defined(MOCK_NRF_UART0)
  NRF_UART_Type m_NRF_UART0 = {0};
  NRF_UART_Type * NRF_UART0 = &m_NRF_UART0;
#endif

#if defined(MOCK_NRF_SPIM0)
  NRF_SPIM_Type m_NRF_SPIM0 = {0};
  NRF_SPIM_Type * NRF_SPIM0 = &m_NRF_SPIM0;
#endif

#if defined(MOCK_NRF_SPIS0)
  NRF_SPIS_Type m_NRF_SPIS0 = {0};
  NRF_SPIS_Type * NRF_SPIS0 = &m_NRF_SPIS0;
#endif

#if defined(MOCK_NRF_TWIM0)
  NRF_TWIM_Type m_NRF_TWIM0 = {0};
  NRF_TWIM_Type * NRF_TWIM0 = &m_NRF_TWIM0;
#endif

#if defined(MOCK_NRF_TWIS0)
  NRF_TWIS_Type m_NRF_TWIS0 = {0};
  NRF_TWIS_Type * NRF_TWIS0 = &m_NRF_TWIS0;
#endif

#if defined(MOCK_NRF_SPI0)
  NRF_SPI_Type m_NRF_SPI0 = {0};
  NRF_SPI_Type * NRF_SPI0 = &m_NRF_SPI0;
#endif

#if defined(MOCK_NRF_TWI0)
  NRF_TWI_Type m_NRF_TWI0 = {0};
  NRF_TWI_Type * NRF_TWI0 = &m_NRF_TWI0;
#endif

#if defined(MOCK_NRF_SPIM1)
  NRF_SPIM_Type m_NRF_SPIM1 = {0};
  NRF_SPIM_Type * NRF_SPIM1 = &m_NRF_SPIM1;
#endif

#if defined(MOCK_NRF_SPIS1)
  NRF_SPIS_Type m_NRF_SPIS1 = {0};
  NRF_SPIS_Type * NRF_SPIS1 = &m_NRF_SPIS1;
#endif

#if defined(MOCK_NRF_TWIM1)
  NRF_TWIM_Type m_NRF_TWIM1 = {0};
  NRF_TWIM_Type * NRF_TWIM1 = &m_NRF_TWIM1;
#endif

#if defined(MOCK_NRF_TWIS1)
  NRF_TWIS_Type m_NRF_TWIS1 = {0};
  NRF_TWIS_Type * NRF_TWIS1 = &m_NRF_TWIS1;
#endif

#if defined(MOCK_NRF_SPI1)
  NRF_SPI_Type m_NRF_SPI1 = {0};
  NRF_SPI_Type * NRF_SPI1 = &m_NRF_SPI1;
#endif

#if defined(MOCK_NRF_TWI1)
  NRF_TWI_Type m_NRF_TWI1 = {0};
  NRF_TWI_Type * NRF_TWI1 = &m_NRF_TWI1;
#endif

#if defined(MOCK_NRF_NFCT)
  NRF_NFCT_Type m_NRF_NFCT = {0};
  NRF_NFCT_Type * NRF_NFCT = &m_NRF_NFCT;
#endif

#if defined(MOCK_NRF_GPIOTE)
  NRF_GPIOTE_Type m_NRF_GPIOTE = {0};
  NRF_GPIOTE_Type * NRF_GPIOTE = &m_NRF_GPIOTE;
#endif

#if defined(MOCK_NRF_SAADC)
  NRF_SAADC_Type m_NRF_SAADC = {0};
  NRF_SAADC_Type * NRF_SAADC = &m_NRF_SAADC;
#endif

#if defined(MOCK_NRF_TIMER0)
  NRF_TIMER_Type m_NRF_TIMER0 = {0};
  NRF_TIMER_Type * NRF_TIMER0 = &m_NRF_TIMER0;
#endif

#if defined(MOCK_NRF_TIMER1)
  NRF_TIMER_Type m_NRF_TIMER1 = {0};
  NRF_TIMER_Type * NRF_TIMER1 = &m_NRF_TIMER1;
#endif

#if defined(MOCK_NRF_TIMER2)
  NRF_TIMER_Type m_NRF_TIMER2 = {0};
  NRF_TIMER_Type * NRF_TIMER2 = &m_NRF_TIMER2;
#endif

#if defined(MOCK_NRF_RTC0)
  NRF_RTC_Type m_NRF_RTC0 = {0};
  NRF_RTC_Type * NRF_RTC0 = &m_NRF_RTC0;
#endif

#if defined(MOCK_NRF_TEMP)
  NRF_TEMP_Type m_NRF_TEMP = {0};
  NRF_TEMP_Type * NRF_TEMP = &m_NRF_TEMP;
#endif

#if defined(MOCK_NRF_RNG)
  NRF_RNG_Type m_NRF_RNG = {0};
  NRF_RNG_Type * NRF_RNG = &m_NRF_RNG;
#endif

#if defined(MOCK_NRF_ECB)
  NRF_ECB_Type m_NRF_ECB = {0};
  NRF_ECB_Type * NRF_ECB = &m_NRF_ECB;
#endif

#if defined(MOCK_NRF_CCM)
  NRF_CCM_Type m_NRF_CCM = {0};
  NRF_CCM_Type * NRF_CCM = &m_NRF_CCM;
#endif

#if defined(MOCK_NRF_AAR)
  NRF_AAR_Type m_NRF_AAR = {0};
  NRF_AAR_Type * NRF_AAR = &m_NRF_AAR;
#endif

#if defined(MOCK_NRF_WDT)
  NRF_WDT_Type m_NRF_WDT = {0};
  NRF_WDT_Type * NRF_WDT = &m_NRF_WDT;
#endif

#if defined(MOCK_NRF_RTC1)
  NRF_RTC_Type m_NRF_RTC1 = {0};
  NRF_RTC_Type * NRF_RTC1 = &m_NRF_RTC1;
#endif

#if defined(MOCK_NRF_QDEC)
  NRF_QDEC_Type m_NRF_QDEC = {0};
  NRF_QDEC_Type * NRF_QDEC = &m_NRF_QDEC;
#endif

#if defined(MOCK_NRF_COMP)
  NRF_COMP_Type m_NRF_COMP = {0};
  NRF_COMP_Type * NRF_COMP = &m_NRF_COMP;
#endif

#if defined(MOCK_NRF_LPCOMP)
  NRF_LPCOMP_Type m_NRF_LPCOMP = {0};
  NRF_LPCOMP_Type * NRF_LPCOMP = &m_NRF_LPCOMP;
#endif

#if defined(MOCK_NRF_SWI0)
  NRF_SWI_Type m_NRF_SWI0 = {0};
  NRF_SWI_Type * NRF_SWI0 = &m_NRF_SWI0;
#endif

#if defined(MOCK_NRF_EGU0)
  NRF_EGU_Type m_NRF_EGU0 = {0};
  NRF_EGU_Type * NRF_EGU0 = &m_NRF_EGU0;
#endif

#if defined(MOCK_NRF_SWI1)
  NRF_SWI_Type m_NRF_SWI1 = {0};
  NRF_SWI_Type * NRF_SWI1 = &m_NRF_SWI1;
#endif

#if defined(MOCK_NRF_EGU1)
  NRF_EGU_Type m_NRF_EGU1 = {0};
  NRF_EGU_Type * NRF_EGU1 = &m_NRF_EGU1;
#endif

#if defined(MOCK_NRF_SWI2)
  NRF_SWI_Type m_NRF_SWI2 = {0};
  NRF_SWI_Type * NRF_SWI2 = &m_NRF_SWI2;
#endif

#if defined(MOCK_NRF_EGU2)
  NRF_EGU_Type m_NRF_EGU2 = {0};
  NRF_EGU_Type * NRF_EGU2 = &m_NRF_EGU2;
#endif

#if defined(MOCK_NRF_SWI3)
  NRF_SWI_Type m_NRF_SWI3 = {0};
  NRF_SWI_Type * NRF_SWI3 = &m_NRF_SWI3;
#endif

#if defined(MOCK_NRF_EGU3)
  NRF_EGU_Type m_NRF_EGU3 = {0};
  NRF_EGU_Type * NRF_EGU3 = &m_NRF_EGU3;
#endif

#if defined(MOCK_NRF_SWI4)
  NRF_SWI_Type m_NRF_SWI4 = {0};
  NRF_SWI_Type * NRF_SWI4 = &m_NRF_SWI4;
#endif

#if defined(MOCK_NRF_EGU4)
  NRF_EGU_Type m_NRF_EGU4 = {0};
  NRF_EGU_Type * NRF_EGU4 = &m_NRF_EGU4;
#endif

#if defined(MOCK_NRF_SWI5)
  NRF_SWI_Type m_NRF_SWI5 = {0};
  NRF_SWI_Type * NRF_SWI5 = &m_NRF_SWI5;
#endif

#if defined(MOCK_NRF_EGU5)
  NRF_EGU_Type m_NRF_EGU5 = {0};
  NRF_EGU_Type * NRF_EGU5 = &m_NRF_EGU5;
#endif

#if defined(MOCK_NRF_TIMER3)
  NRF_TIMER_Type m_NRF_TIMER3 = {0};
  NRF_TIMER_Type * NRF_TIMER3 = &m_NRF_TIMER3;
#endif

#if defined(MOCK_NRF_TIMER4)
  NRF_TIMER_Type m_NRF_TIMER4 = {0};
  NRF_TIMER_Type * NRF_TIMER4 = &m_NRF_TIMER4;
#endif

#if defined(MOCK_NRF_PWM0)
  NRF_PWM_Type m_NRF_PWM0 = {0};
  NRF_PWM_Type * NRF_PWM0 = &m_NRF_PWM0;
#endif

#if defined(MOCK_NRF_PDM)
  NRF_PDM_Type m_NRF_PDM = {0};
  NRF_PDM_Type * NRF_PDM = &m_NRF_PDM;
#endif

#if defined(MOCK_NRF_NVMC)
  NRF_NVMC_Type m_NRF_NVMC = {0};
  NRF_NVMC_Type * NRF_NVMC = &m_NRF_NVMC;
#endif

#if defined(MOCK_NRF_PPI)
  NRF_PPI_Type m_NRF_PPI = {0};
  NRF_PPI_Type * NRF_PPI = &m_NRF_PPI;
#endif

#if defined(MOCK_NRF_MWU)
  NRF_MWU_Type m_NRF_MWU = {0};
  NRF_MWU_Type * NRF_MWU = &m_NRF_MWU;
#endif

#if defined(MOCK_NRF_PWM1)
  NRF_PWM_Type m_NRF_PWM1 = {0};
  NRF_PWM_Type * NRF_PWM1 = &m_NRF_PWM1;
#endif

#if defined(MOCK_NRF_PWM2)
  NRF_PWM_Type m_NRF_PWM2 = {0};
  NRF_PWM_Type * NRF_PWM2 = &m_NRF_PWM2;
#endif

#if defined(MOCK_NRF_SPIM2)
  NRF_SPIM_Type m_NRF_SPIM2 = {0};
  NRF_SPIM_Type * NRF_SPIM2 = &m_NRF_SPIM2;
#endif

#if defined(MOCK_NRF_SPIS2)
  NRF_SPIS_Type m_NRF_SPIS2 = {0};
  NRF_SPIS_Type * NRF_SPIS2 = &m_NRF_SPIS2;
#endif

#if defined(MOCK_NRF_SPI2)
  NRF_SPI_Type m_NRF_SPI2 = {0};
  NRF_SPI_Type * NRF_SPI2 = &m_NRF_SPI2;
#endif

#if defined(MOCK_NRF_RTC2)
  NRF_RTC_Type m_NRF_RTC2 = {0};
  NRF_RTC_Type * NRF_RTC2 = &m_NRF_RTC2;
#endif

#if defined(MOCK_NRF_I2S)
  NRF_I2S_Type m_NRF_I2S = {0};
  NRF_I2S_Type * NRF_I2S = &m_NRF_I2S;
#endif

#if defined(MOCK_NRF_FPU)
  NRF_FPU_Type m_NRF_FPU = {0};
  NRF_FPU_Type * NRF_FPU = &m_NRF_FPU;
#endif

#if defined(MOCK_NRF_P0)
  NRF_GPIO_Type m_NRF_P0 = {0};
  NRF_GPIO_Type * NRF_P0 = &m_NRF_P0;
#endif

#if defined(MOCK_NRF_ACL)
  /* soc_nrf52 writes to out of bounds memory for ACL & BPROT. Make sure to allocate enough memory */
  typedef struct {
    __IM  NRF_ACL_Type data;
    __IM  uint32_t  PADDING[512];
  } NRF_ACL_Alloc_Type;

  NRF_ACL_Alloc_Type m_NRF_ACL = {0};
  NRF_ACL_Type * NRF_ACL = (NRF_ACL_Type*) &m_NRF_ACL;
#endif

#if defined(MOCK_NRF_USBD)
  NRF_USBD_Type m_NRF_USBD = {0};
  NRF_USBD_Type * NRF_USBD = &m_NRF_USBD;
#endif

#if defined(MOCK_NRF_QSPI)
  NRF_QSPI_Type m_NRF_QSPI = {0};
  NRF_QSPI_Type * NRF_QSPI = &m_NRF_QSPI;
#endif

#if defined(MOCK_NRF_PWM3)
  NRF_PWM_Type m_NRF_PWM3 = {0};
  NRF_PWM_Type * NRF_PWM3 = &m_NRF_PWM3;
#endif

#if defined(MOCK_NRF_SPIM3)
  NRF_SPIM_Type m_NRF_SPIM3 = {0};
  NRF_SPIM_Type * NRF_SPIM3 = &m_NRF_SPIM3;
#endif

#if defined(MOCK_NRF_P1)
  NRF_GPIO_Type m_NRF_P1 = {0};
  NRF_GPIO_Type * NRF_P1 = &m_NRF_P1;
#endif

#if defined(MOCK_NRF_CRYPTOCELL)
  NRF_CRYPTOCELL_Type m_NRF_CRYPTOCELL = {0};
  NRF_CRYPTOCELL_Type * NRF_CRYPTOCELL = &m_NRF_CRYPTOCELL;
#endif

#if defined(MOCK_NRF_DPPIC_NS)
  NRF_DPPIC_Type m_NRF_DPPIC_NS = {0};
  NRF_DPPIC_Type * NRF_DPPIC_NS = &m_NRF_DPPIC_NS;
#endif

SCB_Type       m_SCB       = {0};
NVIC_Type      m_NVIC      = {0};

SCB_Type       * SCB       = &m_SCB;
NVIC_Type      * NVIC      = &m_NVIC;
#endif
