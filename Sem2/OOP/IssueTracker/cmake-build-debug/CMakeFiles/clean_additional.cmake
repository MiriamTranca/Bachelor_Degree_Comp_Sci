# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\IssueTracker_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\IssueTracker_autogen.dir\\ParseCache.txt"
  "IssueTracker_autogen"
  )
endif()
