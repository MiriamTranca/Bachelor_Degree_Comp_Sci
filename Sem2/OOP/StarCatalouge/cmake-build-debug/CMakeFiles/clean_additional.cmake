# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\StarCatalouge_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\StarCatalouge_autogen.dir\\ParseCache.txt"
  "StarCatalouge_autogen"
  )
endif()
