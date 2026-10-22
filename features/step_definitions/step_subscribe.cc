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

#include "databroker/databroker_producer_factory.h"
#include "databroker/producer_set_datapoint.h"
#include "databroker/producer_set_request.h"
#include "step.h"

namespace {

using cucumber::ScenarioScope;

constexpr int64_t kProducedTimestamp = 1735689600;  // 2025-01-01T00:00:00Z

/*
  Scenario Outline: HeadlessApp_Subscribe_Sensor_Value
    Given PAL set sensor signal <path> to <datatype> <value>
    Given HeadlessApp subscribe the sensor signal <path> of <datatype>
    Then PAL set the signal at <path> of <datatype> to <values> by order, subscribe stream receive the same data
    And HeadlessApp unsubscribe the sensor signal <path> of <datatype> to close connections
*/
GIVEN("^HeadlessApp subscribe the sensor signal (\\S+) of (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);

  ScenarioScope<ScenarioCtx> context;
  auto* sens = ObtainSignalObject<ISensor>(signal_name);
  auto ret = sens->Subscribe();
  EXPECT_TRUE(ret.IsOk());
  context->subscribe_context_arr.push_back(std::move(ret.TakeOk().value()));
}
THEN(
    "^PAL set the signal at (\\S+) of (\\S+) to (\\[.+\\]) by order, subscribe "
    "stream receive the same data$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, values_str);

  auto* sens = ObtainSignalObject<ISensor>(signal_name);
  ScenarioScope<ScenarioCtx> context;
  auto values = ParseArray<std::string>(std::string(values_str));

  for (std::string& value_str : values) {
    yoriito::ValueType target_value =
        ConvertValueStr2ValueType(datatype_str, value_str);
    auto* producer =
        yoriito::databroker::DataBrokerProducerFactory::GetInstance();
    yoriito::databroker::ProducerSetRequest target{
        std::vector<yoriito::databroker::ProducerSetDataPoint>{
            {signal_name, target_value, true, false}}};
    auto ret = producer->Set(target);
    EXPECT_TRUE(ret.IsOk());

    for (auto& ctx : context->subscribe_context_arr) {
      auto ret = sens->GetMessage(ctx);
      EXPECT_TRUE(ret.IsOk());
      auto data = ret.TakeOk().value();
      EXPECT_EQ(data.GetPath(), signal_name);
      EXPECT_TRUE(yoriito::ValueTypeEquals(target_value, data.GetData()));
      EXPECT_TRUE(data.IsAvailableSensor());
      EXPECT_GT(data.GetStoredTimestamp(), 0);
    }
  }
}
THEN(
    "^HeadlessApp unsubscribe the sensor signal (\\S+) of (\\S+) to close "
    "connections$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);

  ScenarioScope<ScenarioCtx> context;
  auto* sens = ObtainSignalObject<ISensor>(signal_name);
  for (auto&& ctx : context->subscribe_context_arr) {
    auto ret = sens->UnSubscribe(std::move(ctx));
    EXPECT_TRUE(ret.IsOk());
  }
}

/*
  Scenario Outline: Notification of subscribed signals
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    And attempts to subscribe the signal at <path> of datatype <datatype> is succeeded
    When the value of signal at <path> changes to <value_1> of datatype <datatype>
    Then the subscribe stream returns <datatype> <value_1> on <path>
    And HeadlessApp unsubscribe the sensor signal <path> of <datatype> to close connections
*/
GIVEN("^a signal at (\\S+) is set to (\\S+) of datatype (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, datatype_str);

  yoriito::ValueType target_value =
      ConvertValueStr2ValueType(datatype_str, value_str);
  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  yoriito::databroker::ProducerSetRequest target{
      std::vector<yoriito::databroker::ProducerSetDataPoint>{
          {signal_name, target_value, true, false}}};
  auto ret = producer->Set(target);
  EXPECT_TRUE(ret.IsOk());
}
GIVEN(
    "^attempts to subscribe the signal at (\\S+) of datatype (\\S+) is "
    "succeeded$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);

  ScenarioScope<ScenarioCtx> context;
  auto* sens = ObtainSignalObject<ISensor>(signal_name);
  auto ret = sens->Subscribe();
  EXPECT_TRUE(ret.IsOk());
  context->subscribe_context_arr.push_back(std::move(ret.TakeOk().value()));
}
WHEN("^the value of signal at (\\S+) changes to (\\S+) of datatype (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, datatype_str);

  yoriito::ValueType target_value =
      ConvertValueStr2ValueType(datatype_str, value_str);
  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  yoriito::databroker::ProducerSetRequest target{
      std::vector<yoriito::databroker::ProducerSetDataPoint>{
          {signal_name, target_value, true, false}}};
  auto ret = producer->Set(target);
  EXPECT_TRUE(ret.IsOk());
}
THEN("^the subscribe stream returns (\\S+) (\\S+) on (\\S+)$") {
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, signal_name);

  auto* sens = ObtainSignalObject<ISensor>(signal_name);
  ScenarioScope<ScenarioCtx> context;
  yoriito::ValueType target_value =
      ConvertValueStr2ValueType(datatype_str, value_str);

  for (const auto& ctx : context->subscribe_context_arr) {
    auto ret = sens->GetMessage(ctx);
    EXPECT_TRUE(ret.IsOk());
    auto data = ret.TakeOk().value();
    EXPECT_EQ(data.GetPath(), signal_name);
    EXPECT_TRUE(yoriito::ValueTypeEquals(target_value, data.GetData()));
    EXPECT_TRUE(data.IsAvailableSensor());
    EXPECT_GT(data.GetStoredTimestamp(), 0);
  }
}

/*
  Scenario Outline: Notification is delivered even if the signal is unavailable as sensor
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    And attempts to subscribe the signal at <path> of datatype <datatype> is succeeded
    When the value of signal at <path> changes to <value_1> of datatype <datatype> as unavailable
    Then the subscribe stream returns <datatype> <value_1> on <path> as unavailable as sensor
    And HeadlessApp unsubscribe the sensor signal <path> of <datatype> to close connections
*/
// Given is same as the above
WHEN(
    "^the value of signal at (\\S+) changes to (\\S+) of datatype (\\S+) as "
    "unavailable$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, datatype_str);

  yoriito::ValueType target_value =
      ConvertValueStr2ValueType(datatype_str, value_str);
  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  yoriito::databroker::ProducerSetRequest target{
      std::vector<yoriito::databroker::ProducerSetDataPoint>{
          {signal_name, target_value, false, false}}};
  auto ret = producer->Set(target);
  EXPECT_TRUE(ret.IsOk());
}
THEN(
    "^the subscribe stream returns (\\S+) (\\S+) on (\\S+) as unavailable as "
    "sensor$") {
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, signal_name);

  auto* sens = ObtainSignalObject<ISensor>(signal_name);
  ScenarioScope<ScenarioCtx> context;
  yoriito::ValueType target_value =
      ConvertValueStr2ValueType(datatype_str, value_str);

  for (const auto& ctx : context->subscribe_context_arr) {
    auto ret = sens->GetMessage(ctx);
    EXPECT_TRUE(ret.IsOk());
    auto data = ret.TakeOk().value();
    EXPECT_EQ(data.GetPath(), signal_name);
    EXPECT_TRUE(yoriito::ValueTypeEquals(target_value, data.GetData()));
    EXPECT_FALSE(data.IsAvailableSensor());
    EXPECT_GT(data.GetStoredTimestamp(), 0);
  }
}

/*
  Scenario Outline: Notification carries IsAvailableActuator as true when
   reported by the producer
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    And attempts to subscribe the signal at <path> of datatype <datatype> is succeeded
    When the value of signal at <path> changes to <value_1> of datatype <datatype> as available actuator
    Then the subscription stream returns available actuator on <path>
    And HeadlessApp unsubscribe the sensor signal <path> of <datatype> to close connections
*/
// Given is same as the above
WHEN(
    "^the value of signal at (\\S+) changes to (\\S+) of datatype (\\S+) as "
    "available actuator$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, datatype_str);

  yoriito::ValueType target_value =
      ConvertValueStr2ValueType(datatype_str, value_str);
  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  yoriito::databroker::ProducerSetRequest target{
      std::vector<yoriito::databroker::ProducerSetDataPoint>{
          {signal_name, target_value, true, true}}};
  auto ret = producer->Set(target);
  EXPECT_TRUE(ret.IsOk());
}
THEN("^the subscription stream returns available actuator on (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);

  auto* sens = ObtainSignalObject<ISensor>(signal_name);
  ScenarioScope<ScenarioCtx> context;

  for (const auto& ctx : context->subscribe_context_arr) {
    auto ret = sens->GetMessage(ctx);
    EXPECT_TRUE(ret.IsOk());
    auto data = ret.TakeOk().value();
    EXPECT_EQ(data.GetPath(), signal_name);
    EXPECT_TRUE(data.IsAvailableActuator());
  }
}

/*
  Scenario Outline: Notification carries a produced timestamp when the
   producer attaches one
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    And attempts to subscribe the signal at <path> of datatype <datatype> is succeeded
    When the value of signal at <path> changes to <value_1> of datatype <datatype> with a produced timestamp
    Then the subscribe stream returns a produced timestamp on <path>
    And HeadlessApp unsubscribe the sensor signal <path> of <datatype> to close connections
*/
// Given is same as the above
WHEN(
    "^the value of signal at (\\S+) changes to (\\S+) of datatype (\\S+) "
    "with a produced timestamp$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, datatype_str);

  yoriito::ValueType target_value =
      ConvertValueStr2ValueType(datatype_str, value_str);
  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  yoriito::databroker::ProducerSetRequest target{
      std::vector<yoriito::databroker::ProducerSetDataPoint>{
          {signal_name, target_value, true, false, kProducedTimestamp}}};
  auto ret = producer->Set(target);
  EXPECT_TRUE(ret.IsOk());
}
THEN("^the subscribe stream returns a produced timestamp on (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);

  auto* sens = ObtainSignalObject<ISensor>(signal_name);
  ScenarioScope<ScenarioCtx> context;

  for (const auto& ctx : context->subscribe_context_arr) {
    auto ret = sens->GetMessage(ctx);
    EXPECT_TRUE(ret.IsOk());
    auto data = ret.TakeOk().value();
    EXPECT_EQ(data.GetPath(), signal_name);
    EXPECT_EQ(data.GetProducedTimestamp(), kProducedTimestamp);
  }
}

/*
  Scenario Outline: Multiple subscriptions to a signal
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    And attempts to subscribe the signal at <path> of datatype <datatype> for <count> times with duplex <duplex> are all succeeded
    When the value of signal at <path> changes to <value_1> of datatype <datatype>
    Then the subscribe stream returns <datatype> <value_1> on <path>
    And HeadlessApp unsubscribe the sensor signal <path> of <datatype> to close connections
*/
std::mutex subscribe_mutex;
GIVEN(
    "^attempts to subscribe the signal at (\\S+) of datatype (\\S+) for "
    "([0-9]+) times with duplex ([0-9]+) are all succeeded$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(int, subscription_times);
  REGEX_PARAM(int, num_threads);

  ScenarioScope<ScenarioCtx> context;

  // subscribe the signal and set to subscribe_context with multi-thread
  std::vector<std::thread> ths(num_threads);
  for (auto& th : ths) {
    th = std::thread([&] {
      auto* sens = ObtainSignalObject<ISensor>(signal_name);
      for (int i = 0; i < subscription_times; i++) {
        auto ret = sens->Subscribe();
        EXPECT_TRUE(ret.IsOk());
        {
          std::lock_guard<std::mutex> lock(subscribe_mutex);
          context->subscribe_context_arr.push_back(
              std::move(ret.TakeOk().value()));
        }
      }
    });
  }
  for (auto&& th : ths) th.join();

  EXPECT_EQ(context->subscribe_context_arr.size(),
            subscription_times * num_threads);
}
// WHEN is same as the above
// THEN is same as the above

/*
  Scenario Outline: Notification issued even if signal value being changed
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    And attempts to subscribe the signal at <path> of datatype <datatype> is succeeded
    When the value of signal at <path> changes to <value_1> of datatype <datatype>, which is equal to the current value
    Then the subscribe stream returns <datatype> <value_1> on <path>
    And HeadlessApp unsubscribe the sensor signal <path> of <datatype> to close connections
*/
// GIVEN is same as the above
WHEN(
    "^the value of signal at (\\S+) changes to (\\S+) of datatype (\\S+), "
    "which is equal to the current value") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, datatype_str);

  yoriito::ValueType target_value =
      ConvertValueStr2ValueType(datatype_str, value_str);
  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  yoriito::databroker::ProducerSetRequest target{
      std::vector<yoriito::databroker::ProducerSetDataPoint>{
          {signal_name, target_value, true, false}}};
  auto ret = producer->Set(target);
  EXPECT_TRUE(ret.IsOk());
}
// THEN is same as the above

/*
  Scenario Outline: Millions of subscribe requests do not kill kura server &
   subscription_ids are correctly returned
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    And attempts to subscribe the signal at <path> of datatype <datatype> for <count> times with duplex <duplex> are all succeeded
    When the value of signal at <path> changes to <value_1> of datatype <datatype>
    Then the subscribe stream returns <datatype> <value_1> on <path>
    And HeadlessApp unsubscribe the sensor signal <path> of <datatype> to close connections
*/
// GIVEN is same as the above
// WHEN is same as the above
// THEN is same as the above

/*
  @CleanupRestoreServer
  Scenario Outline: Subscribe requests are failed when the server is stopped
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    When the server is stopped
    Then an attempt to subscribe the signal at <path> of datatype <datatype> is failed
*/
WHEN("^the server is stopped$") {
  EXPECT_TRUE(OperateKura(KuraOperation::kStop));
}
THEN(
    "^an attempt to subscribe the signal at (\\S+) of datatype (\\S+) is "
    "failed$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);

  auto* sens = ObtainSignalObject<ISensor>(signal_name);
  auto ret = sens->Subscribe();
  EXPECT_FALSE(ret.IsOk());
}

AFTER("@CleanupRestoreServer") { OperateKura(KuraOperation::kReset); }
AFTER("@CleanupRestoreNetwork") { OperateNetwork(NetworkOperation::kCleanup); }

/*
  Scenario Outline: Subscribe requests are failed when the network communication failure
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    When network failure of <network_failure> is injected
    Then attempt to subscribe the signal at <path> of datatype <datatype> is failed
*/
// GIVEN is same as the above
WHEN("^network failure of (\\S+) is injected$") {
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

/*
  Scenario Outline: Subscribe contexts are no longer available after the server is reset
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    And attempts to subscribe the signal at <path> of datatype <datatype> is succeeded
    When the server is reset And the value of signal at <path> changes to <value_1> of datatype <datatype>
    Then the subscribe stream for the signal <path> returns no data
    And HeadlessApp unsubscribe the sensor signal <path> of <datatype> to close connections
*/
// GIVEN is same as the above
WHEN("^the server is reset$") {
  // reset the server
  OperateKura(KuraOperation::kReset);
}
THEN("^the subscribe stream for the signal (\\S+) returns no data$") {
  REGEX_PARAM(std::string, signal_name);
  auto* sens = ObtainSignalObject<ISensor>(signal_name);

  ScenarioScope<ScenarioCtx> context;
  for (const auto& ctx : context->subscribe_context_arr) {
    auto msg = sens->GetMessage(ctx);
    EXPECT_FALSE(msg.IsOk());
  }
}

/*
  Scenario Outline: All updates are notified to subscriptions without any drops even large burden on server or network
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    And attempts to subscribe the signal at <path> of datatype <datatype> is succeeded
    When the signal at <path> of numeric datatype <datatype> is updated <count> times, any updates are captured from subscribe stream
    Then HeadlessApp unsubscribe the sensor signal <path> of <datatype> to close connections
*/
// GIVEN is same as the above
WHEN(
    "^the signal at (\\S+) of numeric datatype (\\S+) is updated ([0-9]+) "
    "times, any updates are captured from subscribe stream$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(int, max_count);

  auto* sens = ObtainSignalObject<ISensor>(signal_name);

  std::thread th_set;
  std::thread th_subscribe;

  EXPECT_TRUE(!IsArray(datatype_str) &&
              (datatype_str != "string" && datatype_str != "bool"));

  // generate expected
  ScenarioScope<ScenarioCtx> context;
  if (datatype_str == "float") {
    float start = 0.0F;
    float diff = 1.0F;
    for (auto i = 0; i < max_count; i++) {
      context->subscribe_expect.push_back(
          yoriito::ValueType{std::in_place_type<float>, start += diff});
    }
  }
  if (datatype_str == "double") {
    double start = 0.0;
    double diff = 1.0;
    for (auto i = 0; i < max_count; i++) {
      context->subscribe_expect.push_back(
          yoriito::ValueType{std::in_place_type<double>, start += diff});
    }
  }
  if (datatype_str == "int8") {
    int8_t start = 0;
    int8_t diff = 1;
    for (auto i = 0; i < max_count; i++) {
      context->subscribe_expect.push_back(
          yoriito::ValueType{std::in_place_type<int8_t>, start += diff});
    }
  }
  if (datatype_str == "int16") {
    int16_t start = 0;
    int16_t diff = 1;
    for (auto i = 0; i < max_count; i++) {
      context->subscribe_expect.push_back(
          yoriito::ValueType{std::in_place_type<int16_t>, start += diff});
    }
  }
  if (datatype_str == "int32") {
    int32_t start = 0;
    int32_t diff = 1;
    for (auto i = 0; i < max_count; i++) {
      context->subscribe_expect.push_back(
          yoriito::ValueType{std::in_place_type<int32_t>, start += diff});
    }
  }
  if (datatype_str == "int64") {
    int64_t start = 0;
    int64_t diff = 1;
    for (auto i = 0; i < max_count; i++) {
      context->subscribe_expect.push_back(
          yoriito::ValueType{std::in_place_type<int64_t>, start += diff});
    }
  }
  if (datatype_str == "uint8") {
    uint8_t start = 0;
    uint8_t diff = 1;
    for (auto i = 0; i < max_count; i++) {
      context->subscribe_expect.push_back(
          yoriito::ValueType{std::in_place_type<uint8_t>, start += diff});
    }
  }
  if (datatype_str == "uint16") {
    uint16_t start = 0;
    uint16_t diff = 1;
    for (auto i = 0; i < max_count; i++) {
      context->subscribe_expect.push_back(
          yoriito::ValueType{std::in_place_type<uint16_t>, start += diff});
    }
  }
  if (datatype_str == "uint32") {
    uint32_t start = 0;
    uint32_t diff = 1;
    for (auto i = 0; i < max_count; i++) {
      context->subscribe_expect.push_back(
          yoriito::ValueType{std::in_place_type<uint32_t>, start += diff});
    }
  }
  if (datatype_str == "uint64") {
    uint64_t start = 0;
    uint64_t diff = 1;
    for (auto i = 0; i < max_count; i++) {
      context->subscribe_expect.push_back(
          yoriito::ValueType{std::in_place_type<uint64_t>, start += diff});
    }
  }

  // thread for subscribe
  th_subscribe = std::thread([&] {
    ScenarioScope<ScenarioCtx> context;
    for (size_t i = 0; i < context->subscribe_expect.size(); i++) {
      for (const auto& ctx : context->subscribe_context_arr) {
        auto msg = sens->GetMessage(ctx);
        EXPECT_TRUE(msg.IsOk());
        auto data = msg.TakeOk().value();

        EXPECT_EQ(data.GetPath(), signal_name);
        const auto& curr_val = data.GetData();
        EXPECT_TRUE(
            yoriito::ValueTypeEquals(curr_val, context->subscribe_expect[i]));
        EXPECT_GT(data.GetStoredTimestamp(), 0);
      }
    }
  });
  // thread for set
  th_set = std::thread([&] {
    ScenarioScope<ScenarioCtx> context;
    for (auto&& target_value : context->subscribe_expect) {
      auto* producer =
          yoriito::databroker::DataBrokerProducerFactory::GetInstance();
      yoriito::databroker::ProducerSetRequest target{
          std::vector<yoriito::databroker::ProducerSetDataPoint>{
              {signal_name, target_value, true, false}}};
      auto ret = producer->Set(target);
      EXPECT_TRUE(ret.IsOk());
    }
  });

  th_set.join();
  th_subscribe.join();
}
// THEN is same as the above

// Not implemented
/*
Scenario Outline: Notification is delivered only when filter conditions are satisfied
  Given a signal at <path> with an initial value <value_0> of datatype <datatype> is subscribed with filter <condition>
  When a signal at <path> of datatype <datatype> is updated but the conditions are not satisfied, no data is on subscribe stream 
  But a signal at <path> of datatype <datatype> is updated and the conditions are satisfied, the data is on subscribe stream

Scenario Outline: Authentication is required to use subscribe requests
  Given a signal at <path> with an initial value <value_0> of datatype <datatype>
  When a subscribe request to the signal <path> of <datatype> with invalid authentication data is sent, the request is failed 
  But a subscribe request to the signal <path> of <datatype> with valid authentication data is sent, the request is succeeded
*/
}  // namespace