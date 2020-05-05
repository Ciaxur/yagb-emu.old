#include "../include/Utilities.h"

using namespace std;

void Utilities::hexDump(char *filePath, std::ostream &out) {
  u_char buffer[1000];
  int addr = 0;
  int n;
  std::ifstream infile;
  infile.open(filePath);

  // Check if file exists
  if (!infile) {
    std::cout << "File not found" << std::endl;
    return;
  }

  while (true) {
    infile.read((char *)buffer, 16);
    // Return buffer size up to 16
    n = infile.gcount();
    if (n <= 0) {
      break;
    }
    // Offset 16 bytes per line
    addr += 16;
    // Print line of n bytes
    for (int i = 0; i < 16; i++) {
      if (i + 1 <= n) {
	out << hex << setw(2) << setfill('0') << (int)buffer[i];
      }
      // Space each byte
      out << " ";
    }
    // New line after n bytes
    out << "\n";
    // Break if end of file
    if (infile.eof()) {
      break;
    }
  }
}

void Utilities::disassemble(char *filePath, std::ostream &out) {
  bool dataSectionFound = false;
  stringstream ss;
  Utilities::hexDump(filePath, ss);

  // Format cout Flags
  ios_base::fmtflags prevFlags(out.flags());  // To restore cout Output Style
  out << hex << uppercase << setw(2) << setfill('0');

  ss.seekg(0x100);

  u_int16_t PC = 0x100;  // Start at Cartridge Header
  u_int16_t opcode;      // 16-bit Opcode
  u_int8_t param8;       // 8-bit Data
  u_int16_t param16;     // 16-bit Data
  u_int16_t addr;        // 16-bit Address

  while (ss >> opcode) {
    //ss >> param;
    out << setw(4) << setfill('0') << PC << '\t';
    out << setw(2) << setfill('0') << opcode << ' ';  //<< setw(2) << setfill('0') << param << '\t';

    if (!dataSectionFound) {
      //0-A
      switch (opcode & 0xF0) {
      case 0x00:
	switch(opcode & 0x0F){
	case 0x00: cout <<"NOP "; break;
	case 0x01: cout <<"STOP 0 "; break;
	case 0x02: cout <<"JR NZ r8"; break;
	case 0x03: cout <<"JR NC r8"; break;
	case 0x04: cout <<"LD B B"; break;
	case 0x05: cout <<"LD D B"; break;
	case 0x06: cout <<"LD H B"; break;
	case 0x07: cout <<"LD (HL) B"; break;
	case 0x08: cout <<"ADD A B"; break;
	case 0x09: cout <<"SUB B "; break;
	case 0x0a: cout <<"AND B "; break;
	case 0x0b: cout <<"OR B "; break;
	case 0x0c: cout <<"RET NZ "; break;
	case 0x0d: cout <<"RET NC "; break;
	case 0x0e: cout <<"LDH (a8) A"; break;
	case 0x0f: cout <<"LDH A (a8)"; break;
	default:break;
	}
	break;

      case 0x10:
	switch(opcode & 0x0F){
	case 0x00: cout <<"LD BC d16"; break;
	case 0x01: cout <<"LD DE d16"; break;
	case 0x02: cout <<"LD HL d16"; break;
	case 0x03: cout <<"LD SP d16"; break;
	case 0x04: cout <<"LD B C"; break;
	case 0x05: cout <<"LD D C"; break;
	case 0x06: cout <<"LD H C"; break;
	case 0x07: cout <<"LD (HL) C"; break;
	case 0x08: cout <<"ADD A C"; break;
	case 0x09: cout <<"SUB C "; break;
	case 0x0a: cout <<"AND C "; break;
	case 0x0b: cout <<"OR C "; break;
	case 0x0c: cout <<"POP BC "; break;
	case 0x0d: cout <<"POP DE "; break;
	case 0x0e: cout <<"POP HL "; break;
	case 0x0f: cout <<"POP AF "; break;
	default: break;
	}
	break;

      case 0x20:
	switch(opcode & 0x0F){
	case 0x00: cout <<"LD (BC) A"; break;
	case 0x01: cout <<"LD (DE) A"; break;
	case 0x02: cout <<"LD (HL+) A"; break;
	case 0x03: cout <<"LD (HL-) A"; break;
	case 0x04: cout <<"LD B D"; break;
	case 0x05: cout <<"LD D D"; break;
	case 0x06: cout <<"LD H D"; break;
	case 0x07: cout <<"LD (HL) D"; break;
	case 0x08: cout <<"ADD A D"; break;
	case 0x09: cout <<"SUB D "; break;
	case 0x0a: cout <<"AND D "; break;
	case 0x0b: cout <<"OR D "; break;
	case 0x0c: cout <<"JP NZ a16"; break;
	case 0x0d: cout <<"JP NC a16"; break;
	case 0x0e: cout <<"LD (C) A"; break;
	case 0x0f: cout <<"LD A (C)"; break;
	default: break;
	}
	break;

      case 0x30:
	switch(opcode & 0x0F){
	case 0x00: cout << "INC BC "; break;
	case 0x03: cout << "INC SP "; break;
	case 0x04: cout << "LD B E"; break;
	case 0x05: cout << "LD D E"; break;
	case 0x06: cout << "LD H E"; break;
	case 0x07: cout << "LD (HL) E"; break;
	case 0x08: cout << "ADD A E"; break;
	case 0x09: cout << "SUB E "; break;
	case 0x0a: cout << "AND E "; break;
	case 0x0b: cout << "OR E "; break;
	case 0x0c: cout << "JP a16 "; break;
	case 0x0f: cout << "DI "; break;
	default: break;
	}
	break;


      case 0x40:
	switch(opcode & 0x0F){
	case 0x00: cout << "INC B "; break;
	case 0x01: cout << "INC D "; break;
	case 0x02: cout << "INC H "; break;
	case 0x03: cout << "INC (HL) "; break;
	case 0x04: cout << "LD B H"; break;
	case 0x05: cout << "LD D H"; break;
	case 0x06: cout << "LD H H"; break;
	case 0x07: cout << "LD (HL) H"; break;
	case 0x08: cout << "ADD A H"; break;
	case 0x09: cout << "SUB H "; break;
	case 0x0a: cout << "AND H "; break;
	case 0x0b: cout << "OR H "; break;
	case 0x0c: cout << "CALL NZ a16"; break;
	case 0x0d: cout << "CALL NC a16"; break;
	default: break;
	}
	break;

      case 0x50:
	switch(opcode & 0x0F){
	case 0x00: cout << "DEC B "; break;
	case 0x01: cout << "DEC D "; break;
	case 0x02: cout << "DEC H "; break;
	case 0x03: cout << "DEC (HL) "; break;
	case 0x04: cout << "LD B L"; break;
	case 0x05: cout << "LD D L"; break;
	case 0x06: cout << "LD H L"; break;
	case 0x07: cout << "LD (HL) L"; break;
	case 0x08: cout << "ADD A L"; break;
	case 0x09: cout << "SUB L "; break;
	case 0x0a: cout << "AND L "; break;
	case 0x0b: cout << "OR L "; break;
	case 0x0c: cout << "PUSH BC "; break;
	case 0x0d: cout << "PUSH DE "; break;
	case 0x0e: cout << "PUSH HL "; break;
	case 0x0f: cout << "PUSH AF "; break;
	default: break;
	}
	break;

      case 0x60:
	switch(opcode & 0x0F){
	case 0x00: cout << "LD B d8"; break;
	case 0x01: cout << "LD D d8"; break;
	case 0x02: cout << "LD H d8"; break;
	case 0x03: cout << "LD (HL) d8"; break;
	case 0x04: cout << "LD B (HL)"; break;
	case 0x05: cout << "LD D (HL)"; break;
	case 0x06: cout << "LD H (HL)"; break;
	case 0x07: cout << "HALT "; break;
	case 0x08: cout << "ADD A (HL)"; break;
	case 0x09: cout << "SUB (HL) "; break;
	case 0x0a: cout << "AND (HL) "; break;
	case 0x0b: cout << "OR (HL) "; break;
	case 0x0c: cout << "ADD A d8"; break;
	case 0x0d: cout << "SUB d8 "; break;
	case 0x0e: cout << "AND d8 "; break;
	case 0x0f: cout << "OR d8 "; break;
	default: break;
	}
	break;

      case 0x70:
	switch(opcode & 0x0F){
	case 0x00: cout << "RLCA "; break;
	case 0x01: cout << "RLA "; break;
	case 0x02: cout << "DAA "; break;
	case 0x03: cout << "SCF "; break;
	case 0x04: cout << "LD B A"; break;
	case 0x05: cout << "LD D A"; break;
	case 0x06: cout << "LD H A"; break;
	case 0x07: cout << "LD (HL) A"; break;
	case 0x08: cout << "ADD A A"; break;
	case 0x09: cout << "SUB A "; break;
	case 0x0a: cout << "AND A "; break;
	case 0x0b: cout << "OR A "; break;
	case 0x0c: cout << "RST 00H "; break;
	case 0x0d: cout << "RST 10H "; break;
	case 0x0e: cout << "RST 20H "; break;
	case 0x0f: cout << "RST 30H "; break;
	default: break;
	}
	break;

      case 0x80:
	switch(opcode & 0x0F){
	case 0x00: cout << "LD (a16) SP"; break;
	case 0x01: cout << "JR r8 "; break;
	case 0x02: cout << "JR Z r8"; break;
	case 0x03: cout << "JR C r8"; break;
	case 0x04: cout << "LD C B"; break;
	case 0x05: cout << "LD E B"; break;
	case 0x06: cout << "LD L B"; break;
	case 0x07: cout << "LD A B"; break;
	case 0x08: cout << "ADC A B"; break;
	case 0x09: cout << "SBC A B"; break;
	case 0x0a: cout << "XOR B "; break;
	case 0x0b: cout << "CP B "; break;
	case 0x0c: cout << "RET Z "; break;
	case 0x0d: cout << "RET C "; break;
	case 0x0e: cout << "ADD SP r8"; break;
	case 0x0f: cout << "LD HL SP+r8"; break;
	default: break;
	}
	break;

      case 0x90:
	switch(opcode & 0x0F){
	case 0x00: cout << "ADD HL BC"; break;
	case 0x01: cout << "ADD HL DE"; break;
	case 0x02: cout << "ADD HL HL"; break;
	case 0x03: cout << "ADD HL SP"; break;
	case 0x04: cout << "LD C C"; break;
	case 0x05: cout << "LD E C"; break;
	case 0x06: cout << "LD L C"; break;
	case 0x07: cout << "LD A C"; break;
	case 0x08: cout << "ADC A C"; break;
	case 0x09: cout << "SBC A C"; break;
	case 0x0a: cout << "XOR C "; break;
	case 0x0b: cout << "CP C "; break;
	case 0x0c: cout << "RET "; break;
	case 0x0d: cout << "RETI "; break;
	case 0x0e: cout << "JP (HL) "; break;
	case 0x0f: cout << "LD SP HL"; break;
	default: break;
	}
	break;

	// case 0x00: Not really needed anymore.
	//     switch (opcode & 0x0F) {
	//     case 0x00:
	//         out << "NOP";
	//         break;
	//     }
	//     break;
	// case 0x10:
	//     switch (opcode & 0x0F) {
	//     case 0x00:
	//         out << "STOP";
	//         break;
	//     }
	// case 0x20: cout << "JR NZ"; break;
	//     break;


		
	// A-F
      case 0xA0:
	switch (opcode & 0x0F) {
	case 0x00:                // LD A,[r16]
	  out << "LD A, (BC)";  // Obtain r16 from 16-bit Register BC
	  break;

	case 0x01:
	  out << "LD A, (DE)";  // Obtain r16 from 16-bit Register DE
	  break;
	case 0x02:
	  // HL+ -> Load value into Register 'A'
	  //  pointed by HL and increment HL Afterwards
	  out << "LD A, (HL+)";  // Obtain r16 from 16-bit Register HL
	  break;
	case 0x03:
	  // HL+ -> Load value into Register 'A'
	  //  pointed by HL and decrement HL Afterwards
	  out << "LD A, (HL-)";  // Obtain r16 from 16-bit Register HL
	  break;
	case 0x04:
	  out << "LD C, D";
	  break;
	case 0x05:
	  out << "LD E, D";
	  break;
	case 0x06:
	  out << "LD L, D";
	  break;
	case 0x07:
	  out << "LD A, D";
	  break;
	case 0x08:
	  out << "ADC A, D";
	  break;
	case 0x09:
	  out << "SBC A, D";
	  break;
	case 0x0A:
	  out << "XOR D";
	  break;
	case 0x0B:
	  out << "CP D";
	  break;
	case 0x0C:
	  out << "JP Z, ";

	  // Obtain 16bit Address
	  ss >> addr;
	  out << addr;
	  break;
	  break;
	case 0x0D:
	  out << "JP C, ";

	  // Obtain 16bit Address
	  ss >> addr;
	  out << addr;
	  break;
	case 0x0E:
	  // Obtain 16bit Address
	  ss >> addr;
	  out << "JP " << addr << ", A";
	  break;
	case 0x0F:
	  // Obtain 16bit Address
	  ss >> addr;
	  out << "JP A, " << addr;
	  break;


	default:
	  break;
	}
	break;

      case 0xB0:
	switch (opcode & 0x0F) {
	case 0x00:
	  out << "DEC BC";
	  break;
	case 0x01:
	  out << "DEC DE";
	  break;
	case 0x02:
	  out << "DEC HL";
	  break;
	case 0x03:
	  out << "DEC SP";
	  break;
	case 0x04:
	  out << "LD C, E";
	  break;
	case 0x05:
	  out << "LD E, E";
	  break;
	case 0x06:
	  out << "LD L, E";
	  break;
	case 0x07:
	  out << "LD A, E";
	  break;
	case 0x08:
	  out << "ADC A, E";
	  break;
	case 0x09:
	  out << "SBC A, E";
	  break;
	case 0x0A:
	  out << "XOR E";
	  break;
	case 0x0B:
	  out << "CP E";
	  break;
	case 0x0C:
	  out << "PREFIX";
	  break;
	case 0x0F:
	  out << "EI";
	  break;

	default:
	  break;
	}
	break;

      case 0xC0:
	switch (opcode & 0x0F) {
	case 0x00:
	  out << "INC C";
	  break;
	case 0x01:
	  out << "INC E";
	  break;
	case 0x02:
	  out << "INC L";
	  break;
	case 0x03:
	  out << "INC A";
	  break;
	case 0x04:
	  out << "LD C, H";
	  break;
	case 0x05:
	  out << "LD E, H";
	  break;
	case 0x06:
	  out << "LD L, H";
	  break;
	case 0x07:
	  out << "LD A, H";
	  break;
	case 0x08:
	  out << "ADC A, H";
	  break;
	case 0x09:
	  out << "SBC A, H";
	  break;
	case 0x0A:
	  out << "XOR H";
	  break;
	case 0x0B:
	  out << "CP H";
	  break;
	case 0x0C:
	  // Obtain 16bit Address
	  ss >> addr;
	  out << "CALL Z, " << addr;
	  break;
	case 0x0D:
	  // Obtain 16bit Address
	  ss >> addr;
	  out << "CALL C, " << addr;
	  break;

	default:
	  break;
	}
	break;

      case 0xD0:
	switch (opcode & 0x0F) {
	case 0x00:
	  out << "DEC C";
	  break;
	case 0x01:
	  out << "DEC E";
	  break;
	case 0x02:
	  out << "DEC L";
	  break;
	case 0x03:
	  out << "DEC A";
	  break;
	case 0x04:
	  out << "LD C, L";
	  break;
	case 0x05:
	  out << "LD E, L";
	  break;
	case 0x06:
	  out << "LD L, L";
	  break;
	case 0x07:
	  out << "LD A, L";
	  break;
	case 0x08:
	  out << "ADC A, L";
	  break;
	case 0x09:
	  out << "SBC A, L";
	  break;
	case 0x0A:
	  out << "XOR L";
	  break;
	case 0x0B:
	  out << "CP L";
	  break;
	case 0x0C:
	  // Obtain 16bit Address
	  ss >> addr;
	  out << "CALL, " << addr;
	  break;

	default:
	  break;
	}
	break;

      case 0xE0:
	switch (opcode & 0x0F) {
	case 0x00:
	  // Obtain 8bit Param (Immediate Data)
	  ss >> param8;
	  out << "LD C, " << param8;
	  break;
	case 0x01:
	  // Obtain 8bit Param (Immediate Data)
	  ss >> param8;
	  out << "LD E, " << param8;
	  break;
	case 0x02:
	  // Obtain 8bit Param (Immediate Data)
	  ss >> param8;
	  out << "LD L, " << param8;
	  break;
	case 0x03:
	  // Obtain 8bit Param (Immediate Data)
	  ss >> param8;
	  out << "LD A, " << param8;
	  break;
	case 0x04:
	  out << "LD C, (HL)";
	  break;
	case 0x05:
	  out << "LD E, (HL)";
	  break;
	case 0x06:
	  out << "LD L, (HL)";
	  break;
	case 0x07:
	  out << "LD A, (HL)";
	  break;
	case 0x08:
	  out << "ADC A, (HL)";
	  break;
	case 0x09:
	  out << "SBC A, (HL)";
	  break;
	case 0x0A:
	  out << "XOR (HL)";
	  break;
	case 0x0B:
	  out << "CP (HL)";
	  break;
	case 0x0C:
	  // Obtain 8bit Param (Immediate Data)
	  ss >> param8;
	  out << "ADC A, " << param8;
	  break;
	case 0x0D:
	  // Obtain 8bit Param (Immediate Data)
	  ss >> param8;
	  out << "SBC A, " << param8;
	  break;
	case 0x0E:
	  // Obtain 8bit Param (Immediate Data)
	  ss >> param8;
	  out << "XOR " << param8;
	  break;
	case 0x0F:
	  // Obtain 8bit Param (Immediate Data)
	  ss >> param8;
	  out << "CP " << param8;
	  break;

	default:
	  break;
	}
	break;

      case 0xF0:
	switch (opcode & 0x0F) {
	case 0x00:
	  out << "RRCA";
	  break;
	case 0x01:
	  out << "RRA";
	  break;
	case 0x02:
	  out << "CPL";
	  break;
	case 0x03:
	  out << "CCF";
	  break;
	case 0x04:
	  out << "LD C, A";
	  break;
	case 0x05:
	  out << "LD E, A";
	  break;
	case 0x06:
	  out << "LD L, A";
	  break;
	case 0x07:
	  out << "LD A, A";
	  break;
	case 0x08:
	  out << "ADC A, A";
	  break;
	case 0x09:
	  out << "SBC A, A";
	  break;
	case 0x0A:
	  out << "XOR A";
	  break;
	case 0x0B:
	  out << "CP A";
	  break;
	case 0x0C:
	  out << "RST 08H";
	  break;
	case 0x0D:
	  out << "RST 18H";
	  break;
	case 0x0E:
	  out << "RST 28H";
	  break;
	case 0x0F:
	  out << "RST 38H";
	  break;

	default:
	  break;
	}
	break;

      default:
	// dataSectionFound = true;
	break;
      }
    }

    PC += 0x1;
    out << "\n";
  }
}
