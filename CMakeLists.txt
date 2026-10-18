# Copyright (c) 2026 carrefinho
# SPDX-License-Identifier: MIT

if(CONFIG_ZMK_HID_INDICATORS)
  zephyr_library()
  zephyr_library_sources(src/caps_led.c)

  zephyr_library_include_directories(${APPLICATION_SOURCE_DIR}/include)
endif()
