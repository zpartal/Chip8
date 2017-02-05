#include "chip8_tester.h"
#include <iostream>
#include <stdio.h>
#include <cstring>

namespace {
  const std::string sPass("PASSED");
  const std::string sFail("FAILED");
}

bool Chip8Tester::runTests() {
  bool res =
    runTest("3XNNa", std::bind(&Chip8Tester::testCpu3XNNa, this)) &&
    runTest("3XNNb", std::bind(&Chip8Tester::testCpu3XNNb, this)) &&
    runTest("4XNNa", std::bind(&Chip8Tester::testCpu4XNNa, this)) &&
    runTest("4XNNb", std::bind(&Chip8Tester::testCpu4XNNb, this)) &&
    runTest("5XY0a", std::bind(&Chip8Tester::testCpu5XY0a, this)) &&
    runTest("5XY0b", std::bind(&Chip8Tester::testCpu5XY0b, this)) &&
    runTest("6XNN", std::bind(&Chip8Tester::testCpu6XNN, this)) &&
    runTest("7XNN", std::bind(&Chip8Tester::testCpu7XNN, this)) &&
    runTest("8XY0", std::bind(&Chip8Tester::testCpu8XY0, this)) &&
    runTest("8XY1", std::bind(&Chip8Tester::testCpu8XY1, this)) &&
    runTest("8XY2", std::bind(&Chip8Tester::testCpu8XY2, this)) &&
    runTest("8XY3", std::bind(&Chip8Tester::testCpu8XY3, this)) &&
    runTest("8XY4", std::bind(&Chip8Tester::testCpu8XY4, this)) &&
    runTest("8XY6a", std::bind(&Chip8Tester::testCpu8XY6a, this)) &&
    runTest("8XY6b", std::bind(&Chip8Tester::testCpu8XY6b, this)) &&
    runTest("8XYEa", std::bind(&Chip8Tester::testCpu8XYEa, this)) &&
    runTest("8XYEb", std::bind(&Chip8Tester::testCpu8XYEb, this)) &&
    runTest("9XY0a", std::bind(&Chip8Tester::testCpu9XY0a, this)) &&
    runTest("9XY0b", std::bind(&Chip8Tester::testCpu9XY0b, this)) &&
    runTest("BNNN", std::bind(&Chip8Tester::testCpuBNNN, this)) &&
    runTest("FX07", std::bind(&Chip8Tester::testCpuFX07, this)) &&
    runTest("FX15", std::bind(&Chip8Tester::testCpuFX15, this)) &&
    runTest("FX18", std::bind(&Chip8Tester::testCpuFX18, this)) &&
    runTest("FX1E", std::bind(&Chip8Tester::testCpuFX1E, this)) &&
    runTest("FX55", std::bind(&Chip8Tester::testCpuFX55, this)) &&
    runTest("FX66", std::bind(&Chip8Tester::testCpuFX66, this)) &&
    true;
  return res;
}

bool Chip8Tester::runTest(const std::string name, std::function<bool()> test) {
  m_chip.initialize();
  bool result = test();
  printf("TEST %s: %s\n", name.c_str(), (result ? sPass.c_str() : sFail.c_str()));
  return result;
}

bool Chip8Tester::testCpu3XNNa() {
  m_chip.loadInstruction(0x3245);
  m_chip.loadRegister(2, 0x45);
  m_chip.execute();
  return m_chip.verifyPC(0x204);
}

bool Chip8Tester::testCpu3XNNb() {
  m_chip.loadInstruction(0x3245);
  m_chip.loadRegister(2, 0x44);
  m_chip.execute();
  return m_chip.verifyPC(0x202);
}

bool Chip8Tester::testCpu4XNNa() {
  m_chip.loadInstruction(0x4245);
  m_chip.loadRegister(2, 0x44);
  m_chip.execute();
  return m_chip.verifyPC(0x204);
}

bool Chip8Tester::testCpu4XNNb() {
  m_chip.loadInstruction(0x4245);
  m_chip.loadRegister(2, 0x45);
  m_chip.execute();
  return m_chip.verifyPC(0x202);
}

bool Chip8Tester::testCpu5XY0a() {
  m_chip.loadInstruction(0x5120);
  m_chip.loadRegister(1, 0x12);
  m_chip.loadRegister(2, 0x12);
  m_chip.execute();
  return m_chip.verifyPC(0x204);
}

bool Chip8Tester::testCpu5XY0b() {
  m_chip.loadInstruction(0x5120);
  m_chip.loadRegister(1, 0x12);
  m_chip.loadRegister(2, 0x13);
  m_chip.execute();
  return m_chip.verifyPC(0x202);
}

bool Chip8Tester::testCpu6XNN() {
  m_chip.loadInstruction(0x6142);
  m_chip.execute();
  return m_chip.verifyRegister(1, 0x42);
}

bool Chip8Tester::testCpu7XNN() {
  m_chip.loadInstruction(0x7121);
  m_chip.loadRegister(1, 0x21);
  m_chip.execute();
  return m_chip.verifyRegister(1, 0x42);
}

bool Chip8Tester::testCpu8XY0() {
  m_chip.loadInstruction(0x8120);
  m_chip.loadRegister(2, 0x21);
  m_chip.execute();
  return m_chip.verifyRegister(1, 0x21);
}

bool Chip8Tester::testCpu8XY1() {
  m_chip.loadInstruction(0x8011);
  m_chip.loadRegister(0, 0x00);
  m_chip.loadRegister(1, 0x01);
  m_chip.execute();
  return m_chip.verifyRegister(0, 0x01);
}

bool Chip8Tester::testCpu8XY2() {
  m_chip.loadInstruction(0x8012);
  m_chip.loadRegister(0, 0x11);
  m_chip.loadRegister(1, 0x10);
  m_chip.execute();
  return m_chip.verifyRegister(0, 0x10);
}

bool Chip8Tester::testCpu8XY3() {
  m_chip.loadInstruction(0x8013);
  m_chip.loadRegister(0, 0x11);
  m_chip.loadRegister(1, 0x22);
  m_chip.execute();
  return m_chip.verifyRegister(0, 0x33);
}

bool Chip8Tester::testCpu8XY4() {
  m_chip.loadInstruction(0x8014);
  m_chip.loadRegister(0, 0xFF);
  m_chip.loadRegister(1, 0x01);
  m_chip.execute();
  return m_chip.verifyRegister(0, 0x00) &&
         m_chip.verifyRegister(15, 0x01);
}

bool Chip8Tester::testCpu8XY6a() {
  m_chip.loadInstruction(0x8106);
  m_chip.loadRegister(1, 0x5);
  m_chip.execute();
  return m_chip.verifyRegister(1, 0x2) &&
         m_chip.verifyRegister(0xF, 0x1);
}

bool Chip8Tester::testCpu8XY6b() {
  m_chip.loadInstruction(0x8106);
  m_chip.loadRegister(1, 0x2);
  m_chip.execute();
  return m_chip.verifyRegister(1, 0x1) &&
         m_chip.verifyRegister(0xF, 0x0);
}

bool Chip8Tester::testCpu8XYEa() {
  m_chip.loadInstruction(0x810E);
  m_chip.loadRegister(1, 0x81);
  m_chip.execute();
  return m_chip.verifyRegister(1, 0x2) &&
         m_chip.verifyRegister(0xF, 0x1);
}

bool Chip8Tester::testCpu8XYEb() {
  m_chip.loadInstruction(0x810E);
  m_chip.loadRegister(1, 0x01);
  m_chip.execute();
  return m_chip.verifyRegister(1, 0x2) &&
         m_chip.verifyRegister(0xF, 0x0);
}

bool Chip8Tester::testCpu9XY0a() {
  m_chip.loadInstruction(0x9120);
  m_chip.loadRegister(1, 0x12);
  m_chip.loadRegister(2, 0x12);
  m_chip.execute();
  return m_chip.verifyPC(0x202);
}

bool Chip8Tester::testCpu9XY0b() {
  m_chip.loadInstruction(0x9120);
  m_chip.loadRegister(1, 0x12);
  m_chip.loadRegister(2, 0x13);
  m_chip.execute();
  return m_chip.verifyPC(0x204);
}

bool Chip8Tester::testCpuBNNN() {
  m_chip.loadInstruction(0xB120);
  m_chip.loadRegister(0, 0x03);
  m_chip.execute();
  return m_chip.verifyPC(0x123);
}

bool Chip8Tester::testCpuFX07() {
  m_chip.loadInstruction(0xF107);
  m_chip.setDelayTimer(0x7);
  m_chip.execute();
  return m_chip.verifyRegister(1,0x7);
}

bool Chip8Tester::testCpuFX15() {
  m_chip.loadInstruction(0xF115);
  m_chip.loadRegister(1, 0x7);
  m_chip.execute();
  return m_chip.verifyDelayTimer(0x7);
}

bool Chip8Tester::testCpuFX18() {
  m_chip.loadInstruction(0xF118);
  m_chip.loadRegister(1, 0x7);
  m_chip.execute();
  return m_chip.verifySoundTimer(0x7);
}

bool Chip8Tester::testCpuFX1E() {
  m_chip.loadInstruction(0xF11E);
  m_chip.loadRegister(1, 0x7);
  m_chip.execute();
  return m_chip.verifyI(0x7);
}

bool Chip8Tester::testCpuFX55() {
  m_chip.loadInstruction(0xFF55);
  m_chip.loadRegister(0x0, 0x7);
  m_chip.loadRegister(0x5, 0x8);
  m_chip.loadRegister(0xF, 0x9);
  m_chip.setI(0x5);
  m_chip.execute();
  return m_chip.verifyMemory(0x5, 0x7) &&
         m_chip.verifyMemory(0xA, 0x8) &&
         m_chip.verifyMemory(0x14, 0x9);
}

bool Chip8Tester::testCpuFX66() {
  m_chip.loadInstruction(0xFF66);
  m_chip.setI(0x5);
  m_chip.loadMemory(0x5, 0x7);
  m_chip.loadMemory(0xA, 0x8);
  m_chip.loadMemory(0x14, 0x9);
  m_chip.execute();
  return m_chip.verifyRegister(0x0, 0x7) &&
         m_chip.verifyRegister(0x5, 0x8) &&
         m_chip.verifyRegister(0xF, 0x9);
}