cmake_minimum_required(VERSION 3.10)

project(libcodecarbon VERSION 0.1.1)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PYTHON REQUIRED python3-embed)

add_library(codecarbon STATIC
  libcodecarbon.c
)

target_include_directories(codecarbon PRIVATE ${PYTHON_INCLUDE_DIRS})
target_compile_options(codecarbon PRIVATE -fPIC)  # -fPIE → -fPIC (for static lib)

add_executable(test_libcodecarbon
  test_libcodecarbon.c
)

target_compile_options(test_libcodecarbon PRIVATE -fPIE)
target_link_options(test_libcodecarbon PRIVATE -pie)

target_link_libraries(test_libcodecarbon PRIVATE codecarbon ${PYTHON_LIBRARIES} m)
