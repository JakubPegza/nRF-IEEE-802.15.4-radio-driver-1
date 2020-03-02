add_library(radio_driver src/nrf_802154.c
                         src/nrf_802154_core.c
                         src/nrf_802154_core_hooks.c
                         src/nrf_802154_critical_section.c
                         src/nrf_802154_debug.c
                         src/nrf_802154_pib.c
                         src/nrf_802154_queue.c
                         src/nrf_802154_rssi.c
                         src/nrf_802154_rx_buffer.c
                         src/nrf_802154_stats.c
                         src/nrf_802154_timer_coord.c
                         src/nrf_802154_trx.c
                         src/fal/nrf_802154_fal.c
                         src/mac_features/nrf_802154_csma_ca.c
                         src/mac_features/nrf_802154_delayed_trx.c
                         src/mac_features/nrf_802154_filter.c
                         src/mac_features/nrf_802154_frame_parser.c
                         src/mac_features/nrf_802154_ifs.c
                         src/mac_features/nrf_802154_precise_ack_timeout.c
                         src/mac_features/ack_generator/nrf_802154_ack_data.c
                         src/mac_features/ack_generator/nrf_802154_ack_generator.c
                         src/mac_features/ack_generator/nrf_802154_enh_ack_generator.c
                         src/mac_features/ack_generator/nrf_802154_imm_ack_generator.c
                         src/platform/clock/nrf_802154_clock_nrfx.c
                         src/platform/hp_timer/nrf_802154_hp_timer.c
                         src/platform/lp_timer/nrf_802154_lp_timer_nodrv.c
                         src/platform/random/nrf_802154_random_stdlib.c
                         src/platform/temperature/nrf_802154_temperature_none.c
                         src/rsch/nrf_802154_rsch.c
                         src/rsch/nrf_802154_rsch_crit_sect.c
                         src/timer_scheduler/nrf_802154_timer_sched.c
                         src/nrf_802154_notification_direct.c
                         src/nrf_802154_priority_drop_direct.c
                         src/nrf_802154_request_direct.c
                         src/nrf_802154_swi.c
                         src/rsch/raal/single_phy/single_phy.c
                         src/fem/simple_gpio/nrf_fem_simple_gpio.c)

target_compile_definitions(radio_driver PUBLIC "ENABLE_FEM=1")
target_link_libraries(radio_driver nrfx)
target_include_directories(radio_driver PUBLIC src/
                                               src/fem/
                                               src/fem/simple_gpio/
                                               src/platform/coex/)

add_library(nowificoex src/platform/coex/nrf_802154_wifi_coex_none.c)
target_link_libraries(nowificoex radio_driver)