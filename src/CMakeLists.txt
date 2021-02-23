
set(RDMTEST_LIB_TARGET_NAME RDMTest_lib)

set(RDMTEST_CORE_SOURCES
  # RDMTest headers
  ${RDMTEST_ROOT}/include/dmxrdm/rdm_controller.h
  ${RDMTEST_ROOT}/include/dmxrdm/rdm_device.h
  ${RDMTEST_ROOT}/include/ui/shell.h
  # RDMTest sources
  ${RDMTEST_ROOT}/src/dmxrdm/rdm_controller.cpp
  ${RDMTEST_ROOT}/src/dmxrdm/rdm_device.cpp
  ${RDMTEST_ROOT}/src/ui/shell.cpp
)

add_library(${RDMTEST_LIB_TARGET_NAME} ${RDMTEST_CORE_SOURCES})
target_include_directories(${RDMTEST_LIB_TARGET_NAME} PUBLIC
  ${RDMTEST_ROOT}/include
)
target_include_directories(${RDMTEST_LIB_TARGET_NAME} PRIVATE
  ${RDMTEST_ROOT}/src
)

target_link_libraries(${RDMTEST_LIB_TARGET_NAME} PUBLIC GadgetDLL::GadgetDLL)
target_link_libraries(${RDMTEST_LIB_TARGET_NAME} PUBLIC EtcPal)
target_link_libraries(${RDMTEST_LIB_TARGET_NAME} PUBLIC RDM)

if(CMAKE_SIZEOF_VOID_P STREQUAL 4)
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/external/libGadget/Win32)
else()
  list(APPEND CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/external/libGadget/x64)
endif()

find_package(GadgetDLL 2.1.0 REQUIRED)


add_executable(RDMTest "main.cpp")

target_link_libraries(RDMTest PUBLIC ${RDMTEST_LIB_TARGET_NAME})

get_target_property(GADGET_DLL_LOCATION GadgetDLL::GadgetDLL IMPORTED_LOCATION_RELEASE)
add_custom_command(
  TARGET RDMTest
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${GADGET_DLL_LOCATION} $<TARGET_FILE_DIR:RDMTest>
  COMMENT "Copying Gadget DLL to executable directory..."
)
