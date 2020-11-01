#if defined(NRF5340_XXAA)

#include "unity.h"

#include "nrf_802154_trx_ppi_api.h"
TEST_FILE("nrf_802154_trx_dppi.c")

#include "nrf_802154_peripherals.h"
#include "hal/nrf_egu.h"
#include "hal/nrf_radio.h"
#include "hal/nrf_timer.h"

// HW mocks
#include "nrf_mock.h"

// SL mocks
#include "mock_nrf_fem_protocol_api.h"

void setUp(void)
{
    nrf_mock_reset();
}

void tearDown(void) {}

// Tests for RADIO ramp up
void test_nrf_802154_trx_ppi_for_ramp_up_set_Shall_configure_dppis_when_timer_is_disabled(void)
{
    // Trigger
    nrf_802154_trx_ppi_for_ramp_up_set(NRF_RADIO_TASK_RXEN, false);

    // Verify
    uint32_t expected_ppi_channel;

    expected_ppi_channel = 0x80000000 | NRF_802154_DPPI_EGU_TO_RADIO_RAMP_UP;
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_802154_EGU_INSTANCE->PUBLISH_TRIGGERED[15]);
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_RADIO->SUBSCRIBE_RXEN);
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_DPPIC->SUBSCRIBE_CHG[0].DIS);

    expected_ppi_channel = 0x80000000 | NRF_802154_DPPI_RADIO_DISABLED_TO_EGU;
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_RADIO->PUBLISH_DISABLED);
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_802154_EGU_INSTANCE->SUBSCRIBE_TRIGGER[15]);

    uint32_t expected_group_mask = (1UL << NRF_802154_DPPI_EGU_TO_RADIO_RAMP_UP);
    TEST_ASSERT_EQUAL(expected_group_mask, NRF_DPPIC->CHG[0]);

    uint32_t expected_chen_mask = (1UL << NRF_802154_DPPI_RADIO_DISABLED_TO_EGU) |
                                  (1UL << NRF_802154_DPPI_EGU_TO_RADIO_RAMP_UP);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_DPPIC->CHENSET);

    TEST_ASSERT_EQUAL(0, NRF_802154_TIMER_INSTANCE->SUBSCRIBE_START);
}

void test_nrf_802154_trx_ppi_for_ramp_up_set_Shall_configure_ppis_when_timer_is_enabled(void)
{
    // Trigger
    nrf_802154_trx_ppi_for_ramp_up_set(NRF_RADIO_TASK_TXEN, true);

    // Verify
    uint32_t expected_ppi_channel;

    expected_ppi_channel = 0x80000000 | NRF_802154_DPPI_EGU_TO_RADIO_RAMP_UP;
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_802154_EGU_INSTANCE->PUBLISH_TRIGGERED[15]);
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_RADIO->SUBSCRIBE_TXEN);
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_DPPIC->SUBSCRIBE_CHG[0].DIS);

    expected_ppi_channel = 0x80000000 | NRF_802154_DPPI_RADIO_DISABLED_TO_EGU;
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_RADIO->PUBLISH_DISABLED);
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_802154_EGU_INSTANCE->SUBSCRIBE_TRIGGER[15]);
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_802154_TIMER_INSTANCE->SUBSCRIBE_START);

    uint32_t expected_group_mask = (1UL << NRF_802154_DPPI_EGU_TO_RADIO_RAMP_UP);
    TEST_ASSERT_EQUAL(expected_group_mask, NRF_DPPIC->CHG[0]);

    uint32_t expected_chen_mask = (1UL << NRF_802154_DPPI_RADIO_DISABLED_TO_EGU) |
                                  (1UL << NRF_802154_DPPI_EGU_TO_RADIO_RAMP_UP);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_DPPIC->CHENSET);
}

void test_nrf_802154_trx_ppi_for_ramp_up_clear_Shall_deconfigure_ppis_when_timer_is_disabled(void)
{
    // Setup
    nrf_802154_trx_ppi_for_ramp_up_set(NRF_RADIO_TASK_RXEN, false);

    // Trigger
    nrf_802154_trx_ppi_for_ramp_up_clear(NRF_RADIO_TASK_RXEN, false);

    // Verify
    TEST_ASSERT_EQUAL(0, NRF_802154_EGU_INSTANCE->PUBLISH_TRIGGERED[15]);
    TEST_ASSERT_EQUAL(0, NRF_RADIO->SUBSCRIBE_RXEN);
    TEST_ASSERT_EQUAL(0, NRF_DPPIC->SUBSCRIBE_CHG[0].DIS);

    TEST_ASSERT_EQUAL(0, NRF_RADIO->PUBLISH_DISABLED);
    TEST_ASSERT_EQUAL(0, NRF_802154_EGU_INSTANCE->SUBSCRIBE_TRIGGER[15]);

    TEST_ASSERT_EQUAL(0, NRF_DPPIC->CHG[0]);

    uint32_t expected_chen_mask = (1UL << NRF_802154_DPPI_RADIO_DISABLED_TO_EGU) |
                                  (1UL << NRF_802154_DPPI_EGU_TO_RADIO_RAMP_UP);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_DPPIC->CHENCLR);

    TEST_ASSERT_EQUAL(0, NRF_802154_TIMER_INSTANCE->SUBSCRIBE_START);
}

void test_nrf_802154_trx_ppi_for_ramp_up_clear_Shall_deconfigure_ppis_when_timer_is_enabled(void)
{
    // Setup
    nrf_802154_trx_ppi_for_ramp_up_set(NRF_RADIO_TASK_TXEN, true);

    // Trigger
    nrf_802154_trx_ppi_for_ramp_up_clear(NRF_RADIO_TASK_TXEN, true);

    // Verify
    TEST_ASSERT_EQUAL(0, NRF_802154_EGU_INSTANCE->PUBLISH_TRIGGERED[15]);
    TEST_ASSERT_EQUAL(0, NRF_RADIO->SUBSCRIBE_TXEN);
    TEST_ASSERT_EQUAL(0, NRF_DPPIC->SUBSCRIBE_CHG[0].DIS);

    TEST_ASSERT_EQUAL(0, NRF_RADIO->PUBLISH_DISABLED);
    TEST_ASSERT_EQUAL(0, NRF_802154_EGU_INSTANCE->SUBSCRIBE_TRIGGER[15]);
    TEST_ASSERT_EQUAL(0, NRF_802154_TIMER_INSTANCE->SUBSCRIBE_START);

    TEST_ASSERT_EQUAL(0, NRF_DPPIC->CHG[0]);

    uint32_t expected_chen_mask = (1UL << NRF_802154_DPPI_RADIO_DISABLED_TO_EGU) |
                                  (1UL << NRF_802154_DPPI_EGU_TO_RADIO_RAMP_UP);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_DPPIC->CHENCLR);
}

void test_nrf_802154_trx_ppi_for_ramp_up_was_triggered_Shall_return_true_if_radio_is_ramping_down(void)
{
    uint32_t ramp_down_states[] = {
        RADIO_STATE_STATE_RxDisable,
        RADIO_STATE_STATE_TxDisable,
    };

    for (size_t i = 0; i < sizeof(ramp_down_states) / sizeof(ramp_down_states[0]); i++)
    {
        // Setup
        uint32_t * p_radio_state_reg = (uint32_t *)&NRF_RADIO->STATE; // Make this register RW to mock it
        *p_radio_state_reg = ramp_down_states[i];

        // Trigger
        bool result = nrf_802154_trx_ppi_for_ramp_up_was_triggered();

        // Verify
        TEST_ASSERT_TRUE(result);
    }
}

void test_nrf_802154_trx_ppi_for_ramp_up_was_triggered_Shall_return_true_if_radio_is_ramping_up(void)
{
    uint32_t ramp_up_states[] = {
        RADIO_STATE_STATE_RxRu,
        RADIO_STATE_STATE_TxRu,
    };

    for (size_t i = 0; i < sizeof(ramp_up_states) / sizeof(ramp_up_states[0]); i++)
    {
        // Setup
        uint32_t * p_radio_state_reg = (uint32_t *)&NRF_RADIO->STATE; // Make this register RW to mock it
        *p_radio_state_reg = ramp_up_states[i];

        // Trigger
        bool result = nrf_802154_trx_ppi_for_ramp_up_was_triggered();

        // Verify
        TEST_ASSERT_TRUE(result);
    }
}

void test_nrf_802154_trx_ppi_for_ramp_up_was_triggered_Shall_return_true_if_radio_is_active(void)
{
    uint32_t active_states[] = {
        RADIO_STATE_STATE_Rx,
        RADIO_STATE_STATE_Tx,
        RADIO_STATE_STATE_RxIdle,
        RADIO_STATE_STATE_TxIdle,
    };

    for (size_t i = 0; i < sizeof(active_states) / sizeof(active_states[0]); i++)
    {
        // Setup
        uint32_t * p_radio_state_reg = (uint32_t *)&NRF_RADIO->STATE; // Make this register RW to mock it
        *p_radio_state_reg = active_states[i];

        // Trigger
        bool result = nrf_802154_trx_ppi_for_ramp_up_was_triggered();

        // Verify
        TEST_ASSERT_TRUE(result);
    }
}

void test_nrf_802154_trx_ppi_for_ramp_up_was_triggered_Shall_return_true_if_egu_triggered(void)
{
    // Setup
    uint32_t * p_radio_state_reg = (uint32_t *)&NRF_RADIO->STATE; // Make this register RW to mock it
    *p_radio_state_reg = RADIO_STATE_STATE_Disabled;

    NRF_802154_SWI_EGU_INSTANCE->EVENTS_TRIGGERED[15] = 1;
    
    // Trigger
    bool result = nrf_802154_trx_ppi_for_ramp_up_was_triggered();

    // Verify
    TEST_ASSERT_TRUE(result);
}

void test_nrf_802154_trx_ppi_for_ramp_up_was_triggered_Shall_return_false_if_radio_is_disabled_and_egu_not_triggered(void)
{
    // Setup
    uint32_t * p_radio_state_reg = (uint32_t *)&NRF_RADIO->STATE; // Make this register RW to mock it
    *p_radio_state_reg = RADIO_STATE_STATE_Disabled;

    NRF_802154_SWI_EGU_INSTANCE->EVENTS_TRIGGERED[15] = 0;
    
    // Trigger
    bool result = nrf_802154_trx_ppi_for_ramp_up_was_triggered();

    // Verify
    TEST_ASSERT_FALSE(result);
}

void test_nrf_802154_trx_ppi_for_ramp_up_was_triggered_Shall_return_false_if_egu_triggered_before_ramp_up_setup(void)
{
    // Setup
    uint32_t * p_radio_state_reg = (uint32_t *)&NRF_RADIO->STATE; // Make this register RW to mock it
    *p_radio_state_reg = RADIO_STATE_STATE_Disabled;

    NRF_802154_SWI_EGU_INSTANCE->EVENTS_TRIGGERED[15] = 1;

    nrf_802154_trx_ppi_for_ramp_up_set(NRF_RADIO_TASK_RXEN, false);
    
    // Trigger
    bool result = nrf_802154_trx_ppi_for_ramp_up_was_triggered();

    // Verify
    TEST_ASSERT_FALSE(result);
}

void test_nrf_802154_trx_ppi_for_ramp_up_was_triggered_Shall_return_true_if_egu_triggered_after_ramp_up_setup(void)
{
    // Setup
    uint32_t * p_radio_state_reg = (uint32_t *)&NRF_RADIO->STATE; // Make this register RW to mock it
    *p_radio_state_reg = RADIO_STATE_STATE_Disabled;

    nrf_802154_trx_ppi_for_ramp_up_set(NRF_RADIO_TASK_RXEN, false);

    NRF_802154_SWI_EGU_INSTANCE->EVENTS_TRIGGERED[15] = 1;
    
    // Trigger
    bool result = nrf_802154_trx_ppi_for_ramp_up_was_triggered();

    // Verify
    TEST_ASSERT_TRUE(result);
}

// Tests for ACK TX
void test_nrf_802154_trx_ppi_for_ack_tx_set_Shall_configure_ppis(void)
{
    // Trigger
    nrf_802154_trx_ppi_for_ack_tx_set();

    // Verify
    uint32_t expected_ppi_channel;

    expected_ppi_channel = 0x80000000 | NRF_802154_DPPI_TIMER_COMPARE_TO_RADIO_TXEN;
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_802154_TIMER_INSTANCE->PUBLISH_COMPARE[1]);
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_RADIO->SUBSCRIBE_TXEN);

    uint32_t expected_chen_mask = (1UL << NRF_802154_DPPI_TIMER_COMPARE_TO_RADIO_TXEN);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_DPPIC->CHENSET);
}

void test_nrf_802154_trx_ppi_for_ack_tx_clear_Shall_deconfigure_ppis(void)
{
    // Trigger
    nrf_802154_trx_ppi_for_ack_tx_set();

    // Trigger
    nrf_802154_trx_ppi_for_ack_tx_clear();

    // Verify
    TEST_ASSERT_EQUAL(0, NRF_802154_TIMER_INSTANCE->PUBLISH_COMPARE[1]);
    TEST_ASSERT_EQUAL(0, NRF_RADIO->SUBSCRIBE_TXEN);

    uint32_t expected_chen_mask = (1UL << NRF_802154_DPPI_TIMER_COMPARE_TO_RADIO_TXEN);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_DPPIC->CHENCLR);
}

// Tests for FEM
void test_nrf_802154_trx_ppi_for_fem_set_Shall_configure_ppis(void)
{
    // Trigger
    nrf_802154_trx_ppi_for_fem_set();

    // Verify
    uint32_t expected_ppi_channel;

    expected_ppi_channel = 0x80000000 | NRF_802154_DPPI_RADIO_DISABLED_TO_EGU;
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_802154_TIMER_INSTANCE->SUBSCRIBE_START);
}

void test_nrf_802154_trx_ppi_for_fem_clear_Shall_deconfigure_ppis(void)
{
    // Setup
    nrf_802154_trx_ppi_for_fem_set();

    // Trigger
    nrf_802154_trx_ppi_for_fem_clear();

    // Verify
    TEST_ASSERT_EQUAL(0, NRF_802154_TIMER_INSTANCE->SUBSCRIBE_START);
}

// TODO: Tests for FEM powerdown to be implmeneted when FEM supports nRF53

#if defined(RADIO_INTENSET_SYNC_Msk)
// Tests for RADIO SYNC
void test_nrf_802154_trx_ppi_for_radio_sync_set_Shall_configure_ppis(void)
{
    nrf_egu_task_t task = NRF_EGU_TASK_TRIGGER14;

    // Trigger
    nrf_802154_trx_ppi_for_radio_sync_set(task);

    // Verify
    uint32_t expected_ppi_channel;

    expected_ppi_channel = 0x80000000 | NRF_802154_DPPI_RADIO_SYNC_TO_EGU_SYNC;
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_RADIO->PUBLISH_SYNC);
    TEST_ASSERT_EQUAL(expected_ppi_channel, NRF_802154_EGU_INSTANCE->SUBSCRIBE_TRIGGER[14]);

    uint32_t expected_chen_mask = (1UL << NRF_802154_DPPI_RADIO_SYNC_TO_EGU_SYNC);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_DPPIC->CHENSET);
}

void test_nrf_802154_trx_ppi_for_radio_sync_clear_Shall_deconfigure_ppis(void)
{
    nrf_egu_task_t task = NRF_EGU_TASK_TRIGGER13;

    // Setup
    nrf_802154_trx_ppi_for_radio_sync_set(task);

    // Trigger
    nrf_802154_trx_ppi_for_radio_sync_clear(task);

    // Verify
    TEST_ASSERT_EQUAL(0, NRF_RADIO->PUBLISH_SYNC);
    TEST_ASSERT_EQUAL(0, NRF_802154_EGU_INSTANCE->SUBSCRIBE_TRIGGER[13]);

    uint32_t expected_chen_mask = (1UL << NRF_802154_DPPI_RADIO_SYNC_TO_EGU_SYNC);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_DPPIC->CHENCLR);
}
#endif // defined(RADIO_INTENSET_SYNC_Msk)

#endif // SoCs with DPPI peripheral
