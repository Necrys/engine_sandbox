FetchContent_Declare(
  engine
  GIT_REPOSITORY https://github.com/Necrys/engine.git
)

FetchContent_GetProperties( engine )
if( NOT engine_POPULATED )
  FetchContent_Populate( engine )
  message( STATUS "engine source dir: ${engine_SOURCE_DIR}" )
  message( STATUS "engine binary dir: ${engine_BINARY_DIR}" )
endif()

add_subdirectory( ${engine_SOURCE_DIR} ${engine_BINARY_DIR} )
