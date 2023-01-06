cmake_minimum_required(VERSION 3.0.0)
project(test-luabind VERSION 0.1.0)

find_package(Boost REQUIRED)
find_package(Lua REQUIRED)

include(FindLuaBind.cmake)

include_directories(${LUA_INCLUDE_DIR})
include_directories(${LUABIND_INCLUDE_DIR})

add_executable(test-luabind 
  src/main.cpp
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE BOOST_BIND_GLOBAL_PLACEHOLDERS
)

target_link_libraries(${PROJECT_NAME} 
  ${BOOST_LIBRARIES}
  ${LUA_LIBRARIES}
  ${LUABIND_LIBRARIES}
)
