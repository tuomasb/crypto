#include "stream.h"
#include <string.h>

//Initialisation function
// The key is of lenght 16 bytes and will corresponds to the 16 first bytes of the 1600-bits state S. The others bytes correspond to the initial value. Here 0. 
void initialisation(unsigned char *S,unsigned char* key){
  memset(S, 0, 200); // Initial zero 200*8=1600
  memcpy(S, key, 16); // First 16 bytes are the key
}


// This encryption function return a ciphertext of lenght lenght corresponding to the plaintext Plaintext. The key is 16-bytes. 
unsigned char* encrypt( unsigned char* key, unsigned char* Plaintext,unsigned int lenght){
  unsigned char * ciphertext = malloc(lenght);
  unsigned char * state = malloc(200);
  initialisation(state, key); // Initialize key

  // Loop for byte at a time
  for(int x=0; x<lenght;x++) {
    if(x%128==0) KeccakF_bytes(state); // New key for every 128 bytes
    ciphertext[x] = Plaintext[x] ^ state[x%128]; // Xor plaintext with keystream
  }
  free(state);
  return ciphertext;
}
