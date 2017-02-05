#include "chip8.h"
#include <iostream>
#include <stdio.h>
#include <cstring>

void Chip8::execute() {
  fetchOpcode();
  decodeOpcode();
}

void Chip8::fetchOpcode() {
  opcode = memory[pc] << 8 | memory[pc + 1];
}

void Chip8::decodeOpcode() {
  short x = (opcode & 0x0F00) >> 0x8;
  short y = (opcode & 0x00F0) >> 0x4;
  switch(opcode & 0xF000)
  {
    // 0000
    case 0x0000:
      switch(opcode & 0x000F)
      {
        // 0x00E0: Clears the screen
        case 0x0000:
          std::memset(gfx, 0, sizeof gfx);
          pc += 2;
        break;

        // 0x00EE: Returns from subroutine
        case 0x000E:
        break;

        default:
          printf("Unknown opcode [0x0000]: 0x%X\n", opcode);
      }

    // 2NNN: Calls subroutine at NNN.
    case 0x2000:
      stack[sp] = pc;
      ++sp;
      pc = opcode & 0x0FFF;
    break;

    // 3XNN: Skips the next instruction if VX equals NN.
    case 0x3000:
      if(V[x] == (opcode & 0x00FF)) {
        pc += 2;
      }
      pc += 2;
    break;

    // 4XNN: Skips the next instruction if VX doesn't equal NN.
    case 0x4000:
      if(V[x] != (opcode & 0x00FF)) {
        pc += 2;
      }
      pc += 2;
    break;

    // 5XY0: Skips the next instruction if VX equals VY.
    case 0x5000:
      if(V[x] == V[y]) {
        pc += 2;
      }
      pc += 2;
    break;

    // 6XNN: Sets VX to NN.
    case 0x6000:
      V[x] = opcode & 0x00FF;
      pc += 2;
    break;

    // 7XNN: Adds NN to VX.
    case 0x7000:
      V[x] += opcode & 0x00FF;
      pc += 2;
    break;

    // 8XXX
    case 0x8000:
      switch(opcode & 0x000F)
      {
        // 8XY0: Sets VX to the value of VY.
        case 0x0000:
          V[x] = V[y];
          pc += 2;
        break;

        // 8XY1: Sets VX to VX or VY.
        case 0x0001:
          V[x] |= V[y];
          pc += 2;
        break;

        // 8XY2: Sets VX to VX and VY.
        case 0x0002:
          V[x] &= V[y];
          pc += 2;
        break;

        // 8XY3: Sets VX to VX xor VY.
        case 0x0003:
          V[x] ^= V[y];
          pc += 2;
        break;

        // 8XY4: Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
        case 0x0004:
          if(V[y]  > (0xFF - V[x])) {
            V[0xF] = 1;
          }
          else {
            V[0xF] = 0;
          }
          V[x] += V[y];
          pc += 2;
        break;

        // 8XY5: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
        case 0x0005:

        break;

        // 8XY6: Shifts VX right by one. VF is set to the value of the lsb of VX before the shift.
        case 0x0006:
          V[0xF] = V[x] & 0x1;
          V[x] = V[x] >> 1;
          pc += 2;
        break;

        // 8XY7: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
        case 0x0007:

        break;

        // 8XYE: Shifts VX left by one. VF is set to the value of the msb of VX before the shift.
        case 0x000E:
          V[0xF] = (V[x] >> 7) && 0x1;
          V[x] = V[x] << 1;
          pc += 2;
        break;

        default:
          printf ("Unknown opcode [0x8000]: 0x%X\n", opcode);
      }
    break;

    // 9XY0:  Skips the next instruction if VX doesn't equal VY
    case 0x9000:
      if(V[x] != V[y]) {
        pc += 2;
      }
      pc += 2;
    break;

    // ANNN: Sets I to the addres NNN
    case 0xA000:
      I = opcode & 0x0FFF;
      pc += 2;
    break;

    // BNNN: Jumps to the address NNN plus V0
    case 0xB000:
      pc = V[0] + (opcode & 0x0FFF);
    break;

    // CXNN: Sets VX to the result of an AND op on a random number and NN
    case 0xC000:
      V[x] = (rand() % 255) & (opcode & 0x00FF);
      pc += 2;
    break;

    // FXXX
    case 0xF000:
      switch(opcode & 0x00FF)
      {
        // FX07: Sets VX to the value of the delay timer.
        case 0x0007:
          V[x] = delay_timer;
          pc += 2;
        break;

        // FX0A: A key press is awaited, and then stored in VX.
        case 0x000A:
        break;

        // FX15: Sets the delay timer to VX.
        case 0x0015:
          delay_timer = V[x];
          pc += 2;
        break;

        // FX18: Sets the sound timer to VX.
        case 0x0018:
          sound_timer = V[x];
          pc += 2;
        break;

        // FX1E: Adds VX to I.
        case 0x001E:
          I += V[x];
          pc += 2;
        break;

        // FX29: Sets I to the location of the sprite for the character in VX.
        case 0x0028:
        break;

        // FX33: Stores the binary-coded decimal representation of VX
        case 0x0033:
          memory[I] = V[x] /100;
          memory[I + 1] = (V[x] / 10) % 10;
          memory[I + 2] = (V[x] % 100) % 10;
          pc += 2;
        break;

        // FX55: Stores V0 to VX in memory starting at address I.
        case 0x0055:
          for (int i = 0; i <= x; ++i) {
            memory[I+i] = V[i];
          }
          pc += 2;
        break;

        // FX66: Fills V0 to VX with values from memory starting at address I
        case 0x0066:
          for (int i = 0; i <= x; ++i) {
            V[i] = memory[I+i];
          }
          pc += 2;
        break;

        default:
          printf ("Unknown opcode [0xF000]: 0x%X\n", opcode);
      }
    break;
    default:
      printf("Unknown opcode: 0x%X\n", opcode);
  }
}