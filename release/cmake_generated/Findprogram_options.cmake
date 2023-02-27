# AUTOGENERATED, DON'T CHANGE THIS FILE!


if (NOT USERVER_CHECK_PACKAGE_VERSIONS)
  unset(program_options_FIND_VERSION)
endif()

if (TARGET program_options)
  if (NOT program_options_FIND_VERSION)
      set(program_options_FOUND ON)
      return()
  endif()

  if (program_options_VERSION)
      if (program_options_FIND_VERSION VERSION_LESS_EQUAL program_options_VERSION)
          set(program_options_FOUND ON)
          return()
      else()
          message(FATAL_ERROR
              "Already using version ${program_options_VERSION} "
              "of program_options when version ${program_options_FIND_VERSION} "
              "was requested."
          )
      endif()
  endif()
endif()

set(FULL_ERROR_MESSAGE "Could not find `program_options` package.\n\tDebian: sudo apt update && sudo apt install libboost-program-options-dev\n\tMacOS: brew install boost\n\tFedora: sudo dnf install boost-devel\n\tArchLinux: sudo pacman -S boost\\n")


include(FindPackageHandleStandardArgs)

find_library(program_options_LIBRARIES_boost_program_options
  NAMES boost_program_options
)
list(APPEND program_options_LIBRARIES ${program_options_LIBRARIES_boost_program_options})

find_path(program_options_INCLUDE_DIRS_boost_program_options_config_hpp
  NAMES boost/program_options/config.hpp
)
list(APPEND program_options_INCLUDE_DIRS ${program_options_INCLUDE_DIRS_boost_program_options_config_hpp})



if (program_options_VERSION)
  set(program_options_VERSION ${program_options_VERSION})
endif()

if (NOT program_options_VERSION)
  include(DetectVersion)

  if (UNIX AND NOT APPLE)
    deb_version(program_options_VERSION libboost-program-options-dev)
    rpm_version(program_options_VERSION boost-devel)
    pacman_version(program_options_VERSION boost)
    
  endif()
  if (APPLE)
    brew_version(program_options_VERSION boost)
  endif()
  
endif()

 
find_package_handle_standard_args(
  program_options
    REQUIRED_VARS
      program_options_LIBRARIES
      program_options_INCLUDE_DIRS
      
    FAIL_MESSAGE
      "${FULL_ERROR_MESSAGE}"
)
mark_as_advanced(
  program_options_LIBRARIES
  program_options_INCLUDE_DIRS
  
)

if (NOT program_options_FOUND)
  if (program_options_FIND_REQUIRED)
      message(FATAL_ERROR "${FULL_ERROR_MESSAGE}. Required version is at least ${program_options_FIND_VERSION}")
  endif()

  return()
endif()

if (program_options_FIND_VERSION)
  if (program_options_VERSION VERSION_LESS program_options_FIND_VERSION)
      message(STATUS
          "Version of program_options is '${program_options_VERSION}'. "
          "Required version is at least '${program_options_FIND_VERSION}'. "
          "Ignoring found program_options. "
          "Note: Set -DUSERVER_CHECK_PACKAGE_VERSIONS=0 to skip package version checks if the package is fine."
      )
      set(program_options_FOUND OFF)
      return()
  endif()
endif()

 
if (NOT TARGET program_options)
  add_library(program_options INTERFACE IMPORTED GLOBAL)

  if (TARGET Boost::program_options)
    target_link_libraries(program_options INTERFACE Boost::program_options)
  endif()
  target_include_directories(program_options INTERFACE ${program_options_INCLUDE_DIRS})
  message(STATUS "program_options include directories: ${program_options_INCLUDE_DIRS}")
  target_link_libraries(program_options INTERFACE ${program_options_LIBRARIES})
  message(STATUS "program_options libraries: ${program_options_LIBRARIES}")
  
  # Target program_options is created
endif()

if (program_options_VERSION)
  set(program_options_VERSION "${program_options_VERSION}" CACHE STRING "Version of the program_options")
endif()
