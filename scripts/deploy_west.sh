#!/bin/bash

# Paths
script_dir=$(realpath $(dirname "$0"))
source_dir=$(realpath "${script_dir}/..")

args=()
while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
        -h|--help)
        echo "Script for deploying 802.15.4 Radio Driver into NCS."
        echo "The script will copy necessary files and apply changes to NCS"
        echo ""
        echo "required arguments:"
        echo "NCS_PATH   path to the NCS installation, should contain nrf/west.yml"
        exit 0
        ;;
        *)    # unknown option
        args+=("$1")
        shift
        ;;
    esac
done

# Check number of arguments
if [ ${#args[*]} -gt 1 ]; then
    echo "Warning: too many arguments. Additional arguments will be ignored"
fi

if [ ${#args[*]} -eq 0 ]; then
    echo "Error: please specify NCS path."
    exit -1
fi

ncs_path_raw=${args[0]}

# Get NCS deploy path
if [ ! -d ${ncs_path_raw} ]; then
    echo "Error: path ${ncs_path_raw} does not exist."
    exit -1
else
    if [ ! -f ${ncs_path_raw}/nrf/west.yml ]; then
        echo "Error: path $(realpath "${ncs_path_raw}") does not seem to contain an NCS installation."
        exit -1
    else
        export DEPLOY_TARGET_ROOT_DIR=$(realpath "${ncs_path_raw}")
    fi
fi

cd $source_dir

# Deploy Radio Driver
${script_dir}/deploy_ncs.sh