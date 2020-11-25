#include "unity.h"

#include "nrf_802154_rssi.h"

#include <math.h>
#include "mock_nrf_802154_temperature.h"

/** @brief Maximal difference between refrence and calculated corected RSSI value. */
#define CORRECTED_RSSI_MAX_DELTA 1U
#define ARRAY_SIZE(x)            (sizeof(x) / sizeof(x[0]))

void setUp(void)
{
}

void tearDown(void)
{
}

#if defined(NRF52_SERIES)

// Intentionally empty. Test not implemented.

#elif defined(NRF5340_XXAA)

uint8_t corrected_rssi_reference_value_get(uint8_t rssi_sample, int8_t temp)
{
    float reference_rssi_value;

    reference_rssi_value = (float)(1.56f * rssi_sample)
                           + (float)(4.9e-5 * pow(rssi_sample, 3))
                           - (float)(9.9e-3 * pow(rssi_sample, 2))
                           - (0.05f * ((float)temp)) - 7.2f;

    return (uint8_t)round(reference_rssi_value);
}

void test_nrf_802154_rssi_sample_temp_corr_value_get_returns_correct_value(void)
{
    const uint8_t rssi_samples[] = {0U, 40U, 80U, 120U, 127U};
    const int8_t  temp_values[]  = {-40, -20, 0, 20, 40, 60, 80, 105};

    uint8_t reference_rssi_value;
    int8_t  rssi_temp_corr_value;
    char    message_buffer[128];

    for (uint8_t i = 0U; i < ARRAY_SIZE(rssi_samples); i++)
    {
        for (uint8_t j = 0U; j < ARRAY_SIZE(temp_values); j++)
        {
            reference_rssi_value = corrected_rssi_reference_value_get(rssi_samples[i],
                                                                      temp_values[j]);
            sprintf(message_buffer, "RSSI sample = %u, temp = %d", rssi_samples[i], temp_values[j]);

            nrf_802154_temperature_get_ExpectAndReturn(temp_values[j]);

            rssi_temp_corr_value = nrf_802154_rssi_sample_temp_corr_value_get(rssi_samples[i]);

            TEST_ASSERT_INT8_WITHIN_MESSAGE(CORRECTED_RSSI_MAX_DELTA,
                                            (int8_t)reference_rssi_value - rssi_samples[i],
                                            rssi_temp_corr_value,
                                            message_buffer);
        }
    }
}

#endif
