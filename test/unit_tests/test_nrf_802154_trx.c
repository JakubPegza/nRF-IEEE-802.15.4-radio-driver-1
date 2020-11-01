#define TESTING
#include "unity.h"

#include "nrf_802154_trx.h"
#include "nrf_802154_peripherals.h"

#if defined(NRF52840_XXAA) || \
    defined(NRF52833_XXAA) || \
    defined(NRF52820_XXAA) || \
    defined(NRF52811_XXAA)
#define PPI
TEST_FILE("nrf_802154_trx_ppi.c")

#elif defined(NRF5340_XXAA)
#define DPPI
TEST_FILE("nrf_802154_trx_dppi.c")

#else
#error Unknown SoC
#endif

// HW mocks
#include "nrf.h"
#include "nrf_mock.h"

// Driver mocks
#include "mock_nrf_802154_critical_section.h"
#include "mock_nrf_802154_pib.h"
#include "mock_nrf_802154_rssi.h"
#include "mock_nrf_802154_swi.h"

// SL mocks
#include "mock_nrf_802154_irq.h"
#include "mock_nrf_802154_sl_ant_div.h"
#include "mock_nrf_fem_protocol_api.h"

// Callout mocks
#include "mock_trx_callouts.h"

extern void nrf_802154_trx_module_reset(void);
extern void nrf_802154_radio_irq_handler(void);

void setUp(void)
{
    nrf_mock_reset();
    nrf_802154_trx_module_reset();
}

void tearDown(void) {}

void test_nrf_802154_trx_abort_shall_do_nothing(void)
{
    nrf_802154_trx_abort();
}

// State transition mocks
static void mock_trx_disable(bool from_idle)
{
    nrf_802154_irq_clear_pending_Expect(RADIO_IRQn);

#ifdef PPI
    nrf_802154_fal_abort_clear_ExpectAndReturn(NRFX_SUCCESS);
#endif
    nrf_802154_fal_deactivate_now_Expect(NRF_802154_FAL_ALL);

    if (!from_idle)
    {
        nrf_802154_fal_deactivate_now_Expect(NRF_802154_FAL_ALL);

#ifdef PPI
        nrf_fem_prepare_powerdown_ExpectAndReturn(NULL, 0, 0, false);
        nrf_fem_prepare_powerdown_IgnoreArg_p_instance();
        nrf_fem_prepare_powerdown_IgnoreArg_compare_channel();
        nrf_fem_prepare_powerdown_IgnoreArg_ppi_id();
#endif
    }
}

static void mock_and_trigger_trx_enable(void)
{
    nrf_802154_cca_cfg_t cca_cfg = {
        .mode           = 0,
        .ed_threshold   = 0x14,
        .corr_threshold = 0,
        .corr_limit     = 0,
    };

    nrf_802154_pib_cca_cfg_get_Expect(NULL);
    nrf_802154_pib_cca_cfg_get_IgnoreArg_p_cca_cfg();
    nrf_802154_pib_cca_cfg_get_ReturnThruPtr_p_cca_cfg(&cca_cfg);

    nrf_802154_rssi_cca_ed_threshold_corrected_get_ExpectAndReturn(cca_cfg.ed_threshold, 0x14);

    nrf_802154_pib_channel_get_ExpectAndReturn(11);

    nrf_802154_irq_init_Expect(RADIO_IRQn, NRF_802154_IRQ_PRIORITY, NULL);
    nrf_802154_irq_init_IgnoreArg_isr();

    nrf_802154_irq_enable_Expect(RADIO_IRQn);

#ifdef PPI
    nrf_802154_fal_abort_set_ExpectAndReturn(0, 0, NRFX_SUCCESS);
    nrf_802154_fal_abort_set_IgnoreArg_event();
    nrf_802154_fal_abort_set_IgnoreArg_group();
#endif
    nrf_802154_fal_deactivate_now_Expect(NRF_802154_FAL_ALL);

    nrf_802154_trx_enable();
}

static void mock_and_trigger_trx_go_idle(void)
{
    bool result = nrf_802154_trx_go_idle();
    TEST_ASSERT_TRUE(result);
}

static void mock_and_trigger_trx_receive_frame(void)
{
    nrf_802154_pib_tx_power_get_ExpectAndReturn(0);

#ifdef RADIO_INTENSET_SYNC_Msk
    nrf_802154_sl_ant_div_cfg_mode_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_RX, NRF_802154_SL_ANT_DIV_MODE_AUTO);
#endif

    nrf_802154_fal_lna_configuration_set_ExpectAndReturn(NULL, NULL, NRFX_SUCCESS);
    nrf_802154_fal_lna_configuration_set_IgnoreArg_p_activate_event();

    nrf_802154_sl_ant_div_cfg_mode_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_RX, NRF_802154_SL_ANT_DIV_MODE_AUTO);
    nrf_802154_sl_ant_div_rx_started_notify_Expect();

    nrf_802154_trx_receive_frame(16, 0);
}

static void mock_ack_trigger_trx_transmit_ack(void)
{
    const uint8_t buffer[] = {0x61, 0x98, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};

    nrf_802154_fal_pa_configuration_set_ExpectAndReturn(NULL, NULL, NRFX_SUCCESS);
    nrf_802154_fal_pa_configuration_set_IgnoreArg_p_activate_event();

    nrf_802154_sl_ant_div_cfg_mode_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_RX, NRF_802154_SL_ANT_DIV_MODE_AUTO);
    nrf_802154_sl_ant_div_txack_notify_Expect();

    // Mock that radio is already ramping up
    uint32_t * p_radio_state = (uint32_t *)&NRF_RADIO->STATE;
    *p_radio_state = RADIO_STATE_STATE_TxRu;

    bool result = nrf_802154_trx_transmit_ack(buffer, 192);
    TEST_ASSERT_TRUE(result);
}

static void mock_and_trigger_trx_transmit_frame(void)
{
    const uint8_t buffer[] = {0x61, 0x98, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};

    nrf_802154_pib_tx_power_get_ExpectAndReturn(0);

    nrf_802154_fal_lna_configuration_set_ExpectAndReturn(NULL, NULL, NRFX_SUCCESS);
    nrf_802154_fal_lna_configuration_set_IgnoreArg_p_activate_event();
    nrf_802154_fal_lna_configuration_set_IgnoreArg_p_deactivate_event();

    nrf_802154_fal_pa_configuration_set_ExpectAndReturn(NULL, NULL, NRFX_SUCCESS);
    nrf_802154_fal_pa_configuration_set_IgnoreArg_p_activate_event();

    nrf_802154_sl_ant_div_cfg_mode_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_TX, NRF_802154_SL_ANT_DIV_MODE_MANUAL);
    nrf_802154_sl_ant_div_cfg_antenna_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_TX, 0);
    nrf_802154_sl_ant_div_antenna_set_ExpectAndReturn(0, true);

    nrf_802154_trx_transmit_frame(buffer, true, 0);
}

static void mock_and_trigger_trx_receive_ack(void)
{
    nrf_802154_fal_lna_configuration_set_ExpectAndReturn(NULL, NULL, NRFX_SUCCESS);
    nrf_802154_fal_lna_configuration_set_IgnoreArg_p_activate_event();

    nrf_802154_sl_ant_div_cfg_mode_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_TX, NRF_802154_SL_ANT_DIV_MODE_MANUAL);
    nrf_802154_sl_ant_div_cfg_antenna_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_TX, 1);
    nrf_802154_sl_ant_div_antenna_set_ExpectAndReturn(1, true);

    nrf_802154_trx_receive_ack();
}

static void mock_and_trigger_trx_standalone_cca(void)
{
    nrf_802154_fal_lna_configuration_set_ExpectAndReturn(NULL, NULL, NRFX_SUCCESS);
    nrf_802154_fal_lna_configuration_set_IgnoreArg_p_activate_event();

    nrf_802154_sl_ant_div_cfg_mode_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_TX, NRF_802154_SL_ANT_DIV_MODE_MANUAL);
    nrf_802154_sl_ant_div_cfg_antenna_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_TX, 1);
    nrf_802154_sl_ant_div_antenna_set_ExpectAndReturn(1, true);

    nrf_802154_trx_standalone_cca();
}

static void mock_and_trigger_trx_energy_detection(void)
{
    nrf_802154_fal_lna_configuration_set_ExpectAndReturn(NULL, NULL, NRFX_SUCCESS);
    nrf_802154_fal_lna_configuration_set_IgnoreArg_p_activate_event();

    nrf_802154_sl_ant_div_cfg_mode_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_RX, NRF_802154_SL_ANT_DIV_MODE_MANUAL);
    nrf_802154_sl_ant_div_cfg_antenna_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_RX, 0);
    nrf_802154_sl_ant_div_antenna_set_ExpectAndReturn(0, true);

    nrf_802154_trx_energy_detection(4);
}

static void mock_and_trigger_trx_continuous_carrier(void)
{
    nrf_802154_pib_tx_power_get_ExpectAndReturn(0);

    nrf_802154_fal_pa_configuration_set_ExpectAndReturn(NULL, NULL, NRFX_SUCCESS);
    nrf_802154_fal_pa_configuration_set_IgnoreArg_p_activate_event();

    nrf_802154_sl_ant_div_cfg_mode_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_TX, NRF_802154_SL_ANT_DIV_MODE_MANUAL);
    nrf_802154_sl_ant_div_cfg_antenna_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_TX, 0);
    nrf_802154_sl_ant_div_antenna_set_ExpectAndReturn(0, true);

    nrf_802154_trx_continuous_carrier();
}

static void mock_and_trigger_trx_modulated_carrier(void)
{
    const uint8_t buffer[] = "Hello!";

    nrf_802154_pib_tx_power_get_ExpectAndReturn(0);

    nrf_802154_fal_pa_configuration_set_ExpectAndReturn(NULL, NULL, NRFX_SUCCESS);
    nrf_802154_fal_pa_configuration_set_IgnoreArg_p_activate_event();

    nrf_802154_sl_ant_div_cfg_mode_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_TX, NRF_802154_SL_ANT_DIV_MODE_MANUAL);
    nrf_802154_sl_ant_div_cfg_antenna_get_ExpectAndReturn(NRF_802154_SL_ANT_DIV_OP_TX, 0);
    nrf_802154_sl_ant_div_antenna_set_ExpectAndReturn(0, true);

    nrf_802154_trx_modulated_carrier(buffer);
}

static void mock_and_trigger_irq_crcok(void)
{
    NRF_RADIO->EVENTS_CRCOK = 1;

    nrf_802154_critical_section_forcefully_enter_Expect();
    nrf_802154_fal_lna_configuration_clear_ExpectAndReturn(NRFX_SUCCESS);
    nrf_802154_trx_receive_frame_received_Expect();
    nrf_802154_critical_section_exit_Expect();

    nrf_802154_radio_irq_handler();
}

static void mock_and_trigger_irq_phyend(void)
{
    NRF_RADIO->EVENTS_PHYEND = 1;

    nrf_802154_critical_section_forcefully_enter_Expect();
    // Is this order correct?
    nrf_802154_fal_lna_configuration_clear_ExpectAndReturn(NRFX_SUCCESS);
    nrf_802154_fal_pa_configuration_clear_ExpectAndReturn(NRFX_SUCCESS);

    nrf_802154_trx_transmit_frame_transmitted_Expect();

    nrf_802154_critical_section_exit_Expect();

    nrf_802154_radio_irq_handler();
}

// Verify that all PPIs are cleared when entering DISABLED state

static void verify_all_ppis_are_cleared(void)
{
#if defined(PPI)
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].TEP);

    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].TEP);

    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_EGU_TO_TIMER_START].TEP);

    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN].TEP);

    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_RADIO_SYNC_TO_EGU_SYNC].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_RADIO_SYNC_TO_EGU_SYNC].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_RADIO_SYNC_TO_EGU_SYNC].TEP);

    TEST_ASSERT_EQUAL(0, NRF_PPI->CHG[0]);
#elif defined(DPPI)
    TEST_ASSERT_EQUAL(0, NRF_RADIO->PUBLISH_DISABLED);
    TEST_ASSERT_EQUAL(0, NRF_RADIO->PUBLISH_SYNC);
    TEST_ASSERT_EQUAL(0, NRF_RADIO->SUBSCRIBE_TXEN);
    TEST_ASSERT_EQUAL(0, NRF_RADIO->SUBSCRIBE_RXEN);

    for (int i = 0; i < 16; i++)
    {
        TEST_ASSERT_EQUAL(0, NRF_802154_EGU_INSTANCE->PUBLISH_TRIGGERED[i]);
        TEST_ASSERT_EQUAL(0, NRF_802154_EGU_INSTANCE->SUBSCRIBE_TRIGGER[i]);
    }

    TEST_ASSERT_EQUAL(0, NRF_DPPIC->SUBSCRIBE_CHG[0].DIS);
    TEST_ASSERT_EQUAL(0, NRF_DPPIC->CHG[0]);

    TEST_ASSERT_EQUAL(0, NRF_802154_TIMER_INSTANCE->SUBSCRIBE_START);
    TEST_ASSERT_EQUAL(0, NRF_802154_TIMER_INSTANCE->PUBLISH_COMPARE[0]);
    TEST_ASSERT_EQUAL(0, NRF_802154_TIMER_INSTANCE->PUBLISH_COMPARE[1]);
    TEST_ASSERT_EQUAL(0, NRF_802154_TIMER_INSTANCE->PUBLISH_COMPARE[2]);
    TEST_ASSERT_EQUAL(0, NRF_802154_TIMER_INSTANCE->PUBLISH_COMPARE[3]);
#endif

    // It's not possible to veirfy if all previously enabled channels are disabled now with simple
    // memory mock for peripherals. Disabling PPI channel overrides previously disabled channels.
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_disabled_state(void)
{
    // Setup
    // Intentionally empty

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_idle_state(void)
{
    // Setup
    mock_and_trigger_trx_enable();
    mock_trx_disable(true);

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_going_idle_state(void)
{
    // Setup
    mock_and_trigger_trx_enable();
    mock_and_trigger_trx_transmit_frame();
    mock_and_trigger_irq_phyend();
    mock_and_trigger_trx_go_idle();
    mock_trx_disable(false);

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_rxframe_finished_state(void)
{
    // Setup
    mock_and_trigger_trx_enable();
    mock_and_trigger_trx_receive_frame();
    mock_and_trigger_irq_crcok();
    mock_trx_disable(false);

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_finished_state(void)
{
    // Setup
    mock_and_trigger_trx_enable();
    mock_and_trigger_trx_transmit_frame();
    mock_and_trigger_irq_phyend();
    mock_trx_disable(false);

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_rxframe_state(void)
{
    // Setup
    mock_and_trigger_trx_enable();
    mock_and_trigger_trx_receive_frame();
    mock_trx_disable(false);

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_rxack_state(void)
{
    // Setup
    mock_and_trigger_trx_enable();
    mock_and_trigger_trx_transmit_frame();
    mock_and_trigger_irq_phyend();
    mock_and_trigger_trx_receive_ack();
    mock_trx_disable(false);

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_txframe_state(void)
{
    // Setup
    mock_and_trigger_trx_enable();
    mock_and_trigger_trx_transmit_frame();
    mock_trx_disable(false);

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_txack_state(void)
{
    // Setup
    mock_and_trigger_trx_enable();
    mock_and_trigger_trx_receive_frame();
    mock_and_trigger_irq_crcok();
    mock_ack_trigger_trx_transmit_ack();
    mock_trx_disable(false);

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_standalone_cca_state(void)
{
    // Setup
    mock_and_trigger_trx_enable();
    mock_and_trigger_trx_standalone_cca();
    mock_trx_disable(false);

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_continuous_carrier_state(void)
{
    // Setup
    mock_and_trigger_trx_enable();
    mock_and_trigger_trx_continuous_carrier();
    mock_trx_disable(false);

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_modulated_carrier_state(void)
{
    // Setup
    mock_and_trigger_trx_enable();
    mock_and_trigger_trx_modulated_carrier();
    mock_trx_disable(false);

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}

void test_nrf_802154_trx_disable_shall_reset_all_ppis_in_energy_detection_state(void)
{
    // Setup
    mock_and_trigger_trx_enable();
    mock_and_trigger_trx_energy_detection();
    mock_trx_disable(false);

    // Trigger
    nrf_802154_trx_disable();

    // Verify
    verify_all_ppis_are_cleared();
}
