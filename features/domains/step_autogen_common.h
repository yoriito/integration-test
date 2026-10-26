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


#ifndef __INTEGRATION_TEST_STEP_AUTOGEN_COMMON_HEADER__
#define __INTEGRATION_TEST_STEP_AUTOGEN_COMMON_HEADER__

#include "databroker_type.h"
#include "Struct_Acceleration.h"
#include "Struct_AngularVelocity.h"
#include "Struct_Electricity.h"
#include "Struct_GNSSLocation.h"
#include "Struct_Location.h"
#include "Struct_PointingDirection.h"
#include "Struct_Pose.h"
#include "Struct_RoadFrictionRange.h"
#include "Struct_ThreePhaseCurrentMeasurements.h"
#include "Struct_ThreePhaseVoltageMeasurements.h"
#include "Struct_VehicleLocation.h"


namespace integration::valuetype {
// Primary template for primitive (double, int8, ...) & STL(string, vector) data types.
template <typename T>
struct ReflectValueType {
    static T FromValueType(const yoriito::ValueType& v) {
        T out = std::get<T>(v);
        return out;
    }
    static yoriito::ValueType ToValueType(T& v) {
        return yoriito::ValueType{std::in_place_type<T>, v};
    }
};

// Specialized templates for complex data types (aka 'struct').
template<>
struct ReflectValueType<yoriito::types::Acceleration> {
    static yoriito::types::Acceleration FromValueType(const yoriito::ValueType& v) {
        yoriito::types::Acceleration obj{};
        const auto& st = std::get<yoriito::StructDataPtr>(v);
        for(const auto& [key, val] : st->GetProperties()) {
            if (key == "Longitudinal") {
                obj.longitudinal = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "Lateral") {
                obj.lateral = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "Vertical") {
                obj.vertical = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            
        }
        return obj;
    }

    static yoriito::ValueType ToValueType(yoriito::types::Acceleration& obj) {
        yoriito::StructDataPtr st = std::make_unique<yoriito::StructData>();
        st->SetProperty("Longitudinal", ReflectValueType<float>::ToValueType(obj.longitudinal));
        st->SetProperty("Lateral", ReflectValueType<float>::ToValueType(obj.lateral));
        st->SetProperty("Vertical", ReflectValueType<float>::ToValueType(obj.vertical));
        
        return yoriito::ValueType{std::in_place_type<yoriito::StructDataPtr>, std::move(st)};
    }
};
template<>
struct ReflectValueType<yoriito::types::AngularVelocity> {
    static yoriito::types::AngularVelocity FromValueType(const yoriito::ValueType& v) {
        yoriito::types::AngularVelocity obj{};
        const auto& st = std::get<yoriito::StructDataPtr>(v);
        for(const auto& [key, val] : st->GetProperties()) {
            if (key == "Roll") {
                obj.roll = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "Pitch") {
                obj.pitch = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "Yaw") {
                obj.yaw = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            
        }
        return obj;
    }

    static yoriito::ValueType ToValueType(yoriito::types::AngularVelocity& obj) {
        yoriito::StructDataPtr st = std::make_unique<yoriito::StructData>();
        st->SetProperty("Roll", ReflectValueType<float>::ToValueType(obj.roll));
        st->SetProperty("Pitch", ReflectValueType<float>::ToValueType(obj.pitch));
        st->SetProperty("Yaw", ReflectValueType<float>::ToValueType(obj.yaw));
        
        return yoriito::ValueType{std::in_place_type<yoriito::StructDataPtr>, std::move(st)};
    }
};
template<>
struct ReflectValueType<yoriito::types::Electricity> {
    static yoriito::types::Electricity FromValueType(const yoriito::ValueType& v) {
        yoriito::types::Electricity obj{};
        const auto& st = std::get<yoriito::StructDataPtr>(v);
        for(const auto& [key, val] : st->GetProperties()) {
            if (key == "Voltage") {
                obj.voltage = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "Current") {
                obj.current = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            
        }
        return obj;
    }

    static yoriito::ValueType ToValueType(yoriito::types::Electricity& obj) {
        yoriito::StructDataPtr st = std::make_unique<yoriito::StructData>();
        st->SetProperty("Voltage", ReflectValueType<float>::ToValueType(obj.voltage));
        st->SetProperty("Current", ReflectValueType<float>::ToValueType(obj.current));
        
        return yoriito::ValueType{std::in_place_type<yoriito::StructDataPtr>, std::move(st)};
    }
};
template<>
struct ReflectValueType<yoriito::types::GNSSLocation> {
    static yoriito::types::GNSSLocation FromValueType(const yoriito::ValueType& v) {
        yoriito::types::GNSSLocation obj{};
        const auto& st = std::get<yoriito::StructDataPtr>(v);
        for(const auto& [key, val] : st->GetProperties()) {
            if (key == "Timestamp") {
                obj.timestamp = ReflectValueType<std::string>::FromValueType(val);
                continue;
            }
            if (key == "Latitude") {
                obj.latitude = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            if (key == "Longitude") {
                obj.longitude = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            if (key == "HorizontalAccuracy") {
                obj.horizontal_accuracy = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            if (key == "Altitude") {
                obj.altitude = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            if (key == "VerticalAccuracy") {
                obj.vertical_accuracy = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            if (key == "FixType") {
                obj.fix_type = ReflectValueType<std::string>::FromValueType(val);
                continue;
            }
            
        }
        return obj;
    }

    static yoriito::ValueType ToValueType(yoriito::types::GNSSLocation& obj) {
        yoriito::StructDataPtr st = std::make_unique<yoriito::StructData>();
        st->SetProperty("Timestamp", ReflectValueType<std::string>::ToValueType(obj.timestamp));
        st->SetProperty("Latitude", ReflectValueType<double>::ToValueType(obj.latitude));
        st->SetProperty("Longitude", ReflectValueType<double>::ToValueType(obj.longitude));
        st->SetProperty("HorizontalAccuracy", ReflectValueType<double>::ToValueType(obj.horizontal_accuracy));
        st->SetProperty("Altitude", ReflectValueType<double>::ToValueType(obj.altitude));
        st->SetProperty("VerticalAccuracy", ReflectValueType<double>::ToValueType(obj.vertical_accuracy));
        st->SetProperty("FixType", ReflectValueType<std::string>::ToValueType(obj.fix_type));
        
        return yoriito::ValueType{std::in_place_type<yoriito::StructDataPtr>, std::move(st)};
    }
};
template<>
struct ReflectValueType<yoriito::types::Location> {
    static yoriito::types::Location FromValueType(const yoriito::ValueType& v) {
        yoriito::types::Location obj{};
        const auto& st = std::get<yoriito::StructDataPtr>(v);
        for(const auto& [key, val] : st->GetProperties()) {
            if (key == "Latitude") {
                obj.latitude = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            if (key == "Longitude") {
                obj.longitude = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            if (key == "Altitude") {
                obj.altitude = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            
        }
        return obj;
    }

    static yoriito::ValueType ToValueType(yoriito::types::Location& obj) {
        yoriito::StructDataPtr st = std::make_unique<yoriito::StructData>();
        st->SetProperty("Latitude", ReflectValueType<double>::ToValueType(obj.latitude));
        st->SetProperty("Longitude", ReflectValueType<double>::ToValueType(obj.longitude));
        st->SetProperty("Altitude", ReflectValueType<double>::ToValueType(obj.altitude));
        
        return yoriito::ValueType{std::in_place_type<yoriito::StructDataPtr>, std::move(st)};
    }
};
template<>
struct ReflectValueType<yoriito::types::PointingDirection> {
    static yoriito::types::PointingDirection FromValueType(const yoriito::ValueType& v) {
        yoriito::types::PointingDirection obj{};
        const auto& st = std::get<yoriito::StructDataPtr>(v);
        for(const auto& [key, val] : st->GetProperties()) {
            if (key == "Azimuth") {
                obj.azimuth = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "Elevation") {
                obj.elevation = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            
        }
        return obj;
    }

    static yoriito::ValueType ToValueType(yoriito::types::PointingDirection& obj) {
        yoriito::StructDataPtr st = std::make_unique<yoriito::StructData>();
        st->SetProperty("Azimuth", ReflectValueType<float>::ToValueType(obj.azimuth));
        st->SetProperty("Elevation", ReflectValueType<float>::ToValueType(obj.elevation));
        
        return yoriito::ValueType{std::in_place_type<yoriito::StructDataPtr>, std::move(st)};
    }
};
template<>
struct ReflectValueType<yoriito::types::Pose> {
    static yoriito::types::Pose FromValueType(const yoriito::ValueType& v) {
        yoriito::types::Pose obj{};
        const auto& st = std::get<yoriito::StructDataPtr>(v);
        for(const auto& [key, val] : st->GetProperties()) {
            if (key == "X") {
                obj.x = ReflectValueType<int16_t>::FromValueType(val);
                continue;
            }
            if (key == "Y") {
                obj.y = ReflectValueType<int16_t>::FromValueType(val);
                continue;
            }
            if (key == "Z") {
                obj.z = ReflectValueType<int16_t>::FromValueType(val);
                continue;
            }
            if (key == "Yaw") {
                obj.yaw = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "Pitch") {
                obj.pitch = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "Roll") {
                obj.roll = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            
        }
        return obj;
    }

    static yoriito::ValueType ToValueType(yoriito::types::Pose& obj) {
        yoriito::StructDataPtr st = std::make_unique<yoriito::StructData>();
        st->SetProperty("X", ReflectValueType<int16_t>::ToValueType(obj.x));
        st->SetProperty("Y", ReflectValueType<int16_t>::ToValueType(obj.y));
        st->SetProperty("Z", ReflectValueType<int16_t>::ToValueType(obj.z));
        st->SetProperty("Yaw", ReflectValueType<float>::ToValueType(obj.yaw));
        st->SetProperty("Pitch", ReflectValueType<float>::ToValueType(obj.pitch));
        st->SetProperty("Roll", ReflectValueType<float>::ToValueType(obj.roll));
        
        return yoriito::ValueType{std::in_place_type<yoriito::StructDataPtr>, std::move(st)};
    }
};
template<>
struct ReflectValueType<yoriito::types::RoadFrictionRange> {
    static yoriito::types::RoadFrictionRange FromValueType(const yoriito::ValueType& v) {
        yoriito::types::RoadFrictionRange obj{};
        const auto& st = std::get<yoriito::StructDataPtr>(v);
        for(const auto& [key, val] : st->GetProperties()) {
            if (key == "MostProbable") {
                obj.most_probable = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "LowerBound") {
                obj.lower_bound = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "UpperBound") {
                obj.upper_bound = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            
        }
        return obj;
    }

    static yoriito::ValueType ToValueType(yoriito::types::RoadFrictionRange& obj) {
        yoriito::StructDataPtr st = std::make_unique<yoriito::StructData>();
        st->SetProperty("MostProbable", ReflectValueType<float>::ToValueType(obj.most_probable));
        st->SetProperty("LowerBound", ReflectValueType<float>::ToValueType(obj.lower_bound));
        st->SetProperty("UpperBound", ReflectValueType<float>::ToValueType(obj.upper_bound));
        
        return yoriito::ValueType{std::in_place_type<yoriito::StructDataPtr>, std::move(st)};
    }
};
template<>
struct ReflectValueType<yoriito::types::ThreePhaseCurrentMeasurements> {
    static yoriito::types::ThreePhaseCurrentMeasurements FromValueType(const yoriito::ValueType& v) {
        yoriito::types::ThreePhaseCurrentMeasurements obj{};
        const auto& st = std::get<yoriito::StructDataPtr>(v);
        for(const auto& [key, val] : st->GetProperties()) {
            if (key == "Phase1") {
                obj.phase1 = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "Phase2") {
                obj.phase2 = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "Phase3") {
                obj.phase3 = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            
        }
        return obj;
    }

    static yoriito::ValueType ToValueType(yoriito::types::ThreePhaseCurrentMeasurements& obj) {
        yoriito::StructDataPtr st = std::make_unique<yoriito::StructData>();
        st->SetProperty("Phase1", ReflectValueType<float>::ToValueType(obj.phase1));
        st->SetProperty("Phase2", ReflectValueType<float>::ToValueType(obj.phase2));
        st->SetProperty("Phase3", ReflectValueType<float>::ToValueType(obj.phase3));
        
        return yoriito::ValueType{std::in_place_type<yoriito::StructDataPtr>, std::move(st)};
    }
};
template<>
struct ReflectValueType<yoriito::types::ThreePhaseVoltageMeasurements> {
    static yoriito::types::ThreePhaseVoltageMeasurements FromValueType(const yoriito::ValueType& v) {
        yoriito::types::ThreePhaseVoltageMeasurements obj{};
        const auto& st = std::get<yoriito::StructDataPtr>(v);
        for(const auto& [key, val] : st->GetProperties()) {
            if (key == "Phase1") {
                obj.phase1 = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "Phase2") {
                obj.phase2 = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            if (key == "Phase3") {
                obj.phase3 = ReflectValueType<float>::FromValueType(val);
                continue;
            }
            
        }
        return obj;
    }

    static yoriito::ValueType ToValueType(yoriito::types::ThreePhaseVoltageMeasurements& obj) {
        yoriito::StructDataPtr st = std::make_unique<yoriito::StructData>();
        st->SetProperty("Phase1", ReflectValueType<float>::ToValueType(obj.phase1));
        st->SetProperty("Phase2", ReflectValueType<float>::ToValueType(obj.phase2));
        st->SetProperty("Phase3", ReflectValueType<float>::ToValueType(obj.phase3));
        
        return yoriito::ValueType{std::in_place_type<yoriito::StructDataPtr>, std::move(st)};
    }
};
template<>
struct ReflectValueType<yoriito::types::VehicleLocation> {
    static yoriito::types::VehicleLocation FromValueType(const yoriito::ValueType& v) {
        yoriito::types::VehicleLocation obj{};
        const auto& st = std::get<yoriito::StructDataPtr>(v);
        for(const auto& [key, val] : st->GetProperties()) {
            if (key == "Timestamp") {
                obj.timestamp = ReflectValueType<std::string>::FromValueType(val);
                continue;
            }
            if (key == "Latitude") {
                obj.latitude = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            if (key == "Longitude") {
                obj.longitude = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            if (key == "HorizontalAccuracy") {
                obj.horizontal_accuracy = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            if (key == "Altitude") {
                obj.altitude = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            if (key == "VerticalAccuracy") {
                obj.vertical_accuracy = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            if (key == "Heading") {
                obj.heading = ReflectValueType<double>::FromValueType(val);
                continue;
            }
            
        }
        return obj;
    }

    static yoriito::ValueType ToValueType(yoriito::types::VehicleLocation& obj) {
        yoriito::StructDataPtr st = std::make_unique<yoriito::StructData>();
        st->SetProperty("Timestamp", ReflectValueType<std::string>::ToValueType(obj.timestamp));
        st->SetProperty("Latitude", ReflectValueType<double>::ToValueType(obj.latitude));
        st->SetProperty("Longitude", ReflectValueType<double>::ToValueType(obj.longitude));
        st->SetProperty("HorizontalAccuracy", ReflectValueType<double>::ToValueType(obj.horizontal_accuracy));
        st->SetProperty("Altitude", ReflectValueType<double>::ToValueType(obj.altitude));
        st->SetProperty("VerticalAccuracy", ReflectValueType<double>::ToValueType(obj.vertical_accuracy));
        st->SetProperty("Heading", ReflectValueType<double>::ToValueType(obj.heading));
        
        return yoriito::ValueType{std::in_place_type<yoriito::StructDataPtr>, std::move(st)};
    }
};

} // namespace integration::valuetype
#endif