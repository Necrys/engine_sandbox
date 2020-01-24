FetchContent_Declare(
  sprites
  GIT_REPOSITORY https://github.com/brenopolanski/cactusjs-sprites-games.git
)

FetchContent_GetProperties( sprites )
if( NOT sprites_POPULATED )
  FetchContent_Populate( sprites )
  message( STATUS "sprites source dir: ${sprites_SOURCE_DIR}" )
  message( STATUS "sprites binary dir: ${sprites_BINARY_DIR}" )
endif()
