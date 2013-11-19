/* implementation of the internal permutation of Keccak with a 1600-bit state*/
// Tuomas Blomqvist
// tuomas.blomqvist@aalto.fi
// 67300C
// References used: http://keccak.noekeon.org/Keccak-implementation-3.2.pdf
// Probably not the most optimal implementation but was easy to implement while reading the pseudocode on pages 7 and 8


#include "stdio.h"
#include "stdlib.h"
#include "KeccakF1600.h"
#include "string.h"

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
// Does nothing unless DEBUG defined
void dbgprint(unsigned long** STATE, char * str) {
#ifdef DEBUG
  char c; // Something for scanf
  printf("State after %s\n", str);
  for(int x=0; x<5; x++) {
    for(int y=0; y<5; y++) {
      printf("%lx ", STATE[y][x]); // Reverse x,y
    }
  printf("\n");
  }
  scanf("%c", &c);
#endif
}


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
// Move lanes around
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
// Xor the first 64-bit lane with the round constant
void Iota(unsigned long** STATE, unsigned long RC) {
  STATE[0][0] = STATE[0][0] ^ RC;
}

// One round of Keccak-permutation (along with my debug-statements)
// dbgprint does nothing unless DEBUG is defined
void Round(unsigned long** STATE, unsigned long RC) {
  Theta(STATE);
  dbgprint(STATE, "Theta");
  Rho(STATE);
  dbgprint(STATE, "Rho");
  Pi(STATE);
  dbgprint(STATE, "Pi");
  Chi(STATE);
  dbgprint(STATE, "Chi");
  Iota(STATE, RC);
  dbgprint(STATE, "Iota");
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

void fromBytesToWords(unsigned long  **stateAsWords, unsigned char *stateAsBytes)
{
  for(int i=0; i<(1600/64); i++) {
    stateAsWords[i%5][i/5] = 0;
    for(int j=0; j<(64/8); j++)
      stateAsWords[i%5][i/5] |= (unsigned long )(stateAsBytes[i*(64/8)+j]) << (8*j);
  }
}


//Function to add  to the previous assignement.
 //The state is composed of 200 byte
unsigned char* KeccakF_bytes(unsigned char *state){
  unsigned long** stateWords=malloc(5*sizeof(unsigned long));
  unsigned long** output;

  for(int x=0;x<5;x++){
    stateWords[x]=malloc(5*sizeof(unsigned long));
  }

  // Populate stateWords with input state
  fromBytesToWords(stateWords, state);
  // Apply KeccakF
  dbgprint(stateWords, "State before Keccak");
  output = KeccakF(stateWords);
  dbgprint(output, "State after Keccak");
  

  // fromWordsToBytes
  int pos = 0;
  for(int x=0;x<5;x++) {
    for(int y=0; y<5;y++) {
      for(int i=0; i<8; i++) {
        state[pos] = (unsigned char)((output[y][x] >> i*8) & 0x00000000000000FF);
        pos++;
      }
    }
  }

  // Free memory
  for(int x=0;x<5;x++){
    free(stateWords[x]);
    free(output[x]);
  }
  free(stateWords);
  free(output);

  return state;
}

