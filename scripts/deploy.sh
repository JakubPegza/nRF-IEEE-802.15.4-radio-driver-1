#!/bin/bash

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
echo "${DEPLOY_SOURCE_ROOT_DIR:?}" > /dev/null

# ------------------------------------------------------------------------
# Helper functions

copy_files_recursive()
{
    for f in $(find "$1" -type f -name "$2" -printf "%P\n"); do
        src="$1/${f}"
        dst="$3/${f}"

        mkdir -p $(dirname "${dst}")
        cp -v "${src}" "${dst}" || exit -1
    done
}
export -f copy_files_recursive

copy_files()
{
    for f in $(find "$1" -type f -name "$2" -maxdepth 1 -printf "%P\n"); do
        src="$1/${f}"
        dst="$3/${f}"

        mkdir -p $(dirname "${dst}")
        cp -v "${src}" "${dst}" || exit -1
    done
}
export -f copy_files

# ------------------------------------------------------------------------
# Process DEPLOY_SOURCE_ROOT_DIR
for f in $(find "${DEPLOY_SOURCE_ROOT_DIR}"); do
    # Let's make target name based on f (from deploy-source dir) in target tree
    export DEPLOY_RELA=$(realpath --relative-to="${DEPLOY_SOURCE_ROOT_DIR}" "${f}")
    target="${DEPLOY_TARGET_ROOT_DIR}"/"${DEPLOY_RELA}"

    if [ -d "${f}" ]; then
        # This is a directory. Try to run deployfile.sh script if it's inside the directory.
        if [ -f "${f}/deployfile.sh" ]; then

            export DEPLOY_SOURCE_CURR_DIR="${DEPLOY_SOURCE_ROOT_DIR}/${DEPLOY_RELA}"
            export DEPLOY_TARGET_CURR_DIR="${DEPLOY_TARGET_ROOT_DIR}/${DEPLOY_RELA}"

            echo "Running deployfile '${f}/deployfile.sh'"
            if "${f}/deployfile.sh"; then
                echo "Done deployfile '${f}/deployfile.sh'"
            else
                echo "Error: deployfile '${f}/deployfile.sh' failed"
                exit -1
            fi
        fi
        # Let's create corresponding directory in target tree.
        mkdir -v -p "${target}" || exit -1

    elif [ $(basename "${f}") = 'deployfile.sh' ]; then
        # This is a deployfile.sh file itself, we run this file when we encountered directory.
        # We don't copy it to target tree.
        :
    else
        # It is a file, copy to target tree.
        cp -v "${f}" "${target}"
    fi
done
