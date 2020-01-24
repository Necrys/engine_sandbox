cmake_minimum_required( VERSION 3.15.5 FATAL_ERROR )
project( sandbox )

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

set ( CMAKE_CXX_STANDARD 17 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS OFF )

include ( cmake/fetch_dependencies.cmake )

add_subdirectory( src )

add_executable( ${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCE}
)

target_include_directories( ${PROJECT_NAME}
  PRIVATE
    ${${PROJECT_NAME}_INCLUDE}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries( ${PROJECT_NAME}
  PRIVATE
    engine
    ecs
)

target_link_options( ${PROJECT_NAME}
  PRIVATE
    $<$<CXX_COMPILER_ID:GNU>: -static -static-libgcc -static-libstdc++>
    $<$<CXX_COMPILER_ID:Clang>: -static -static-libgcc -static-libstdc++>
)
