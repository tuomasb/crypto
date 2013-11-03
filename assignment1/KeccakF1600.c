/* implementation of the internal permutation of Keccak with a 1600-bit state*/
// Tuomas Blomqvist
// tuomas.blomqvist@aalto.fi
// 67300C
// References used: http://keccak.noekeon.org/Keccak-implementation-3.2.pdf
// Probably not the most optimal implementation but was easy to implement while only reading the pseudocode on pages 7 and 8


#include "stdio.h"
#include "stdlib.h"
#include "KeccakF1600.h"

// Uncomment #define below to be able to inspect internal permutation state after each step
//#define DEBUG

//The offset constants
const char r[5][5]={{0,36,3,41,18},{1,44,10,45,2},{62,6,43,15,61},{28,55,25,21,56},{27,20,39,8,14}};

//The round constants
const unsigned long RC[24]={0x0000000000000001, 0x0000000000008082,
			    0x800000000000808A, 0x8000000080008000,
			    0x000000000000808B, 0x0000000080000001,
			    0x8000000080008081, 0x8000000000008009,
			    0x000000000000008A, 0x0000000000000088,
			    0x0000000080008009, 0x000000008000000A,
			    0x000000008000808B, 0x800000000000008B,
			    0x8000000000008089, 0x8000000000008003,
			    0x8000000000008002, 0x8000000000000080,
			    0x000000000000800A, 0x800000008000000A,
			    0x8000000080008081, 0x8000000000008080,
			    0x0000000080000001, 0x8000000080008008 };


// Print internal same in the same format as https://github.com/gvanas/KeccakCodePackage/blob/master/TestVectors/KeccakF-1600-IntermediateValues.txt
#ifdef DEBUG
void dbgprint(unsigned long** STATE) {
  for(int x=0; x<5; x++) {
    for(int y=0; y<5; y++) {
      printf("%lx ", STATE[y][x]); // Reverse x,y
    }
  printf("\n");
  }
  printf("\nStep Complete\n");
  scanf("%c");
}
#endif


// Rotate 64bit word specified amount of times to left
// Left shift by offset, rightshift by 64-offset and xor the results together
// Helper function to simplify code
unsigned long Rot(unsigned long lane, int offset) {
  if(offset != 0) {
    return ((lane << offset) ^ (lane >> (64 - offset))); 
  } else {
  return lane;
  }
}

// Theta-step
//
void Theta(unsigned long** STATE) {
  unsigned long C[5];
  unsigned long D[5];

  for(int x=0; x<5; x++) {
    C[x] = STATE[x][0] ^ STATE[x][1] ^ STATE[x][2] ^ STATE[x][3] ^ STATE[x][4];
  }


  for(int x=0; x<5; x++) {
    D[x] = C[((x-1)+5)%5] ^ Rot(C[(x+1)%5], 1); // Adding five to the index before modulo operator to deal with negative index -1
  }


  for(int x=0; x<5; x++) {
    for(int y=0; y<5; y++) {
      STATE[x][y] = STATE[x][y] ^ D[x];
    }
  }

}

// Rho-step
// Rotate each word by the amount specified by offset constants (table r)
void Rho(unsigned long** STATE) {
  for(int x=0; x<5; x++) {
    for(int y=0; y<5; y++) {
      STATE[x][y] = Rot(STATE[x][y], r[x][y]);
    }
  }
}

// Pi-step

void Pi(unsigned long** STATE) {
  // Need to copy the current state to be able to relocate the words without overwriting words that have not yet been relocated anywhere
  // Memory from stack, no need to be freed
  unsigned long copy[5][5];
  for(int x=0; x<5; x++) {
    for(int y=0; y<5; y++) {
      copy[x][y] = STATE[x][y];
    }
  }

  for(int x=0; x<5; x++) {
    for(int y=0; y<5; y++) {
      STATE[y][(2*x+3*y)%5] = copy[x][y];
    }
  }
}

// Chi-step
void Chi(unsigned long** STATE) {
  // Again need a copy
  unsigned long copy[5][5];
  for(int x=0; x<5; x++) {
    for(int y=0; y<5; y++) {
      copy[x][y] = STATE[x][y];
    }
  }
  for(int x=0; x<5; x++) {
    for(int y=0; y<5; y++) {
      STATE[x][y] = copy[x][y] ^ ((~copy[(x+1)%5][y]) & copy[(x+2)%5][y]);
    }
  }
}

// Iota-step
// Xor the first 64-bit word with the round constant
void Iota(unsigned long** STATE, unsigned long RC) {
  STATE[0][0] = STATE[0][0] ^ RC;
}

// One round of Keccak-permutation (along with my debug-statements)
void Round(unsigned long** STATE, unsigned long RC) {
  Theta(STATE);
  #ifdef DEBUG
  printf("After theta\n");
  dbgprint(STATE);
  #endif
  Rho(STATE);
  #ifdef DEBUG
  printf("After rho\n");
  dbgprint(STATE);
  #endif
  Pi(STATE);
  #ifdef DEBUG
  printf("After pi\n");
  dbgprint(STATE);
  #endif
  Chi(STATE);
  #ifdef DEBUG
  printf("After chi\n");
  dbgprint(STATE);
  #endif
  Iota(STATE, RC);
  #ifdef DEBUG
  printf("After iota\n");
  dbgprint(STATE);
  #endif
}

//Return the state after 24 rounds
//Do not modify the name of this fonction  
unsigned long** KeccakF(unsigned long** INPUT){

  unsigned long** STATE=malloc(5*sizeof(unsigned long));
  for(int x=0; x<5; x++){
    STATE[x]=malloc(5*sizeof(unsigned long));
  }

  for(int x=0; x<5; x++) {
    for(int y=0; y<5; y++) {
      STATE[x][y] = INPUT[x][y];
    }
  }

  for(int x=0; x<24; x++) { // Apply 24 rounds
    Round(STATE, RC[x]); // One keccak round with the corresponding Round Constant
  }
  return STATE;
}

