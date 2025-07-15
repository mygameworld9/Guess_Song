# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "123_autogen"
  "CMakeFiles\\123_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\123_autogen.dir\\ParseCache.txt"
  )
endif()
