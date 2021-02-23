cmake_minimum_required (VERSION 3.8)

########################## Global Project Attributes ##########################

project (RDMTest)

# Sometimes the seems to be some weirdness with drive letter capitalization on Windows, so do a
# case-insensitive comparision
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Windows)
  string(TOLOWER ${PROJECT_SOURCE_DIR} PROJECT_SOURCE_DIR_LC)
  string(TOLOWER ${CMAKE_SOURCE_DIR} CMAKE_SOURCE_DIR_LC)
else()
  set(PROJECT_SOURCE_DIR_LC ${PROJECT_SOURCE_DIR})
  set(CMAKE_SOURCE_DIR_LC ${CMAKE_SOURCE_DIR})
endif()

set(RDMTEST_ROOT ${CMAKE_CURRENT_LIST_DIR})

# Include sub-projects.
add_subdirectory (external/EtcPal)
add_subdirectory (external/RDM)

################################# Main library ################################

add_subdirectory(src)


