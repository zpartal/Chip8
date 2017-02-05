#ifndef CHIP8_H
#define CHIP8_H

#include <string>
#include <functional>

class Chip8
{
public:
  Chip8(bool selfTest = false);

  void initialize();
  void emulateCycle();
  void execute();

private:
  void fetchOpcode();
  void decodeOpcode();

private:
  unsigned short opcode;       // 2-byte opcodes

  unsigned char  memory[4096]; // memory
  unsigned char  V[16];        // registers
  unsigned short I;            // 0x000 to 0xFFF
  unsigned short pc;           // 0x000 to 0xFFF

  unsigned short sp;
  unsigned short stack[16];

  unsigned char  delay_timer;
  unsigned char  sound_timer;

  unsigned char  gfx[64 * 32];
  unsigned char  key[16];

  unsigned char chip8_fontset[80];

public:
  // Test Helper Functions
  void loadInstruction(const unsigned short instr, const int addr = 0x200);
  void loadRegister(const int reg, const char val) { V[reg] = val; }
  void loadMemory(const int mem, const char val) { memory[mem] = val; }
  void setI(const short val) { I = val; }
  void setPC(const short val) { pc = val; }

  bool verifyRegister(const int reg, const char val) { return V[reg] == val; }
  bool verifyPC(const short val) { return val == pc; }
  bool verifyI(const short val) { return val == I; }
  bool verifyMemory(const int mem, const char val) { return memory[mem] == val; }

  void setDelayTimer(const char val) { delay_timer = val; }
  bool verifyDelayTimer(const char val) { return val == delay_timer; }
  void setSoundTimer(const char val) { sound_timer = val; }
  bool verifySoundTimer(const char val) { return val == sound_timer; }

};

#endif