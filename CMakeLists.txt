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
"funcs/*.cpp"
"funcs/*.hpp"
)

# Add executable and link with ATL library
add_executable (ATL ${SOURCES})

# Define DEBUG macro
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(ATL PRIVATE DEBUG=1)
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ATL PROPERTY CXX_STANDARD 20)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(ATL PRIVATE /WX)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(ATL PRIVATE -Werror)
endif()
