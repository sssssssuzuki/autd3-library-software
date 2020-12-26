﻿// File: core.hpp
// Project: include
// Created Date: 11/04/2018
// Author: Shun Suzuki
// -----
// Last Modified: 26/12/2020
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2018-2020 Hapis Lab. All rights reserved.
//

#pragma once

#ifdef USE_EIGEN_AUTD
#if WIN32
#include <codeanalysis/warnings.h>  // NOLINT
#pragma warning(push)
#pragma warning(disable : ALL_CODE_ANALYSIS_WARNINGS)
#endif
#include <Eigen/Geometry>
#if WIN32
#pragma warning(pop)
#endif
#else
#include "quaternion.hpp"
#include "vector3.hpp"
#endif

#include <array>
#include <memory>

#include "consts.hpp"

namespace autd {

#ifdef USE_EIGEN_AUTD
#ifdef USE_DOUBLE_AUTD
using Vector3 = Eigen::Vector3d;
using Quaternion = Eigen::Quaterniond;
#else
using Vector3 = Eigen::Vector3f;
using Quaternion = Eigen::Quaternionf;
#endif
#else
using utils::Quaternion;
using utils::Vector3;
#endif

class Controller;
class Geometry;
class Timer;

namespace link {
class Link;
}  // namespace link

namespace gain {
class Gain;
class PlaneWaveGain;
class FocalPointGain;
class BesselBeamGain;
class CustomGain;
class GroupedGain;
class MatlabGain;
class HoloGain;
class TransducerTestGain;
using NullGain = Gain;
using MultiFoci = HoloGain;
}  // namespace gain

namespace modulation {
class Modulation;
class SineModulation;
class SawModulation;
class RawPCMModulation;
class WavModulation;
}  // namespace modulation

namespace sequence {
class PointSequence;
class CircumSeq;
}  // namespace sequence

class FirmwareInfo;

using AUTDDataArray = std::array<uint16_t, NUM_TRANS_IN_UNIT>;

using GainPtr = std::shared_ptr<gain::Gain>;
using LinkPtr = std::unique_ptr<link::Link>;
using ModulationPtr = std::shared_ptr<modulation::Modulation>;
using SequencePtr = std::shared_ptr<sequence::PointSequence>;
using ControllerPtr = std::shared_ptr<Controller>;
}  // namespace autd
