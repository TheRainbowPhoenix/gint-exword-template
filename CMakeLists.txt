cmake_minimum_required(VERSION 3.15)
project(GintExwordTemplate VERSION 0.1 LANGUAGES C ASM)

if(NOT FXSDK_PLATFORM_LONG STREQUAL "exword")
  message(FATAL_ERROR "Use the EXWORD.cmake toolchain")
endif()

include(GenerateD01)
include(GenerateEXWORDPackage)
find_package(Gint 2.11 REQUIRED)

add_executable(ginttest src/main.c)
target_compile_options(ginttest PRIVATE
  -Wall -Wextra -Os -flto=auto -fno-pic -fno-pie
  -fno-stack-protector -ffunction-sections -fdata-sections)
target_link_options(ginttest PRIVATE
  -flto=auto -nostdlib -no-pie -Wl,--build-id=none
  -Wl,--no-warn-rwx-segments -Wl,-Map=ginttest.map
  -Wl,--print-memory-usage)
target_link_libraries(ginttest Gint::Gint)

generate_d01(TARGET ginttest
  OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/ginttest.d01"
  MODULE "gintt")

if(NOT EXWORD_METADATA_SOURCE)
  message(FATAL_ERROR "Set EXWORD_METADATA_SOURCE to the EX-word metadata repo")
endif()
generate_exword_package(
  TARGET ginttest
  D01 "${CMAKE_CURRENT_BINARY_DIR}/ginttest.d01"
  APPID "GINTT"
  TITLE "gint EX-word EXIT test"
  HTML_DIR "${EXWORD_METADATA_SOURCE}/html"
  OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/packages"
  LOCALES ja cn)
