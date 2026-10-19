// SPDX-License-Identifier: Apache-2.0
//
// Copyright 2026 JASPAR
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gtest/gtest.h>

#include "cucumber-cpp/internal/step/StepMacros.hpp"
#include "databroker/databroker_producer_factory.h"
#include "databroker/producer_get_request.h"
#include "step.h"

namespace {

/*
    Scenario Outline: Cold start once and seed initial actuator values
        Given Kura service is cleanly restarted
        When HeadlessApp sets the following actuator signals
        Then PAL should report the following actuator signals
*/
GIVEN("^Kura service is cleanly restarted$") {
  OperateKura(KuraOperation::kReset);
}

WHEN("^HeadlessApp sets the following actuator signals$") {
  const auto& table = getArgs()->getTableArg();
  const auto rows = table.hashes();

  for (const auto& r : rows) {
    const std::string signal_name = r.at("path");
    const std::string datatype_str = r.at("datatype");
    const std::string value_str = r.at("value");

    yoriito::ValueType target_value =
        ConvertValueStr2ValueType(datatype_str, value_str);
    auto* act = ObtainSignalObject<IActuator>(signal_name);
    auto ret = act->Set(std::move(target_value));
    EXPECT_TRUE(ret.IsOk());
  }
}

THEN("^PAL should report the following actuator signals$") {
  const auto& table = getArgs()->getTableArg();
  const auto rows = table.hashes();

  for (const auto& r : rows) {
    const std::string signal_name = r.at("path");
    const std::string datatype_str = r.at("datatype");
    const std::string value_str = r.at("value");

    yoriito::ValueType expected_value =
        ConvertValueStr2ValueType(datatype_str, value_str);

    auto* producer =
        yoriito::databroker::DataBrokerProducerFactory::GetInstance();
    std::string path_to_move = signal_name;
    auto resp = producer->Get(
        yoriito::databroker::ProducerGetRequest{std::move(path_to_move)});
    EXPECT_TRUE(resp.IsOk());
    EXPECT_TRUE(yoriito::ValueTypeEquals(
        expected_value,
        resp.TakeOk().value().GetDataPoints().front().GetData()));
  }
}

/*
  Scenario Outline: Overwrite/confirm after cold start (no restart)
    Given Set the actuator signal <path> to <datatype> <default_value>
    When HeadlessApp set the actuator signal <path> to <datatype> <checked_value> 
    Then the result obtained from the actuator signal by PAL should be <datatype> <checked_value> on <path>
*/
GIVEN("^Set the actuator signal (\\S+) to (\\S+) (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);

  yoriito::ValueType target_value =
      ConvertValueStr2ValueType(datatype_str, value_str);
  auto* act = ObtainSignalObject<IActuator>(signal_name);
  auto ret = act->Set(std::move(target_value));
  if (ret.IsErr()) {
    auto e = ret.TakeErr();
    std::cerr << "code: " << e->ErrorCode() << " msg: " << e->Message()
              << std::endl;
  }
  EXPECT_TRUE(ret.IsOk());
}

WHEN("^HeadlessApp set the actuator signal (\\S+) to (\\S+) (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);

  yoriito::ValueType target_value =
      ConvertValueStr2ValueType(datatype_str, value_str);
  auto* act = ObtainSignalObject<IActuator>(signal_name);
  auto ret = act->Set(std::move(target_value));
  EXPECT_TRUE(ret.IsOk());
}

THEN(
    "^the result obtained from the actuator signal by PAL should be (\\S+) "
    "(\\S+) on (\\S+)$") {
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, signal_name);

  yoriito::ValueType expected_value =
      ConvertValueStr2ValueType(datatype_str, value_str);

  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  std::string path_to_move = signal_name;
  auto resp = producer->Get(
      yoriito::databroker::ProducerGetRequest{std::move(path_to_move)});
  EXPECT_TRUE(resp.IsOk());
  EXPECT_TRUE(yoriito::ValueTypeEquals(
      expected_value, resp.TakeOk().value().GetDataPoints().front().GetData()));
}

/*
  Scenario Outline: Millions of set requests do not kill kura server & values remain consistent 
    When HeadlessApp set the signal <path> to <datatype> <checked_value> <count> times with duplex <duplex> 
    Then the result obtained from the actuator signal by PAL should be <datatype> <checked_value> on <path>
*/
WHEN(
    "^HeadlessApp set the signal (\\S+) to (\\S+) (\\S+) ([0-9]+) times with "
    "duplex ([0-9]+)$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(int, set_times);
  REGEX_PARAM(int, num_threads);

  std::atomic<int> ok{0};
  std::vector<std::thread> ths(num_threads);

  for (auto& th : ths) {
    th = std::thread([&, set_times, datatype_str, value_str] {
      auto* act = ObtainSignalObject<IActuator>(signal_name);

      for (int i = 0; i < set_times; i++) {
        yoriito::ValueType target_value =
            ConvertValueStr2ValueType(datatype_str, value_str);
        auto ret = act->Set(std::move(target_value));
        EXPECT_TRUE(ret.IsOk());
        ok.fetch_add(1, std::memory_order_relaxed);
      }
    });
  }

  for (auto& th : ths) th.join();

  EXPECT_EQ(ok.load(), set_times * num_threads)
      << "Insufficient simultaneous set call successes";
}
// THEN is same as the above

/*
  @CleanupRestoreServer
  Scenario Outline: Subscribe requests are failed when the server is stopped
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    When the server is stopped
    Then an attempt to subscribe the signal at <path> of datatype <datatype> is failed
*/
WHEN("^the server is stopped for set$") {
  EXPECT_TRUE(OperateKura(KuraOperation::kStop));
}
THEN(
    "^an attempt to set the actuator signal (\\S+) to (\\S+) (\\S+) is "
    "failed$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);

  yoriito::ValueType target_value =
      ConvertValueStr2ValueType(datatype_str, value_str);
  auto* act = ObtainSignalObject<IActuator>(signal_name);
  auto ret = act->Set(std::move(target_value));
  EXPECT_FALSE(ret.IsOk());
}

AFTER("@CleanupRestoreServerforSet") { OperateKura(KuraOperation::kReset); }
AFTER("@CleanupRestoreNetworkforSet") {
  OperateNetwork(NetworkOperation::kCleanup);
}

/*
  Scenario Outline: Set requests are failed when the network communication failure
    When network failure of <network_failure> is injected
    Then an attempt to set the actuator signal <path> to <datatype> <checked_value> is failed
*/
WHEN("^network failure of (\\S+) is injected for set$") {
  REGEX_PARAM(std::string, network_failure);
  if (network_failure == "timeout") {
    EXPECT_TRUE(OperateNetwork(NetworkOperation::kTimeout));
  } else if (network_failure == "reject") {
    EXPECT_TRUE(OperateNetwork(NetworkOperation::kReject));
  } else {
    EXPECT_STREQ(network_failure.c_str(),
                 "network_failure should be either timeout or reject");
  }
}
// THEN is same as the above
}  // namespace