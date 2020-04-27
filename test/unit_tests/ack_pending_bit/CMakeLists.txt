#
# Copyright (c) 2020 Nordic Semiconductor ASA. All Rights Reserved.
#
# The information contained herein is confidential property of Nordic Semiconductor ASA.
# The use, copying, transfer or disclosure of such information is prohibited except by
# express written agreement with Nordic Semiconductor ASA.
#

cmake_minimum_required(VERSION 3.13.1)

include(${CMAKE_CURRENT_LIST_DIR}/../unit_test_boilerplate.cmake)
project(nrf_802154_ack_data_pending_bit_unit_test)

# Generate Unity runner for the test
test_runner_generate(unity_test.c)

# Create mocks for dependencies of the module being unit tested
cmock_handle(${nrf_radio_802154_root}/src/mac_features/nrf_802154_frame_parser.h)

# Trick nrfx that the platform is nRRF52840
target_compile_definitions(app PRIVATE NRF52840_XXAA)

# Set unit test compilation flag
target_compile_definitions(app PRIVATE UNIT_TEST)

# Include dependencies
target_include_directories(app PRIVATE ./../)
target_include_directories(app PRIVATE ${nrfx_root}/mdk)
target_include_directories(app PRIVATE ${nrf_radio_802154_root}/src)
target_include_directories(app PRIVATE ${nrf_radio_802154_root}/src/mac_features/ack_generator)

# Add the test file
target_sources(app PRIVATE unity_test.c)
