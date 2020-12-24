﻿// File: soem_link.cpp
// Project: lib
// Created Date: 24/08/2019
// Author: Shun Suzuki
// -----
// Last Modified: 24/12/2020
// Modified By: Shun Suzuki (suzuki@hapis.k.u-tokyo.ac.jp)
// -----
// Copyright (c) 2019-2020 Hapis Lab. All rights reserved.
//

#include "soem_link.hpp"

#include <algorithm>
#include <bitset>
#include <chrono>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../lib/ec_config.hpp"
#include "autdsoem.hpp"

namespace autd::link {

EtherCATAdapters SOEMLink::EnumerateAdapters(size_t* const size) {
  const auto adapters = autdsoem::EtherCATAdapterInfo::EnumerateAdapters();
  *size = adapters.size();
  EtherCATAdapters res;
  for (const auto& adapter : autdsoem::EtherCATAdapterInfo::EnumerateAdapters()) {
    EtherCATAdapter p;
    p.first = adapter.desc;
    p.second = adapter.name;
    res.push_back(p);
  }
  return res;
}

class SOEMLinkImpl final : public SOEMLink {
 public:
  SOEMLinkImpl(std::string ifname, const size_t device_num) : SOEMLink(), _device_num(device_num), _ifname(std::move(ifname)) {}
  ~SOEMLinkImpl() override = default;
  SOEMLinkImpl(const SOEMLinkImpl& v) noexcept = delete;
  SOEMLinkImpl& operator=(const SOEMLinkImpl& obj) = delete;
  SOEMLinkImpl(SOEMLinkImpl&& obj) = default;
  SOEMLinkImpl& operator=(SOEMLinkImpl&& obj) = default;

 protected:
  void Open() override;
  void Close() override;
  void Send(size_t size, std::unique_ptr<uint8_t[]> buf) override;
  std::vector<uint8_t> Read(uint32_t buffer_len) override;
  bool is_open() override;

 private:
  std::unique_ptr<autdsoem::SOEMController> _cnt;
  size_t _device_num = 0;
  std::string _ifname;
  autdsoem::ECConfig _config{};
};

LinkPtr SOEMLink::Create(const std::string& ifname, const size_t device_num) {
  LinkPtr link = std::make_unique<SOEMLinkImpl>(ifname, device_num);
  return link;
}

void SOEMLinkImpl::Open() {
  _cnt = autdsoem::SOEMController::Create();

  _config = autdsoem::ECConfig{};
  _config.ec_sm3_cycle_time_ns = EC_SM3_CYCLE_TIME_NANO_SEC;
  _config.ec_sync0_cycle_time_ns = EC_SYNC0_CYCLE_TIME_NANO_SEC;
  _config.header_size = HEADER_SIZE;
  _config.body_size = NUM_TRANS_IN_UNIT * 2;
  _config.input_frame_size = EC_INPUT_FRAME_SIZE;

  _cnt->Open(_ifname.c_str(), _device_num, _config);
}

void SOEMLinkImpl::Close() {
  if (_cnt->is_open()) {
    _cnt->Close();
  }
}

void SOEMLinkImpl::Send(const size_t size, std::unique_ptr<uint8_t[]> buf) {
  if (_cnt->is_open()) {
    _cnt->Send(size, std::move(buf));
  }
}

std::vector<uint8_t> SOEMLinkImpl::Read([[maybe_unused]] uint32_t buffer_len) { return _cnt->Read(); }

bool SOEMLinkImpl::is_open() { return _cnt->is_open(); }
}  // namespace autd::link
