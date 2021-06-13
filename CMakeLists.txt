# Project:     git-committer
# File name:   CMakeLists.txt
# Purpose:     Configuration of project via cmake
# Author:      Boris Boesler
# Modified by:
# Created:     13.06.2021
# Copyright:   (c) 2021 Boris Boesler


##############
# requirements
cmake_minimum_required(VERSION 3.5)


######################################################################
# the project
######################################################################

project(GIT_COMMITTER
  VERSION 0.1.0)

# set default cmake build type to Debug
# built type \in {None Debug Release RelWithDebInfo MinSizeRel}
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "Checking build type ... " ${CMAKE_BUILD_TYPE})


######################################################################
# configuration files
######################################################################


######################################################################
# source code
######################################################################

add_subdirectory(src)


######################################################################
# display status message for important variables
######################################################################

message(STATUS)
message(STATUS "---------------------------------------------------------------")

message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

message(STATUS "GIT_COMMITTER_VERSION_MAJOR = ${GIT_COMMITTER_VERSION_MAJOR}")
message(STATUS "GIT_COMMITTER_VERSION_MINOR = ${GIT_COMMITTER_VERSION_MINOR}")
message(STATUS "GIT_COMMITTER_VERSION_PATCH = ${GIT_COMMITTER_VERSION_PATCH}")

message(STATUS "---------------------------------------------------------------")
