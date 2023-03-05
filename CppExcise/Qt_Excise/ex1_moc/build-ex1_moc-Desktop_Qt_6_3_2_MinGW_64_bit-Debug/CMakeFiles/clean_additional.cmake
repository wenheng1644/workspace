# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ex1_moc_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ex1_moc_autogen.dir\\ParseCache.txt"
  "ex1_moc_autogen"
  )
endif()
