#if defined(NRF52_SERIES)

#include "unity.h"

#include "nrf_802154_trx_ppi_api.h"
TEST_FILE("nrf_802154_trx_ppi.h")

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

void tearDown(void)
{
}

// Tests for RADIO ramp up
void test_nrf_802154_trx_ppi_for_ramp_up_set_Shall_configure_ppis_when_timer_is_disabled(void)
{
    // Trigger
    nrf_802154_trx_ppi_for_ramp_up_set(NRF_RADIO_TASK_RXEN, false);

    // Verify
    uint32_t expected_event_address;
    uint32_t expected_task_address;
    uint32_t expected_fork_address;

    expected_event_address = nrf_egu_event_address_get(NRF_802154_EGU_INSTANCE, NRF_EGU_EVENT_TRIGGERED15);
    expected_task_address = nrf_radio_task_address_get(NRF_RADIO, NRF_RADIO_TASK_RXEN);
    expected_fork_address = nrf_ppi_task_address_get(NRF_PPI, NRF_PPI_TASK_CHG0_DIS);
    TEST_ASSERT_EQUAL(expected_event_address, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].EEP);
    TEST_ASSERT_EQUAL(expected_task_address, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].TEP);
    TEST_ASSERT_EQUAL(expected_fork_address, NRF_PPI->FORK[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].TEP);

    expected_event_address = nrf_radio_event_address_get(NRF_RADIO, NRF_RADIO_EVENT_DISABLED);
    expected_task_address  = nrf_egu_task_address_get(NRF_802154_EGU_INSTANCE, NRF_EGU_TASK_TRIGGER15);
    TEST_ASSERT_EQUAL(expected_event_address, NRF_PPI->CH[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].EEP);
    TEST_ASSERT_EQUAL(expected_task_address, NRF_PPI->CH[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].TEP);

    uint32_t expected_group_mask = (1UL << NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP);
    TEST_ASSERT_EQUAL(expected_group_mask, NRF_PPI->CHG[0]);

    uint32_t expected_chen_mask = (1UL << NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP) |
                                  (1UL << NRF_802154_PPI_RADIO_DISABLED_TO_EGU);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_PPI->CHENSET);

    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_EGU_TO_TIMER_START].TEP);
}

void test_nrf_802154_trx_ppi_for_ramp_up_set_Shall_configure_ppis_when_timer_is_enabled(void)
{
    // Trigger
    nrf_802154_trx_ppi_for_ramp_up_set(NRF_RADIO_TASK_TXEN, true);

    // Verify
    uint32_t expected_event_address;
    uint32_t expected_task_address;
    uint32_t expected_fork_address;

    expected_event_address = nrf_egu_event_address_get(NRF_802154_EGU_INSTANCE, NRF_EGU_EVENT_TRIGGERED15);
    expected_task_address = nrf_radio_task_address_get(NRF_RADIO, NRF_RADIO_TASK_TXEN);
    expected_fork_address = nrf_ppi_task_address_get(NRF_PPI, NRF_PPI_TASK_CHG0_DIS);
    TEST_ASSERT_EQUAL(expected_event_address, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].EEP);
    TEST_ASSERT_EQUAL(expected_task_address, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].TEP);
    TEST_ASSERT_EQUAL(expected_fork_address, NRF_PPI->FORK[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].TEP);

    expected_event_address = nrf_radio_event_address_get(NRF_RADIO, NRF_RADIO_EVENT_DISABLED);
    expected_task_address  = nrf_egu_task_address_get(NRF_802154_EGU_INSTANCE, NRF_EGU_TASK_TRIGGER15);
    TEST_ASSERT_EQUAL(expected_event_address, NRF_PPI->CH[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].EEP);
    TEST_ASSERT_EQUAL(expected_task_address, NRF_PPI->CH[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].TEP);

    expected_event_address = nrf_egu_event_address_get(NRF_802154_EGU_INSTANCE, NRF_EGU_EVENT_TRIGGERED15);
    expected_task_address  = nrf_timer_task_address_get(NRF_802154_TIMER_INSTANCE, NRF_TIMER_TASK_START);
    TEST_ASSERT_EQUAL(expected_event_address, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].EEP);
    TEST_ASSERT_EQUAL(expected_task_address, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_EGU_TO_TIMER_START].TEP);

    uint32_t expected_group_mask = (1UL << NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP);
    TEST_ASSERT_EQUAL(expected_group_mask, NRF_PPI->CHG[0]);

    uint32_t expected_chen_mask = (1UL << NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP) |
                                  (1UL << NRF_802154_PPI_RADIO_DISABLED_TO_EGU) |
                                  (1UL << NRF_802154_PPI_EGU_TO_TIMER_START);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_PPI->CHENSET);
}

void test_nrf_802154_trx_ppi_for_ramp_up_clear_Shall_deconfigure_ppis_when_timer_is_disabled(void)
{
    // Setup
    nrf_802154_trx_ppi_for_ramp_up_set(NRF_RADIO_TASK_RXEN, false);

    // Trigger
    nrf_802154_trx_ppi_for_ramp_up_clear(NRF_RADIO_TASK_RXEN, false);

    // Verify
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].TEP);

    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].TEP);

    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_EGU_TO_TIMER_START].TEP);

    TEST_ASSERT_EQUAL(0, NRF_PPI->CHG[0]);

    uint32_t expected_chdis_mask = (1UL << NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP) |
                                   (1UL << NRF_802154_PPI_RADIO_DISABLED_TO_EGU);
    TEST_ASSERT_EQUAL(expected_chdis_mask, NRF_PPI->CHENCLR);
}

void test_nrf_802154_trx_ppi_for_ramp_up_clear_Shall_deconfigure_ppis_when_timer_is_enabled(void)
{
    // Setup
    nrf_802154_trx_ppi_for_ramp_up_set(NRF_RADIO_TASK_TXEN, true);

    // Trigger
    nrf_802154_trx_ppi_for_ramp_up_clear(NRF_RADIO_TASK_TXEN, true);

    // Verify
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP].TEP);

    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_RADIO_DISABLED_TO_EGU].TEP);

    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_EGU_TO_TIMER_START].TEP);

    TEST_ASSERT_EQUAL(0, NRF_PPI->CHG[0]);

    uint32_t expected_chdis_mask = (1UL << NRF_802154_PPI_EGU_TO_RADIO_RAMP_UP) |
                                   (1UL << NRF_802154_PPI_RADIO_DISABLED_TO_EGU) |
                                   (1UL << NRF_802154_PPI_EGU_TO_TIMER_START);
    TEST_ASSERT_EQUAL(expected_chdis_mask, NRF_PPI->CHENCLR);
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

    NRF_802154_EGU_INSTANCE->EVENTS_TRIGGERED[15] = 1;
    
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

    NRF_802154_EGU_INSTANCE->EVENTS_TRIGGERED[15] = 0;
    
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

    NRF_802154_EGU_INSTANCE->EVENTS_TRIGGERED[15] = 1;

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

    NRF_802154_EGU_INSTANCE->EVENTS_TRIGGERED[15] = 1;
    
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
    uint32_t expected_event_address;
    uint32_t expected_task_address;

    expected_event_address = nrf_timer_event_address_get(NRF_802154_TIMER_INSTANCE, NRF_TIMER_EVENT_COMPARE1);
    expected_task_address = nrf_radio_task_address_get(NRF_RADIO, NRF_RADIO_TASK_TXEN);
    TEST_ASSERT_EQUAL(expected_event_address, NRF_PPI->CH[NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN].EEP);
    TEST_ASSERT_EQUAL(expected_task_address, NRF_PPI->CH[NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN].TEP);

    uint32_t expected_chen_mask = (1UL << NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_PPI->CHENSET);
}

void test_nrf_802154_trx_ppi_for_ack_tx_clear_Shall_deconfigure_ppis(void)
{
    // Trigger
    nrf_802154_trx_ppi_for_ack_tx_set();

    // Trigger
    nrf_802154_trx_ppi_for_ack_tx_clear();

    // Verify
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN].TEP);

    uint32_t expected_chen_mask = (1UL << NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_PPI->CHENCLR);
}

// Tests for FEM
void test_nrf_802154_trx_ppi_for_fem_set_Shall_configure_ppis(void)
{
    // Trigger
    nrf_802154_trx_ppi_for_fem_set();

    // Verify
    uint32_t expected_event_address;
    uint32_t expected_task_address;

    expected_event_address = nrf_egu_event_address_get(NRF_802154_EGU_INSTANCE, NRF_EGU_EVENT_TRIGGERED15);
    expected_task_address = nrf_timer_task_address_get(NRF_802154_TIMER_INSTANCE, NRF_TIMER_TASK_START);
    TEST_ASSERT_EQUAL(expected_event_address, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].EEP);
    TEST_ASSERT_EQUAL(expected_task_address, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN].TEP);

    uint32_t expected_chen_mask = (1UL << NRF_802154_PPI_EGU_TO_TIMER_START);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_PPI->CHENSET);
}

void test_nrf_802154_trx_ppi_for_fem_clear_Shall_deconfigure_ppis(void)
{
    // Setup
    nrf_802154_trx_ppi_for_fem_set();

    // Trigger
    nrf_802154_trx_ppi_for_fem_clear();

    // Verify
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_EGU_TO_TIMER_START].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_TIMER_COMPARE_TO_RADIO_TXEN].TEP);

    uint32_t expected_chen_mask = (1UL << NRF_802154_PPI_EGU_TO_TIMER_START);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_PPI->CHENCLR);
}

// Tests for FEM powerdown
void test_nrf_802154_trx_ppi_for_fem_powerdown_set_Shall_prepare_fem_powerdown(void)
{
    NRF_TIMER_Type * const p_instance = (NRF_TIMER_Type *)0x40120123;
    const uint32_t         cc         = 0x21;

    // Setup
    nrf_fem_prepare_powerdown_ExpectAndReturn(p_instance, cc, NRF_802154_PPI_EGU_TO_TIMER_START, true);

    // Trigger
    bool result = nrf_802154_trx_ppi_for_fem_powerdown_set(p_instance, cc);

    // Verify
    TEST_ASSERT_TRUE(result);
}

void test_nrf_802154_trx_ppi_for_fem_powerdown_set_Shall_return_false_if_powerdown_is_not_needed(void)
{
    NRF_TIMER_Type * const p_instance = (NRF_TIMER_Type *)0x500103ab;
    const uint32_t         cc         = 0x2;

    // Setup
    nrf_fem_prepare_powerdown_ExpectAndReturn(p_instance, cc, NRF_802154_PPI_EGU_TO_TIMER_START, false);

    // Trigger
    bool result = nrf_802154_trx_ppi_for_fem_powerdown_set(p_instance, cc);

    // Verify
    TEST_ASSERT_FALSE(result);
}

void test_nrf_802154_trx_ppi_for_fem_powerdown_clear_Shall_disable_powerdown_ppi(void)
{
    // Trigger
    nrf_802154_trx_ppi_for_fem_powerdown_clear();

    // Verify
    uint32_t expected_chen_mask = (1UL << NRF_802154_PPI_EGU_TO_TIMER_START);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_PPI->CHENCLR);
}

#if defined(RADIO_INTENSET_SYNC_Msk)
// Tests for RADIO SYNC
void test_nrf_802154_trx_ppi_for_radio_sync_set_Shall_configure_ppis(void)
{
    nrf_egu_task_t task = NRF_EGU_TASK_TRIGGER14;

    // Trigger
    nrf_802154_trx_ppi_for_radio_sync_set(task);

    // Verify
    uint32_t expected_event_address;
    uint32_t expected_task_address;

    expected_event_address = nrf_radio_event_address_get(NRF_RADIO, NRF_RADIO_EVENT_SYNC);
    expected_task_address = nrf_egu_task_address_get(NRF_802154_EGU_INSTANCE, task);
    TEST_ASSERT_EQUAL(expected_event_address, NRF_PPI->CH[NRF_802154_PPI_RADIO_SYNC_TO_EGU_SYNC].EEP);
    TEST_ASSERT_EQUAL(expected_task_address, NRF_PPI->CH[NRF_802154_PPI_RADIO_SYNC_TO_EGU_SYNC].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_RADIO_SYNC_TO_EGU_SYNC].TEP);

    uint32_t expected_chen_mask = (1UL << NRF_802154_PPI_RADIO_SYNC_TO_EGU_SYNC);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_PPI->CHENSET);
}

void test_nrf_802154_trx_ppi_for_radio_sync_clear_Shall_deconfigure_ppis(void)
{
    nrf_egu_task_t task = NRF_EGU_TASK_TRIGGER13;

    // Trigger
    nrf_802154_trx_ppi_for_radio_sync_clear(task);

    // Verify
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_RADIO_SYNC_TO_EGU_SYNC].EEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->CH[NRF_802154_PPI_RADIO_SYNC_TO_EGU_SYNC].TEP);
    TEST_ASSERT_EQUAL(0, NRF_PPI->FORK[NRF_802154_PPI_RADIO_SYNC_TO_EGU_SYNC].TEP);

    uint32_t expected_chen_mask = (1UL << NRF_802154_PPI_RADIO_SYNC_TO_EGU_SYNC);
    TEST_ASSERT_EQUAL(expected_chen_mask, NRF_PPI->CHENCLR);
}
#endif // defined(RADIO_INTENSET_SYNC_Msk)

#endif // SoCs with PPI peripheral
