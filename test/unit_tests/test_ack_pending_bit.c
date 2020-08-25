/*
 * Copyright (c) 2020 Nordic Semiconductor ASA. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor ASA.
 * The use, copying, transfer or disclosure of such information is prohibited except by
 * express written agreement with Nordic Semiconductor ASA.
 */

#include "unity.h"

#include "nrf_802154_config.h"

#include "mock_nrf_802154_frame_parser.h"

#ifdef NRF_802154_PENDING_SHORT_ADDRESSES
    #undef NRF_802154_PENDING_SHORT_ADDRESSES
    #define NRF_802154_PENDING_SHORT_ADDRESSES    4
#endif
#ifdef NRF_802154_PENDING_EXTENDED_ADDRESSES
    #undef NRF_802154_PENDING_EXTENDED_ADDRESSES
    #define NRF_802154_PENDING_EXTENDED_ADDRESSES 4
#endif

#include "mac_features/ack_generator/nrf_802154_ack_data.c"

/***********************************************************************************/
/***********************************************************************************/
/***********************************************************************************/

void setUp(void)
{

}

void tearDown(void)
{
    memset(m_pending_bit.extended_addr, 0, sizeof(m_pending_bit.extended_addr));
    memset(m_pending_bit.short_addr, 0xff, sizeof(m_pending_bit.short_addr));
}

/***********************************************************************************/
/****************************** ACK PENDING BIT TESTS ******************************/
/***********************************************************************************/

static uint8_t test_addr_extended_1[EXTENDED_ADDRESS_SIZE] = { 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89 };
static uint8_t test_addr_extended_2[EXTENDED_ADDRESS_SIZE] = { 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a };
static uint8_t test_addr_extended_3[EXTENDED_ADDRESS_SIZE] = { 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab };
static uint8_t test_addr_extended_4[EXTENDED_ADDRESS_SIZE] = { 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab, 0xbc };
static uint8_t test_addr_extended_5[EXTENDED_ADDRESS_SIZE] = { 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab, 0xbc, 0xcd };

static uint8_t test_addr_short_1[SHORT_ADDRESS_SIZE] = { 0x12, 0x23 };
static uint8_t test_addr_short_2[SHORT_ADDRESS_SIZE] = { 0x23, 0x34 };
static uint8_t test_addr_short_3[SHORT_ADDRESS_SIZE] = { 0x34, 0x45 };
static uint8_t test_addr_short_4[SHORT_ADDRESS_SIZE] = { 0x45, 0x56 };
static uint8_t test_addr_short_5[SHORT_ADDRESS_SIZE] = { 0x56, 0x67 };

static uint8_t test_psdu_extended[EXTENDED_ADDRESS_SIZE + SRC_ADDR_OFFSET_EXTENDED_DST] = 
{
    0x00, 0x40, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89 
};

static uint8_t test_psdu_short[SHORT_ADDRESS_SIZE + SRC_ADDR_OFFSET_SHORT_DST] = 
{
    0x00, 0x40, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x23 
};

void test_ShouldAddAddressToTheList(void)
{
     nrf_802154_ack_data_init();

    bool result;

    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);

    result = nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
}

void test_ShouldFailToAddAddressToTheListWhenListIsFull(void)
{
    nrf_802154_ack_data_init();

    bool result;

    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_5, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_FALSE(result);

    result = nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_short_5, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_FALSE(result);
}

void test_ShouldKeepAscendingOrderAfterAddingExtendedAddressToTheList(void)
{
    nrf_802154_ack_data_init();

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_3, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[3], sizeof(test_addr_extended_4));

    nrf_802154_ack_data_reset(true, NRF_802154_ACK_DATA_PENDING_BIT);
}

void test_ShouldKeepAscendingOrderAfterAddingShortAddressToTheList(void)
{
    nrf_802154_ack_data_init();

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_3, m_pending_bit.short_addr[2], sizeof(test_addr_short_3));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[3], sizeof(test_addr_short_4));

    nrf_802154_ack_data_reset(false, NRF_802154_ACK_DATA_PENDING_BIT);
}

void test_ShouldNotAddAddressWhenAddressAlreadyOnTheList(void)
{
    nrf_802154_ack_data_init();

    bool result;

    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_UINT8(1, m_pending_bit.num_of_ext_addr);

    result = nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_UINT8(1, m_pending_bit.num_of_short_addr);
}

void test_ShouldRemoveAddressFromTheList(void)
{
    nrf_802154_ack_data_init();

    bool result;

    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_clear(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT);
    TEST_ASSERT_TRUE(result);

    result = nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_clear(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT);
    TEST_ASSERT_TRUE(result);
}

void test_ShouldFailToRemoveAddressFromTheListWhenListIsEmpty(void)
{
    nrf_802154_ack_data_init();

    bool result;

    result = nrf_802154_ack_data_for_addr_clear(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT);
    TEST_ASSERT_FALSE(result);

    result = nrf_802154_ack_data_for_addr_clear(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT);
    TEST_ASSERT_FALSE(result);
}

void test_ShouldKeepAscendingOrderAfterRemovingAddressFromTheList(void)
{
    nrf_802154_ack_data_init();

    nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_4, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_clear(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT);

    nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_4, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    nrf_802154_ack_data_for_addr_clear(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT);

    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_1, m_pending_bit.extended_addr[0], sizeof(test_addr_extended_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_2, m_pending_bit.extended_addr[1], sizeof(test_addr_extended_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_extended_4, m_pending_bit.extended_addr[2], sizeof(test_addr_extended_4));

    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_1, m_pending_bit.short_addr[0], sizeof(test_addr_short_1));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_2, m_pending_bit.short_addr[1], sizeof(test_addr_short_2));
    TEST_ASSERT_EQUAL_MEMORY(test_addr_short_4, m_pending_bit.short_addr[2], sizeof(test_addr_short_4));
}

void test_ShouldNotRemoveAddressWhenAddressNotOnTheList(void)
{
    nrf_802154_ack_data_init();

    bool result;

    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_2, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_clear(test_addr_extended_3, true, NRF_802154_ACK_DATA_PENDING_BIT);
    TEST_ASSERT_FALSE(result);

    result = nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_set(test_addr_short_2, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);
    result = nrf_802154_ack_data_for_addr_clear(test_addr_short_3, false, NRF_802154_ACK_DATA_PENDING_BIT);
    TEST_ASSERT_FALSE(result);
}

void test_ShouldSetAckPendingBit(void)
{
    nrf_802154_ack_data_init();

    bool result;
    bool src_addr_extended = true;

    ///////////////////////////////////////////////////////////////////////////////////////////////

    nrf_802154_frame_parser_src_addr_get_ExpectAndReturn(test_psdu_extended, &src_addr_extended, test_addr_extended_1);
    nrf_802154_frame_parser_src_addr_get_IgnoreArg_p_src_addr_extended();
    nrf_802154_frame_parser_src_addr_get_ReturnThruPtr_p_src_addr_extended(&src_addr_extended);

    result = nrf_802154_ack_data_pending_bit_should_be_set(test_psdu_extended);
    TEST_ASSERT_FALSE(result);


    result = nrf_802154_ack_data_for_addr_set(test_addr_extended_1, true, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);


    nrf_802154_frame_parser_src_addr_get_ExpectAndReturn(test_psdu_extended, &src_addr_extended, test_addr_extended_1);
    nrf_802154_frame_parser_src_addr_get_IgnoreArg_p_src_addr_extended();
    nrf_802154_frame_parser_src_addr_get_ReturnThruPtr_p_src_addr_extended(&src_addr_extended);

    result = nrf_802154_ack_data_pending_bit_should_be_set(test_psdu_extended);
    TEST_ASSERT_TRUE(result);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    src_addr_extended = false;

    nrf_802154_frame_parser_src_addr_get_ExpectAndReturn(test_psdu_short, &src_addr_extended, test_addr_short_1);
    nrf_802154_frame_parser_src_addr_get_IgnoreArg_p_src_addr_extended();
    nrf_802154_frame_parser_src_addr_get_ReturnThruPtr_p_src_addr_extended(&src_addr_extended);

    result = nrf_802154_ack_data_pending_bit_should_be_set(test_psdu_short);
    TEST_ASSERT_FALSE(result);


    result = nrf_802154_ack_data_for_addr_set(test_addr_short_1, false, NRF_802154_ACK_DATA_PENDING_BIT, NULL, 0);
    TEST_ASSERT_TRUE(result);


    nrf_802154_frame_parser_src_addr_get_ExpectAndReturn(test_psdu_short, &src_addr_extended, test_addr_short_1);
    nrf_802154_frame_parser_src_addr_get_IgnoreArg_p_src_addr_extended();
    nrf_802154_frame_parser_src_addr_get_ReturnThruPtr_p_src_addr_extended(&src_addr_extended);

    result = nrf_802154_ack_data_pending_bit_should_be_set(test_psdu_short);
    TEST_ASSERT_TRUE(result);
}
