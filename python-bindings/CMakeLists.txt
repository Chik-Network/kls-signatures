
FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.11.1
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(klspy ${CMAKE_CURRENT_SOURCE_DIR}/pythonbindings.cpp)
target_link_libraries(klspy PRIVATE bls)

if((NOT MSVC) AND (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin"))
  target_link_options(klspy PRIVATE -Wl,-Bsymbolic)
endif()
