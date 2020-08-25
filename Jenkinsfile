//
// Copyright (c) 2020 Nordic Semiconductor ASA. All Rights Reserved.
//
// The information contained herein is confidential property of Nordic Semiconductor ASA.
// The use, copying, transfer or disclosure of such information is prohibited except by
// express written agreement with Nordic Semiconductor ASA.
//

@Library("CI_LIB") _

HashMap CI_STATE = lib_State.getConfig(JOB_NAME)

pipeline {

    parameters {
        string(name: 'jsonstr_CI_STATE', description: 'Default State if no upstream job', defaultValue: CI_STATE.CFG.INPUT_STATE_STR)
        string(name: 'nrfx_refspec', description: 'Git refspec of nrfx used in unit tests', defaultValue: 'v2.3.0')
    }

    environment {
        SWDEV_PASS=credentials('swdev_build_password')
    }

    agent {
        docker {
            label CI_STATE.CFG.AGENT_LABELS
            image "$CI_STATE.CFG.DOCKER_REG/$CI_STATE.CFG.IMAGE_TAG"
        }
    }

    stages {
        stage('Load') {
            steps {
                script {
                    CI_STATE = lib_State.load('NRF802154', CI_STATE)
                }
            }
        }
        stage('Wipe-out workspace') {
            steps {
                echo "Wiping-out workspace on node: ${NODE_NAME}"
                sh 'find . -name . -o -prune -exec rm -rf -- {} +'
            }
        }
        stage('Checkout') {
            steps {
                checkout_repo(CI_STATE, 'nrf802154')
            }
        }
        stage('Build and host tests') {
            parallel {
                stage('Check pretty') {
                    stages{
                        stage('Install uncrustify') {
                            steps {
                                sh '''
                                    wget https://github.com/uncrustify/uncrustify/archive/uncrustify-0.69.0.tar.gz
                                    tar xzf uncrustify-0.69.0.tar.gz
                                    cd uncrustify-uncrustify-0.69.0
                                    mkdir build
                                    cd build
                                    cmake .. -DCMAKE_BUILD_TYPE=Release
                                    make -j
                                    export PATH=$PWD:$PATH
                                    cd ../..
                                    uncrustify --version
                                '''
                            }
                        }
                        stage('Check Radio Driver style') {
                            steps {
                                dir('nrf802154') {
                                    sh 'PATH=${WORKSPACE}/uncrustify-uncrustify-0.69.0/build:$PATH scripts/pretty.sh check'
                                }
                            }
                        }
                    }
                }
                stage('Unit tests') {
                    stages{
                        stage('Install ceedling') {
                            steps {
                                sh '''
                                    export PATH=/home/.gem/ruby/2.5.0/bin:$PATH
                                    gem install --user-install ceedling
                                    ceedling version
                                '''
                            }
                        }
                        stage('Checkout dependencies') {
                            steps {
                                dir('sl') {
                                    checkout_refspec('master', 'ssh://git@bitbucket.nordicsemi.no:7999/krknwk/nrf-802.15.4-sl.git')
                                }
                                dir('nrfx') {
                                    checkout_refspec(nrfx_refspec, 'ssh://git@bitbucket.nordicsemi.no:7999/nrffosdk/nrfx.git')
                                }
                            }
                        }
                        stage('Run tests') {
                            steps {
                                dir('nrf802154') {
                                    sh 'PATH=/home/.gem/ruby/2.5.0/bin:$PATH SL_PATH=../sl NRFX_PATH=../nrfx ceedling options:nrf52840 test:all'
                                    sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf52840.xml'

                                    sh 'PATH=/home/.gem/ruby/2.5.0/bin:$PATH SL_PATH=../sl NRFX_PATH=../nrfx ceedling options:nrf52833 test:all'
                                    sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf52833.xml'

                                    sh 'PATH=/home/.gem/ruby/2.5.0/bin:$PATH SL_PATH=../sl NRFX_PATH=../nrfx ceedling options:nrf52820 test:all'
                                    sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf52820.xml'

                                    sh 'PATH=/home/.gem/ruby/2.5.0/bin:$PATH SL_PATH=../sl NRFX_PATH=../nrfx ceedling options:nrf52811 test:all'
                                    sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf52811.xml'
                                }
                            }
                            post {
                                always {
                                    xunit tools: [Custom(customXSL: 'nrf802154/test/unit_tests/unity.xsl', pattern: 'nrf802154/build/artifacts/test/report*.xml', skipNoTestFiles: false, stopProcessingIfError: true)]
                                }
                            }
                        }
                    }
                }
            }
        }
        stage('Target tests') {
            steps {
                build job: '/latest/test-fw-nrfconnect-rs/master', parameters: [
                    string(name: 'NRF_802154_RADIO_DRIVER_REFSPEC', value: lib_State.getGitRef('NRF802154', CI_STATE)),
                    string(name: 'NRF_802154_SL_REFSPEC', value: 'master'),
                    string(name: 'TEST_APPS_REFSPEC', value: 'master'),
                    string(name: 'TEST_CYCLE', value: 'COMMIT')
                ]
            }
        }
    }
    post {
        cleanup {
            script {
                cleanWs()
            }
        }
    }
}

// TODO: Revmoe this function when lib_Main.checkoutRepo() supports submodules
def checkout_refspec(String refspec, String url) {
    checkout([$class: 'GitSCM',
        branches: [[name: 'FETCH_HEAD']],
        doGenerateSubmoduleConfigurations: false,
        extensions: [[$class: 'SubmoduleOption',
            disableSubmodules: false,
            parentCredentials: true,
            recursiveSubmodules: true,
            reference: '',
            shallow: false,
            trackingSubmodules: false
        ]],
        submoduleCfg: [],
        userRemoteConfigs: [[
            refspec: "${refspec}",
            credentialsId: 'swdev_build-ssh-priv-key',
            url: "${url}"
        ]]
    ])
}

def checkout_repo(HashMap CI_STATE, String subdir) {
    refspec=lib_State.getGitRef('NRF802154', CI_STATE)
    echo "Checking-out ${CI_STATE.SELF.GIT_URL}:${refspec} on node: ${NODE_NAME}"

    // TODO: Use lib_Main checkout if it supports submodules
    //return lib_Main.checkoutRepo( CI_STATE.SELF.GIT_URL, subdir, CI_STATE.SELF, true )
    dir(subdir) {
        checkout_refspec(refspec, 'ssh://git@bitbucket.nordicsemi.no:7999/krknwk/nrf-802.15.4-driver.git')
    }
}
