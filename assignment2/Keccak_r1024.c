#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KeccakF1600.h"
#include "Keccak_r1024.h"
// #define DEBUG

void dbgprint2(unsigned char * state, int len, unsigned char * msg) {
  #ifdef DEBUG
  printf("\n%s\n", msg);
  for(int x=0;x<len;x++) {
    printf("%02x ", state[x]);
  }
  #endif
}

// DO NOT MODIFY THE HEADING OF THIS FUNCTION
unsigned char* Hash(unsigned char* mess, unsigned int lenght){
  unsigned char * hash = malloc(130);
  // Apply padding
  unsigned char * padded = malloc(lenght + 130); // Maximum length with padding and some more
  memcpy(padded, mess, lenght); // No null pointer just copy the message
  memset(padded+lenght, 0x01, 1); // First byte after mess to \x01
  int nullbytes = (128-((lenght+2)%128));
  int total = lenght + 2 + nullbytes;
  int blocks = total / 128;
  #ifdef DEBUG
  printf("0x01 position: %d\n", lenght+1);
  printf("0x00 start: %d\n", lenght+2);
  printf("0x00 amount: %d\n", nullbytes);
  printf("0x80 position: %d\n", lenght+2+nullbytes);
  printf("Padded Length in bytes: %d\n", total);
  printf("Amount of blocks: %d\n", blocks);
  #endif
  memset(padded+lenght+1, 0x00, nullbytes); // Bytes after \x01 to 0x00 until 
  memset(padded+lenght+1+nullbytes, 0x80, 1); // Final piece of padding 0x80 byte

  // Initialization
  unsigned char * state = calloc(201, sizeof(unsigned char));
  
  // Absorbing phase
  for(int x=0; x<blocks; x++) {
    for(int y=0;y<128; y++) {
      state[y] ^= padded[x*128+y];
    }
    dbgprint2(state, 200, "Before KeccakF_bytes");
    KeccakF_bytes(state);
    dbgprint2(state, 200, "After KeccakF_bytes");
  }

  // Squeezing phase (only 128 bytes of input needed so no need to call KeccakF_bytes again)
  memcpy(hash, state, 128);
  hash[128] = 0x00;
  return hash;
}
