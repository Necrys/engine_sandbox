#pragma once

#include <set>

#include <engine.h>
#include <registry.h>

class Application: public engine::ApplicationBase {
public:
  Application( const std::string& name );

protected:
  bool init();
  void deinit();
  bool tick( const double );

private:
  ecs::registry m_world;
};
