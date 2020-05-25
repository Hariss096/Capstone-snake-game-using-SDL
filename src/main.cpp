#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include<vector>
#include <random>

int main() {
  char difficultyLevel;
  std::map<char, int> dlevel;
  dlevel['e'] = 5;
  dlevel['m'] = 10;
  dlevel['h'] = 15;
  std::cout << "Please Choose difficulty level " << std::endl;
  std::cout << "Easy (Press e) " << std::endl;
  std::cout << "Medium (Press m) " << std::endl;
  std::cout << "Hard (Press h) " << std::endl;
  std::cin >> difficultyLevel;
  std::cout << difficultyLevel << std::endl;
  auto obstacles = dlevel.find(difficultyLevel)->second;
  std::vector<int> rand_obstacle_x;
  std::vector<int> rand_obstacle_y;

  for (int n=0; n < obstacles; n++) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> for_x(1, 31);
  std::uniform_int_distribution<> for_y(1, 31);
    rand_obstacle_x.push_back(for_x(gen));
    rand_obstacle_y.push_back(for_y(gen));
  }
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight, obstacles, rand_obstacle_x, rand_obstacle_y);
  Controller controller;
  Game game(kGridWidth, kGridHeight, rand_obstacle_x, rand_obstacle_y);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}