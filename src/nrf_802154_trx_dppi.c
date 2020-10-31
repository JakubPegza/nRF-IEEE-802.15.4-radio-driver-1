/*
 * Copyright (c) 2020, Nordic Semiconductor ASA
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

#define NRF_802154_MODULE_ID NRF_802154_DRV_MODULE_ID_TRX_PPI

#include "nrf_802154_trx_ppi.h"

#include "nrf_802154_debug_log.h"
#include "nrf_802154_peripherals.h"

#include "hal/nrf_egu.h"
#include "hal/nrf_radio.h"
#include "hal/nrf_timer.h"

void nrf_802154_trx_ppi_all_clear(void)
{
    nrf_802154_log_function_enter(NRF_802154_LOG_VERBOSITY_HIGH);

    // TODO: Implement this function

    nrf_802154_log_function_exit(NRF_802154_LOG_VERBOSITY_HIGH);
}

void nrf_802154_trx_ppi_for_ramp_up_set(nrf_radio_task_t ramp_up_task, bool start_timer)
{
    nrf_802154_log_function_enter(NRF_802154_LOG_VERBOSITY_HIGH);

    // TODO: Implement this function

    nrf_802154_log_function_exit(NRF_802154_LOG_VERBOSITY_HIGH);
}

void nrf_802154_trx_ppi_for_ramp_up_clear(bool start_timer)
{
    nrf_802154_log_function_enter(NRF_802154_LOG_VERBOSITY_HIGH);

    // TODO: Implement this function

    nrf_802154_log_function_exit(NRF_802154_LOG_VERBOSITY_HIGH);
}

/** Wait time needed to propagate event through PPI to EGU.
 *
 * During detection if trigger of DISABLED event caused start of hardware procedure, detecting
 * function needs to wait until event is propagated from RADIO through PPI to EGU. This delay is
 * required to make sure EGU event is set if hardware was prepared before DISABLED event was
 * triggered.
 */
void nrf_802154_trx_ppi_for_ramp_up_propagation_delay_wait(void)
{
    // TODO: Implement this function
}

bool nrf_802154_trx_ppi_for_ramp_up_was_triggered(void)
{
    nrf_802154_log_function_enter(NRF_802154_LOG_VERBOSITY_HIGH);

    // TODO: Implement this function

    nrf_802154_log_function_exit(NRF_802154_LOG_VERBOSITY_HIGH);
    return false;
}

void nrf_802154_trx_ppi_for_ack_tx_set(void)
{
    nrf_802154_log_function_enter(NRF_802154_LOG_VERBOSITY_HIGH);

    // TODO: Implement this function

    nrf_802154_log_function_exit(NRF_802154_LOG_VERBOSITY_HIGH);
}

void nrf_802154_trx_ppi_for_ack_tx_clear(void)
{
    nrf_802154_log_function_enter(NRF_802154_LOG_VERBOSITY_HIGH);

    // TODO: Implement this function

    nrf_802154_log_function_exit(NRF_802154_LOG_VERBOSITY_HIGH);
}

void nrf_802154_trx_ppi_for_fem_set(void)
{
    nrf_802154_log_function_enter(NRF_802154_LOG_VERBOSITY_HIGH);

    // TODO: Implement this function

    nrf_802154_log_function_exit(NRF_802154_LOG_VERBOSITY_HIGH);
}

void nrf_802154_trx_ppi_for_fem_clear(void)
{
    nrf_802154_log_function_enter(NRF_802154_LOG_VERBOSITY_HIGH);

    // TODO: Implement this function

    nrf_802154_log_function_exit(NRF_802154_LOG_VERBOSITY_HIGH);
}

bool nrf_802154_trx_ppi_for_fem_powerdown_set(NRF_TIMER_Type * p_instance,
                                              uint32_t         compare_channel)
{
    nrf_802154_log_function_enter(NRF_802154_LOG_VERBOSITY_HIGH);

    // TODO: Implement this function

    nrf_802154_log_function_exit(NRF_802154_LOG_VERBOSITY_HIGH);
    return false;
}

void nrf_802154_trx_ppi_for_fem_powerdown_clear(void)
{
    nrf_802154_log_function_enter(NRF_802154_LOG_VERBOSITY_HIGH);

    // TODO: Implement this function

    nrf_802154_log_function_exit(NRF_802154_LOG_VERBOSITY_HIGH);
}

uint32_t nrf_802154_trx_ppi_group_for_abort_get(void)
{
    return 0;
}

#if defined(RADIO_INTENSET_SYNC_Msk)
void nrf_802154_trx_ppi_for_radio_sync_set(uint32_t task_address)
{
    nrf_802154_log_function_enter(NRF_802154_LOG_VERBOSITY_HIGH);

    // TODO: Implement this function

    nrf_802154_log_function_exit(NRF_802154_LOG_VERBOSITY_HIGH);
}

void nrf_802154_trx_ppi_for_radio_sync_clear(void)
{
    nrf_802154_log_function_enter(NRF_802154_LOG_VERBOSITY_HIGH);

    // TODO: Implement this function

    nrf_802154_log_function_exit(NRF_802154_LOG_VERBOSITY_HIGH);
}

#endif
