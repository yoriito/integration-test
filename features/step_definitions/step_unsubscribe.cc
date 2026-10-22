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

/*
  Scenario: The unsubscribe request for a signal that is currently subscribed has been successfully processed
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    And attempts to subscribe the signal at <path> of datatype <datatype> is succeeded
    Then attempts to unsubscribe the signal at <path> of datatype <datatype> is succeeded
*/
// GIVEN is same as the step in step_subscribe.cpp
THEN(
    "^attempts to unsubscribe the signal at (\\S+) of datatype (\\S+) is "
    "succeeded$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  ScenarioScope<ScenarioCtx> context;
  auto* sens = ObtainSignalObject<ISensor>(signal_name);

  auto ret =
      sens->UnSubscribe(std::move(context->subscribe_context_arr.front()));
  EXPECT_TRUE(ret.IsOk());
}

/*
  Scenario Outline: Unsubscribe of one subscription_id does not hinder other subscription_ids
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    And attempts to subscribe the signal at <path> of datatype <datatype> for <count> times with duplex <duplex> are all succeeded
    When attempts to unsubscribe the signal at <path> of datatype <datatype> is succeeded
    And the value of signal at <path> changes to <value_1> of datatype <datatype>
    Then The other subscription_ids stream returns <datatype> <value_1> on <path>
*/
// GIVEN is same as the step in step_subscribe.cpp

// WHEN is same as the above
THEN("^The other subscription_ids stream returns (\\S+) (\\S+) on (\\S+)$") {
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, signal_name);

  ScenarioScope<ScenarioCtx> context;
  yoriito::ValueType expected =
      ConvertValueStr2ValueType(datatype_str, value_str);

  auto* sens = ObtainSignalObject<ISensor>(signal_name);

  auto v = sens->GetMessage(context->subscribe_context_arr[1]);
  EXPECT_TRUE(v.IsOk());
  auto data = v.TakeOk().value();
  EXPECT_EQ(data.GetPath(), signal_name);
  EXPECT_TRUE(yoriito::ValueTypeEquals(expected, data.GetData()));
  EXPECT_TRUE(data.IsAvailableSensor());
  EXPECT_GT(data.GetStoredTimestamp(), 0);

  // after that, unsubscribe the existing context
  auto ret = sens->UnSubscribe(std::move(context->subscribe_context_arr[1]));
  EXPECT_TRUE(ret.IsOk());
}

// ----- unsubscribe non-normal -----
/*
  Scenario Outline: Millions of unsubscribe requests do not kill kura server
    Given a signal at <path> is set to <value_0> of datatype <datatype>
    When attempts to subscribe the signal at <path> of datatype <datatype> for <count> times with duplex <duplex> are all succeeded
    Then HeadlessApp unsubscribe the sensor signal <path> of <datatype> to close connections with duplex <duplex> are all succeeded

*/
// GIVEN is same as the step in step_subscribe.cpp
// WHEN is same as the step in step_subscribe.cpp
std::mutex unsubscribe_mutex;
THEN(
    "^HeadlessApp unsubscribe the sensor signal (\\S+) of (\\S+) to close "
    "connections with duplex ([0-9]+) are all succeeded$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(int, num_threads);

  // unsubscribe the signal and set to subscribe_context with multi-thread
  std::vector<std::thread> ths(num_threads);
  for (auto& th : ths) {
    th = std::thread([&] {
      ScenarioScope<ScenarioCtx> context;
      auto* sens = ObtainSignalObject<ISensor>(signal_name);

      while (true) {
        std::any subsc_ctx;
        {
          std::lock_guard<std::mutex> lock(unsubscribe_mutex);
          if (!context->subscribe_context_arr.empty()) {
            subsc_ctx = std::move(context->subscribe_context_arr.back());
            context->subscribe_context_arr.pop_back();
          } else {
            break;  // break while
          }
        }
        auto ret = sens->UnSubscribe(std::move(subsc_ctx));
        EXPECT_TRUE(ret.IsOk());
      }
    });
  }
  for (auto&& th : ths) th.join();
}

/*
  @CleanupRestoreNetwork
  Scenario Outline: Unsubscribe requests during network failure result in client error
    Given HeadlessApp subscribe the sensor signal <path> which is initialized <value> of datatype <datatype>
    When network failure of <network_failure> is injected
    Then attempts to unsubscribe the subscription to <path> of <datatype> are failed
*/
GIVEN(
    "^HeadlessApp subscribe the sensor signal (\\S+) which is initialized "
    "(\\S+) of datatype (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, datatype_str);

  yoriito::ValueType value_init =
      ConvertValueStr2ValueType(datatype_str, value_str);

  // set
  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  yoriito::databroker::ProducerSetRequest target{
      std::vector<yoriito::databroker::ProducerSetDataPoint>{
          {signal_name, value_init, true, false}}};
  auto ret = producer->Set(target);
  EXPECT_TRUE(ret.IsOk());

  // subscribe
  auto* sens = ObtainSignalObject<ISensor>(signal_name);

  auto subsc_ret = sens->Subscribe();
  EXPECT_TRUE(subsc_ret.IsOk());
  ScenarioScope<ScenarioCtx> context;
  context->subscribe_context_arr.push_back(
      std::move(subsc_ret.TakeOk().value()));
}

// WHEN is same as the step in step_subscribe.cpp
THEN(
    "^attempts to unsubscribe the subscription to (\\S+) of (\\S+) are "
    "failed$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);

  ScenarioScope<ScenarioCtx> context;
  auto* sens = ObtainSignalObject<ISensor>(signal_name);

  for (auto&& ctx : context->subscribe_context_arr) {
    auto ret = sens->UnSubscribe(std::move(ctx));
    EXPECT_FALSE(ret.IsOk());
  }
}

/*
  Scenario Outline: Unsubscribe requests after recovery from network failure are succeeded
    Given HeadlessApp subscribe the sensor signal <path> which is initialized <value> of datatype <datatype>
    When network failure of <network_failure> is injected
    And network is restored from the failure
    Then attempts to unsubscribe the subscription to <path> of <datatype> are succeeded
*/
// GIVEN is same as the step in step_unsubscribe.cpp
// WHEN is same as the step in step_subscribe.cpp
WHEN("^network is restored from the failure$") {
  // restore network & wait for a while
  OperateNetwork(NetworkOperation::kCleanup);
}
THEN(
    "^attempts to unsubscribe the subscription to (\\S+) of (\\S+) are "
    "succeeded$") {
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
  @CleanupRestoreServer
  Scenario Outline: Unsubscribe requests during server down result in client error
    Given HeadlessApp subscribe the sensor signal <path> which is initialized <value> of datatype <datatype>
    When the server is stopped
    Then attempts to unsubscribe the subscription to <path> of <datatype> are failed
*/
// GIVEN is same as the step in step_subscribe.cpp
// WHEN is same as the step in step_subscribe.cpp
// THEN is same as the step in step_subscribe.cpp

/*
  @CleanupRestoreServer
  Scenario Outline: Unsubscribe requests after server reset are succeeded
    Given HeadlessApp subscribe the sensor signal <path> which is initialized <value> of datatype <datatype>
    When the server is reset 
    Then attempts to unsubscribe the subscription to <path> of <datatype> are succeeded
*/
// GIVEN is same as the step in step_subscribe.cpp
// WHEN is same as the step in step_subscribe.cpp
// THEN is same as the step in step_subscribe.cpp
}  // namespace
