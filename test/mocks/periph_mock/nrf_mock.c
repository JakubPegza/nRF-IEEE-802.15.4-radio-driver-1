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

