cmake_minimum_required(VERSION 2.8)
project(JointAttention)
find_package(qibuild)

include_directories(include)
## building Logger module

option(LOGGER_JA_IS_REMOTE
  "module is compiled as a remote module (ON or OFF)"
  OFF)

set(_srcsLogger_ja
  src/logmodule_loader_ja.cpp
  include/logmodule_ja.hpp
  src/logmodule_ja.cpp
)

if(LOGGER_JA_IS_REMOTE)
  add_definitions(" -DLOGGER_JA_IS_REMOTE ")
  qi_create_bin(logger_ja ${_srcsLogger_ja})
else()
  qi_create_lib(logger_ja SHARED ${_srcsLogger_ja} SUBFOLDER Logger_ja)
endif()

qi_use_lib(logger_ja ALCOMMON)

## building Interface module

option(INTERFACE_JA_IS_REMOTE
  "module is compiled as a remote module (ON or OFF)"
  OFF)

set(_srcsInterface_ja
  src/uimodule_loader_ja.cpp
  include/uimodule_ja.hpp
  src/uimodule_ja.cpp
)

if(INTERFACE_JA_IS_REMOTE)
  add_definitions(" -DINTERFACE_JA_IS_REMOTE ")
  qi_create_bin(interface_ja ${_srcsInterface_ja})
else()
  qi_create_lib(interface_ja SHARED ${_srcsInterface_ja} SUBFOLDER Interface_ja)
endif()

qi_use_lib(interface_ja ALCOMMON)
