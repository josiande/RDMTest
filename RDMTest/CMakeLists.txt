# CMakeList.txt : CMake project for RDMTest, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


# add_library(RDMTestClass_lib STATIC RDMTestClass.cpp RDMTestClass.h)
# target_include_directories(RDMTestClass_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Add source to this project's executable.
add_executable (RDMTest "RDMTest.cpp" "RDMTest.h" "RDMTestClass.cpp" "RDMTestClass.h")

if(CMAKE_SIZEOF_VOID_P STREQUAL 4)
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/libGadget/Win32)
else()
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/libGadget/x64)
endif()

find_package(GadgetDLL 2.1.0 REQUIRED)


target_link_libraries(RDMTest PRIVATE GadgetDLL::GadgetDLL)
target_link_libraries(RDMTest PRIVATE EtcPal)
target_link_libraries(RDMTest PRIVATE RDM)

get_target_property(GADGET_DLL_LOCATION GadgetDLL::GadgetDLL IMPORTED_LOCATION_RELEASE)
add_custom_command(
  TARGET RDMTest
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${GADGET_DLL_LOCATION} $<TARGET_FILE_DIR:RDMTest>
  COMMENT "Copying Gadget DLL to executable directory..."
)
# TODO: Add tests and install targets if needed.

