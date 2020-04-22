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
 * @defgroup nrf_802154 802.15.4 Radio Controller
 * @{
 *
 */

#ifndef NRF_802154_H_
#define NRF_802154_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "nrf_802154_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NRF_802154_VER_MAJ 2  // !< Major version of the 802.15.4 Radio Controller
#define NRF_802154_VER_MIN 0  // !< Minor version of the 802.15.4 Radio Controller
#define NRF_802154_VER_PAT 0  // !< Patch version of the 802.15.4 Radio Controller

/** @brief Macro containing combined version of the 802.15.4 Radio Controller.
 *
 * This macro combines major version (as number of hundred of hundreds) with minor version (as
 * number of hundreds) with patch version (as number) summed together.
 *
 * The version 2.0.0 is represented as 20000.
 * The version 2.0.4 is represented as 20004.
 * The version 2.14.0 is represented as 21400.
 */
#define NRF_802154_VER ((NRF_802154_VER_MAJ * 10000) +                                             \
                        (NRF_802154_VER_MIN * 100) +                                               \
                        (NRF_802154_VER_PAT))

/**
 * @brief Structure with initialization parameters of the module.
 */
typedef struct
{
    // Intentionally empty
} nrf_802154_init_cfg_t;

#define NRF_802154_INIT_CFG_DEF (nrf_802154_init_cfg_t){                                           \
}

/**
 * @brief Initialize the 802.15.4 driver.
 *
 * This function initializes the RADIO peripheral in the @ref RADIO_STATE_SLEEP state.
 *
 * This function is to be called once, before any other functions from this module. Calling this
 * function again without calling @ref nrf_802154_uninit earlier results in undefined behavior.
 *
 * To reinitialize the module with different configuration call @ref nrf_802154_uninit and
 * @ref nrf_802154_init again with new configuration.
 *
 * @param[in] p_cfg  Structure with initialization parameters of the module. Default initialization
 *                   parameters are available with @ref NRF_802154_INIT_CFG_DEF macro.
 */
void nrf_802154_init(const nrf_802154_init_cfg_t * p_cfg);

/**
 * @brief Deinitialize the 802.15.4 driver.
 *
 * This function uninitializes the RADIO peripheral and resets it to the default state.
 */
void nrf_802154_uninit(void);

#if !NRF_802154_INTERNAL_RADIO_IRQ_HANDLING
/**
 * @brief Handle the interrupt request from the RADIO peripheral.
 *
 * @note If NRF_802154_INTERNAL_RADIO_IRQ_HANDLING is enabled, the driver internally handles the
 *       RADIO IRQ, and this function must not be called.
 *
 * This function is intended for use in an operating system environment, where the OS handles IRQ
 * and indirectly passes it to the driver, or with a radio arbiter implementation that indirectly
 * passes radio IRQ to the driver (like MPSL or SoftDevice).
 */
void nrf_802154_radio_irq_handler(void);
#endif // !NRF_802154_INTERNAL_RADIO_IRQ_HANDLING

/**
 * @defgroup nrf_802154_config IEEE 802.15.4 interface management
 * @{
 */

/**
 * @brief Structure with configuration setter metadata.
 */
typedef struct
{
} nrf_802154_cfg_set_metadata_t;

/**
 * @brief Initialize the configuration setter metadata to default values.
 */
static inline void nrf_802154_cfg_set_metadata_init(nrf_802154_cfg_set_metadata_t * p_metadata)
{
    // Intentionally empty
}

/**
 * @brief Set selected configuration parameter of the radio interface.
 *
 * The @p p_value pointer must point to the type defined by given @p type. Refer to @p type
 * documentation for details.
 *
 * The value pointed by @p p_value is copied by this function.
 *
 * @param[in]  type       Type of the configuration parameter to set.
 * @param[in]  p_value    Value of the configuration parameter to set.
 * @param[in]  p_metadata Optional metadata for the command. If NULL, the default metadata like
 *                        created by @ref nrf_802154_cfg_set_metadata_init are used.
 *
 * @retval NRF_802154_RET_SUCCESS        Configuration parameter updated.
 * @retval NRF_802154_RET_INVALID_PARAM  At least one of the parameters has an invalid value.
 * @retval NRF_802154_RET_INVALID_STATE  The requested parameter cannot be changed in the current
 *                                       radio state.
 */
nrf_802154_ret_t nrf_802154_cfg_set(nrf_802154_cfg_par_t                  type, 
                                    const void                          * p_value,
                                    const nrf_802154_cfg_set_metadata_t * p_metadata);

/**
 * @brief Structure with configuration getter metadata.
 */
typedef struct
{
} nrf_802154_cfg_get_metadata_t;

/**
 * @brief Initialize the configuration getter metadata to default values.
 */
static inline void nrf_802154_cfg_get_metadata_init(nrf_802154_cfg_get_metadata_t * p_metadata)
{
    // Intentionally empty
}

/**
 * @brief Get selected configuration parameter of the radio interface.
 *
 * The @p p_value pointer must point to the type defined by given @p type. Refer to @p type
 * documentation for details.
 *
 * The required value is copied to the @p p_value pointer location.
 *
 * @param[in]  type        Type of the configuration parameter to get.
 * @param[out] p_value     Value of retrieved configuration parameter.
 * @param[in]  p_metadata  Optional metadata for the command. If NULL, the default metadata like
 *                         created by @ref nrf_802154_cfg_get_metadata_init are used.
 *
 * @retval NRF_802154_RET_SUCCESS       Configuration parameter retrieved.
 * @retval NRF_802154_RET_INVALID_PARAM At least one of the parameters has an invalid value.
 */
nrf_802154_ret_t nrf_802154_cfg_get(nrf_802154_cfg_par_t                  type,
                                    void                                * p_value,
                                    const nrf_802154_cfg_get_metadata_t * p_metadata);


/**
 * @}
 * @defgroup nrf_802154_data Functions to calculate data given by the driver
 * @{
 */

/**
 * @brief  Convert the energy level received during the energy detection procedure to a dBm value.
 *
 * @param[in]  energy_level  Energy level passed by @ref nrf_802154_energy_detected.
 *
 * @return  Result of the energy detection procedure in dBm.
 */
int8_t nrf_802154_dbm_from_energy_level_calculate(uint8_t energy_level);

/**
 * @brief Structure with the frame timings calculation metadata.
 */
typedef struct
{
    // Intentionally empty
} nrf_802154_frame_timestamp_get_metadata_t;

/**
 * @brief Initialize the frame timings calculation metadata.
 */
static inline void nrf_802154_frame_timestamp_get_metadata_init(nrf_802154_frame_timestamp_get_metadata_t * p_metadata)
{
    // Intentionally empty
}

/**
 * @brief  Calculate the timestamp of the first symbol of the preamble in a received frame.
 *
 * @param[in]  end_timestamp  Timestamp of the end of the last symbol in the frame,
 *                            in microseconds.
 * @param[in]  psdu_length    Number of bytes in the frame PSDU.
 * @param[in]  p_metadata     Metadata describing the frame timings. If NULL the default metadata,
 *                            like created with @ref nrf_802154_frame_timestamp_get_metadata_init is
 *                            used.
 *
 * @return  Timestamp of the beginning of the first preamble symbol of a given frame,
 *          in microseconds.
 */
uint32_t nrf_802154_first_symbol_timestamp_get(
        uint32_t                                          end_timestamp, 
        uint32_t                                          psdu_length, 
        const nrf_802154_frame_timestamp_get_metadata_t * p_metadata);

/**
 * @}
 * @defgroup nrf_802154_stable_states Functions to request entering stable radio states.
 * @{
 */

/**
 * @brief Structure with the state getter metadata.
 */
typedef struct
{
} nrf_802154_state_get_metadata_t;

/**
 * @brief Initialize state getter metadata to default values.
 */
static inline void nrf_802154_state_get_metadata_init(nrf_802154_state_get_metadata_t * p_metadata)
{
    // Intentionally empty
}

/**
 * @brief Get the current state of the radio.
 *
 * @param[in]  p_metadata  Optional metadata. If NULL, the default metadata like created by
 *                         @ref nrf_802154_state_get_metadata_init are used.
 *
 * @note This function returns the current state of the radio. There can be an enqueued state change
 *       requests in the driver that will change the state soon.
 */
nrf_802154_state_t nrf_802154_state_get(const nrf_802154_state_get_metadata * p_metadata);

/**
 * @brief Structure with sleep request metadata.
 */
typedef struct
{
    bool gracefully; // !< Entering sleep state is requested only when the radio is idle (idle-listening or between operations). Prevents enetering sleep state during PSDU reception.
} nrf_802154_sleep_metadata_t;

/**
 * @brief Initialize sleep request metadata to default values.
 */
static inline void nrf_802154_sleep_metadata_init(nrf_802154_sleep_metadata_t * p_metadata)
{
    p_metadata->gracefully = false;
}

/**
 * @brief Change the radio state to the @ref RADIO_STATE_SLEEP state.
 *
 * The sleep state is the lowest power state. In this state, the radio cannot transmit or receive
 * frames. It is the only state in which the driver releases the high-frequency clock and does not
 * request timeslots from a radio arbiter.
 *
 * This function is an asynchronous request.
 *
 * @note If another module requests it, the high-frequency clock may be enabled even in the radio
 *       sleep state.
 *
 * @param[in]  p_metadata  Optional metadata. If NULL, the default metadata like created by
 *                         @ref nrf_802154_sleep_metadata_init are used.
 *
 * @retval  NRF_802154_RET_SUCCESS   The radio changes its state to the low power mode.
 * @retval  NRF_802154_RET_BUSY      The radio cannot change its state at the moment. To enter the
 *                                   sleep state, call this function again later.
 */
nrf_802154_ret_t nrf_802154_sleep(const nrf_802154_sleep_metadata_t * p_metadata);

/**
 * @brief Structure with receive request metadata.
 */
typedef struct
{
    void * p_context; // !< User-defined context copied to @ref nrf_802154_receive_done_metadata_t.
} nrf_802154_receive_metadata_t;

/**
 * @brief Initialize receive request metadata to default values.
 */
static inline void nrf_802154_receive_metadata_init(nrf_802154_receive_metadata_t * p_metadata)
{
    p_metadata->p_context = NULL;
}

/**
 * @brief Request change of the radio state to @ref RADIO_STATE_RX.
 *
 * In the receive state, the radio receives frames and may automatically send ACK frames when
 * appropriate. The received frame is reported to the higher layer by a call to
 * @ref nrf_802154_receive_done.
 *
 * @param[in] p_metadata  Metadata describing receive procedure. If NULL, the default metadata
 *                        like created by @ref nrf_802154_receive_metadata_init are used.
 *
 * @retval  NRF_802154_RET_SUCCESS   The radio enters the receive state.
 */
nrf_802154_ret_t nrf_802154_receive(const nrf_802154_receive_metadata_t * p_metadata);

/**
 * @brief Structure with receive notification metadata.
 */
typedef struct
{
    nrf_802154_ret_t                   status;           // !< Status of the finished receive operation.
    void                             * p_context;        // !< User-defined context copied from @ref nrf_802154_receive_metadata_t or from @ref nrf_802154_receive_at_metadata_t.

    int8_t                             power;            // !< Power of the received frame in dBm. If the frame was not received, the value is set to @ref NRF_802154_INVALID_POWER but is irrelevant.
    uint8_t                            lqi;              // !< LQI of the received frame. If the frame was not received, the value is set to 0 but is irrelevant.
    bool                               timestamp_valid;  // !< If @ref timestamp of the received frame is known, the value is true. If the timestamp is unknown, the value is false. If the frame was not received the value is set to false but is irrelevant.
    uint32_t                           timestamp;        // !< Timestamp in microseconds, taken when the last symbol of the received frame was received. If the frame was not received the value is set to 0 but is irrelevant.

    bool                               ack_pb;           // !< True if Pending Bit in the transmitted ACK was set. False if the ACK was not transmitted or Pending Bit fields was cleared in the ACK.

    nrf_802154_ant_diversity_antenna_t best_antenna;     // !< Antenna with the best signal used to receive the frame. If the frame was not received, or the antenna diversity receive mode is other than automatic, or the automatic antenna selection algorithm could not select the best antenna, this value is set to @ref NRF_802154_ANT_DIVERSITY_ANTENNA_NONE.
} nrf_802154_receive_done_metadata_t;

/**
 * @brief Notify that the requested receive operation has finished.
 *
 * The receive operation may finish with a received frame (@p p_metadata->status equal to 
 * @ref NRF_802154_RET_SUCCESS) or with an error (@p p_metadata->status indicates the reason).
 * After the receive operation finished, the radio automatically enters the receive state again,
 * unless the operation was aborted by entering any other radio state.
 *
 * The buffer pointed to by @p p_data is valid only in scope of this function. To prevent the buffer
 * from beint released, call @ref nrf_802154_buffer_ref_inc in the body of this function. If 
 * @ref nrf_802154_buffer_ref_inc is called, the buffer is not released or modified by this library
 * (and cannot be used to receive a frame) until @ref nrf_802154_buffer_ref_dec is called.
 *
 * The buffer pointed to by @p p_data may be modified by this function handler. To modify it by
 * other procedures or modules call @ref nrf_802154_buffer_ref_inc. The buffer may be modified by 
 * the other modules until @ref nrf_802154_buffer_ref_dec is called.
 *
 * @note The higher layer must expect that this function is called anytime.
 *
 * @verbatim
 *     p_data
 *       v
 * +-----+-----------------------------------------------------------+------------+
 * | PHR | MAC Header and payload                                    | FCS        |
 * +-----+-----------------------------------------------------------+------------+
 *       |                                                           |
 *       | <------------------------- length ----------------------> |
 * @endverbatim
 *
 * @param[in]  p_data     Pointer to a buffer that contains PSDU of the received frame. If the
 *                        frame was not received the value is set to NULL but is irrelevant.
 * @param[in]  length     Length in bytes of the data in the @p p_data buffer. If the frame was not
 *                        received the value is set to 0 but is irrelevant.
 * @param[in]  p_metadata Metadata describing the receive operation.
 */
extern void nrf_802154_receive_done(uint8_t                                * p_data, 
                                    uint32_t                                 length,
                                    const nrf_802154_receive_done_metadata * p_metadata);

/**
 * @brief Structure with continuous carrier request metadata.
 */
typedef struct
{
} nrf_802154_continuous_carrier_metadata_t;

/**
 * @brief Initialize continuous carrier request metadata to default values.
 */
static inline void nrf_802154_continuous_carrier_metadata_init(
        nrf_802154_continuous_carrier_metadata_t * p_metadata)
{
    // Intentionally empty
}

/**
 * @brief Request change of the radio state to continuous carrier.
 *
 * @note When the radio is emitting continuous carrier signals, it blocks all transmissions on the
 *       selected channel. This function is to be called only during radio tests. Do not use it
 *       during normal device operation.
 *
 * @param[in] p_metadata  Metadata describing continuous carrier procedure. If NULL, the default
 *                        metadata like created by @ref nrf_802154_continuous_carrier_metadata_init
 *                        are used.
 *
 * @retval  NRF_802154_RET_SUCCESS   The continuous carrier procedure was scheduled.
 */
nrf_802154_ret_t nrf_802154_continuous_carrier(const nrf_802154_continuous_carrier_metadata_t * p_metadata);

/**
 * @brief Structure with modulated carrier request metadata.
 */
typedef struct
{
} nrf_802154_modulated_carrier_metadata_t;

/**
 * @brief Initialize modulated carrier request metadata to default values.
 */
static inline void nrf_802154_modulated_carrier_metadata_init(
        nrf_802154_modulated_carrier_metadata_t * p_metadata)
{
    // Intentionally empty
}

/**
 * @brief Request change of the radio state to modulated carrier.
 *
 * @note When the radio is emitting modulated carrier signals, it blocks all transmissions on the
 *       selected channel. This function is to be called only during radio tests. Do not use it
 *       during normal device operation.
 *
 * If @p p_data buffer was acquired with the @ref nrf_802154_buffer_get function, this function
 * works in a zero-copy fasion. The buffer must be released with the @ref nrf_802154_buffer_free
 * function after the radio exits the modulated carrier state.If @p p_data buffer was not acquired
 * with the @ref nrf_802154_buffer_get function, this function creates internal copy of the buffer
 * that is automatically released.
 *
 * @param[in] p_data     Pointer to a buffer to modulate the carrier with.
 * @param[in] length     Number of bytes in the @p_data buffer.
 * @param[in] p_metadata Metadata describing modulated carrier procedure. If NULL, the default
 *                       metadata like created by @ref nrf_802154_modulated_carrier_metadata_init
 *                       are used.
 *
 * @retval  NRF_802154_RET_SUCCESS   The modulated carrier procedure was scheduled.
 */
nrf_802154_ret_t nrf_802154_modulated_carrier(
        const uint8_t                                 * p_data, 
        uint32_t                                        length, 
        const nrf_802154_modulated_carrier_metadata_t * p_metadata);

/**
 * @}
 * @defgroup nrf_802154_rssi RSSI measurement function
 * @{
 */

/**
 * @brief Metadata describing the RSSI measurement request.
 */
typedef struct
{
} nrf_802154_rssi_measure_metadata_t;

/**
 * @brief Initialize the RSSI measurement request metadata to default values.
 */
static inline void nrf_802154_rssi_measure_metadata_init(nrf_802154_rssi_measure_metadata_t * p_metadata)
{
    // Intentionally empty
}

/**
 * @brief Begin the RSSI measurement.
 *
 * @note This function is to be called in the @ref RADIO_STATE_RX state. It does not prevent or
 *       terminate the ongoing receiving operation.
 *
 * When the measurement process is finished the @ref nrf_802154_rssi_measure_done function is
 * called.
 *
 * @param[in]  p_metadata  Metadata describing the request.
 *
 * @retval NRF_802154_RET_SUCCESS       RSSI measurement successfully requested.
 * @retval NRF_802154_RET_INVALID_STATE RSSI measurement cannot be scheduled because radio is not
 *                                      receiving.
 */
nrf_802154_ret_t nrf_802154_rssi_measure(const nrf_802154_rssi_measure_metadata_t * p_metadata);

/**
 * @brief Structure with RSSI notification metadata.
 */
typedef struct
{
    /** @brief Status of the requested RSSI measurement procedure.
     *
     * NRF_802154_RET_SUCCESS The procedure finished successfully.
     * NRF_802154_RET_ABORTED The procedure was aborted by other operation.
     */
    nrf_802154_ret_t status;
} nrf_802154_rssi_measure_done_metadata_t;

/**
 * @brief Notify that the RSSI measurement procedure has finished.
 *
 * @param[in]  rssi          Power level measured at the channel. The value is set to
 *                           @ref NRF_802154_INVALID_POWER and is irrelevant if the measurement
 *                           failed.
 * @param[in]  p_metadata    Metadata describing the RSSI measurement procedure notification status.
 */
extern void nrf_802154_rssi_measure_done(
        int8_t                                          rssi, 
        const nrf_802154_rssi_measure_done_metadata_t * p_metadata);


/**
 * @}
 * @defgroup nrf_802154_async_op Functions to request asynchronous radio operations (temporary states).
 * @{
 */

/**
 * @brief Structure with transmit request metadata.
 */
typedef struct
{
    void                    * p_context;    // !< User-defined context copied to @ref nrf_802154_transmit_done_metadata_t.
    nrf_802154_tx_procedure_t tx_procedure; // !< Selected transmission procedure.
} nrf_802154_transmit_metadata_t;

/**
 * @brief Initialize transmit request metadata to default values.
 */
static inline void nrf_802154_transmit_metadata_init(nrf_802154_transmit_metadata_t * p_metadata)
{
    p_metadata->p_context    = NULL;
    p_metadata->tx_procedure = NRF_802154_TX_PROCEDURE_CCA;
}

/**
 * @brief Request transmission of a frame.
 *
 * @note If the CPU is halted or interrupted while this function is executed,
 *       @ref nrf_802154_transmit_done can be called before this function returns a result.
 *
 * If the buffer passed to this function was acquired with @ref nrf_802154_buffer_get or from 
 * @ref nrf_802154_receive_done parameter p_data with @ref nrf_802154_buffer_ref_inc, this function
 * works in zero-copy fasion. The acquired buffer must be released with 
 * @ref nrf_802154_buffer_inc_dec after this function is finished. 
 *
 * If the buffer passed to this function was not acquired with @ref nrf_802154_buffer_get, the
 * passed buffer is copied to internally allocated buffer, that will be released automatically.
 *
 * The @p p_data buffer passed to this function must not be modified until the transmit procedure is
 * finished, what is notified with an error code returned by this function or a call to the 
 * @ref nrf_802154_transmit_done function.
 *
 * The requested transmission will be performed as soon as possible. If the frame given by the
 * @p p_data buffer has the Ack Request bit set in the Frame Control Field (as defined in the
 * IEEE 802.15.4 specification), the radio waits needed time for an ACK frame after the
 * transmission.
 *
 * The transmission result is reported to the higher layer by call to @ref nrf_802154_transmit_done.
 * When the transmission procedure is finished, radio automatically enters the receive state, unless
 * the operation was aborted by entering any other radio state.
 *
 * @verbatim
 *       p_data
 *       v
 * +-----+-----------------------------------------------------------+------------+
 * | PHR | MAC header and payload                                    | FCS        |
 * +-----+-----------------------------------------------------------+------------+
 *       |                                                           |
 *       | <------------------ length -----------------------------> |
 * @endverbatim
 *
 * @param[in]  p_data     Pointer to the array with the payload of data to transmit. The array
 *                        must exclude PHR or FCS fields of the 802.15.4 frame.
 * @param[in]  length     Length of the given frame. This value must exclude PHR and FCS fields
 *                        from the given frame (exact size of buffer pointed to by @p p_data).
 * @param[in]  p_metadata Metadata describing the transmission procedure. If NULL, the default
 *                        metadata like created by @ref nrf_802154_transmit_metadata_init are used.
 *
 * @retval  NRF_802154_RET_SUCCESS        The transmission procedure was scheduled.
 * @retval  NRF_802154_RET_INVALID_PARAM  The @p p_metadata parameter contains invalid value.
 */
nrf_802154_ret_t nrf_802154_transmit(const uint8_t                        * p_data,
                                     uint32_t                               length, 
                                     const nrf_802154_transmit_metadata_t * p_metadata);

/**
 * @brief Structure with transmit notification metadata.
 */
typedef struct
{
    /** @brief Status of the requested transmission.
     *
     * @ref NRF_802154_RET_SUCCESS          The frame transmitted successfully.
     * @ref NRF_802154_RET_BUSY_CHANNEL     Transmission failed, because channel was busy.
     * @ref NRF_802154_RET_INVALID_ACK      Unexpected frame or unexpected value in ACK received.
     * @ref NRF_802154_RET_NO_ACK           No ACK frame received within specified time.
     * @ref NRF_802154_RET_ABORTED          The transmission was aborted by other operation.
     * @ref NRF_802154_RET_TIMESLOT_ENDED   The transmission timeslot was preempted.
     * @ref NRF_802154_RET_TIMESLOT_DENIED  The delayed transmission has not started, because
     *                                      timeslot for the transmission was denied.
     */
    nrf_802154_ret_t status;
    void           * p_context;           // !< User-defined context copied from @ref nrf_802154_transmit_metadata_t.

    uint8_t        * p_ack;               // !< Pointer to a buffer that contains PSDU of the received ACK. If ACK was not received the value is set to NULL and is irrelevant.
    uint32_t         ack_length;          // !< Lenth of PSDU of the received ACK. If ACK was not received the value is set to 0 and is irrelevant.
    int8_t           ack_power;           // !< Power in dBm of the received ACK. If ACK was not received the value is set to @ref NRF_802154_INVALID_POWER and is irrelevant.
    uint8_t          ack_lqi;             // !< LQI of the received ACK. If ACK was not received the value is set to 0 and is irrelevant.
    bool             ack_timestamp_valid; // !< If ACK was received and its timestamp is valid.
    uint32_t         ack_timestamp;       // !< Timestamp taken when the last symbol of ACK is received. If ACK was not received or the value is unknown the value is set to 0 and is irrelevant.

    uint32_t         csmaca_backoffs;     // !< Number of CSMA-CA backoffs used during the transmission procedure. If the CSMA-CA algorithm was not performed, the value is set to 0 and is irrelevant.
} nrf_802154_transmit_done_metadata_t;

/**
 * @brief Notify that the transmission procedure has finished.
 *
 * If the transmission failed, this function is called as soon as the failure occurs.
 * If transmission was successful and ACK was requested for the transmitted frame, this
 * function is called after a proper ACK is received. If transmission was successful and ACK
 * was not requested, this function is called just after transmission has ended.
 *
 * The buffer pointed to by @p p_metadata->p_ack is valid only in scope of this function. To prevent
 * the buffer from being released, call @ref nrf_802154_buffer_ref_inc in the body of this function.
 * If @ref nrf_802154_buffer_ref_inc is called, the buffer is not released or modified by this
 * library (and cannot be used to receive a frame) until @ref nrf_802154_buffer_ref_dec is called.
 *
 * The buffer pointed to by @p p_metadata->p_ack may be modified by this function handler. To modify
 * it by other procedures or modules call @ref nrf_802154_buffer_ref_inc. The buffer may be modified
 * by the other modules until @ref nrf_802154_buffer_ref_dec is called.
 *
 * @param[in]  p_metadata  Metadata of the transmission status notification.
 */
extern void nrf_802154_transmit_done(const nrf_802154_transmit_done_metadata_t * p_metadata);

/**
 * @brief Structure with energy detection request metadata.
 */
typedef struct
{
    void  * p_context; // !< User-defined context copied to @ref nrf_802154_energy_detection_done_metadata_t.
} nrf_802154_energy_detection_metadata_t;

/**
 * @brief Initialize the energy detection request metadata to default values.
 */
static inline void nrf_802154_energy_detection_metadata_init(
        nrf_802154_energy_detection_metadata_t * p_metadata)
{
    p_metadata->p_context = NULL;
}

/**
 * @brief Request the energy detection procedure.
 *
 * During the energy detection procedure, the radio detects the maximum energy for a given time.
 * The result of the detection is reported to the higher layer by
 * @ref nrf_802154_energy_detection_done.
 * When the energy detection procedure is finished, radio automatically enters the receive state.
 *
 * @note @ref nrf_802154_energy_detection_done can be called before this function returns a result.
 *
 * @note Performing the energy detection procedure can take longer than requested in @p time_us.
 *       The procedure is performed only during the timeslots granted by a radio arbiter.
 *       It can be interrupted by other protocols using the radio. If the procedure is
 *       interrupted, it is automatically continued and the sum of time periods during which the
 *       procedure is carried out is not less than the requested @p time_us.
 *
 * @param[in]  time_us    Duration of energy detection procedure. The given value is rounded up to
 *                        multiplication of 8 symbols (128 us).
 * @param[in]  p_metadata Metadata describing the energy detection procedure. If NULL the default
 *                        metadata like created with @ref nrf_802154_energy_detection_metadata_init
 *                        are used.
 *
 * @retval  NRF_802154_RET_SUCCESS  The energy detection procedure was scheduled.
 */
nrf_802154_ret_t nrf_802154_energy_detection(
        uint32_t                                       time_us, 
        const nrf_802154_energy_detection_metadata_t * p_metadata);

/**
 * @brief Structure with energy detection notification metadata.
 */
typedef struct
{
    /** @brief Status of the requested energy_detection.
     *
     * NRF_802154_RET_SUCCESS The energy detection procedure finished successfully.
     * NRF_802154_RET_ABORTED The energy detection procedure was aborted by other operation.
     */
    nrf_802154_ret_t status;

    void * p_context; // !< User-defined context copied from @ref nrf_802154_energy_detection_metadata_t.
} nrf_802154_energy_detection_done_metadata_t;

/**
 * @brief Notify that the energy detection procedure finished.
 *
 * This function passes the EnergyLevel defined in the IEEE 802.15.4 specification: 0x00 - 0xff,
 * proportionally to the detected energy level (dBm above receiver sensitivity). 
 *
 * To calculate the result in dBm, use @ref nrf_802154_dbm_from_energy_level_calculate.
 *
 * @param[in]  result      Maximum energy detected during the energy detection procedure if the
 *                         procedure succeeded. If the procedure failed the value is set to 0.
 * @param[in]  p_metadata  Metadata of the energy measurement status notification.
 */
extern void nrf_802154_energy_detection_done(
        uint8_t                                             result, 
        const nrf_802154_energy_detection_done_metadata_t * p_metadata);

/**
 * @brief Structure with CCA request metadata.
 */
typedef struct
{
    void  * p_context; // !< User-defined context copied to @ref nrf_802154_cca_done_metadata_t.
} nrf_802154_cca_metadata_t;

/**
 * @brief Initialize the CCA request metadata to default values.
 */
static inline void nrf_802154_cca_metadata_init(nrf_802154_cca_metadata_t * p_metadata)
{
    p_metadata->p_context = NULL;
}

/**
 * @brief Request the CCA procedure.
 *
 * @note @ref nrf_802154_cca_done can be called before this function returns a result.
 *
 * During the CCA procedure, the radio verifies if the channel is clear. The result of
 * the verification is reported to the higher layer by @ref nrf_802154_cca_done.
 * When the CCA procedure is finished, radio automatically enters the receive state.
 *
 * @param[in] p_metadata  Metadata describing the requested CCA procedure. If NULL the default
 *                        metadata like created with @ref nrf_802154_cca_metadata_init are used.
 *
 * @retval  NRF_802154_RET_SUCCESS   The CCA procedure was scheduled.
 */
nrf_802154_ret_t nrf_802154_cca(const nrf_802154_cca_metadata_t * p_metadata);

/**
 * @brief Structure with CCA notification metadata.
 */
typedef struct
{
    /** @brief Status of the requested CCA procedure.
     *
     * NRF_802154_RET_SUCCESS The CCA procedure finished successfully.
     * NRF_802154_RET_ABORTED The CCA procedure was aborted by other operation.
     */
    nrf_802154_ret_t status;

    void * p_context; // !< User-defined context copied from @ref nrf_802154_cca_metadata_t.
} nrf_802154_cca_done_metadata_t;

/**
 * @brief Notify that the CCA procedure has finished.
 *
 * @param[in]  channel_free  Indication if the channel is free. If the procedure failed, the value
 *                           is set to false and is irrelevant.
 * @param[in]  p_metadata    Metadata describing the CCA procedure notification status.
 */
extern void nrf_802154_cca_done(bool                                   channel_free, 
                                const nrf_802154_cca_done_metadata_t * p_metadata);

/**
 * @}
 * @defgroup nrf_802154_delayed_op Functions to request and cancel delayed radio operations.
 * @{
 */

/**
 * @brief Structure with delayed reception request metadata.
 */
typedef struct
{
    void  * p_context; // !< User-defined context copied to @ref nrf_802154_receive_done_metadata_t.
    uint8_t channel;   // !< Channel at which requested reception shall be performed. If set to @ref NRF_802154_INVALID_CHANNEL, the channel configured with @ref nrf_802154_cfg_set function lately is used.
} nrf_802154_receive_at_metadata_t;

/**
 * @brief Initialize the delayed reception request metadata to default values.
 */
static inline void nrf_802154_receive_at_metadata_init(
        nrf_802154_receive_at_metadata_t * p_metadata)
{
    p_metadata->p_context = NULL;
    p_metadata->channel   = NRF_802154_INVALID_CHANNEL;
}

/**
 * @brief Request delayed reception at the specified time.
 *
 * This function works as a delayed version of @ref nrf_802154_receive. It is asynchronous. Only
 * one delayed reception can be scheduled at a time. To modify already scheduled delayed reception
 * parameters, cancel it with @ref nrf_802154_receive_at_cancel and request it again with new
 * parameters.
 *
 * If the reception cannot be started at the specified time, the @nrf_802154_receive_done function
 * is called with @ref NRF_802154_RET_TIMESLOT_DENIED status code.
 * There is no notification when the reception starts. If the reception window is aborted by another
 * radio procedure, it is notified with the @nrf_802154_receive_done function with the
 * @ref NRF_802154_RET_ABORT status code. When reception window is about to end, it is notified
 * with the @nrf_802154_receive_done function with the @ref NRF_802154_RET_TIMEOUT status code.
 * After @ref NRF_802154_RET_TIMEOUT notification the radio stays in the receive state. It is
 * responsibility of the higher layer to change the radio state after
 * the @ref NRF_802154_RET_TIMEOUT notification.
 *
 * Frames received during the delayed reception window are notified with the same function as
 * any other received frames: @ref nrf_802154_receive_done with the @ref NRF_802154_RET_SUCCESS
 * status code. After a frame is received, the reception window is kept open.
 *
 * A scheduled reception can be cancelled by a call to @ref nrf_802154_receive_at_cancel.
 *
 * Before termination of ongoing reception window with a radio state change request function or
 * with any asynchronous radio operation, the reception procedure must be cancelled by a call to
 * @ref nrf_802154_receive_at_cancel.
 *
 * @param[in]  time       Absolute target time when the reception procedure is requested to start,
 *                        in microseconds (us).
 * @param[in]  timeout    Reception timeout (counted from @p time), in microseconds (us).
 * @param[in]  p_metadata Metadata describing delayed reception request. If NULL the default
 *                        metadata like created with @ref nrf_802154_receive_at_metadata_init are
 *                        used.
 *
 * @retval  NRF_802154_RET_SUCCESS   The reception procedure is scheduled.
 */
nrf_802154_ret_t nrf_802154_receive_at(uint32_t                                 time,
                                       uint32_t                                 timeout,
                                       const nrf_802154_receive_at_metadata_t * p_metadata);

/**
 * @brief Structure with delayed reception cancellation request metadata.
 */
typedef struct
{
} nrf_802154_receive_at_cancel_metadata_t;

/**
 * @brief Initialize the delayed reception cancellation request metadata to default values.
 */
static inline void nrf_802154_receive_at_cancel_metadata_init(
        nrf_802154_receive_at_cancel_metadata_t * p_metadata)
{
    // Intentionally empty
}

/**
 * @brief Cancel a delayed reception scheduled by a call to @ref nrf_802154_receive_at.
 *
 * If the receive window has been scheduled but has not started yet, this function prevents
 * entering the receive window. If the receive window has been scheduled and has already started,
 * the radio remains in the receive state, but a window timeout will not be reported.
 *
 * @param[in]  p_metadata  Metadata describing the request. If NULL the default metadata like
 *                         created with @ref nrf_802154_receive_at_cancel_metadata_init are used.
 *
 * @retval  NRF_802154_RET_SUCCESS   The delayed reception was scheduled and successfully cancelled.
 * @retval  NRF_802154_RET_NOT_FOUND No delayed reception was scheduled.
 */
nrf_802154_ret_t nrf_802154_receive_at_cancel(
        const nrf_802154_receive_at_cancel_metadata_t * p_metadata);

/**
 * @brief Structure with delayed transmission request metadata.
 */
typedef struct
{
    void  * p_context;    // !< User-defined context copied to @ref nrf_802154_transmit_done_metadata_t.
    uint8_t tx_procedure; // !< Selected transmission procedure.
    uint8_t channel;      // !< Channel at which requested transmission shall be performed. If set to @ref NRF_802154_INVALID_CHANNEL, the channel configured with @ref nrf_802154_cfg_set function lately is used.
    int8_t  tx_power;     // !< Transmission power to be used for the requested transmission operation. If set to @ref NRF_802154_INVALID_POWER, the transmission power configured with @ref nrf_802154_cfg_set function lately is used.
} nrf_802154_transmit_at_metadata_t;

/**
 * @brief Initialize the delayed transmission request metadata to default values.
 */
static inline void nrf_802154_transmit_at_metadata_init(
        nrf_802154_transmit_at_metadata_t * p_metadata)
{
    p_metadata->p_context    = NULL;
    p_metadata->tx_procedure = NRF_802154_TX_PROCEDURE_CCA;
    p_metadata->channel      = NRF_802154_INVALID_CHANNEL;
    p_metadata->tx_power     = NRF_802154_INVALID_POWER;
}

/**
 * @brief Request transmission at the specified time.
 *
 * This function works as a delayed version of @ref nrf_802154_transmit. It is asynchronous.
 * Only one delayed transmission can be scheduled at a time. To modify parameters of the scheduled
 * delayed transmission, cancel it with @ref nrf_802154_transmit_at_cancel and request it again
 * with new parameters.
 *
 * The set of supported TX procedures is limited to @ref NRF_802154_TX_PROCEDURE_SIMPLE and
 * @ref NRF_802154_TX_PROCEDURE_CCA.
 *
 * This function is designed to transmit the first symbol of SHR at the given time.
 *
 * If the transmission cannot be started at the specified time, the @nrf_802154_transmit_done
 * function is called with @ref NRF_802154_RET_TIMESLOT_DENIED status code.
 * There is no notification when the transmission starts. Status of the finished transmission
 * procedure is notified like any other transmission procedure with @ref nrf_802154_transmit_done.
 *
 * After finished transmission procedure, the radio enters the receive state.
 *
 * A scheduled transmission can be cancelled by a call to @ref nrf_802154_transmit_at_cancel.
 *
 * @param[in]  p_data     Pointer to the array with the payload of data to transmit. The array
 *                        should exclude PHR or FCS fields of the 802.15.4 frame.
 * @param[in]  length     Length of the given frame. This value must exclude PHR and FCS fields
 *                        from the given frame (exact size of buffer pointed to by @p p_data).
 * @param[in]  time       Absolute target time when the transmission procedure is requested to
 *                        start, in microseconds (us). The first symbol of the preamble starts
 *                        transmission at requested time.
 * @param[in]  p_metadata Metadata describing the transmission procedure. If NULL the default
 *                        metadata like created with @ref nrf_802154_transmit_at_metadata_init are
 *                        used.
 *
 * @retval  NRF_802154_RET_SUCCESS        The transmission procedure was scheduled.
 * @retval  NRF_802154_RET_INVALID_PARAM  @p one of the parameters contains invalid value.
 */
nrf_802154_ret_t nrf_802154_transmit_at(const uint8_t                           * p_data,
                                        uint32_t                                  length,
                                        uint32_t                                  time,
                                        const nrf_802154_transmit_at_metadata_t * p_metadata);

/**
 * @brief Structure with delayed transmission cancellation request metadata.
 */
typedef struct
{
} nrf_802154_transmit_at_cancel_metadata_t;

/**
 * @brief Initialize the delayed transmission canellation request metadata to default values.
 */
static inline void nrf_802154_transmit_at_cancel_metadata_init(
        nrf_802154_transmit_at_cancel_metadata_t * p_metadata)
{
    // Intentionally empty
}

/**
 * @brief Cancel a delayed transmission scheduled by a call to @ref nrf_802154_transmit_at.
 *
 * If a delayed transmission has been scheduled but the transmission has not been started yet,
 * a call to this function prevents the transmission. If the transmission is ongoing,
 * it will not be aborted.
 *
 * If a delayed transmission has not been scheduled (or has already finished), this function does
 * not change state and returns @ref NRF_802154_RET_NOT_FOUND.
 *
 * @param[in]  p_metadata  Metadata describing the request. If NULL the default metadata like
 *                         created with @ref nrf_802154_transmit_at_cancel_metadata_init are used.
 *
 * @retval  NRF_802154_RET_SUCCESS    The delayed transmission was scheduled and successfully
 *                                    cancelled.
 * @retval  NRF_802154_RET_NOT_FOUND  No delayed transmission was scheduled.
 */
nrf_802154_ret_t nrf_802154_transmit_at_cancel(const nrf_802154_transmit_at_cancel_metadata_t * p_metadata);

/**
 * @}
 * @defgroup nrf_802154_memman Driver memory management
 * @{
 */

/**
 * @brief Allocate a buffer in the radio controller buffer pool.
 *
 * The buffer allocated with this buffer has reference counter equal to 1. To free this buffer
 * the reference counter must be decremented to 0 with @ref nrf_802154_buffer_ref_dec. The
 * reference counter may be decremented right after the transmission procedure was requested,
 * because the transmission procedure internally increments the reference counter for the duration
 * of the transmission procedure.
 *
 * The radio driver can transmit frames using any buffer passed to the transmission request
 * functions. However, to perform zero-copy transmission, a buffer allocated with this function
 * must be used.
 *
 * @return  Pointer to an allocated transmission buffer or NULL if no buffers are available.
 */
uint8_t * nrf_802154_buffer_get(void);

/**
 * @brief Increment the reference counter of the given buffer.
 *
 * The reference counter of one of the buffers managed by this library may be incremented to
 * prevent releasing the buffer. The released buffer could be reused and modified by other
 * operations managed by this library.
 *
 * Typical scenario to use this function is when the radio controller reports a received frame with
 * the @ref nrf_802154_receive_done function passing a buffer as one of the parameters. To perform
 * zero-copy frame handling out of the @ref nrf_802154_receive_done function and prevent the library
 * from releasing the buffer right after the @ref nrf_802154_receive_done function is finished,
 * the function must call @ref nrf_802154_buffer_ref_inc. When handling of the frame is finished in
 * another context, the reference counter must be decremented with @ref nrf_802154_buffer_ref_dec to
 * release the buffer. 
 *
 * @note Call to this function must be followed by a single call to the 
 *       @ref nrf_802154_buffer_ref_dec with the same parameter.
 *
 * @param[in]  p_data  Pointer to the buffer connected with the reference counter to be incremented.
 *
 * @retval NRF_802154_RET_SUCCESS        Buffer reference counter incremented.
 * @retval NRF_802154_RET_INVALID_PARAM  @p p_data does not point to an allocated memory buffer.
 */
nrf_802154_ret_t nrf_802154_buffer_ref_inc(const uint8_t * p_data);

/**
 * @brief Decrement the reference counter of the given buffer.
 *
 * The reference counter of one of the buffers managed by this library may be decremented to
 * indicate that the buffer is not used by external entities anymore.
 *
 * When the reference counter is decremented to 0, the buffer is released and may be acquired for
 * other operations by any module. After call to this function the buffer must not be modified by
 * the caller and the @p p_data pointer must be considered as invalid.
 *
 * @note Call to this function must be preceded by a call to the @ref nrf_802154_buffer_ref_inc
 *       function with the same parameter.
 *
 * @param[in]  p_data  Pointer to the buffer connected with the reference counter to be decremented.
 *
 * @retval NRF_802154_RET_SUCCESS        Buffer reference counter decremented.
 * @retval NRF_802154_RET_INVALID_PARAM  @p p_data does not point to an allocated memory buffer.
 */
nrf_802154_ret_t nrf_802154_buffer_ref_dec(const uint8_t * p_data);


/**
 * @}
 * @defgroup nrf_802154_autoack Auto ACK management
 * @{
 */

/**
 * @brief Structure describing data included to the ACK frames.
 */
typedef struct
{
    nrf_802154_ack_data_t data_type;  // !< Type of data. Refer to the @ref nrf_802154_ack_data_t type.

    const void * p_data;              // !< Pointer to the buffer containing data to be set.
    uint32_t     length;              // !< Length of @p p_data in bytes.
} nrf_802154_ack_data_metadata_t;

/**
 * @brief Set @ref nrf_802154_ack_data_metadata_t to default values.
 */
static inline nrf_802154_ack_data_metadata_init(nrf_802154_ack_data_metadata_t * p_metadata)
{
    p_metadata->data_type = NRF_802154_ACK_DATA_PENDING_BIT;
    p_metadata->p_data    = NULL;
    p_metadata->length    = 0;
}

/**
 * @brief Add the address of a peer node for which the provided ACK data is to be added to the list.
 *
 * The ACK frames in the 802.15.4 protocol contain additional data like the Pending Bit field or
 * Information Elements. This function allows the higher layer to prepare data used in
 * automatically sent ACKs.
 *
 * The data provided by this function is copied to the internal storage of this library. The number
 * of entries in the internal storage is defined by @ref NRF_802154_PENDING_SHORT_ADDRESSES and
 * @ref NRF_802154_PENDING_EXTENDED_ADDRESSES constants. The size of buffers for Information
 * Elements is defined by @ref NRF_802154_MAX_ACK_IE_SIZE.
 *
 * The pending bit list works differently, depending on the selected algorithm.
 * For more information, see @ref NRF_802154_CFG_PAR_ACK_PB_METHOD.
 * The method can be set during the initialization phase by calling @ref nrf_802154_cfg_set.
 *
 * @param[in]  addr_type  The type of given address. This field indicates length of the @p p_addr
 *                        buffer.
 * @param[in]  p_addr     Pointer to the memory buffer containing the peer address (little-endian).
 * @param[in]  p_metadata Metadata describing the data included to the ACK frame. If NULL the
 *                        default metadata like created with @ref nrf_802154_ack_data_metadata_init
 *                        is used.
 *
 * @retval NRF_802154_RET_SUCCESS        Address successfully added to the list.
 * @retval NRF_802154_RET_INVALID_PARAM  At least one of the parameters contains an invalid value.
 * @retval NRF_802154_RET_NO_MEM         Not enough memory to store this address in the list.
 */
nrf_802154_ret_t nrf_802154_ack_data_add(nrf_802154_addr_type_t                 addr_type,
                                         const uint8_t                        * p_addr,
                                         const nrf_802154_ack_data_metadata_t * p_metadata);

/**
 * @brief Remove the address of a peer node for which the ACK data is set from the list.
 *
 * @p p_metadata->data_type must match type of data to be removed. Other fields from
 * the @p p_metadata structure are ignored.
 *
 * The ACK data that was previously set for the given address is automatically removed.
 *
 * @param[in]  addr_type  The type of given address. This field indicates length of the @p p_addr
 *                        buffer.
 * @param[in]  p_addr     Pointer to the memory buffer containing the peer address (little-endian).
 * @param[in]  p_metadata Metadata describing the data included to the ACK frame. If NULL the
 *                        default metadata like created with @ref nrf_802154_ack_data_metadata_init
 *                        is used.
 *
 * @retval NRF_802154_RET_SUCCESS        Address removed from the list.
 * @retval NRF_802154_RET_NOT_FOUND      Address not found in the list.
 * @retval NRF_802154_RET_INVALID_PARAM  At least one of the parameters contains an invalid value.
 */
nrf_802154_ret_t nrf_802154_ack_data_remove(nrf_802154_addr_type_t                 addr_type,
                                            const uint8_t                        * p_addr,
                                            const nrf_802154_ack_data_metadata_t * p_metadata);

/**
 * @brief Remove all addresses of a given type from the ACK data list.
 *
 * @p p_metadata->data_type must match type of data to be removed. Other fields from
 * the @p p_metadata structure are ignored.
 *
 * The ACK data that was previously set for the given address is automatically removed.
 *
 * @param[in]  addr_type  Type of addresses the function is to remove.
 * @param[in]  p_metadata Metadata describing the data included to the ACK frame. If NULL the
 *                        default metadata like created with @ref nrf_802154_ack_data_metadata_init
 *                        is used.
 *
 * @retval NRF_802154_RET_SUCCESS        Addresses removed from the list.
 * @retval NRF_802154_RET_INVALID_PARAM  At least one of the parameters contains an invalid value.
 */
nrf_802154_ret_t nrf_802154_ack_data_remove_all(nrf_802154_addr_type_t                 addr_type,
                                                const nrf_802154_ack_data_metadata_t * p_metadata);

/**
 * @}
 * @defgroup nrf_802154_stats Statistics and measurements.
 * @{
 */

/**
 * @brief Structure describing statistics getter metadata.
 */
typedef struct
{
} nrf_802154_stats_get_metadata_t;

/**
 * @brief Set @ref nrf_802154_stats_get_metadata_t to default values.
 */
static inline nrf_802154_stats_get_metadata_init(nrf_802154_stats_get_metadata_t * p_metadata)
{
    // Intentionally empty
}

/**
 * @brief Structure describing statistics subtraction metadata.
 */
typedef struct
{
} nrf_802154_stats_subtract_metadata_t;

/**
 * @brief Set @ref nrf_802154_stats_subtract_metadata_t to default values.
 */
static inline nrf_802154_stats_subtract_metadata_init(
        nrf_802154_stats_subtract_metadata_t * p_metadata)
{
    // Intentionally empty
}

/**
 * @brief Structure describing statistics reset metadata.
 */
typedef struct
{
} nrf_802154_stats_reset_metadata_t;

/**
 * @brief Set @ref nrf_802154_stats_reset_metadata_t to default values.
 */
static inline nrf_802154_stats_reset_metadata_init(nrf_802154_stats_reset_metadata_t * p_metadata)
{
    // Intentionally empty
}


/**
 * @brief Get current statistics.
 *
 * @param[out] p_stats    Structure that will be filled with current stats values.
 * @param[in]  p_metadata Optional metadata. If NULL, the default metadata like created with
 *                        @ref nrf_802154_stats_get_metadata_init is used.
 */
void nrf_802154_stats_get(nrf_802154_stats_t                    * p_stats,
                          const nrf_802154_stats_get_metadata_t * p_metadata);

/**
 * @brief Get current statistics.
 *
 * @note This returns part of information returned by @ref nrf_802154_stats_get
 *
 * @param[out] p_stat_counters    Structure that will be filled with current stats counter values.
 * @param[in]  p_metadata         Optional metadata. If NULL, the default metadata like created with
 *                                @ref nrf_802154_stats_get_metadata_init is used.
 */
void nrf_802154_stat_counters_get(nrf_802154_stat_counters_t            * p_stat_counters,
                                  const nrf_802154_stats_get_metadata_t * p_metadata);

/**
 * @brief Decrease current statistic counter values by the provided ones.
 *
 * This function is intended to be called together with @ref nrf_802154_stats_get
 * to avoid missing any counted events.
 *
 * @param[in] p_stat_counters Current stat counter values will be decreased by values provided
 *                            behind this pointer.
 * @param[in] p_metadata      Optional metadata. If NULL, the default metadata like created with
 *                            @ref nrf_802154_stats_subtract_metadata_init is used.
 */
void nrf_802154_stat_counters_subtract(const nrf_802154_stat_counters_t           * p_stat_counters,
                                       const nrf_802154_stats_subtract_metadata_t * p_metadata);

/**
 * @brief Get time stamps of events gathered by the last operation.
 *
 * @param[out] p_stat_timestamps Structure that will be filled with current time stamps of events.
 * @param[in]  p_metadata        Optional metadata. If NULL, the default metadata like created with
 *                               @ref nrf_802154_stats_get_metadata_init is used.
 */
void nrf_802154_stat_timestamps_get(nrf_802154_stat_timestamps_t          * p_stat_timestamps,
                                    const nrf_802154_stats_get_metadata_t * p_metadata);

/**
 * @brief Reset current stat counters to 0.
 *
 * @note @ref nrf_802154_stat_counters_get and @ref nrf_802154_stat_counters_reset may lead to
 *       missing events if an counted event occurs between these calls. Use
 *       @ref nrf_802154_stat_counters_subtract to avoid such condition if necessary.
 *
 * @param[in]  p_metadata  Optional metadata. If NULL, the default metadata like created with
 *                         @ref nrf_802154_stats_reset_metadata_init is used.
 */
void nrf_802154_stat_counters_reset(const nrf_802154_stats_reset_metadata_t * p_metadata);

/**
 * @brief Get total times spent in certain states.
 *
 * @param[out] p_stat_totals Structure that will be filled with times spent in certain states
 *                           until now.
 * @param[in]  p_metadata    Optional metadata. If NULL, the default metadata like created with
 *                           @ref nrf_802154_stats_get_metadata_init is used.
 */
void nrf_802154_stat_totals_get(nrf_802154_stat_totals_t              * p_stat_totals,
                                const nrf_802154_stats_get_metadata_t * p_metadata);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* NRF_802154_H_ */

/** @} */
