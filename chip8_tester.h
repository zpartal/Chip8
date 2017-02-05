#ifndef CHIP8_TESTER_H
#define CHIP8_TESTER_H

#include <string>
#include <functional>
#include "chip8.h"

class Chip8Tester
{
public:
  Chip8Tester() {};

  bool runTests();

private:
  bool runTest(const std::string name, std::function<bool()> test);

  bool testCpu3XNNa();
  bool testCpu3XNNb();
  bool testCpu4XNNa();
  bool testCpu4XNNb();
  bool testCpu5XY0a();
  bool testCpu5XY0b();
  bool testCpu6XNN();
  bool testCpu7XNN();
  bool testCpu8XY0();
  bool testCpu8XY1();
  bool testCpu8XY2();
  bool testCpu8XY3();
  bool testCpu8XY4();
  bool testCpu8XY6a();
  bool testCpu8XY6b();
  bool testCpu8XYEa();
  bool testCpu8XYEb();
  bool testCpu9XY0a();
  bool testCpu9XY0b();
  bool testCpuBNNN();
  bool testCpuFX07();
  bool testCpuFX15();
  bool testCpuFX18();
  bool testCpuFX1E();
  bool testCpuFX55();
  bool testCpuFX66();

private:
  Chip8 m_chip;
};

#endif