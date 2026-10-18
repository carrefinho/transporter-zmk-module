# Copyright (c) 2026 carrefinho
# SPDX-License-Identifier: MIT

# These runners only exist in the carrefinho/zephyr fork. On stock zephyr
# `west flash` is unavailable, so flash with wchisp directly.
board_runner_args(minichlink "--dt-flash=y")
board_runner_args(wlink "--chip=CH32X035")
board_runner_args(wchisp)
if(EXISTS ${ZEPHYR_BASE}/boards/common/minichlink.board.cmake)
  include(${ZEPHYR_BASE}/boards/common/minichlink.board.cmake)
endif()
if(EXISTS ${ZEPHYR_BASE}/boards/common/wlink.board.cmake)
  include(${ZEPHYR_BASE}/boards/common/wlink.board.cmake)
endif()
if(EXISTS ${ZEPHYR_BASE}/boards/common/wchisp.board.cmake)
  include(${ZEPHYR_BASE}/boards/common/wchisp.board.cmake)
endif()
