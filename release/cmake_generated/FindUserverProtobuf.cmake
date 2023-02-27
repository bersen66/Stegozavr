# AUTOGENERATED, DON'T CHANGE THIS FILE!


if (NOT USERVER_CHECK_PACKAGE_VERSIONS)
  unset(UserverProtobuf_FIND_VERSION)
endif()

if (TARGET UserverProtobuf)
  if (NOT UserverProtobuf_FIND_VERSION)
      set(UserverProtobuf_FOUND ON)
      return()
  endif()

  if (UserverProtobuf_VERSION)
      if (UserverProtobuf_FIND_VERSION VERSION_LESS_EQUAL UserverProtobuf_VERSION)
          set(UserverProtobuf_FOUND ON)
          return()
      else()
          message(FATAL_ERROR
              "Already using version ${UserverProtobuf_VERSION} "
              "of UserverProtobuf when version ${UserverProtobuf_FIND_VERSION} "
              "was requested."
          )
      endif()
  endif()
endif()

set(FULL_ERROR_MESSAGE "Could not find `UserverProtobuf` package.\n\tDebian: sudo apt update && sudo apt install protoc-dev protobuf-compiler python3-protobuf libprotoc-dev\n\tMacOS: brew install protobuf\n\tArchLinux: sudo pacman -S protobuf\\n")


include(FindPackageHandleStandardArgs)

find_library(UserverProtobuf_LIBRARIES_protobuf
  NAMES protobuf
)
list(APPEND UserverProtobuf_LIBRARIES ${UserverProtobuf_LIBRARIES_protobuf})

find_path(UserverProtobuf_INCLUDE_DIRS_google_protobuf_port_def_inc_google_protobuf_compiler_cpp_cpp_generator_h
  NAMES google/protobuf/port_def.inc google/protobuf/compiler/cpp/cpp_generator.h
)
list(APPEND UserverProtobuf_INCLUDE_DIRS ${UserverProtobuf_INCLUDE_DIRS_google_protobuf_port_def_inc_google_protobuf_compiler_cpp_cpp_generator_h})



if (UserverProtobuf_VERSION)
  set(UserverProtobuf_VERSION ${UserverProtobuf_VERSION})
endif()

if (NOT UserverProtobuf_VERSION)
  include(DetectVersion)

  if (UNIX AND NOT APPLE)
    deb_version(UserverProtobuf_VERSION protoc-dev)
    
    pacman_version(UserverProtobuf_VERSION protobuf)
    
  endif()
  if (APPLE)
    brew_version(UserverProtobuf_VERSION protobuf)
  endif()
  pkg_config_version(UserverProtobuf_VERSION protobuf)
endif()

 
find_package_handle_standard_args(
  UserverProtobuf
    REQUIRED_VARS
      UserverProtobuf_LIBRARIES
      UserverProtobuf_INCLUDE_DIRS
      
    FAIL_MESSAGE
      "${FULL_ERROR_MESSAGE}"
)
mark_as_advanced(
  UserverProtobuf_LIBRARIES
  UserverProtobuf_INCLUDE_DIRS
  
)

if (NOT UserverProtobuf_FOUND)
  if (UserverProtobuf_FIND_REQUIRED)
      message(FATAL_ERROR "${FULL_ERROR_MESSAGE}. Required version is at least ${UserverProtobuf_FIND_VERSION}")
  endif()

  return()
endif()

if (UserverProtobuf_FIND_VERSION)
  if (UserverProtobuf_VERSION VERSION_LESS UserverProtobuf_FIND_VERSION)
      message(STATUS
          "Version of UserverProtobuf is '${UserverProtobuf_VERSION}'. "
          "Required version is at least '${UserverProtobuf_FIND_VERSION}'. "
          "Ignoring found UserverProtobuf. "
          "Note: Set -DUSERVER_CHECK_PACKAGE_VERSIONS=0 to skip package version checks if the package is fine."
      )
      set(UserverProtobuf_FOUND OFF)
      return()
  endif()
endif()

 
if (NOT TARGET UserverProtobuf)
  add_library(UserverProtobuf INTERFACE IMPORTED GLOBAL)

  target_include_directories(UserverProtobuf INTERFACE ${UserverProtobuf_INCLUDE_DIRS})
  message(STATUS "UserverProtobuf include directories: ${UserverProtobuf_INCLUDE_DIRS}")
  target_link_libraries(UserverProtobuf INTERFACE ${UserverProtobuf_LIBRARIES})
  message(STATUS "UserverProtobuf libraries: ${UserverProtobuf_LIBRARIES}")
  
  # Target UserverProtobuf is created
endif()

if (UserverProtobuf_VERSION)
  set(UserverProtobuf_VERSION "${UserverProtobuf_VERSION}" CACHE STRING "Version of the UserverProtobuf")
endif()
