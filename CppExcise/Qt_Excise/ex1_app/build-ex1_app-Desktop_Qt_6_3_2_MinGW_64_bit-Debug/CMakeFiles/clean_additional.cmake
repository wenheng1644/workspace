# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ex1_app_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ex1_app_autogen.dir\\ParseCache.txt"
  "ex1_app_autogen"
  )
endif()
