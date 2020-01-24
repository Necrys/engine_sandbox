#include "app.h"
#include "grid.h"
#include "sprite_renderer.h"
#include "position.h"
#include "rotation.h"
#include "assets.h"

#include <math.h>
#include <sprite.h>

#include <cmath>
#include <glm/ext.hpp>

Application::Application( const std::string& name ):
  engine::ApplicationBase( name ) {
}

bool Application::init() {
  m_world.add_system< SpriteRenderer >( m_world, renderer() );

  auto sprites = engine::resources::Texture::loadFromPNG( assets_path + "/Hunter/Idle/hunter-idle0.png" );
  if ( !sprites )
    return false;

  auto e = m_world.allocate();
  e.add< engine::gfx::Sprite >( sprites, 0, 0, 82, 106 );
  e.add< Position >( 0.0, 0.0 );

  e = m_world.allocate();
  auto& spr = e.add< engine::gfx::Sprite >( sprites, 0, 0, 82, 106 );
  spr.m_pivot = { 41, 53 };

  e.add< Position >( 196.0, 64.0 );
  e.add< Rotation >( 0.0 );

  return true;
}

void Application::deinit() {
}

bool Application::tick( const double dt ) {
  m_world.update();

  m_world.components().join< Rotation >( [ dt ]( const ecs::eid_t id, Rotation& r ) {
    r.angle += dt * 0.001;
  } );

  const double step = glm::pi<double>() / 10.0;
  for ( double a = 0.0; a < glm::pi<double>() * 2.0; a += step ) {
    double x1 = std::sin( a );
    double y1 = std::cos( a );

    // test drawing points
    renderer().drawPoint( x1 * 100.0 + 200.0, y1 * 100.0 + 200.0, 0xffff00ff );

    // test drawing lines
    double x2 = std::sin( a + step );
    double y2 = std::cos( a + step );
    renderer().drawLine( x1 * 120.0 + 200.0, y1 * 120.0 + 200.0, x2 * 120.0 + 200.0, y2 * 120.0 + 200.0, 0xff00ffff );
  }

  renderer().drawQuad( 130.0, 130.0, 140.0, 140.0, 0.5, 0xffffff00 );

  engine::gfx::BatchRenderer::Triangle tri;
  tri.v[ 0 ] = engine::gfx::BatchRenderer::Vertex {
    { 200.0, 150.0, 1.0 },
    0xffffffff,
    { 0.0, 0.0 }
  };
  tri.v[ 1 ] = engine::gfx::BatchRenderer::Vertex {
    { 250.0, 250.0, 1.0 },
    0xffffffff,
    { 1.0, 0.0 }    
  };
  tri.v[ 2 ] = engine::gfx::BatchRenderer::Vertex {
    { 150.0, 250.0, 1.0 },
    0xffffffff,
    { 0.0, 1.0 }
  };

  renderer().drawTriangle( tri );

  

  return true;
}
