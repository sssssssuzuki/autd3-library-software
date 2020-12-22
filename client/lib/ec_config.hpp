// File: ec_config.hpp
// Project: lib
// Created Date: 21/02/2020
// Author: Shun Suzuki
// -----
// Last Modified: 22/12/2020
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2020 Hapis Lab. All rights reserved.
//

#pragma once

#include "../lib/privdef.hpp"
#include "consts.hpp"

constexpr size_t HEADER_SIZE = 128;
constexpr size_t EC_OUTPUT_FRAME_SIZE = autd::NUM_TRANS_IN_UNIT * 2 + HEADER_SIZE;
constexpr size_t EC_INPUT_FRAME_SIZE = 2;

constexpr uint32_t EC_SM3_CYCLE_TIME_MICRO_SEC = 1000;
constexpr uint32_t EC_SYNC0_CYCLE_TIME_MICRO_SEC = 1000;

constexpr uint32_t EC_SM3_CYCLE_TIME_NANO_SEC = EC_SM3_CYCLE_TIME_MICRO_SEC * 1000;
constexpr uint32_t EC_SYNC0_CYCLE_TIME_NANO_SEC = EC_SYNC0_CYCLE_TIME_MICRO_SEC * 1000;

constexpr uint8_t READ_MOD_IDX_BASE_HEADER = 0xC0;
constexpr uint8_t READ_MOD_IDX_BASE_HEADER_AFTER_SHIFT = 0xE0;
constexpr uint8_t READ_MOD_IDX_BASE_HEADER_MASK = 0xE0;
constexpr size_t EC_DEVICE_PER_FRAME = 2;
constexpr size_t EC_FRAME_LENGTH = 14 + 2 + (10 + EC_OUTPUT_FRAME_SIZE + EC_INPUT_FRAME_SIZE + 2) * EC_DEVICE_PER_FRAME + 10;
constexpr double EC_SPEED_BPS = 100.0 * 1000 * 1000;
constexpr double EC_TRAFFIC_DELAY = EC_FRAME_LENGTH * 8 / EC_SPEED_BPS;
