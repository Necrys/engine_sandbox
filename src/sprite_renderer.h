#pragma once

namespace ecs {
  class registry;
}

namespace engine {
namespace gfx {
  class BatchRenderer;
}
}

class SpriteRenderer {
public:
  SpriteRenderer( ecs::registry&, engine::gfx::BatchRenderer& );

  void update();

private:
  ecs::registry&              m_world;
  engine::gfx::BatchRenderer& m_renderer;
};
