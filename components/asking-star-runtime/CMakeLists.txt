cmake_minimum_required(VERSION 3.20)

project(asking_star_runtime LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE ASKING_STAR_RUNTIME_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(asking_star_runtime STATIC ${ASKING_STAR_RUNTIME_SOURCES})
target_include_directories(asking_star_runtime
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

enable_testing()

function(add_asking_star_runtime_test target source)
  add_executable(${target} ${source})
  target_link_libraries(${target} PRIVATE asking_star_runtime)
  add_test(NAME ${target} COMMAND ${target})
endfunction()

add_asking_star_runtime_test(test_gcyy_digital_set_fragment
  tests/unit/gcyy/test_digital_set_fragment.cpp)
add_asking_star_runtime_test(test_gcyy_gene_view
  tests/unit/gcyy/test_gene_view.cpp)
add_asking_star_runtime_test(test_gcyy_charge_view
  tests/unit/gcyy/test_charge_view.cpp)
add_asking_star_runtime_test(test_digital_set_record
  tests/unit/digitalset/test_digital_set_record.cpp)
add_asking_star_runtime_test(test_ref_resolver
  tests/unit/digitalset/test_ref_resolver.cpp)
add_asking_star_runtime_test(test_fragment_to_cell_record
  tests/integration/test_fragment_to_cell_record.cpp)

add_asking_star_runtime_test(test_v55_s1_primordial_seed_refs
  tests/v55/test_s1_primordial_seed_refs.cpp)
add_asking_star_runtime_test(test_v55_s2_algebra_skeleton
  tests/v55/test_s2_algebra_skeleton.cpp)
add_asking_star_runtime_test(test_v55_s3_s4_walker_app_gene_charge
  tests/v55/test_s3_s4_walker_app_gene_charge.cpp)
add_asking_star_runtime_test(test_v55_s5_s8_chamber_pouch_reflex_soil
  tests/v55/test_s5_s8_chamber_pouch_reflex_soil.cpp)
add_asking_star_runtime_test(test_v55_s9_s12_skin_demo_pipeline
  tests/v55/test_s9_s12_skin_demo_pipeline.cpp)
add_asking_star_runtime_test(test_v55_record_mapping
  tests/unit/v55/test_v55_record_mapping.cpp)
add_asking_star_runtime_test(test_v55_app_charge_sun_admission
  tests/integration/test_v55_app_charge_sun_admission.cpp)
add_asking_star_runtime_test(test_v55_rknn_runtime_chamber
  tests/integration/test_v55_rknn_runtime_chamber.cpp)
