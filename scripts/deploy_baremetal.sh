#!/bin/bash

curr_dir="${PWD}"
script_dir=$(dirname "$0")
source_dir=$(realpath "${script_dir}/..")

# Defaults
export DEPLOY_SOURCE_ROOT_DIR="${source_dir}/deploy/baremetal"
export SOURCE_ROOT_DIR="${source_dir}"

# Parse options possibly overriding defaults
while [[ $# -gt 0 ]]; do
    case "$1" in
        -D*)
            re='-D(.+)=(.+)'
            if [[ ! "$1" =~ $re ]] ; then
                echo "Error: Internal error when parsing -D"
                exit -1
            fi
            vname="${BASH_REMATCH[1]}"
            value="${BASH_REMATCH[2]}"
            eval "export ${vname}"="${value}"
            ;;

        *)
            echo "Unrecognized command line option '$1'"
            exit -1
            ;;
    esac
    shift
done

# Let's check if user passed necessary arguments
echo "${DEPLOY_TARGET_ROOT_DIR:?}" > /dev/null

# This will do most of the job, please see deployfile.sh scripts
echo "Running ${script_dir}/deploy.sh"
if ! ${script_dir}/deploy.sh; then
    echo "Error '${script_dir}/deploy.sh' failed"
    exit -1
fi
