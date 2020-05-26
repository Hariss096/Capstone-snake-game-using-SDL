#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include<vector>
#include <random>
#include <fstream>
#include <string>
#include <sysinfo.h>

int main() {
  Sysinfo stats;
  stats.printOS();
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
  if (dlevel.count(difficultyLevel)){
    std::cout << difficultyLevel << std::endl;
  } else {
    std::cout << "Invalid Choice. Please restart the game." << std::endl;
    exit(0);
  }
  
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

  // Writing Best Score to the file
  int score_from_file;
  std::ifstream file("../Last_Best_Score.txt");
  std::string _;
  if (file.good()) {  // Check whether file exists
    file >> _ >> _ >> _ >> _ >> score_from_file;    // Check previous score in file
    std::cout << "wah : " << score_from_file << std::endl;
    if (score_from_file < game.GetScore()) {  // Check if the new score is better than last best
      std::ofstream updated_file;
      updated_file.open("../Last_Best_Score.txt", std::ofstream::out | std::ofstream::trunc);   // Remove content of file
      updated_file << "Your Last Best Score: "<< game.GetScore() << "\n"; // New score in file
      updated_file.close();
      std::cout << "New score: " << game.GetScore() << " "<< "Previous score: " << score_from_file << std::endl;
    }
  } else {
      std::ofstream file;
      file.open("../Last_Best_Score.txt");  // Create file
      file << "Your Last Best Score: "<< game.GetScore() << "\n";
      file.close();
      std::cout << "File Last_Best_Score created: " << std::endl;
  }
  
  return 0;
}