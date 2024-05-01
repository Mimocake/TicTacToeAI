cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("TicTacToeAI")

# Add source to this project's executable.
add_executable (TicTacToeAI "src/main.cpp")

target_link_libraries(TicTacToeAI ${CMAKE_SOURCE_DIR}/lib/sfml-main.lib)
target_link_libraries(TicTacToeAI ${CMAKE_SOURCE_DIR}/lib/sfml-window.lib)
target_link_libraries(TicTacToeAI ${CMAKE_SOURCE_DIR}/lib/sfml-system.lib)
target_link_libraries(TicTacToeAI ${CMAKE_SOURCE_DIR}/lib/sfml-graphics.lib)

include_directories(${CMAKE_SOURCE_DIR}/include)

set_property(TARGET TicTacToeAI PROPERTY CXX_STANDARD 17)
set_property(TARGET TicTacToeAI PROPERTY CXX_STANDARD_REQUIRED ON)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TicTacToeAI PROPERTY CXX_STANDARD 20)
endif()