#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "Settings.h"

using namespace Settings;

int main() {
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  return 0;
}