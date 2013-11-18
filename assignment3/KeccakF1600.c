/* implementation of the F function of Keccak with a 1600-bit state*/

#include "KeccakF1600.h"

 
const char r[5][5]={{0,36,3,41,18},{1,44,10,45,2},{62,6,43,15,61},{28,55,25,21,56},{27,20,39,8,14}};

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






void fromBytesToWords(unsigned long  **stateAsWords, unsigned char *stateAsBytes)
{
  for(int i=0; i<(1600/64); i++) {
    stateAsWords[i%5][i/5] = 0;
    for(int j=0; j<(64/8); j++)
      stateAsWords[i%5][i/5] |= (unsigned long )(stateAsBytes[i*(64/8)+j]) << (8*j);
  }
} 
 

 //The state is composed of 200 byte
unsigned char* KeccakF_bytes(unsigned char *state){
 
}
