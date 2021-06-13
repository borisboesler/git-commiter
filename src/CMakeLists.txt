# Project:     git-committer
# File name:   src/CMakeLists.txt
# Purpose:     Configuration of project via cmake
# Author:      Boris Boesler
# Modified by:
# Created:     13.06.2021
# Copyright:   (c) 2021 Boris Boesler


######################################################################
# options
######################################################################

if(uppercase_CMAKE_BUILD_TYPE STREQUAL "DEBUG" )
  option(GIT_COMMITTER_DEBUG "Enable git-committer Debug mode" "ON")
else()
  option(GIT_COMMITTER_DEBUG "Enable git-committer Debug mode" "OFF")
endif()


######################################################################
# configuration files
######################################################################

# version
configure_file(git-committer-version.h.in git-committer-version.h)

# configuration
configure_file(config.h.in config.h)
add_definitions(-DHAVE_CONFIG_H)


######################################################################
# a simple executable
######################################################################

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_compile_options(-Wall -Wpedantic)

add_executable(git-committer git-committer.c)


######################################################################
# installation
######################################################################

install(TARGETS git-committer
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
              GROUP_READ GROUP_EXECUTE
	      WORLD_READ WORLD_EXECUTE)
