//
// Copyright (c) 2020 Nordic Semiconductor ASA. All Rights Reserved.
//
// The information contained herein is confidential property of Nordic Semiconductor ASA.
// The use, copying, transfer or disclosure of such information is prohibited except by
// express written agreement with Nordic Semiconductor ASA.
//

@Library("CI_LIB") _

HashMap CI_STATE = lib_State.getConfig(JOB_NAME)

properties(
  lib_State.getTriggers()
)

pipeline {
    parameters {
        string(name: 'jsonstr_CI_STATE', description: 'Default State if no upstream job', defaultValue: CI_STATE.CFG.INPUT_STATE_STR)
        string(name: 'nrfx_refspec', description: 'Git refspec of nrfx used in unit tests', defaultValue: 'v2.3.0')
        choice(name: 'TEST_CYCLE', description: 'Test Phase', choices: CI_STATE.CFG.CRON_CHOICES)
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
        stage('Build and host tests') {
            when {
                expression { params.TEST_CYCLE == 'COMMIT'}
            }
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
                                sh 'PATH=${WORKSPACE}/uncrustify-uncrustify-0.69.0/build:$PATH scripts/pretty.sh check'
                            }
                        }
                    }
                }
                stage('Unit tests') {
                    stages{
                        stage('Install ceedling') {
                            steps {
                                sh '''
                                    export PATH=/home/.gem/ruby/2.7.0/bin:$PATH
                                    gem install --user-install ceedling
                                '''
                            }
                        }
                        stage('Checkout dependencies') {
                            steps {
                                dir('sl') {
                                    checkout_refspec('master', 'https://projecttools.nordicsemi.no/bitbucket/scm/krknwk/nrf-802.15.4-sl.git')
                                }
                                dir('nrfx') {
                                    checkout_refspec(nrfx_refspec, 'https://github.com/NordicSemiconductor/nrfx')
                                }
                            }
                        }
                        stage('Run tests') {
                            steps {
                                // TODO: Uncomment when dependencies support nRF53
                                //sh 'PATH=/home/.gem/ruby/2.7.0/bin:$PATH SL_PATH=sl NRFX_PATH=nrfx ceedling options:nrf5340 test:all'
                                //sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf5340.xml'

                                sh 'PATH=/home/.gem/ruby/2.7.0/bin:$PATH SL_PATH=sl NRFX_PATH=nrfx ceedling options:nrf52840 test:all'
                                sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf52840.xml'

                                sh 'PATH=/home/.gem/ruby/2.7.0/bin:$PATH SL_PATH=sl NRFX_PATH=nrfx ceedling options:nrf52833 test:all'
                                sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf52833.xml'

                                sh 'PATH=/home/.gem/ruby/2.7.0/bin:$PATH SL_PATH=sl NRFX_PATH=nrfx ceedling options:nrf52820 test:all'
                                sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf52820.xml'

                                sh 'PATH=/home/.gem/ruby/2.7.0/bin:$PATH SL_PATH=sl NRFX_PATH=nrfx ceedling options:nrf52811 test:all'
                                sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf52811.xml'
                            }
                            post {
                                always {
                                    xunit tools: [Custom(customXSL: 'test/unit_tests/unity.xsl', pattern: 'build/artifacts/test/report*.xml', skipNoTestFiles: false, stopProcessingIfError: true)]
                                }
                            }
                        }
                    }
                }
            }
        }
        stage('Target tests') {
            steps {
                build job: '/latest/test-fw-nrfconnect-rs_drv154_integration/master', parameters: [
                    string(name: 'NRF_802154_RADIO_DRIVER_REFSPEC', value: lib_State.getGitRef('NRF802154', CI_STATE)),
                    string(name: 'NRF_802154_SL_REFSPEC', value: 'master'),
                    string(name: 'NRF_802154_SERIALIZATION_REFSPEC', value: 'master'),
                    string(name: 'TEST_APPS_REFSPEC', value: 'master'),
                    string(name: 'TEST_CYCLE', value: CI_STATE.ORIGIN.TEST_CYCLE)
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

def checkout_refspec(String refspec, String url) {
    checkout([$class: 'GitSCM',
        branches: [[name: 'FETCH_HEAD']],
        doGenerateSubmoduleConfigurations: false,
        userRemoteConfigs: [[
            refspec: "${refspec}",
            credentialsId: 'buran_ci',
            url: "${url}"
        ]]
    ])
}
