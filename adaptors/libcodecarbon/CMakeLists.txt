cmake_minimum_required(VERSION 3.10)

project(libcodecarbon VERSION 0.1.1)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PYTHON REQUIRED python3-embed)

add_library(codecarbon STATIC
  libcodecarbon.c
)

target_include_directories(codecarbon PRIVATE ${PYTHON_INCLUDE_DIRS})

add_executable(carboneye carboneye.c)

add_executable(test_libcodecarbon
  test_libcodecarbon.c
)

target_link_libraries(carboneye PRIVATE codecarbon ${PYTHON_LIBRARIES})
target_link_libraries(test_libcodecarbon PRIVATE codecarbon ${PYTHON_LIBRARIES} m)
