#
# Copyright (c) 2020 - 2021, Nordic Semiconductor ASA.
# All Rights Reserved.
#
# The information contained herein is confidential property of Nordic Semiconductor ASA.
# The use, copying, transfer or disclosure of such information is prohibited except by
# express written agreement with Nordic Semiconductor ASA.
#

include($ENV{ZEPHYR_BASE}/../nrf/cmake/boilerplate.cmake)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)

# Set paths to include directories
set(nrfx_root $ENV{ZEPHYR_BASE}/../modules/hal/nordic/nrfx)
set(nrf_radio_802154_root $ENV{ZEPHYR_BASE}/../modules/hal/nordic/drivers/nrf_radio_802154)
