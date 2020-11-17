#!/bin/bash

echo "${SOURCE_ROOT_DIR:?}" > /dev/null

if ! grep "802154_rpmsg" "${DEPLOY_TARGET_CURR_DIR}/samples/CMakeLists.txt" ; then
    patch -d "${DEPLOY_TARGET_CURR_DIR}" -p1 < "${SOURCE_ROOT_DIR}/deploy/ncs/nrf/child-image.patch"
fi
