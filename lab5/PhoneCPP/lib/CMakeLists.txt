add_library(PhoneLibrary
    PhoneState.h
    Phone.cpp
    WaitingState.cpp
    CallingState.cpp
    TalkingState.cpp
    BlockedState.cpp
)

target_include_directories(PhoneLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
