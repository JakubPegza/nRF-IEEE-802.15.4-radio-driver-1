/*
 * Copyright (c) 2018 - 2020, Nordic Semiconductor ASA
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

#ifndef NRF_802154_TYPES_H__
#define NRF_802154_TYPES_H__

#include <stdint.h>

/**
 * @defgroup nrf_802154_types Type definitions used in the 802.15.4 driver
 * @{
 * @ingroup nrf_802154
 * @brief Definitions of types used in the 802.15.4 driver.
 */

#define NRF_802154_INVALID_CHANNEL UINT8_MAX // !< Channel value indicating invalid channel number.
#define NRF_802154_INVALID_POWER   INT8_MAX  // !< Radio power value indicating invalid value.

//!@{
/**
 * @brief States of the driver.
 */
typedef uint32_t nrf_802154_state_t;

#define NRF_802154_STATE_INVALID            0x01 // !< Radio in an invalid state.
#define NRF_802154_STATE_SLEEP              0x02 // !< Radio in the sleep state.
#define NRF_802154_STATE_RECEIVE            0x03 // !< Radio in the receive state.
#define NRF_802154_STATE_TRANSMIT           0x04 // !< Radio in the transmit state.
#define NRF_802154_STATE_ENERGY_DETECTION   0x05 // !< Radio in the energy detection state.
#define NRF_802154_STATE_CCA                0x06 // !< Radio in the CCA state.
#define NRF_802154_STATE_CONTINUOUS_CARRIER 0x07 // !< Radio in the continuous carrier state.
#define NRF_802154_STATE_MODULATED_CARRIER  0x08 // !< Radio in the modulated carrier state.
//!@}

//!@{
/**
 * @brief Type of result notified by this module.
 */
typedef uint32_t nrf_802154_ret_t;

#define NRF_802154_RET_SUCCESS         0x00 // !< Operation performed successfuly.
#define NRF_802154_RET_INVALID_PARAM   0x01 // !< At least one of passed parameters has value out of valid range.
#define NRF_802154_RET_INVALID_STATE   0x02 // !< The radio is in the state that prevents requested action.
#define NRF_802154_RET_NO_MEM          0x03 // !< Not enough memory available to perform requested operation.
#define NRF_802154_RET_NOT_FOUND       0x04 // !< Requested object was not available.
#define NRF_802154_RET_NOT_SUPPORTED   0x05 // !< Requested functionality is not supported.
#define NRF_802154_RET_ABORTED         0x06 // !< Procedure was aborted by another operation.
#define NRF_802154_RET_RUNTIME_ERROR   0x07 // !< Runtime error occured (for example, CPU was held for too long).
#define NRF_802154_RET_TIMESLOT_ENDED  0x08 // !< Radio timeslot ended during the requested procedure.
#define NRF_802154_RET_TIMESLOT_DENIED 0x09 // !< Operation did not start due to a denied timeslot request.
#define NRF_802154_RET_TIMEOUT         0x0A // !< Time window requested for the operation has elapsed.
#define NRF_802154_RET_BUSY_CHANNEL    0x0B // !< Channel was busy before the transmission.
#define NRF_802154_RET_INVALID_ACK     0x0C // !< Received ACK frame is other than expected.
#define NRF_802154_RET_NO_ACK          0x0D // !< ACK frame was not received during the timeout period.
#define NRF_802154_RET_INVALID_LENGTH  0x0E // !< Received a frame with invalid length.
#define NRF_802154_RET_INVALID_FRAME   0x0F // !< Received a malformed frame.
#define NRF_802154_RET_INVALID_ADDR    0x10 // !< Received a frame with a mismatched destination.
#define NRF_802154_RET_INVALID_FCS     0x11 // !< Received a frame with an invalid checksum.
//!@}


//!@{
/**
 * @brief Type of configuration parameter identifiers.
 */
typedef uint32_t nrf_802154_cfg_par_t;

/** Channel number used for the radio operations.
 *
 *  The value pointer must point to the uint32_t type.
 *  The valid value range is 11-26. The default value is 11.
 *  This parameter is defined in the IEEE 802.15.4 specification as phyCurrentChannel.
 */
#define NRF_802154_CFG_PAR_CHANNEL           0x00

/** Transmission power used for the radio operations.
 *
 * The value pointer must point to the int32_t type.
 * The value contains power in dBm measured at the antenna. The default value is 0.
 * This parameter is defined in the IEEE 802.15.4 specification as phyTxPower.
 */
#define NRF_802154_CFG_PAR_TX_POWER          0x01

/** The identifier of the PAN on which the device is operating.
 *
 * The value pointer must point to an uint8_t array containing 2 elements.
 * The value is little-endian.
 * This parameter is defined in the IEEE 802.15.4 specification as macPanId.
 */
#define NRF_802154_CFG_PAR_PAN_ID            0x02

/** The short address that identifies the device in the PAN.
 *
 * The value pointer must point to an uint8_t array containing 2 elements.
 * The value is little-endian.
 * This parameter is defined in the IEEE 802.15.4 specification as macShortAddress.
 */
#define NRF_802154_CFG_PAR_SHORT_ADDR        0x03

/** The extended address assigned to the device.
 *
 * The value pointer must point to an uint8_t array containing 8 elements.
 * The value is little-endian.
 * This parameter is defined in the IEEE 802.15.4 specification as macExtendedAddress.
 */
#define NRF_802154_CFG_PAR_EXT_ADDR          0x04

/** If the device is a PAN Coordinator.
 *
 * The value pointer must point to the uint32_t type.
 * The value 0 means that the device is not a PAN Coordinator. The value 1 means that the device is
 * a PAN Coordinator. Other values are invalid.
 * The default value is 0.
 */
#define NRF_802154_CFG_PAR_PAN_COORD         0x05

/** If the device is in the promiscuous mode.
 *
 * The value pointer must point to the uint32_t type.
 * The value 0 means that the device is not in the promiscuous mode. The value 1 means that the
 * device is in the promiscuous mode. Other values are invalid.
 * The default value is 0.
 * This parameter is defined in the IEEE 802.15.4 specification as macPromiscuousMode.
 */
#define NRF_802154_CFG_PAR_PROMISCUOUS       0x06

/** If the device automatically transmits ACK frames.
 *
 * The value pointer must point to the uint32_t type.
 * The value 0 means that the device does not transmit ACK frames automatically. The value 1 means
 * that the device transmits ACK frames automatically. Other values are invalid.
 * The default value is 1.
 *
 * The content of the transmitted ACK frames can be managed with @ref nrf_802154_ack_data_add,
 * @ref nrf_802154_ack_data_remove, and @ref nrf_802154_ack_data_remove_all functions.
 */
#define NRF_802154_CFG_PAR_AUTO_ACK          0x07

/** Selected method to set pending bit in automatically transmitted ACK frames.
 *
 * The value pointer must point to the @ref nrf_802154_ack_pb_method_t type.
 * The default value is @ref NRF_802154_ACK_PB_METHOD_DISABLED.
 */
#define NRF_802154_CFG_PAR_ACK_PB_METHOD     0x08

/** Configuration of CCA procedure.
 *
 * The value pointer must point to the @ref nrf_802154_cca_cfg_t type.
 * The default values are:
 * mode = @ref NRF_802154_CCA_MODE_1
 * ed_threshold = -75
 * corr_threshold = 25
 * corr_limit = 5
 *
 * The mode parameter is defined in the IEEE 802.15.4 specification as phyCcaMode.
 */
#define NRF_802154_CFG_PAR_CCA_CFG           0x09

/** The minimum value of the backoff exponent (BE) in the CSMA-CA algorithm.
 *
 * The value pointer must point to the uint32_t type.
 * The default value is 3.
 * This parameter is defined in the IEEE 802.15.4 specification as macMinBe.
 */
#define NRF_802154_CFG_PAR_MIN_BE            0x0A

/** The maximum value of the backoff exponent (BE) in the CSMA-CA algorithm.
 *
 * The value pointer must point to the uint32_t type.
 * The default value is 5.
 * This parameter is defined in the IEEE 802.15.4 specification as macMaxBe.
 */
#define NRF_802154_CFG_PAR_MAX_BE            0x0B

/** The maximum number of backoffs the CSMA-CA algorithm will attempt.
 *
 * The value pointer must point to the uint32_t type.
 * The default value is 4.
 * This parameter is defined in the IEEE 802.15.4 specification as macMaxCsmaBackoffs.
 */
#define NRF_802154_CFG_PAR_MAX_CSMA_BACKOFFS 0x0C

/** Mode of interframe spacing algorithm.
 *
 * The value pointer must point to the @ref nrf_802154_ifs_mode_t type.
 * The default value is @ref NRF_802154_IFS_MODE_DISABLED.
 */
#define NRF_802154_CFG_PAR_IFS_MODE          0x0D

/** The minimum time forming a SIFS period in microseconds.
 *
 * The value pointer must point to the uint32_t type.
 * The default value is 192.
 * This parameter is defined in the IEEE 802.15.4 specification as macSifsPeriod.
 *
 * Unlike the specification, changing this value does not influence Acknowledgement Interframe
 * Spacing that is constant (192 microseconds).
 */
#define NRF_802154_CFG_PAR_SIFS_PERIOD       0x0E

/** The minimum time forming a LIFS period in microseconds.
 *
 * The value pointer must point to the uint32_t type.
 * The default value is 640.
 * This parameter is defined in the IEEE 802.15.4 specification as macLifsPeriod.
 */
#define NRF_802154_CFG_PAR_LIFS_PERIOD       0x0F

/** The coex request mode used in the receive operation.
 *
 * The value pointer must point to the @ref nrf_802154_coex_rx_request_mode_t type.
 * The default value is @ref NRF_802154_COEX_RX_REQUEST_MODE_DESTINED.
 *
 * @note The coex interface is disabled by default. Refer to the coex module API to enable it.
 *
 * This value may be modified only when the radio is in the sleep state.
 */
#define NRF_802154_CFG_PAR_COEX_RX_MODE      0x10

/** The coex request mode used in the transmit operation.
 *
 * The value pointer must point to the @ref nrf_802154_coex_tx_request_mode_t type.
 * The default value is @ref NRF_802154_COEX_TX_REQUEST_MODE_FRAME_READY.
 *
 * @note The coex interface is disabled by default. Refer to the coex module API to enable it.
 *
 * This value may be modified only when the radio is in the sleep state.
 */
#define NRF_802154_CFG_PAR_COEX_TX_MODE      0x11

/** The antenna diversity mode used in the receive operation.
 *
 * The value pointer must point to the @ref nrf_802154_ant_diversity_mode_t type.
 * The default value is @ref NRF_802154_ANT_DIVERSITY_MODE_DISABLED.
 *
 * This value may be modified only when the radio is in the sleep state.
 */
#define NRF_802154_CFG_PAR_ANT_DIV_RX_MODE   0x12

/** The antenna diversity mode used in the transmit operation.
 *
 * The value pointer must point to the @ref nrf_802154_ant_diversity_mode_t type.
 * The default value is @ref NRF_802154_ANT_DIVERSITY_MODE_DISABLED.
 *
 * This value may be modified only when the radio is in the sleep state.
 * @note @ref NRF_802154_ANT_DIVERSITY_MODE_AUTO is not supported for transmission.
 */
#define NRF_802154_CFG_PAR_ANT_DIV_TX_MODE   0x13

/** The antenna selected for the manual antenna diversity mode in the receive operation.
 *
 * The value pointer must point to the @ref nrf_802154_ant_diversity_antenna_t type.
 * The default value is @ref NRF_802154_ANT_DIVERSITY_ANTENNA_1.
 */
#define NRF_802154_CFG_PAR_ANT_DIV_RX_ANT    0x14

/** The antenna selected for the manual antenna diversity mode in the transmit operation.
 *
 * The value pointer must point to the @ref nrf_802154_ant_diversity_antenna_t type.
 * The default value is @ref NRF_802154_ANT_DIVERSITY_ANTENNA_1.
 */
#define NRF_802154_CFG_PAR_ANT_DIV_TX_ANT    0x15
//!@}

//!@{
/**
 * @brief Data type containing the type of IEEE 802.15.4 network addresses.
 */
typedef uint32_t nrf_802154_addr_type_t;

#define NRF_802154_ADDR_TYPE_EXTENDED 0x00 // !< Extended address (8 bytes)
#define NRF_802154_ADDR_TYPE_SHORT    0x01 // !< Short address (2 bytes)
//!@}

//!@{
/**
 * @brief Algorithms for setting Pending Bit in ACK frames.
 *
 * You can use one of the following methods that can be set during the initialization phase
 * by calling @ref nrf_802154_cfg_set with @ref NRF_802154_CFG_PAR_ACK_PB_METHOD parameter:
 *   - @ref NRF_802154_ACK_PB_METHOD_DISABLED -- The pending bit is always set.
 *   - @ref NRF_802154_ACK_PB_METHOD_THREAD -- The pending bit is set only for the addresses found
 *     in the list. This method meets Thread protocl requirements.
 *   - @ref NRF_802154_ACK_PB_METHOD_BLACKLIST -- The pending bit is cleared only for the addresses
 *     found in the list. This method does not set pending bit in an ACK sent as a response to
 *     non-command and non-data-request frames. This method meets Zigbee protocol requirements.
 */
typedef uint32_t nrf_802154_ack_pb_method_t;

/** Pending bit is always set. */
#define NRF_802154_ACK_PB_METHOD_DISABLED   0x00

/** Pending bit is set only for the addresses found in the list.
 *
 * This method meets Thread 1.2 specification requirements (and is proved to work with the devices
 * implementing earlier Thread specifications).
 * It is not strictly following IEEE 802.15.4-2015 standard. The pending bit field is set in
 * an Ack sent as a response to any frame (including data frames and all command frames) if the
 * frame originator's address is in the list, what contradicts chapter 7.3.3 "Ack frame format".
 */
#define NRF_802154_ACK_PB_METHOD_THREAD     0x01

/** Pending bit is set only in an ACK sent as a response to the data poll command, unless the
 * address is found in the list.
 *
 * This method meets the IEEE 802.15.4-2015 specification requirements:
 * - 6.7.3 "Extracting pending data from a coordinator"
 * - 7.2.1.3 "Frame Pending bit"
 * - 7.3.3 "Ack frame format"
 *
 * This method meets Zigbee protocol requirements.
 */
#define NRF_802154_ACK_PB_METHOD_BLACKLIST  0x02
//!@}

//!@{

/**
 * @brief Types of data that can be set in an ACK message.
 */
typedef uint32_t nrf_802154_ack_data_t;

/** Pending bit in an ACK frame.
 *
 * The p_data field in the @ref nrf_802154_ack_data_metadata_t shall be set to NULL and considered
 * irrelevant. The length field shall be set to NULL and considered irrelevant.
 */
#define NRF_802154_ACK_DATA_PENDING_BIT 0x00

/** Information Elements in an Enhanced ACK frame.
 *
 * The p_data field in the @ref nrf_802154_ack_data_metadata_t must point to a data buffer
 * (uint8_t array) with the length defined by the length field. The buffer must contain Information
 * Elements that are to be included in the Enhanced ACK frame. The buffer is copied by the called
 * function. Its lifetime must exceed the function call. After the call the buffer may be released.
 */
#define NRF_802154_ACK_DATA_IE          0x01
//!@}

//!@{
/**
 * @brief Type of CCA mode.
 */
typedef uint32_t nrf_802154_cca_mode_t;

#define NRF_802154_CCA_MODE_1     0x00 // !< Energy Above Threshold. Will report busy whenever energy is detected above set threshold.
#define NRF_802154_CCA_MODE_2     0x01 // !< Carrier Sense Only. Will report busy whenever compliant IEEE 802.15.4 signal is seen.
#define NRF_802154_CCA_MODE_3_AND 0x02 // !< Carrier Sense and Energy Above Threshold. Will report busy whenever energy is detected above set threshold and compliant IEEE 802.15.4 signal is seen.
#define NRF_802154_CCA_MODE_3_OR  0x03 // !< Carrier Sense or Energy Above Threshold. Will report busy whenever energy is detected above set threshold or compliant IEEE 802.15.4 signal is seen.
//!@}

/**
 * @brief Structure for configuring CCA.
 *
 * This structure is to be used as a parameter value->p_ptr in @ref nrf_802154_cfg_set and 
 * @ref nrf_802154_cfg_get functions.
 */
typedef struct
{
    nrf_802154_cca_mode_t mode;           // !< CCA mode.
    int8_t                ed_threshold;   // !< Busy threshold of the CCA energy in dBm. Not used in @ref NRF_RADIO_CCA_MODE_2.
    uint8_t               corr_threshold; // !< Busy threshold of the CCA correlator. Not used in @ref NRF_RADIO_CCA_MODE_1.
    uint8_t               corr_limit;     // !< Limit of occurrences above the busy threshold of the CCA correlator. Not used in @ref NRF_RADIO_CCA_MODE_1.
} nrf_802154_cca_cfg_t;
//!@}

//!@{
/**
 * @brief Type containing selected transmission procedure.
 */
typedef uint32_t nrf_802154_tx_procedure_t;

#define NRF_802154_TX_PROCEDURE_SIMPLE 0x00  // !< Just transmit the data, without checking channel status.
#define NRF_802154_TX_PROCEDURE_CCA    0x01  // !< Perform the CCA procedure before transmission.
#define NRF_802154_TX_PROCEDURE_CSMACA 0x02  // !< Perform the CSMA-CA procedure before transmittion.
//!@}

//!@{
/**
 * @brief Mode of triggering receive request to Coex arbiter.
 *
 * Possible values:
 * - @ref NRF_802154_COEX_RX_REQUEST_MODE_ENERGY_DETECTION,
 * - @ref NRF_802154_COEX_RX_REQUEST_MODE_PREAMBLE,
 * - @ref NRF_802154_COEX_RX_REQUEST_MODE_DESTINED
 */
typedef uint32_t nrf_802154_coex_rx_request_mode_t;

#define NRF_802154_COEX_RX_REQUEST_MODE_ENERGY_DETECTION 0x01 // !< Coex requests to arbiter in receive mode upon energy detected.
#define NRF_802154_COEX_RX_REQUEST_MODE_PREAMBLE         0x02 // !< Coex requests to arbiter in receive mode upon preamble reception.
#define NRF_802154_COEX_RX_REQUEST_MODE_DESTINED         0x03 // !< Coex requests to arbiter in receive mode upon detection that frame is addressed to this device.
//!@}

//!@{
/**
 * @brief Mode of triggering transmit request to Coex arbiter.
 *
 * Possible values:
 * - @ref NRF_802154_COEX_TX_REQUEST_MODE_FRAME_READY,
 * - @ref NRF_802154_COEX_TX_REQUEST_MODE_CCA_START,
 * - @ref NRF_802154_COEX_TX_REQUEST_MODE_CCA_DONE
 */
typedef uint32_t nrf_802154_coex_tx_request_mode_t;

#define NRF_802154_COEX_TX_REQUEST_MODE_FRAME_READY 0x01 // !< Coex requests to arbiter in transmit mode when the frame is ready to be transmitted.
#define NRF_802154_COEX_TX_REQUEST_MODE_CCA_START   0x02 // !< Coex requests to arbiter in transmit mode before CCA is started.
#define NRF_802154_COEX_TX_REQUEST_MODE_CCA_DONE    0x03 // !< Coex requests to arbiter in transmit mode after CCA is finished.
//!@}

//!@{
/**
 * @brief Mode of handling Interframe spacing.
 *
 * Possible values:
 * - @ref NRF_802154_IFS_MODE_DISABLED,
 * - @ref NRF_802154_IFS_MODE_MATCHING_ADDRESSES,
 * - @ref NRF_802154_IFS_MODE_ALWAYS
 */
typedef uint32_t nrf_802154_ifs_mode_t;

#define NRF_802154_IFS_MODE_DISABLED           0x00 // !< Interframe spacing is never inserted.
#define NRF_802154_IFS_MODE_MATCHING_ADDRESSES 0x01 // !< Interframe spacing is inserted only on matching addresses.
#define NRF_802154_IFS_MODE_ALWAYS             0x02 // !< Interframe spacing is always inserted.
//!@}

/**
 * @brief Type of structure holding statistic counters.
 *
 * This structure holds counters of @c uint32_t type only.
 */
typedef struct
{
    uint32_t cca_failed_attempts;     // !< Number of failed CCA attempts.
    uint32_t received_frames;         // !< Number of times an IEEE 802.15.4 compliant was detected in the receive mode.
    uint32_t received_energy_events;  // !< Number of frames received with correct CRC and with filtering passing.
    uint32_t received_preambles;      // !< Number of times a preamble was received in receive mode.
    uint32_t coex_requests;           // !< Number of coex requests issued to the coex arbiter.
    uint32_t coex_granted_requests;   // !< Number of coex requests issued to the coex arbiter that have been granted.
    uint32_t coex_denied_requests;    // !< Number of coex requests issued to the coex arbiter that have been denied.
    uint32_t coex_unsolicited_grants; // !< Number of coex grant activations that have been not requested.
} nrf_802154_stat_counters_t;

/**
 * @brief Type of structure holding time stamps of certain events.
 */
typedef struct
{
    uint32_t last_csmaca_start_timestamp; // !< Timestamp of last CSMA/CA procedure started.
    uint32_t last_cca_start_timestamp;    // !< Timestamp of last CCA start attempt.
    uint32_t last_cca_idle_timestamp;     // !< Timestamp of last CCA attempt finished with CCA IDLE (channel was free to transmit).
    uint32_t last_tx_end_timestamp;       // !< Timestamp when last bit of transmitted frame was sent on the air.
    uint32_t last_ack_end_timestamp;      // !< Timestamp when last bit of acknowledge frame was received
    uint32_t last_rx_end_timestamp;       // !< Timestamp when last bit of received frame was received.
} nrf_802154_stat_timestamps_t;

/**
 * @brief Type of structure holding total times spent in certain states.
 *
 * This structure holds fields of @c uint64_t type only.
 */
typedef struct
{
    uint64_t total_listening_time; // !< Total time in microseconds spent with receiver turned on, but not actually receiving PPDU.
    uint64_t total_receive_time;   // !< Total time in microseconds spent with receiver turned on and actually receiving PPDU.
    uint64_t total_transmit_time;  // !< Total time in microseconds spent on transmission.
} nrf_802154_stat_totals_t;

/**
 * @brief Type of structure holding the Radio Driver statistics.
 */
typedef struct
{
    nrf_802154_stat_counters_t   counters;   // !< Statistic counters
    nrf_802154_stat_timestamps_t timestamps; // !< Time stamps of events
} nrf_802154_stats_t;

/**
 *@}
 **/

#endif // NRF_802154_TYPES_H__
