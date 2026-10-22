# SPDX-License-Identifier: Apache-2.0
#
# Copyright 2026 JASPAR
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.28)
project(test_integration)

include("${CMAKE_SOURCE_DIR}/cmake/yoriito_common.cmake")

include(FetchContent)

# cucumber-cpp
FetchContent_Declare(
    cucumber_cpp
    GIT_REPOSITORY https://github.com/cucumber/cucumber-cpp.git
    GIT_TAG main
)
set(CUKE_ENABLE_GTEST ON CACHE BOOL "" FORCE)

# google test
FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# nlohmann-json (fixme to use upstream nlohmann-json)
FetchContent_Declare(
    NlohmannJson
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG develop
)
FetchContent_MakeAvailable(cucumber_cpp GoogleTest NlohmannJson)

# absl
find_package(absl REQUIRED strings)

# Build per domain wi/ partial refactor in IntegrationTest(IT)
set(INTEGRATION_TEST_SOURCES
    ../../step_definitions/step_get.cc
    ../../step_definitions/step_set.cc
    ../../step_definitions/step_subscribe.cc
    ../../step_definitions/step_unsubscribe.cc
    ../../step_definitions/step_inspect.cc
)
set(INTEGRATION_TEST_DEPENDENCY_LIBRARIES
    cucumber-cpp
    GTest::gtest
    nlohmann_json::nlohmann_json
    absl::strings
    logger
    databroker_producer
    databroker_common
    databroker_consumer
    yoriito_vehicle_api_struct
)

add_subdirectory(features/domains/)