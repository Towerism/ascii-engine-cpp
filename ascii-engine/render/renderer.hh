#pragma once

#include <memory>
#include <vector>
#include "renderable.hh"

class Renderer {
public:

  Renderer(int width = 0, int height = 0);

  void add(Renderable* renderable);
  void render();

  int get_width() const;
  int get_height() const;
  const Renderable* get_renderable(int index) const;
  std::string get_string_at_row(int index) const;

private:

  int width, height;
  std::vector<std::shared_ptr<Renderable>> renderables;
};
