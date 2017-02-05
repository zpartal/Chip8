#include "chip8.h"
#include <iostream>
#include <stdio.h>
#include <cstring>

// Chip 8 Emulator

/* Memory Map
 * 0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
 * 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
 * 0x200-0xFFF - Program ROM and work RAM
 */

Chip8::Chip8(bool selfTest) {
  std::cout << "Chip8 Constructed" << std::endl;
}

void Chip8::initialize()
{
  // Initialize registers and memory once
  pc     = 0x200; // PC starts at 0x200
  opcode = 0;     // Reset current opcode
  I      = 0;     // Reset index register
  sp     = 0;     // Reset stack pointer

  std::memset(gfx, 0, sizeof gfx);       // Clear display
  std::memset(stack, 0, sizeof stack);   // Clear stack
  std::memset(V, 0, sizeof V);           // Clear Registers V0-VF
  std::memset(memory, 0, sizeof memory); // Clear memory

  // Load fontset
  for(int i = 0; i < 80; ++i) {
    memory[i] = chip8_fontset[i];
  }

  // Reset timers
  delay_timer = 0;
  sound_timer = 0;
}

void Chip8::emulateCycle()
{
  // Fetch Opcode
  // Decode Opcode
  // Execute Opcode
  execute();

  // Update timers
  if(delay_timer > 0)
  {
    --delay_timer;
  }

  if(sound_timer > 0)
  {
    if(sound_timer == 1) {
      printf("BEEP!\n");
    }
    --sound_timer;
  }
}

void Chip8::loadInstruction(const unsigned short instr, const int addr) {
  memory[addr]   = (instr & 0xFF00) >> 8;
  memory[addr+1] = instr & 0xFF;
}
