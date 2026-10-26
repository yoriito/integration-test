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

#ifndef __INTEGRATION_TEST_HEADER__
#define __INTEGRATION_TEST_HEADER__
#include <absl/strings/match.h>
#include <gtest/gtest.h>
#include <unistd.h>

#include <any>
#include <cstdlib>
#include <exception>
#include <functional>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <variant>

#include "../domains/step_autogen_common.h"
#include "base_inspect_data.h"
#include "consumer_get_datapoint.h"
#include "cucumber-cpp/autodetect.hpp"
#include "databroker/consumer_get_datapoint.h"
#include "databroker/consumer_inspect_data.h"
#include "databroker_type.h"
#include "error.h"
#include "result.h"
#include "signal/signal_get_datapoint.h"
#include "signal/signal_subscribe_context.h"
#include "signal_data_type.h"
#include "signal_inspect_response.h"

/* Cucumber-CPP */
struct ScenarioCtx {
  std::optional<yoriito::databroker::ConsumerGetDataPoint> get_value;
  yoriito::ValueType set_value;
  std::vector<std::any> subscribe_context_arr;
  std::vector<yoriito::ValueType> subscribe_expect;
  std::vector<yoriito::ValueType> subscribe_actual;
};

/* Utility */

// start/stop/reset/status kura server
enum KuraOperation {
  kStart,
  kStop,
  kReset,
  kStatus,
};
inline bool OperateKura(KuraOperation ko) {
  using namespace std::chrono_literals;
  bool ret = true;
  std::string start("s6-svc -u /run/service/kura/");
  std::string stop(
      "s6-svc -d /run/service/kura/ > /dev/null 2>&1 && pkill kura > "
      "/dev/null 2>&1");
  std::string status("s6-svstat /run/service/kura/");
  switch (ko) {
    case KuraOperation::kStart:
      ret = std::system(start.c_str()) == 0;
      break;
    case KuraOperation::kStop:
      // finish is not registered, send sigterm after svc stop
      ret &= std::system(stop.c_str()) == 0;
      break;
    case KuraOperation::kReset:
      ret &= std::system(stop.c_str()) == 0;
      ret &= std::system(start.c_str()) == 0;
      std::this_thread::sleep_for(15000ms);
      break;
    case KuraOperation::kStatus:
    default:
      ret = false;
  }
  return ret;
}
enum NetworkOperation {
  kTimeout,
  kReject,
  kCleanup,
};
inline bool OperateNetwork(NetworkOperation no) {
  using namespace std::chrono_literals;
  bool ret = true;
  std::string timeout(
      "iptables -A OUTPUT -p tcp --dport 50052 -d 127.0.0.1 -j DROP");
  std::string reject(
      "iptables -A OUTPUT -p tcp --dport 50052 -d 127.0.0.1 -j REJECT "
      "--reject-with tcp-reset");
  std::string cleanup("iptables -D OUTPUT 1 > /dev/null 2>&1");
  switch (no) {
    case NetworkOperation::kTimeout:
      ret &= std::system(timeout.c_str()) == 0;
      std::this_thread::sleep_for(1000ms);
      break;
    case NetworkOperation::kReject:
      ret &= std::system(reject.c_str()) == 0;
      std::this_thread::sleep_for(1000ms);
      break;
    case NetworkOperation::kCleanup:
      ret &= std::system(cleanup.c_str()) == 0;
      std::this_thread::sleep_for(2000ms);
      break;
    default:
      ret = false;
  }
  return ret;
}

template <typename T>
static std::vector<T> ParseArray(const std::string& s) {
  auto j = nlohmann::json::parse(s);

  if (!j.is_array()) {
    throw std::runtime_error("Invalid type: expected an array");
  }
  return j.get<std::vector<T>>();
}

static inline yoriito::ValueType ConvertValueStr2ValueType(const std::string&,
                                                           const std::string&);

static inline yoriito::ValueType ConvertValueStrScalar2ValueType(
    const std::string& datatype_str, const std::string& value_str) {
  if (datatype_str == "bool")
    return value_str == "true"
               ? yoriito::ValueType{std::in_place_type_t<bool>(), true}
               : yoriito::ValueType{std::in_place_type_t<bool>(), false};
  if (datatype_str == "string")
    return yoriito::ValueType{std::in_place_type_t<std::string>(), value_str};
  if (datatype_str == "float")
    return yoriito::ValueType{std::in_place_type_t<float>(),
                              std::strtof(value_str.c_str(), nullptr)};
  if (datatype_str == "double")
    return yoriito::ValueType{std::in_place_type_t<double>(),
                              std::strtod(value_str.c_str(), nullptr)};
  if (datatype_str == "int8")
    return yoriito::ValueType{std::in_place_type_t<int8_t>(),
                              std::strtoll(value_str.c_str(), nullptr, 10)};
  if (datatype_str == "int16")
    return yoriito::ValueType{std::in_place_type_t<int16_t>(),
                              std::strtoll(value_str.c_str(), nullptr, 10)};
  if (datatype_str == "int32")
    return yoriito::ValueType{std::in_place_type_t<int32_t>(),
                              std::strtoll(value_str.c_str(), nullptr, 10)};
  if (datatype_str == "int64")
    return yoriito::ValueType{std::in_place_type_t<int64_t>(),
                              std::strtoll(value_str.c_str(), nullptr, 10)};
  if (datatype_str == "uint8")
    return yoriito::ValueType{std::in_place_type_t<uint8_t>(),
                              std::strtoull(value_str.c_str(), nullptr, 10)};
  if (datatype_str == "uint16")
    return yoriito::ValueType{std::in_place_type_t<uint16_t>(),
                              std::strtoull(value_str.c_str(), nullptr, 10)};
  if (datatype_str == "uint32")
    return yoriito::ValueType{std::in_place_type_t<uint32_t>(),
                              std::strtoull(value_str.c_str(), nullptr, 10)};
  if (datatype_str == "uint64")
    return yoriito::ValueType{std::in_place_type_t<uint64_t>(),
                              std::strtoull(value_str.c_str(), nullptr, 10)};
  EXPECT_STREQ("invalid datatype string", datatype_str.c_str());
  return yoriito::ValueType{};
}

static inline yoriito::ValueType ConvertValueStrArray2ValueType(
    const std::string& datatype_str, const std::string& value_str) {
  if (datatype_str == "bool[]")
    return yoriito::ValueType{std::in_place_type_t<std::vector<bool>>(),
                              ParseArray<bool>(value_str)};
  if (datatype_str == "string[]")
    return yoriito::ValueType{std::in_place_type_t<std::vector<std::string>>(),
                              ParseArray<std::string>(value_str)};
  if (datatype_str == "float[]")
    return yoriito::ValueType{std::in_place_type_t<std::vector<float>>(),
                              ParseArray<float>(value_str)};
  if (datatype_str == "double[]")
    return yoriito::ValueType{std::in_place_type_t<std::vector<double>>(),
                              ParseArray<double>(value_str)};
  if (datatype_str == "int8[]")
    return yoriito::ValueType{std::in_place_type_t<std::vector<int8_t>>(),
                              ParseArray<int8_t>(value_str)};
  if (datatype_str == "int16[]")
    return yoriito::ValueType{std::in_place_type_t<std::vector<int16_t>>(),
                              ParseArray<int16_t>(value_str)};
  if (datatype_str == "int32[]")
    return yoriito::ValueType{std::in_place_type_t<std::vector<int32_t>>(),
                              ParseArray<int32_t>(value_str)};
  if (datatype_str == "int64[]")
    return yoriito::ValueType{std::in_place_type_t<std::vector<int64_t>>(),
                              ParseArray<int64_t>(value_str)};
  if (datatype_str == "uint8[]")
    return yoriito::ValueType{std::in_place_type_t<std::vector<uint8_t>>(),
                              ParseArray<uint8_t>(value_str)};
  if (datatype_str == "uint16[]")
    return yoriito::ValueType{std::in_place_type_t<std::vector<uint16_t>>(),
                              ParseArray<uint16_t>(value_str)};
  if (datatype_str == "uint32[]")
    return yoriito::ValueType{std::in_place_type_t<std::vector<uint32_t>>(),
                              ParseArray<uint32_t>(value_str)};
  if (datatype_str == "uint64[]")
    return yoriito::ValueType{std::in_place_type_t<std::vector<uint64_t>>(),
                              ParseArray<uint64_t>(value_str)};
  EXPECT_STREQ("invalid datatype string", datatype_str.c_str());
  return yoriito::ValueType{};
}

// Expected input:
// (non-nested)
// '{
//    "Latitude": {"type": "double", "value": 35.000},
//    "Longitude": {"type": "double", "value": 135.12345},
//    "Altitude": {"type": "double", "value": 0.00001}
// }'
// (nested)
// '{
//    "prop1": {"type": "double", "value": 101.1},
//    "prop2": {"type": "complex", "value": {
//      "Latitude": {"type": "double", "value": 35.000},
//      "Longitude": {"type": "double", "value": 135.12345},
//      "Altitude": {"type": "double", "value": 0.00001}
//    }
// }'
static inline yoriito::ValueType ConvertValueStrComplex2ValueType(
    const std::string& value_str) {
  auto j = nlohmann::json::parse(value_str);
  if (!j.is_structured()) {
    throw std::runtime_error("Invalid type: expected an dictionary");
  }
  yoriito::StructData sd{};

  for (const auto& [k, v] : j.items()) {
    if (!v["value"].is_string())
      // v["value"] must be changed to string as it would be object in case of 'nested' structure
      sd.SetProperty(k, ConvertValueStr2ValueType(
                            v["type"], nlohmann::to_string(v["value"])));
    else
      sd.SetProperty(k, ConvertValueStr2ValueType(v["type"], v["value"]));
  }
  return yoriito::ValueType{std::make_unique<yoriito::StructData>(sd)};
}

static inline bool IsComplex(const std::string& datatype_str) {
  return datatype_str == "complex";
}

static inline bool IsArray(const std::string& datatype_str) {
  return absl::StrContains(datatype_str, "[]");
}

static inline yoriito::ValueType ConvertValueStr2ValueType(
    const std::string& datatype_str, const std::string& value_str) {
  if (IsComplex(datatype_str)) {
    return ConvertValueStrComplex2ValueType(value_str);
  }
  if (IsArray(datatype_str)) {
    return ConvertValueStrArray2ValueType(datatype_str, value_str);
  }
  return ConvertValueStrScalar2ValueType(datatype_str, value_str);
}

static inline yoriito::databroker::BaseInspectData::DataType
GetDataTypeFromValueType(const yoriito::ValueType& v) {
  using dt = yoriito::databroker::BaseInspectData::DataType;
  if (std::holds_alternative<bool>(v)) return dt::DATA_TYPE_BOOLEAN;
  if (std::holds_alternative<std::string>(v)) return dt::DATA_TYPE_STRING;
  if (std::holds_alternative<float>(v)) return dt::DATA_TYPE_FLOAT;
  if (std::holds_alternative<double>(v)) return dt::DATA_TYPE_DOUBLE;
  if (std::holds_alternative<int8_t>(v)) return dt::DATA_TYPE_INT8;
  if (std::holds_alternative<int16_t>(v)) return dt::DATA_TYPE_INT16;
  if (std::holds_alternative<int32_t>(v)) return dt::DATA_TYPE_INT32;
  if (std::holds_alternative<int64_t>(v)) return dt::DATA_TYPE_INT64;
  if (std::holds_alternative<uint8_t>(v)) return dt::DATA_TYPE_UINT8;
  if (std::holds_alternative<uint16_t>(v)) return dt::DATA_TYPE_UINT16;
  if (std::holds_alternative<uint32_t>(v)) return dt::DATA_TYPE_UINT32;
  if (std::holds_alternative<uint64_t>(v)) return dt::DATA_TYPE_UINT64;
  if (std::holds_alternative<yoriito::StructDataPtr>(v))
    return dt::DATA_TYPE_STRUCT;
  if (std::holds_alternative<std::vector<bool>>(v))
    return dt::DATA_TYPE_BOOLEAN_ARRAY;
  if (std::holds_alternative<std::vector<std::string>>(v))
    return dt::DATA_TYPE_STRING_ARRAY;
  if (std::holds_alternative<std::vector<float>>(v))
    return dt::DATA_TYPE_FLOAT_ARRAY;
  if (std::holds_alternative<std::vector<double>>(v))
    return dt::DATA_TYPE_DOUBLE_ARRAY;
  if (std::holds_alternative<std::vector<int8_t>>(v))
    return dt::DATA_TYPE_INT8_ARRAY;
  if (std::holds_alternative<std::vector<int16_t>>(v))
    return dt::DATA_TYPE_INT16_ARRAY;
  if (std::holds_alternative<std::vector<int32_t>>(v))
    return dt::DATA_TYPE_INT32_ARRAY;
  if (std::holds_alternative<std::vector<int64_t>>(v))
    return dt::DATA_TYPE_INT64_ARRAY;
  if (std::holds_alternative<std::vector<uint8_t>>(v))
    return dt::DATA_TYPE_UINT8_ARRAY;
  if (std::holds_alternative<std::vector<uint16_t>>(v))
    return dt::DATA_TYPE_UINT16_ARRAY;
  if (std::holds_alternative<std::vector<uint32_t>>(v))
    return dt::DATA_TYPE_UINT32_ARRAY;
  if (std::holds_alternative<std::vector<uint64_t>>(v))
    return dt::DATA_TYPE_UINT64_ARRAY;

  return dt::DATA_TYPE_UNSPECIFIED;
}

static inline yoriito::databroker::BaseInspectData::EntryType
FromSignalEntryType(yoriito::signal::SignalEntryType v) {
  using et = yoriito::databroker::BaseInspectData::EntryType;
  using set = yoriito::signal::SignalEntryType;
  switch (v) {
    case set::SIGNAL_ENTRY_TYPE_ACTUATOR:
      return et::ENTRY_TYPE_ACTUATOR;
    case set::SIGNAL_ENTRY_TYPE_ATTRIBUTE:
      return et::ENTRY_TYPE_ATTRIBUTE;
    case set::SIGNAL_ENTRY_TYPE_SENSOR:
      return et::ENTRY_TYPE_SENSOR;
    case set::SIGNAL_ENTRY_TYPE_UNSPECIFIED:
    default:
      return et::ENTRY_TYPE_UNSPECIFIED;
  }
}

static inline yoriito::databroker::BaseInspectData::DataType FromSignalDataType(
    yoriito::signal::SignalDataType v) {
  using sdt = yoriito::signal::SignalDataType;
  using dt = yoriito::databroker::BaseInspectData::DataType;
  switch (v) {
    case sdt::SIGNAL_DATA_TYPE_BOOLEAN:
      return dt::DATA_TYPE_BOOLEAN;
    case sdt::SIGNAL_DATA_TYPE_STRING:
      return dt::DATA_TYPE_STRING;
    case sdt::SIGNAL_DATA_TYPE_FLOAT:
      return dt::DATA_TYPE_FLOAT;
    case sdt::SIGNAL_DATA_TYPE_DOUBLE:
      return dt::DATA_TYPE_DOUBLE;
    case sdt::SIGNAL_DATA_TYPE_INT8:
      return dt::DATA_TYPE_INT8;
    case sdt::SIGNAL_DATA_TYPE_INT16:
      return dt::DATA_TYPE_INT16;
    case sdt::SIGNAL_DATA_TYPE_INT32:
      return dt::DATA_TYPE_INT32;
    case sdt::SIGNAL_DATA_TYPE_INT64:
      return dt::DATA_TYPE_INT64;
    case sdt::SIGNAL_DATA_TYPE_UINT8:
      return dt::DATA_TYPE_UINT8;
    case sdt::SIGNAL_DATA_TYPE_UINT16:
      return dt::DATA_TYPE_UINT16;
    case sdt::SIGNAL_DATA_TYPE_UINT32:
      return dt::DATA_TYPE_UINT32;
    case sdt::SIGNAL_DATA_TYPE_UINT64:
      return dt::DATA_TYPE_UINT64;
    case sdt::SIGNAL_DATA_TYPE_STRUCT:
      return dt::DATA_TYPE_STRUCT;
    case sdt::SIGNAL_DATA_TYPE_BOOLEAN_ARRAY:
      return dt::DATA_TYPE_BOOLEAN_ARRAY;
    case sdt::SIGNAL_DATA_TYPE_STRING_ARRAY:
      return dt::DATA_TYPE_STRING_ARRAY;
    case sdt::SIGNAL_DATA_TYPE_FLOAT_ARRAY:
      return dt::DATA_TYPE_FLOAT_ARRAY;
    case sdt::SIGNAL_DATA_TYPE_DOUBLE_ARRAY:
      return dt::DATA_TYPE_DOUBLE_ARRAY;
    case sdt::SIGNAL_DATA_TYPE_INT8_ARRAY:
      return dt::DATA_TYPE_INT8_ARRAY;
    case sdt::SIGNAL_DATA_TYPE_INT16_ARRAY:
      return dt::DATA_TYPE_INT16_ARRAY;
    case sdt::SIGNAL_DATA_TYPE_INT32_ARRAY:
      return dt::DATA_TYPE_INT32_ARRAY;
    case sdt::SIGNAL_DATA_TYPE_INT64_ARRAY:
      return dt::DATA_TYPE_INT64_ARRAY;
    case sdt::SIGNAL_DATA_TYPE_UINT8_ARRAY:
      return dt::DATA_TYPE_UINT8_ARRAY;
    case sdt::SIGNAL_DATA_TYPE_UINT16_ARRAY:
      return dt::DATA_TYPE_UINT16_ARRAY;
    case sdt::SIGNAL_DATA_TYPE_UINT32_ARRAY:
      return dt::DATA_TYPE_UINT32_ARRAY;
    case sdt::SIGNAL_DATA_TYPE_UINT64_ARRAY:
      return dt::DATA_TYPE_UINT64_ARRAY;
    case sdt::SIGNAL_DATA_TYPE_UNSPECIFIED:
    default:
      return dt::DATA_TYPE_UNSPECIFIED;
  }
}

// Wrap response of Signal API GET into ConsumerGetDataPoint for type erase
template <typename T>
static yoriito::databroker::ConsumerGetDataPoint FromSignalGetDataPoint(
    yoriito::signal::SignalGetDataPoint<T> v) {
  auto data = v.GetData();
  yoriito::databroker::ConsumerGetDataPoint cgdp{
      v.GetPath(),
      integration::valuetype::ReflectValueType<T>::ToValueType(data),
      v.IsAvailableSensor(),
      v.IsAvailableActuator(),
      v.GetStoredTimestamp(),
      v.GetProducedTimestamp()};
  return cgdp;
}
// Wrap response of Signal API INSPECT into ConsumerInspectData for type erase
template <typename T>
static yoriito::databroker::ConsumerInspectData FromSignalInspectResponse(
    yoriito::signal::SignalInspectResponse<T> val) {
  auto v = val.GetDataPoints().front();
  yoriito::databroker::BaseInspectData::Builder bb{};

  auto allowed = v.GetAllowed();
  bb.SetPath(v.GetPath())
      .SetDataType(FromSignalDataType(v.GetDataType()))
      .SetEntryType(FromSignalEntryType(v.GetEntryType()))
      .SetDeprecation(v.GetDeprecation())
      .SetUnit(v.GetUnit())
      .SetAllowed(std::move(allowed))
      .SetDescription(v.GetDescription())
      .SetArraySize(v.GetArraySize())
      .SetPattern(v.GetPattern())
      .SetCustomAttributes(v.GetCustomAttributes())
      .SetComment(v.GetComment());
  if (v.GetMin().has_value()) {
    auto min = v.GetMin().value();
    bb.SetMin(integration::valuetype::ReflectValueType<T>::ToValueType(min));
  }
  if (v.GetMax().has_value()) {
    auto max = v.GetMax().value();
    bb.SetMin(integration::valuetype::ReflectValueType<T>::ToValueType(max));
  }
  if (v.GetDefaultValue().has_value()) {
    auto de_fault = v.GetDefaultValue().value();
    bb.SetMin(
        integration::valuetype::ReflectValueType<T>::ToValueType(de_fault));
  }
  yoriito::databroker::ConsumerInspectData cid{
      yoriito::databroker::BaseInspectData{bb.Build()}};
  return cid;
}
// Wrap response of Signal API Subscribe into ConsumerGetDataPoint for type erase
template <typename T>
yoriito::Result<yoriito::databroker::ConsumerGetDataPoint>
FromSignalSubscribeContext(const std::any& v) {
  yoriito::Result<yoriito::signal::SignalGetDataPoint<T>> msg =
      std::any_cast<
          std::shared_ptr<yoriito::signal::SignalSubscribeContext<T>>>(v)
          ->Messages();
  if (msg.IsErr()) {
    return yoriito::Result<yoriito::databroker::ConsumerGetDataPoint>::Err(
        msg.TakeErr());
  }
  auto sgdp = msg.TakeOk().value();
  auto data = sgdp.GetData();
  yoriito::databroker::ConsumerGetDataPoint cgdp{
      sgdp.GetPath(),
      integration::valuetype::ReflectValueType<T>::ToValueType(data),
      sgdp.IsAvailableSensor(),
      sgdp.IsAvailableActuator(),
      sgdp.GetStoredTimestamp(),
      sgdp.GetProducedTimestamp()};
  return yoriito::Result<yoriito::databroker::ConsumerGetDataPoint>::Ok(cgdp);
}

/* Interfaces */
class IGetable {
 public:
  virtual ~IGetable() = default;
  virtual yoriito::Result<yoriito::databroker::ConsumerGetDataPoint> Get() = 0;
  virtual yoriito::Result<yoriito::databroker::ConsumerInspectData>
  Inspect() = 0;
  virtual yoriito::databroker::BaseInspectData::EntryType GetSignalType() = 0;
};
class ISetable {
 public:
  virtual ~ISetable() = default;
  virtual yoriito::Result<void> Set(const yoriito::ValueType& v) = 0;
};
class ISubscribable {
 public:
  virtual ~ISubscribable() = default;
  virtual yoriito::Result<std::any> Subscribe() = 0;
  virtual yoriito::Result<void> UnSubscribe(std::any) = 0;
  virtual yoriito::Result<yoriito::databroker::ConsumerGetDataPoint> GetMessage(
      const std::any&) = 0;
};
class ISignal : public IGetable {};
class IAttribute : public ISignal {};
class ISensor : public IAttribute, public ISubscribable {};
class IActuator : public ISensor, public ISetable {};

/* Class Definitions & Implementations */
template <class T>
class ActuatorImpl : public IActuator {
 public:
  using GetF =
      std::function<yoriito::Result<yoriito::signal::SignalGetDataPoint<T>>()>;
  using SetF = std::function<yoriito::Result<void>(const T&)>;
  using SubscribeF = std::function<
      yoriito::Result<yoriito::signal::SignalSubscribeContext<T>>()>;
  using UnSubscribeF = std::function<yoriito::Result<void>(
      yoriito::signal::SignalSubscribeContext<T>)>;
  using InspectF = std::function<
      yoriito::Result<yoriito::signal::SignalInspectResponse<T>>()>;
  ActuatorImpl(GetF get, SetF set, SubscribeF sub, UnSubscribeF unsub,
               InspectF insp)
      : get_(std::move(get)),
        set_(std::move(set)),
        sub_(std::move(sub)),
        unsub_(std::move(unsub)),
        insp_(std::move(insp)){};

  yoriito::Result<yoriito::databroker::ConsumerGetDataPoint> Get() override {
    yoriito::Result<yoriito::signal::SignalGetDataPoint<T>> ret = get_();
    if (ret.IsOk()) {
      yoriito::signal::SignalGetDataPoint<T> body = ret.TakeOk().value();
      return yoriito::Result<yoriito::databroker::ConsumerGetDataPoint>::Ok(
          FromSignalGetDataPoint(body));
    }
    return yoriito::Result<yoriito::databroker::ConsumerGetDataPoint>::Err(
        ret.TakeErr());
  };
  yoriito::Result<void> Set(const yoriito::ValueType& v) override {
    T val = integration::valuetype::ReflectValueType<T>::FromValueType(v);
    return set_(val);
  }
  yoriito::Result<std::any> Subscribe() override {
    yoriito::Result<yoriito::signal::SignalSubscribeContext<T>> ret = sub_();
    if (ret.IsOk()) {
      // NOTE: as subscribe context has unique ptr and thus no copy-constructor,
      // it is impossible to store it in std::any, directly.
      // wrap it in shared_ptr<void> is just a hack.
      std::shared_ptr<yoriito::signal::SignalSubscribeContext<T>> v =
          std::make_shared<yoriito::signal::SignalSubscribeContext<T>>(
              std::move(ret.TakeOk().value()));
      return yoriito::Result<std::any>::Ok(v);
    }
    return yoriito::Result<std::any>::Err(ret.TakeErr());
  }
  yoriito::Result<void> UnSubscribe(std::any v) override {
    std::shared_ptr<yoriito::signal::SignalSubscribeContext<T>> ctx =
        std::any_cast<
            std::shared_ptr<yoriito::signal::SignalSubscribeContext<T>>>(v);
    return unsub_(std::move(*ctx));
  }
  yoriito::Result<yoriito::databroker::ConsumerInspectData> Inspect() override {
    yoriito::Result<yoriito::signal::SignalInspectResponse<T>> ret = insp_();
    if (ret.IsOk()) {
      return yoriito::Result<yoriito::databroker::ConsumerInspectData>::Ok(
          FromSignalInspectResponse(ret.TakeOk().value()));
    }
    return yoriito::Result<yoriito::databroker::ConsumerInspectData>::Err(
        ret.TakeErr());
  }
  yoriito::databroker::BaseInspectData::EntryType GetSignalType() override {
    return yoriito::databroker::BaseInspectData::EntryType::ENTRY_TYPE_ACTUATOR;
  }

  yoriito::Result<yoriito::databroker::ConsumerGetDataPoint> GetMessage(
      const std::any& v) override {
    return FromSignalSubscribeContext<T>(v);
  }

 private:
  GetF get_;
  SetF set_;
  SubscribeF sub_;
  UnSubscribeF unsub_;
  InspectF insp_;
};

template <class T>
class SensorImpl : public ISensor {
 public:
  using GetF =
      std::function<yoriito::Result<yoriito::signal::SignalGetDataPoint<T>>()>;
  using SubscribeF = std::function<
      yoriito::Result<yoriito::signal::SignalSubscribeContext<T>>()>;
  using UnSubscribeF = std::function<yoriito::Result<void>(
      yoriito::signal::SignalSubscribeContext<T>)>;
  using InspectF = std::function<
      yoriito::Result<yoriito::signal::SignalInspectResponse<T>>()>;
  SensorImpl(GetF get, SubscribeF sub, UnSubscribeF unsub, InspectF insp)
      : get_(std::move(get)),
        sub_(std::move(sub)),
        unsub_(std::move(unsub)),
        insp_(std::move(insp)){};

  yoriito::Result<yoriito::databroker::ConsumerGetDataPoint> Get() override {
    yoriito::Result<yoriito::signal::SignalGetDataPoint<T>> ret = get_();
    if (ret.IsOk()) {
      yoriito::signal::SignalGetDataPoint<T> body = ret.TakeOk().value();
      return yoriito::Result<yoriito::databroker::ConsumerGetDataPoint>::Ok(
          FromSignalGetDataPoint(body));
    }
    return yoriito::Result<yoriito::databroker::ConsumerGetDataPoint>::Err(
        ret.TakeErr());
  };
  yoriito::Result<std::any> Subscribe() override {
    yoriito::Result<yoriito::signal::SignalSubscribeContext<T>> ret = sub_();
    if (ret.IsOk()) {
      // NOTE: as subscribe context has unique ptr and thus no copy-constructor,
      // it is impossible to store it in std::any, directly.
      // wrap it in shared_ptr<void> is just a hack.
      std::shared_ptr<yoriito::signal::SignalSubscribeContext<T>> v =
          std::make_shared<yoriito::signal::SignalSubscribeContext<T>>(
              std::move(ret.TakeOk().value()));
      return yoriito::Result<std::any>::Ok(v);
    }
    return yoriito::Result<std::any>::Err(ret.TakeErr());
  }
  yoriito::Result<void> UnSubscribe(std::any v) override {
    std::shared_ptr<yoriito::signal::SignalSubscribeContext<T>> ctx =
        std::any_cast<
            std::shared_ptr<yoriito::signal::SignalSubscribeContext<T>>>(v);
    return unsub_(std::move(*ctx));
  }
  yoriito::Result<yoriito::databroker::ConsumerInspectData> Inspect() override {
    yoriito::Result<yoriito::signal::SignalInspectResponse<T>> ret = insp_();
    if (ret.IsOk()) {
      return yoriito::Result<yoriito::databroker::ConsumerInspectData>::Ok(
          FromSignalInspectResponse(ret.TakeOk().value()));
    }
    return yoriito::Result<yoriito::databroker::ConsumerInspectData>::Err(
        ret.TakeErr());
  }
  yoriito::databroker::BaseInspectData::EntryType GetSignalType() override {
    return yoriito::databroker::BaseInspectData::EntryType::ENTRY_TYPE_SENSOR;
  }

  yoriito::Result<yoriito::databroker::ConsumerGetDataPoint> GetMessage(
      const std::any& v) override {
    return FromSignalSubscribeContext<T>(v);
  }

 private:
  GetF get_;
  SubscribeF sub_;
  UnSubscribeF unsub_;
  InspectF insp_;
};

template <class T>
class AttributeImpl : public IAttribute {
 public:
  using GetF =
      std::function<yoriito::Result<yoriito::signal::SignalGetDataPoint<T>>()>;
  using InspectF = std::function<
      yoriito::Result<yoriito::signal::SignalInspectResponse<T>>()>;
  AttributeImpl(GetF get, InspectF insp)
      : get_(std::move(get)), insp_(std::move(insp)){};

  yoriito::Result<yoriito::databroker::ConsumerGetDataPoint> Get() override {
    auto ret = get_();
    if (ret.IsOk()) {
      return yoriito::Result<yoriito::databroker::ConsumerGetDataPoint>::Ok(
          FromSignalGetDataPoint(ret.TakeOk().value()));
    }
    return yoriito::Result<yoriito::databroker::ConsumerGetDataPoint>::Err(
        ret.TakeErr());
  };
  yoriito::Result<yoriito::databroker::ConsumerInspectData> Inspect() override {
    yoriito::Result<yoriito::signal::SignalInspectResponse<T>> ret = insp_();
    if (ret.IsOk()) {
      return yoriito::Result<yoriito::databroker::ConsumerInspectData>::Ok(
          FromSignalInspectResponse(ret.TakeOk().value()));
    }
    return yoriito::Result<yoriito::databroker::ConsumerInspectData>::Err(
        ret.TakeErr());
  }
  yoriito::databroker::BaseInspectData::EntryType GetSignalType() override {
    return yoriito::databroker::BaseInspectData::EntryType::
        ENTRY_TYPE_ATTRIBUTE;
  }

 private:
  GetF get_;
  InspectF insp_;
};

/* Registry */
class SignalRegistry {
 public:
  // singleton
  static SignalRegistry& GetInstance() {
    static SignalRegistry inst;
    return inst;
  }
  // push
  void Register(const std::string& path, std::unique_ptr<ISignal> signal) {
    registry_.emplace(std::move(path), std::move(signal));
  }
  // pop
  ISignal* Obtain(const std::string& path) {
    try {
      return registry_.at(path).get();
    } catch (std::exception& e) {
      EXPECT_STREQ(path.c_str(),
                   "Signal Not Found");  // throw GoogleTestFailureException
      throw;
    }
  }

 private:
  std::unordered_map<std::string, std::unique_ptr<ISignal>> registry_;
};

// Get Signal API object (T is whether IActuator, ISensor or IAttribute)
template <typename T>
T* ObtainSignalObject(const std::string& path) {
  ISignal* sig = SignalRegistry::GetInstance().Obtain(path);
  auto obj = dynamic_cast<T*>(sig);
  EXPECT_NE(obj, nullptr);  // throw GoogleTestFailureException

  return obj;
}

#define REGISTER_ACTUATOR(SIG_NAME, NS, DATA_TYPE)                         \
  {                                                                        \
    /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                       \
    auto instance = std::make_unique<ActuatorImpl<DATA_TYPE>>(             \
        []() {                                                             \
          auto ret = NS::Get();                                            \
          return ret;                                                      \
        },                                                                 \
        [](DATA_TYPE v) {                                                  \
          auto ret = NS::Set(v);                                           \
          return ret;                                                      \
        },                                                                 \
        []() {                                                             \
          auto ret = NS::Subscribe();                                      \
          return ret;                                                      \
        }, /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                \
        [](yoriito::signal::SignalSubscribeContext<DATA_TYPE> v) {         \
          auto ret = NS::UnSubscribe(std::move(v));                        \
          return ret;                                                      \
        },                                                                 \
        []() {                                                             \
          auto ret = NS::Inspect();                                        \
          return ret;                                                      \
        });                                                                \
    SignalRegistry::GetInstance().Register(SIG_NAME, std::move(instance)); \
  }

#define REGISTER_SENSOR(SIG_NAME, NS, DATA_TYPE)                           \
  {                                                                        \
    /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                       \
    auto instance = std::make_unique<SensorImpl<DATA_TYPE>>(               \
        []() {                                                             \
          auto ret = NS::Get();                                            \
          return ret;                                                      \
        },                                                                 \
        []() {                                                             \
          auto ret = NS::Subscribe();                                      \
          return ret;                                                      \
        }, /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                \
        [](yoriito::signal::SignalSubscribeContext<DATA_TYPE> v) {         \
          auto ret = NS::UnSubscribe(std::move(v));                        \
          return ret;                                                      \
        },                                                                 \
        []() {                                                             \
          auto ret = NS::Inspect();                                        \
          return ret;                                                      \
        });                                                                \
    SignalRegistry::GetInstance().Register(SIG_NAME, std::move(instance)); \
  }

#define REGISTER_ATTRIBUTE(SIG_NAME, NS, DATA_TYPE)                        \
  {                                                                        \
    /* NOLINTNEXTLINE(bugprone-macro-parentheses) */                       \
    auto instance = std::make_unique<AttributeImpl<DATA_TYPE>>(            \
        []() {                                                             \
          auto ret = NS::Get();                                            \
          return ret;                                                      \
        },                                                                 \
        []() {                                                             \
          auto ret = NS::Inspect();                                        \
          return ret;                                                      \
        });                                                                \
    SignalRegistry::GetInstance().Register(SIG_NAME, std::move(instance)); \
  }

/* usage xxxxxImpls */
// REGISTER_ACTUATOR("Vehicle.ADAS.ABS.IsEnabled",
//                   yoriito::vehicle::adas::abs::isenabled, bool);
// REGISTER_SENSOR("Vehicle.ADAS.ActiveAutonomyLevel",
//                 yoriito::vehicle::adas::activeautonomylevel, std::string);
// REGISTER_ATTRIBUTE("Vehicle.ADAS.SupportedAutonomyLevel",
//                   yoriito::vehicle::adas::supportedautonomylevel,
//                   std::string);

#endif