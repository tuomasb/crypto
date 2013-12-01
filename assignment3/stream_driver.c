/* this file gets replaced with our own driver when we grade your submission.
 * So do what you want here but realize it won't persist when we grade it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KeccakF1600.h"
#include "stream.h"



int main(){
  int lenght;
  unsigned char* Key;
  unsigned char* Plaintext;
  unsigned char* Ciphertext;
  unsigned char* Ciphertext2; // Added to prevent memoryleaks with my decryption tests since encrypt creates a new string with malloc()
  int count;

  Key=malloc(16*sizeof(unsigned char)); 
  memset(Key, '1' , 16*sizeof(unsigned char));

  lenght=40;
  Plaintext=malloc(lenght*sizeof(unsigned char)); 
  memset(Plaintext, 0x1 , lenght*sizeof(unsigned char));
  Ciphertext=encrypt(Key, Plaintext, lenght);
  // running encrypt again on Ciphertext will result in the Plaintext since it is xorring with the same bitstream - Tuomas
  Ciphertext2=encrypt(Key, Ciphertext, lenght);
  unsigned char *Ciphertext_ref_1="\xCA\xB7\x4E\xE1\xD0\xAD\x12\x8D\x5B\xBA\x0C\xFE\xAA\xDF\x09\x62\x18\x3D\xA9\x73\xEA\xFC\xA7\x1F\xBE\xE1\x8B\x0A\x86\x2D\x43\xDE\xEA\xB0\x53\x24\xE3\x50\x10\xB1\xF1\xD0\x01";



 //check encryption
  count=1;
  for(int i=0;i<lenght;i++){
    if(Ciphertext[i]!=Ciphertext_ref_1[i]){
	count=0;
      }
  }

  if(count==0){
    printf("FAIL (Encrypt reference 1)\n");
  }
  else{
    printf("PASS (Encrypt reference 1)\n");
  }

  // check decryption
  count=1;
  for(int i=0;i<lenght;i++){
    if(Ciphertext2[i]!=Plaintext[i]){
	count=0;
      }
  }

  if(count==0){
    printf("FAIL (Decrypt reference 1)\n");
  }
  else{
    printf("PASS (Decrypt reference 1)\n");
  }


  free(Key);
  free(Plaintext);
  free(Ciphertext);
  free(Ciphertext2);

  /******************* TEST 2************/
  Key=malloc(16*sizeof(unsigned char)); 
  memset(Key, 0 , 16*sizeof(unsigned char));

  lenght=250;
  Plaintext=malloc(lenght*sizeof(unsigned char)); 
  memset(Plaintext, 0xA , lenght*sizeof(unsigned char));
  Ciphertext=encrypt(Key, Plaintext, lenght);
  // running encrypt again on Ciphertext will result in the Plaintext since it is xorring with the same bitstream - Tuomas
  Ciphertext2=encrypt(Key, Ciphertext, lenght);
  unsigned char *Ciphertext_ref_2="\xED\xD7\xEB\x4A\x73\x85\x2F\xFB\x80\x4D\xCA\x39\xF3\xC6\xDF\x8E\xE4\xA3\x50\xAC\x14\x2C\x92\xDF\x47\x43\x8A\x65\x3A\x4D\x1F\xB7\x5D\xDA\x59\x68\x0F\x44\x22\x81\xDE\x65\x84\x75\x27\xAE\x9D\xF5\xCE\x4D\x4C\xAE\xAA\xEF\xF4\x9A\x7C\x24\x13\xDC\x06\xD0\x51\x86\x96\x0F\x13\x11\xFD\xAC\x3A\xA7\x6E\xF6\x85\xDA\xBD\x50\x99\x3A\x3F\xDC\x1D\x29\x35\xA3\x50\xE1\x09\x2B\x7B\x07\x2C\xEC\xAC\xA3\x55\x5F\xC5\xD1\x1C\x76\xAF\x8B\x2C\xC2\x4D\x09\xC7\x3B\xB2\x49\x95\x5C\xAF\x1B\x10\x25\xF8\x0B\x6B\xA4\xD3\x2B\x50\x69\xEF\x0F\x36\xC1\x64\xF3\x47\x9F\x56\x27\x67\xBF\x5D\x7A\xDA\x26\x39\x60\x66\x61\xDD\x7A\x18\x87\x37\x03\x9E\xDA\x63\x5F\xB8\xD3\x2A\x80\x5C\xFB\xED\xEF\x93\x45\x96\x45\x32\xF1\x6F\xD0\xA8\xB3\x5D\xF3\x07\xA5\x7F\x18\xA4\x37\x7D\x8F\xFD\x1A\xD2\xC9\x4D\xF8\xFE\xF0\x53\x8D\x90\xFD\xEC\x94\x11\x15\x2F\xBE\x92\xE4\x05\xC6\xF4\xEE\xAB\x62\xC4\xB3\xBC\x6B\xC4\x62\x45\x9D\x85\xB0\xCE\x6C\xE0\xD4\xFF\xBB\xA5\x64\x89\x37\xCE\x39\xD3\xD1\x13\x2D\x0E\x5E\x0C\xEA\x6F\x18\x89\x03\xFA\xA3\xF2\x76\x49\x4D";


 //check 
  count=1;
  for(int i=0;i<lenght;i++){
    if(Ciphertext[i]!=Ciphertext_ref_2[i]){
	count=0;
      }
  }

  if(count==0){
    printf("FAIL (Encrypt reference 2)\n");
  }
  else{
    printf("PASS (Encrypt reference 2)\n");
    }

  // check decryption
  count=1;
  for(int i=0;i<lenght;i++){
    if(Ciphertext2[i]!=Plaintext[i]){
	count=0;
      }
  }

  if(count==0){
    printf("FAIL (Decrypt reference 2)\n");
  }
  else{
    printf("PASS (Decrypt reference 2)\n");
  }

 
  free(Key);
  free(Plaintext);
  free(Ciphertext);
  free(Ciphertext2);

  /*******************  TEST 3 ADDED BY TUOMAS TO DEMONSTRATE DECRYPTION BY RUNNING ENCRYPT TWICE SINCE XORRING WITH THE SAME BYTESTEAM WILL ALSO DECRYPT AN ENCRYPTED TEXT ************/
  Key=malloc(16*sizeof(unsigned char)); 
  memset(Key, 0 , 16*sizeof(unsigned char));

  lenght=250;
  Plaintext=malloc(lenght*sizeof(unsigned char)); 
  memset(Plaintext, 0x77 , lenght*sizeof(unsigned char));
  // Encrypting twice will result in the original plaintext
  Ciphertext=encrypt(Key, Plaintext, lenght);
  Ciphertext2=encrypt(Key, Ciphertext, lenght);
  // Reference will be the same as the original plaintext


 //check 
  count=1;
  for(int i=0;i<lenght;i++){
    if(Ciphertext2[i]!=Plaintext[i]){
	count=0;
      }
  }

  if(count==0){
    printf("FAIL (Self-added encrypt-then-decrypt test)\n");
  }
  else{
    printf("PASS (Self-added encrypt-then-decrypt test)\n");
    }
 
  free(Key);
  free(Plaintext);
  free(Ciphertext);
  free(Ciphertext2);
}
