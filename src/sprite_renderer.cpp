#include "sprite_renderer.h"
#include "position.h"
#include "rotation.h"

#include <registry.h>
#include <batchrenderer.h>
#include <sprite.h>

static const double ROTATION_EPSILON = 0.001;

SpriteRenderer::SpriteRenderer( ecs::registry& world, engine::gfx::BatchRenderer& renderer ):
  m_world( world ),
  m_renderer( renderer ){
}

void SpriteRenderer::update() {
  m_world.components().join< engine::gfx::Sprite, Position >().exclude< Rotation >( [ & ]( const ecs::eid_t id, const engine::gfx::Sprite& s, const Position& p ) {
    const glm::ivec2 corner = p - s.m_pivot;
    const glm::ivec2& size = s.size();

    const engine::gfx::BatchRenderer::Quad q{{
      { glm::vec3( corner.x,          corner.y,          0.5f ), 0xffffffff, glm::vec2( s.m_rect[ 0 ].x,  s.m_rect[ 0 ].y ) },
      { glm::vec3( corner.x + size.x, corner.y,          0.5f ), 0xffffffff, glm::vec2( s.m_rect[ 1 ].x,  s.m_rect[ 0 ].y ) },
      { glm::vec3( corner.x + size.x, corner.y + size.y, 0.5f ), 0xffffffff, glm::vec2( s.m_rect[ 1 ].x,  s.m_rect[ 1 ].y ) },
      { glm::vec3( corner.x,          corner.y + size.y, 0.5f ), 0xffffffff, glm::vec2( s.m_rect[ 0 ].x,  s.m_rect[ 1 ].y ) },
    }};

    m_renderer.drawQuad( q, s.m_texture );
  } );

  m_world.components().join< engine::gfx::Sprite, Position, Rotation >( [ & ]( const ecs::eid_t id, const engine::gfx::Sprite& s, const Position& p, const Rotation& r ) {
    engine::gfx::BatchRenderer::Quad q;

    if ( fabs( r.angle ) < ROTATION_EPSILON ) {
      const glm::ivec2 corner = p - s.m_pivot;
      const glm::ivec2& size = s.size();

      q.v[ 0 ] = { glm::vec3( corner.x,          corner.y,          0.5f ), 0xffffffff, glm::vec2( s.m_rect[ 0 ].x,  s.m_rect[ 0 ].y ) };
      q.v[ 1 ] = { glm::vec3( corner.x + size.x, corner.y,          0.5f ), 0xffffffff, glm::vec2( s.m_rect[ 1 ].x,  s.m_rect[ 0 ].y ) };
      q.v[ 2 ] = { glm::vec3( corner.x + size.x, corner.y + size.y, 0.5f ), 0xffffffff, glm::vec2( s.m_rect[ 1 ].x,  s.m_rect[ 1 ].y ) };
      q.v[ 3 ] = { glm::vec3( corner.x,          corner.y + size.y, 0.5f ), 0xffffffff, glm::vec2( s.m_rect[ 0 ].x,  s.m_rect[ 1 ].y ) };
    } else {
      const glm::ivec2 corners[] = {
        { -s.m_pivot },
        { s.size() - s.m_pivot }
      };

      const auto cost = cosf( r.angle );
      const auto sint = sinf( r.angle );

      q.v[ 0 ] = { glm::vec3( corners[ 0 ].x * cost - corners[ 0 ].y * sint + p.x, corners[ 0 ].x * sint + corners[ 0 ].y * cost + p.y, 0.5f ), 0xffffffff, glm::vec2( s.m_rect[ 0 ].x,  s.m_rect[ 0 ].y ) };
      q.v[ 1 ] = { glm::vec3( corners[ 1 ].x * cost - corners[ 0 ].y * sint + p.x, corners[ 1 ].x * sint + corners[ 0 ].y * cost + p.y, 0.5f ), 0xffffffff, glm::vec2( s.m_rect[ 1 ].x,  s.m_rect[ 0 ].y ) };
      q.v[ 2 ] = { glm::vec3( corners[ 1 ].x * cost - corners[ 1 ].y * sint + p.x, corners[ 1 ].x * sint + corners[ 1 ].y * cost + p.y, 0.5f ), 0xffffffff, glm::vec2( s.m_rect[ 1 ].x,  s.m_rect[ 1 ].y ) };
      q.v[ 3 ] = { glm::vec3( corners[ 0 ].x * cost - corners[ 1 ].y * sint + p.x, corners[ 0 ].x * sint + corners[ 1 ].y * cost + p.y, 0.5f ), 0xffffffff, glm::vec2( s.m_rect[ 0 ].x,  s.m_rect[ 1 ].y ) };
    }

    m_renderer.drawQuad( q, s.m_texture );
  } );
}
