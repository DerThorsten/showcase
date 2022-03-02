cmake_minimum_required(VERSION 3.9)
project(showcase VERSION 1.0.1 DESCRIPTION "showcase description")

add_executable(showcase main.cpp)
# set_target_properties(showcase PROPERTIES
#     VERSION ${PROJECT_VERSION}
#     SOVERSION 1)

# target_include_directories(showcase
#                             PUBLIC
#                            # ${toy_lib_INCLUDE_DIR}
#                            # $<BUILD_INTERFACE:${toy_lib_INCLUDE_DIR}>
#                            $<INSTALL_INTERFACE:include>)

set_target_properties(showcase PROPERTIES
            CXX_STANDARD 17
            CXX_EXTENSIONS OFF)



set(EM_CXX_FLAGS "${EM_CXX_FLAGS} --bind  -std=c++17")

# linker flags
set(EM_LINKER_FLAGS "${EM_LINKER_FLAGS} -s FORCE_FILESYSTEM=1 -s MODULARIZE -s ERROR_ON_UNDEFINED_SYMBOLS=0")
set(EM_LINKER_FLAGS "${EM_LINKER_FLAGS} -s EXPORT_NAME=\"createModule\" -s EXPORT_ES6=0 -s USE_ES6_IMPORT_META=0 -s ERROR_ON_UNDEFINED_SYMBOLS=0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EM_CXX_FLAGS} ${EM_LINKER_FLAGS}")
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS}  ${EM_CXX_FLAGS} ${EM_LINKER_FLAGS}")



message(STATUS "PYTHON_INCLUDE_DIRS= " ${PYTHON_INCLUDE_DIRS})


find_package(pybind11 REQUIRED CONFIG)



target_link_libraries(showcase PRIVATE $ENV{PREFIX}/lib/python_internal/libmpdec.a)
target_link_libraries(showcase PRIVATE $ENV{PREFIX}/lib/python_internal/libexpat.a)
target_link_libraries(showcase PRIVATE $ENV{PREFIX}/lib/libbz2.a)
target_link_libraries(showcase PRIVATE $ENV{PREFIX}/lib/libz.a)

target_link_libraries(showcase PRIVATE pybind11::embed)

include(GNUInstallDirs)
install(TARGETS showcase
    ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR})


install(FILES
    "$<TARGET_FILE_DIR:showcase>/showcase.js"
    "$<TARGET_FILE_DIR:showcase>/showcase.wasm"
    DESTINATION ${CMAKE_INSTALL_BINDIR})