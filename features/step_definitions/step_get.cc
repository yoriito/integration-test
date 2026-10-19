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
#include "databroker_type.h"
#include "step.h"

namespace {

constexpr int64_t kProducedTimestamp = 1735689600;  // 2025-01-01T00:00:00Z

/*
  Scenario Outline: HeadlessApp_Get_Sensor_Value
      Given PAL set sensor signal <path> to <datatype> <value>
      When HeadlessApp get the sensor signal <path> of <datatype>
      Then the result should be <datatype> <value> on <path>
*/
GIVEN("^PAL set sensor signal (\\S+) to (\\S+) (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);

  yoriito::ValueType value_init =
      ConvertValueStr2ValueType(datatype_str, value_str);

  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  yoriito::databroker::ProducerSetRequest target{
      std::vector<yoriito::databroker::ProducerSetDataPoint>{
          {signal_name, value_init, true, false}}};
  auto ret = producer->Set(target);
  EXPECT_TRUE(ret.IsOk());
}
WHEN("^HeadlessApp get the sensor signal (\\S+) of (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);

  cucumber::ScenarioScope<ScenarioCtx> context;
  auto* obj = ObtainSignalObject<IAttribute>(signal_name);
  auto ret = obj->Get();
  EXPECT_TRUE(ret.IsOk());
  auto val = ret.TakeOk();
  EXPECT_TRUE(val.has_value());
  context->get_value = std::move(val.value());
}
THEN("^the result should be (\\S+) (\\S+) on (\\S+)$") {
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, signal_name);

  cucumber::ScenarioScope<ScenarioCtx> context;
  yoriito::ValueType value_init =
      ConvertValueStr2ValueType(datatype_str, value_str);
  EXPECT_TRUE(
      yoriito::ValueTypeEquals(context->get_value->GetData(), value_init));
  EXPECT_EQ(context->get_value->GetPath(), signal_name);
  EXPECT_TRUE(context->get_value->IsAvailableSensor());
  EXPECT_GT(context->get_value->GetStoredTimestamp(), 0);
}

/*
  Scenario Outline: HeadlessApp_Get_Sensor_Value_Unavailable
      Given PAL set sensor signal <path> to <datatype> <value> as unavailable
      When HeadlessApp get the sensor signal <path> of <datatype>
      Then the result should be <datatype> <value> on <path> as unavailable as sensor
*/
GIVEN("^PAL set sensor signal (\\S+) to (\\S+) (\\S+) as unavailable$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);

  yoriito::ValueType value_init =
      ConvertValueStr2ValueType(datatype_str, value_str);

  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  yoriito::databroker::ProducerSetRequest target{
      std::vector<yoriito::databroker::ProducerSetDataPoint>{
          {signal_name, value_init, false, false}}};
  auto ret = producer->Set(target);
  EXPECT_TRUE(ret.IsOk());
}
// When is same as the above
THEN(
    "^the result should be (\\S+) (\\S+) on (\\S+) as unavailable as sensor$") {
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);
  REGEX_PARAM(std::string, signal_name);

  cucumber::ScenarioScope<ScenarioCtx> context;
  yoriito::ValueType value_init =
      ConvertValueStr2ValueType(datatype_str, value_str);
  EXPECT_TRUE(
      yoriito::ValueTypeEquals(context->get_value->GetData(), value_init));
  EXPECT_EQ(context->get_value->GetPath(), signal_name);
  EXPECT_FALSE(context->get_value->IsAvailableSensor());
  EXPECT_GT(context->get_value->GetStoredTimestamp(), 0);
}

/*
  Scenario Outline: HeadlessApp_Get_Sensor_Available_As_Actuator
      Given PAL set sensor signal <path> to <datatype> <value> as available actuator
      When HeadlessApp get the sensor signal <path> of <datatype>
      Then the result should be available as actuator on <path>
*/
GIVEN("^PAL set sensor signal (\\S+) to (\\S+) (\\S+) as available actuator$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);

  yoriito::ValueType value_init =
      ConvertValueStr2ValueType(datatype_str, value_str);

  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  yoriito::databroker::ProducerSetRequest target{
      std::vector<yoriito::databroker::ProducerSetDataPoint>{
          {signal_name, value_init, true, true}}};
  auto ret = producer->Set(target);
  EXPECT_TRUE(ret.IsOk());
}
// When is same as the above
THEN("^the result should be available as actuator on (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);

  cucumber::ScenarioScope<ScenarioCtx> context;
  EXPECT_EQ(context->get_value->GetPath(), signal_name);
  EXPECT_TRUE(context->get_value->IsAvailableActuator());
}

/*
  Scenario Outline: HeadlessApp_Get_Sensor_With_ProducedTimestamp
      Given PAL set sensor signal <path> to <datatype> <value> with a produced timestamp
      When HeadlessApp get the sensor signal <path> of <datatype>
      Then the result should have a produced timestamp on <path>
*/
GIVEN(
    "^PAL set sensor signal (\\S+) to (\\S+) (\\S+) with a produced "
    "timestamp$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);

  yoriito::ValueType value_init =
      ConvertValueStr2ValueType(datatype_str, value_str);

  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  yoriito::databroker::ProducerSetRequest target{
      std::vector<yoriito::databroker::ProducerSetDataPoint>{
          {signal_name, value_init, true, false, kProducedTimestamp}}};
  auto ret = producer->Set(target);
  EXPECT_TRUE(ret.IsOk());
}
// When is same as the above
THEN("^the result should have a produced timestamp on (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);

  cucumber::ScenarioScope<ScenarioCtx> context;
  EXPECT_EQ(context->get_value->GetPath(), signal_name);
  EXPECT_EQ(context->get_value->GetProducedTimestamp(), kProducedTimestamp);
}
}  // namespace