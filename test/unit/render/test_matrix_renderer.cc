#include <gtest/gtest.h>
#include <string>
#include <ascii-engine/render/matrix_renderer.hh>
#include <ascii-engine/render/renderable.hh>

TEST(Matrix_renderer, CreateDefault) {
  Matrix_renderer renderer;
  std::vector<std::string> lines = renderer.render();

  EXPECT_EQ(0, renderer.get_width());
  EXPECT_EQ(0, renderer.get_height());
  EXPECT_TRUE(lines.empty());
}

TEST(Matrix_renderer, CreateWithDimensions) {
  int width = 3;
  int height = 2;

  Matrix_renderer renderer(3, 2);
  std::vector<std::string> lines = renderer.render();

  EXPECT_EQ(width, renderer.get_width());
  EXPECT_EQ(height, renderer.get_height());
  EXPECT_EQ("   ", lines[0]);
  EXPECT_EQ("   ", lines[1]);
}

TEST(Matrix_renderer, AddRenderable) {
  Renderable* renderable = new Renderable;
  Matrix_renderer renderer;

  renderer.add(renderable);

  EXPECT_EQ(renderable, renderer.get_renderable(0));
}

TEST(Matrix_renderer, RenderSingleCharacterAtOrigin) {
  Renderable* renderable = new Renderable(0, 0, "@");
  Matrix_renderer renderer(2, 2);

  renderer.add(renderable);
  std::vector<std::string> lines = renderer.render();

  EXPECT_EQ("@ ", lines[0]);
}

TEST(Matrix_renderer, RenderSingleCharacterAtNonOrigin) {
  Renderable* renderable = new Renderable(0, 1, "@");
  Matrix_renderer renderer(2, 2);

  renderer.add(renderable);
  std::vector<std::string> lines = renderer.render();

  EXPECT_EQ("  ", lines[0]);
  EXPECT_EQ("@ ", lines[1]);
}

TEST(Matrix_renderer, RenderMultipleCharacters) {
  Renderable* renderable = new Renderable(0, 1, "@#");
  Matrix_renderer renderer(2, 2);

  renderer.add(renderable);
  std::vector<std::string> lines = renderer.render();

  EXPECT_EQ("  ", lines[0]);
  EXPECT_EQ("@#", lines[1]);
}

TEST(Matrix_renderer, RenderMultipleLines) {
  Renderable* renderable = new Renderable(1, 0, "a\nb\nc");
  Matrix_renderer renderer(2, 3);

  renderer.add(renderable);
  std::vector<std::string> lines = renderer.render();

  EXPECT_EQ(" a", lines[0]);
  EXPECT_EQ(" b", lines[1]);
  EXPECT_EQ(" c", lines[2]);
}

TEST(Matrix_renderer, RenderMultipleStrings) {
  Renderable* renderable1 = new Renderable(0, 0, "aa");
  Renderable* renderable2 = new Renderable(1, 0, "b");
  Matrix_renderer renderer(2, 1);

  renderer.add(renderable1);
  renderer.add(renderable2);
  std::vector<std::string> lines = renderer.render();

  EXPECT_EQ("ab", lines[0]);
}