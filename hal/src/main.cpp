#include "hardware.hpp"

hardware::Hardware board;

int main() {
  board.setupHardware();
  board.setupTestStuff();

  while (1) {
    board.doTestStuff();
  }

  return 0;
}