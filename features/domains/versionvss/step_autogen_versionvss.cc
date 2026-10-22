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


#include "../../step_definitions/step.h"


#include "versionvss/VersionVSS.h" // IWYU pragma: keep

namespace {
__attribute__((constructor)) void InitVersionVSS(void) {
    REGISTER_ATTRIBUTE("Vehicle.VersionVSS.Label", yoriito::vehicle::versionvss::label, std::string);
    REGISTER_ATTRIBUTE("Vehicle.VersionVSS.Major", yoriito::vehicle::versionvss::major, uint32_t);
    REGISTER_ATTRIBUTE("Vehicle.VersionVSS.Minor", yoriito::vehicle::versionvss::minor, uint32_t);
    REGISTER_ATTRIBUTE("Vehicle.VersionVSS.Patch", yoriito::vehicle::versionvss::patch, uint32_t);
    
} // namespace
}