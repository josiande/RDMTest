# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

#
project ("RDMTest")

# Include sub-projects.
add_subdirectory ("EtcPal")
add_subdirectory ("RDM")
add_subdirectory ("RDMTest")

