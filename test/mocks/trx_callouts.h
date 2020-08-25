/*
 * Copyright (c) Nordic Semiconductor ASA. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor ASA.
 * The use, copying, transfer or disclosure of such information is prohibited except by
 * express written agreement with Nordic Semiconductor ASA.
 */

#include <stdbool.h>
#include <stdint.h>

void nrf_802154_trx_receive_ack_started(void);
void nrf_802154_trx_receive_frame_prestarted(void);
void nrf_802154_trx_receive_frame_started(void);
uint8_t nrf_802154_trx_receive_frame_bcmatched(uint8_t bcc);
void nrf_802154_trx_receive_frame_received(void);
void nrf_802154_trx_receive_frame_crcerror(void);
void nrf_802154_trx_receive_ack_received(void);
void nrf_802154_trx_receive_ack_crcerror(void);
void nrf_802154_trx_transmit_frame_ccastarted(void);
void nrf_802154_trx_transmit_frame_ccaidle(void);
void nrf_802154_trx_transmit_frame_ccabusy(void);
void nrf_802154_trx_transmit_frame_started(void);
void nrf_802154_trx_transmit_frame_transmitted(void);
void nrf_802154_trx_transmit_ack_started(void);
void nrf_802154_trx_transmit_ack_transmitted(void);
void nrf_802154_trx_go_idle_finished(void);
void nrf_802154_trx_standalone_cca_finished(bool channel_was_idle);
void nrf_802154_trx_energy_detection_finished(uint8_t ed_sample);
