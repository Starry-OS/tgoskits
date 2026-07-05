cmake_minimum_required(VERSION 3.20)

project(asking_star_soil LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT TARGET asking_star_runtime)
  add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/../asking-star-runtime"
    "${CMAKE_BINARY_DIR}/asking-star-runtime"
  )
endif()

file(GLOB_RECURSE ASKING_STAR_SOIL_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(asking_star_soil STATIC ${ASKING_STAR_SOIL_SOURCES})
target_include_directories(asking_star_soil
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/../asking-star-runtime/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/../asking-star-runtime"
)
target_link_libraries(asking_star_soil PUBLIC asking_star_runtime)
target_compile_definitions(asking_star_soil
  PUBLIC
    ASKING_STAR_ENABLE_STARRYOS_ADAPTER=1
    ASKING_STAR_STARRYOS_ADAPTER_MODE_DRYRUN=1
)

enable_testing()

function(add_asking_star_soil_test target source)
  add_executable(${target} ${source})
  target_link_libraries(${target} PRIVATE asking_star_soil asking_star_runtime)
  add_test(NAME ${target} COMMAND ${target})
endfunction()

add_asking_star_soil_test(test_soil_kernel_request
  tests/unit/soil/test_kernel_request.cpp)
add_asking_star_soil_test(test_soil_kernel_request_record_bridge
  tests/unit/soil/test_kernel_request_record_bridge.cpp)
add_asking_star_soil_test(test_soil_kernel_result
  tests/unit/soil/test_kernel_result.cpp)
add_asking_star_soil_test(test_soil_return_rebuilder
  tests/unit/soil/test_return_rebuilder.cpp)
add_asking_star_soil_test(test_soil_starryos_operation_map
  tests/unit/soil/test_starryos_operation_map.cpp)
add_asking_star_soil_test(test_soil_starryos_adapter_dryrun
  tests/unit/soil/test_starryos_adapter_dryrun.cpp)
add_asking_star_soil_test(test_soil_starryos_boardreal_guard
  tests/unit/soil/test_starryos_boardreal_guard.cpp)
add_asking_star_soil_test(test_soil_contract_mock
  tests/integration/test_soil_contract_mock.cpp)
add_asking_star_soil_test(test_soil_linux_user_flow
  tests/integration/test_soil_linux_user_flow.cpp)
add_asking_star_soil_test(test_soil_starryos_dryrun_flow
  tests/integration/test_soil_starryos_dryrun_flow.cpp)
add_asking_star_soil_test(test_soil_forward_organ_return_rebuilder
  tests/integration/test_soil_forward_organ_return_rebuilder.cpp)
add_asking_star_soil_test(test_qemu_dry_run_integration
  tests/test_qemu_dry_run_integration.cpp)
add_asking_star_soil_test(test_v55_chamber_starryos_dryrun
  tests/integration/test_v55_chamber_starryos_dryrun.cpp)
add_asking_star_soil_test(test_v55_pouch_parallel_trace
  ../asking-star-runtime/tests/integration/test_v55_pouch_parallel_trace.cpp)
add_asking_star_soil_test(test_v55_replay_ai_chamber
  ../asking-star-runtime/tests/integration/test_v55_replay_ai_chamber.cpp)
add_asking_star_soil_test(test_v55_stable_starry_dryrun
  tests/integration/test_v55_stable_starry_dryrun.cpp)
add_asking_star_soil_test(test_v55_qemu_report_bridge
  tests/integration/test_v55_qemu_report_bridge.cpp)
