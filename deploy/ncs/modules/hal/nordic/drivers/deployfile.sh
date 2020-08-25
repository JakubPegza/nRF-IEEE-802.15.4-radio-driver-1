#!/bin/bash

echo "${SOURCE_ROOT_DIR:?}" > /dev/null

rm -fr "${DEPLOY_TARGET_CURR_DIR}/nrf_radio_802154"
mkdir -p "${DEPLOY_TARGET_CURR_DIR}/nrf_radio_802154" || exit -1

cp -v -R "${SOURCE_ROOT_DIR}/src" "${DEPLOY_TARGET_CURR_DIR}/nrf_radio_802154" || exit -1

# Note: Patching of ${DEPLOY_TARGET_CURR_DIR}/CMakeList.txt or Kconfig possible here