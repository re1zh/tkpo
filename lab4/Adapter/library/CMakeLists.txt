add_library(GasLibrary
    GasBalloon.cpp
    ObjectAdapter.cpp
)

target_include_directories(GasLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
