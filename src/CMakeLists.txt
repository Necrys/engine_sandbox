cmake_minimum_required( VERSION 3.15.5 FATAL_ERROR )
project( sandbox )

configure_file ( ${CMAKE_CURRENT_SOURCE_DIR}/assets.cpp.in ${CMAKE_CURRENT_SOURCE_DIR}/assets.cpp )

set( ${PROJECT_NAME}_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/assets.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/app.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sprite_renderer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/position.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/assets.h
  ${CMAKE_CURRENT_SOURCE_DIR}/app.h
  ${CMAKE_CURRENT_SOURCE_DIR}/sprite_renderer.h
  ${CMAKE_CURRENT_SOURCE_DIR}/position.h
  ${CMAKE_CURRENT_SOURCE_DIR}/rotation.h

  PARENT_SCOPE
)

set( ${PROJECT_NAME}_INCLUDE
  ${CMAKE_CURRENT_SOURCE_DIR}

  PARENT_SCOPE
)
