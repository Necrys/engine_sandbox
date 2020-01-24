FetchContent_Declare(
  ecs
  GIT_REPOSITORY https://github.com/Necrys/ecs.git
)

FetchContent_GetProperties( ecs )
if( NOT ecs_POPULATED )
  FetchContent_Populate( ecs )
  message( STATUS "ecs source dir: ${ecs_SOURCE_DIR}" )
  message( STATUS "ecs binary dir: ${ecs_BINARY_DIR}" )
endif()

set( ECS_BUILD_TESTS OFF CACHE INTERNAL "" )
add_subdirectory( ${ecs_SOURCE_DIR} ${ecs_BINARY_DIR} )
