#include "unity.h"

#include "nrf_802154_trx.h"

#if defined(NRF52840_XXAA) || \
    defined(NRF52833_XXAA) || \
    defined(NRF52820_XXAA) || \
    defined(NRF52811_XXAA)
#include "nrf_802154_trx_ppi.h"

#elif defined(NRF5340_XXAA)
#include "nrf_802154_trx_dppi.h"

#endif

// HW mocks
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

void setUp(void) {}    // every test file requires this function;
                       // setUp() is called by the generated runner before each test case function

void tearDown(void) {} // every test file requires this function;
                       // tearDown() is called by the generated runner after each test case function

// a test case function
void test_nrf_802154_trx_abort_shall_do_nothing(void)
{
    nrf_802154_trx_abort();
}

