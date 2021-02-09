//
// Copyright (c) 2020 - 2021, Nordic Semiconductor ASA.
// All Rights Reserved.
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
DOWNSTREAM_TEST_JOB_LINK = '/latest/test-fw-nrfconnect-rs_drv154_integration/'

pipeline {
    parameters {
        separator(name: "BUILD_ENVIRONMENT", sectionHeader: "Build Environment",
			separatorStyle: "border-width: 0",
			sectionHeaderStyle: """
				background-color: #7ea6d3;
				text-align: center;
				padding: 4px;
				color: #343434;
				font-size: 22px;
				font-weight: normal;
				text-transform: uppercase;
				font-family: 'Orienta', sans-serif;
				letter-spacing: 1px;
				font-style: italic;
			"""
		)
        booleanParam(name: 'BUILD_AND_DEPLOY_USING_ONLY_WEST_MANIFEST_IN_TEST_APPS', defaultValue: false,
               description: "Build will be deployed only base on defaults in west.yml manifest file that is in below test_apps_ncs branch/refspec")
        string(name: 'TEST_APPS_REFSPEC', defaultValue: "master",
               description: 'Branch of nrf-802.15.4-test-apps-ncs to use.')
        separator(name: "BUILD PARAMETER WITHOUT USING WEST MANIFEST", sectionHeader: "Build Environment not using west manifest yaml",
			separatorStyle: "border-width: 0",
			sectionHeaderStyle: """
				background-color: #7ea6d4;
				text-align: left;
				padding: 4px;
				color: #343434;
				font-size: 14px;
				font-weight: normal;
				font-family: 'Orienta', sans-serif;
				letter-spacing: 1px;
				font-style: italic;
			"""
	    )
        string(name: 'NRF_802154_SL_REFSPEC', defaultValue: "",
               description: '''Refspec of nrf-802.15.14-sl to use.
                               Empty value will cause to use master version required to unit tests,
                               and this value will be propagated to downstream plan.''')
        string(name: 'NRF_802154_SERIALIZATION_REFSPEC', defaultValue: "",
               description: '''Refspec of nrf-802.15.4-serialization to use.
                               Empty value will cause to use version stated in manifest,
                               and this value will be propagated to downstream plan.''')
        string(name: 'MPSL_BRANCH', defaultValue: "",
                description: '''Replace mpsl using plan:
                                https://jenkins-ncs.nordicsemi.no/job/dragoon/job/dragoon-mpsl/job/{branch}/.
                                Empty value will cause to use MPSL as it is in nrfxlib of NCS. ''')
        string(name: 'MPSL_BRANCH_BUILD_NR', defaultValue: "",
                description: '''Replace mpsl using build plan number:
                                https://jenkins-ncs.nordicsemi.no/job/dragoon/job/dragoon-mpsl/job/{branch}/{nr}/.
                                Empty value will cause to use MPSL as it is in nrfxlib of NCS. ''')
        separator(name: "TEST_ENVIRONMENT", sectionHeader: "Test Environment",
			separatorStyle: "border-width: 0",
			sectionHeaderStyle: """
				background-color: #dbdb8e;
				text-align: center;
				padding: 4px;
				color: #343434;
				font-size: 22px;
				font-weight: normal;
				text-transform: uppercase;
				font-family: 'Orienta', sans-serif;
				letter-spacing: 1px;
				font-style: italic;
			"""
		)
        string(name: 'jsonstr_CI_STATE', defaultValue: CI_STATE.CFG.INPUT_STATE_STR,
               description: 'Default State if no upstream job')
        string(name: 'TEST_RELEASE_TAG', defaultValue: "",
               description: '''Use for release purpose if you want to run downstream tests on tag job :)
                            https://jenkins-ncs.nordicsemi.no/job/latest/job/test-fw-nrfconnect-rs_drv154_integration/view/tags/job/{tag}
                            ''')
        string(name: 'nrfx_refspec', defaultValue: 'v2.3.0', description: 'Git refspec of nrfx used in unit tests')
        separator(name: "TEST_FILTER", sectionHeader: "Test filters and parameters",
			separatorStyle: "border-width: 0",
			sectionHeaderStyle: """
				background-color: #dbdb8f;
				text-align: left;
				padding: 4px;
				color: #343434;
				font-size: 14px;
				font-weight: normal;
				font-family: 'Orienta', sans-serif;
				letter-spacing: 1px;
				font-style: italic;
			"""
		)
        choice(name: 'TEST_CYCLE', description: 'Test Phase', choices: CI_STATE.CFG.CRON_CHOICES)
    }

    environment {
        SL_BRANCH = ''
        NRFX_PATH='nrfx'
        SL_PATH='sl'
        THOR_SILENCE_DEPRECATION='true'
        TEST_BUILD_JOB_LINK = ''
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
                    if (params.NRF_802154_SL_REFSPEC == '') {
                        SL_BRANCH = 'master'
                    }
                    else {
                        SL_BRANCH = params.NRF_802154_SL_REFSPEC
                    }
                }
            }
        }
        stage('Build and host tests') {
            when {
                expression { params.TEST_CYCLE == 'COMMIT'}
            }
            parallel {
                stage('Check Radio Driver style') {
                    steps {
                        sh './scripts/pretty.sh check'
                    }
                }
                stage('Unit tests') {
                    stages{
                        stage('Checkout dependencies') {
                            steps {
                                dir("${SL_PATH}") {
                                    checkout_refspec(SL_BRANCH, 'https://projecttools.nordicsemi.no/bitbucket/scm/krknwk/nrf-802.15.4-sl.git')
                                }
                                dir("${NRFX_PATH}") {
                                    checkout_refspec(nrfx_refspec, 'https://github.com/NordicSemiconductor/nrfx')
                                }
                            }
                        }
                        stage('Run tests') {
                            steps {
                                // TODO: Uncomment when dependencies support nRF53
                                //sh 'ceedling options:nrf5340 test:all'
                                //sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf5340.xml'

                                sh 'ceedling options:nrf52840 test:all'
                                sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf52840.xml'

                                sh 'ceedling options:nrf52833 test:all'
                                sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf52833.xml'

                                sh 'ceedling options:nrf52820 test:all'
                                sh 'mv build/artifacts/test/report.xml build/artifacts/test/report_nrf52820.xml'

                                sh 'ceedling options:nrf52811 test:all'
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
                script {
                    if (params.TEST_RELEASE_TAG) {
                        TEST_BUILD_JOB_LINK = DOWNSTREAM_TEST_JOB_LINK + params.TEST_RELEASE_TAG
                    }
                    else {
                        TEST_BUILD_JOB_LINK = DOWNSTREAM_TEST_JOB_LINK + 'master'
                    }
                }
                build job: TEST_BUILD_JOB_LINK, parameters: [
                    booleanParam(name: 'BUILD_AND_DEPLOY_USING_ONLY_WEST_MANIFEST_IN_TEST_APPS', value: params.BUILD_AND_DEPLOY_USING_ONLY_WEST_MANIFEST_IN_TEST_APPS),
                    string(name: 'TEST_APPS_REFSPEC', value: params.TEST_APPS_REFSPEC),
                    string(name: 'NRF_802154_RADIO_DRIVER_REFSPEC', value: lib_State.getGitRef('NRF802154', CI_STATE)),
                    string(name: 'NRF_802154_SL_REFSPEC', value: SL_BRANCH),
                    string(name: 'NRF_802154_SERIALIZATION_REFSPEC', value: params.NRF_802154_SERIALIZATION_REFSPEC),
                    string(name: 'MPSL_BRANCH', value: params.MPSL_BRANCH),
                    string(name: 'MPSL_BRANCH_BUILD_NR', value: params.NRF_802154_SERIALIZATION_REFSPEC),
                    string(name: 'TEST_CYCLE', value: params.TEST_CYCLE)
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
