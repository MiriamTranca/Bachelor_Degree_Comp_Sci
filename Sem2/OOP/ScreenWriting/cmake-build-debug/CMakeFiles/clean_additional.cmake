# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ScreenWriting_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ScreenWriting_autogen.dir\\ParseCache.txt"
  "ScreenWriting_autogen"
  )
endif()
