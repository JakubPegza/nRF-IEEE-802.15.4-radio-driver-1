#if defined(NRF5340_XXAA_NETWORK)

/*
 * The MDK provides macros for accessing the peripheral register structures
 * by using their secure and non-secure address mappings (with the names
 * containing the suffix _S or _NS, respectively). Because the nrfx drivers
 * use the macros without any suffixes, you must translate the names.
 * The following section provides configuration for the name translation.
 */
#define NRF_AAR        NRF_AAR_NS
#define NRF_ACL        NRF_ACL_NS
#define NRF_CCM        NRF_CCM_NS
#define NRF_CLOCK      NRF_CLOCK_NS
#define NRF_CTI        NRF_CTI_NS
#define NRF_CTRLAP     NRF_CTRLAP_NS
#define NRF_DCNF       NRF_DCNF_NS
#define NRF_DPPIC      NRF_DPPIC_NS
#define NRF_ECB        NRF_ECB_NS
#define NRF_EGU0       NRF_EGU0_NS
#define NRF_FICR       NRF_FICR_NS
#define NRF_GPIOTE     NRF_GPIOTE_NS
#define NRF_IPC        NRF_IPC_NS
#define NRF_NVMC       NRF_NVMC_NS
#define NRF_P0         NRF_P0_NS
#define NRF_P1         NRF_P1_NS
#define NRF_POWER      NRF_POWER_NS
#define NRF_RADIO      NRF_RADIO_NS
#define NRF_RESET      NRF_RESET_NS
#define NRF_RNG        NRF_RNG_NS
#define NRF_RTC0       NRF_RTC0_NS
#define NRF_RTC1       NRF_RTC1_NS
#define NRF_SPIM0      NRF_SPIM0_NS
#define NRF_SPIS0      NRF_SPIS0_NS
#define NRF_SWI0       NRF_SWI0_NS
#define NRF_SWI1       NRF_SWI1_NS
#define NRF_SWI2       NRF_SWI2_NS
#define NRF_SWI3       NRF_SWI3_NS
#define NRF_TEMP       NRF_TEMP_NS
#define NRF_TIMER0     NRF_TIMER0_NS
#define NRF_TIMER1     NRF_TIMER1_NS
#define NRF_TIMER2     NRF_TIMER2_NS
#define NRF_TWIM0      NRF_TWIM0_NS
#define NRF_TWIS0      NRF_TWIS0_NS
#define NRF_UARTE0     NRF_UARTE0_NS
#define NRF_UICR       NRF_UICR_NS
#define NRF_VMC        NRF_VMC_NS
#define NRF_VREQCTRL   NRF_VREQCTRL_NS
#define NRF_WDT        NRF_WDT_NS

#endif // NRF5340_XXAA_NETWORK
