/*
 * Copyright (c) 2017 - 2020, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file implements the nrf 802.15.4 WiFi Coexitstence abstraction in case no implementation is used.
 *
 */

#include "nrf_802154_wifi_coex.h"

#include "stddef.h"

#include <nrf.h>

void nrf_802154_wifi_coex_init(void)
{
    // Assume RF Access is always granted.
    nrf_802154_wifi_coex_granted(WIFI_COEX_REQUEST_STATE_NO_REQUEST);
}

void nrf_802154_wifi_coex_uninit(void)
{
    // Intentionally empty
}

void nrf_802154_wifi_coex_prio_request(rsch_prio_t priority)
{
    (void)priority;
    // Intentionally empty
}

void * nrf_802154_wifi_coex_deny_event_addr_get(void)
{
    // Intentionally empty
    return NULL;
}

__WEAK void nrf_802154_wifi_coex_prio_changed(rsch_prio_t priority)
{
    (void)priority;
    // Intentionally empty
}

bool nrf_802154_wifi_coex_enable(void)
{
    // Wifi coex signaling cannot be enabled
    return false;
}

void nrf_802154_wifi_coex_disable(void)
{
    // Intentionally empty
}

bool nrf_802154_wifi_coex_is_enabled(void)
{
    return false;
}
