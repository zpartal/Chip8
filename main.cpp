#include <iostream>

#include "chip8.h"
#include "chip8_tester.h"

int main(int argc, char const *argv[])
{
  // Chip8 chip(true);
  Chip8Tester tester;
  tester.runTests();
  return 0;
}