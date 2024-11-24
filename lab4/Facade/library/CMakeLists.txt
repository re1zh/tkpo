add_library(InsuranceLibrary
    Property.cpp
    Facade.cpp
)

target_include_directories(InsuranceLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
