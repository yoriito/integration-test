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

GIVEN("^PAL set a signal (\\S+) to (\\S+) (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);
  REGEX_PARAM(std::string, value_str);

  cucumber::ScenarioScope<ScenarioCtx> context;
  yoriito::ValueType value_init =
      ConvertValueStr2ValueType(datatype_str, value_str);
  auto* producer =
      yoriito::databroker::DataBrokerProducerFactory::GetInstance();
  yoriito::databroker::ProducerSetRequest target{
      std::vector<yoriito::databroker::ProducerSetDataPoint>{
          {signal_name, value_init, true, false}}};
  auto ret = producer->Set(target);
  EXPECT_TRUE(ret.IsOk());

  context->set_value = std::move(value_init);
}

THEN("^HeadlessApp can inspect the signal (\\S+) of (\\S+)$") {
  REGEX_PARAM(std::string, signal_name);
  REGEX_PARAM(std::string, datatype_str);

  cucumber::ScenarioScope<ScenarioCtx> context;
  auto* obj = ObtainSignalObject<IAttribute>(signal_name);
  auto ret = obj->Inspect();
  EXPECT_TRUE(ret.IsOk());
  auto metadata = ret.TakeOk().value();
  EXPECT_EQ(metadata.GetPath(), signal_name);
  EXPECT_EQ(metadata.GetEntryType(), obj->GetSignalType());
  EXPECT_EQ(metadata.GetDataType(),
            GetDataTypeFromValueType(context->set_value));
}
}  // namespace