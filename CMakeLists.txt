cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ATL")

# Include header directory
include_directories("${PROJECT_SOURCE_DIR}/libs/include")

file(GLOB SOURCES 
"./*.cpp"
"./*.hpp"
"glb/*.cpp"
"glb/*.hpp"
)

# Add executable and link with ATL library
add_executable (ATL ${SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ATL PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.