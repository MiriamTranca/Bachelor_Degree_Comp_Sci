# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "ArtAuctionPlatform_autogen"
  "CMakeFiles\\ArtAuctionPlatform_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ArtAuctionPlatform_autogen.dir\\ParseCache.txt"
  )
endif()
