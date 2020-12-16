#!/bin/bash

echo "${SOURCE_ROOT_DIR:?}" > /dev/null

if [ ! -d "${DEPLOY_TARGET_CURR_DIR}/samples/boards/nrf/ieee802154/802154_rpmsg" ] ; then
    patch -d "${DEPLOY_TARGET_CURR_DIR}" -p1 < "${SOURCE_ROOT_DIR}/deploy/ncs/zephyr/serialization-sample.patch"
fi
