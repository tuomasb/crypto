/* this file gets replaced with our own driver when we grade your submission.
 * So do what you want here but realize it won't persist when we grade it.
 */

#include <stdio.h>
#include <stdlib.h>
#include "KeccakF1600.h"
#include "Keccak_r1024.h"
#include <string.h>



void check(unsigned char* print_message, unsigned char *Z,unsigned char *Z_ref){
  int count=1;
  for(int i=0;i<128;i++){
    if(Z[i]!=Z_ref[i]){
 	count=0;
      }
  }
  if(count==0){
    printf(" %s FAIL\n", print_message);
  }
  else{
    printf(" %s PASS\n", print_message);
    }
} 


int main(){
  /*******************Second message of  *****************************************/
  /***  https://github.com/gvanas/KeccakCodePackage/blob/master/TestVectors/KeccakSpongeIntermediateValues_r1024c576.txt  ***/
  /*** The intermediate values on the link can be used to debug the different steps of the program ***/

 unsigned char *mess =
        "\x83\xAF\x34\x27\x9C\xCB\x54\x30\xFE\xBE\xC0\x7A\x81\x95\x0D\x30"
        "\xF4\xB6\x6F\x48\x48\x26\xAF\xEE\x74\x56\xF0\x07\x1A\x51\xE1\xBB"
        "\xC5\x55\x70\xB5\xCC\x7E\xC6\xF9\x30\x9C\x17\xBF\x5B\xEF\xDD\x7C"
        "\x6B\xA6\xE9\x68\xCF\x21\x8A\x2B\x34\xBD\x5C\xF9\x27\xAB\x84\x6E"
        "\x38\xA4\x0B\xBD\x81\x75\x9E\x9E\x33\x38\x10\x16\xA7\x55\xF6\x99"
        "\xDF\x35\xD6\x60\x00\x7B\x5E\xAD\xF2\x92\xFE\xEF\xB7\x35\x20\x7E"
        "\xBF\x70\xB5\xBD\x17\x83\x4F\x7B\xFA\x0E\x16\xCB\x21\x9A\xD4\xAF"
        "\x52\x4A\xB1\xEA\x37\x33\x4A\xA6\x64\x35\xE5\xD3\x97\xFC\x0A\x06"
        "\x5C\x41\x1E\xBB\xCE\x32\xC2\x40\xB9\x04\x76\xD3\x07\xCE\x80\x2E"
        "\xC8\x2C\x1C\x49\xBC\x1B\xEC\x48\xC0\x67\x5E\xC2\xA6\xC6\xF3\xED"
        "\x3E\x5B\x74\x1D\x13\x43\x70\x95\x70\x7C\x56\x5E\x10\xD8\xA2\x0B"
        "\x8C\x20\x46\x8F\xF9\x51\x4F\xCF\x31\xB4\x24\x9C\xD8\x2D\xCE\xE5"
        "\x8C\x0A\x2A\xF5\x38\xB2\x91\xA8\x7E\x33\x90\xD7\x37\x19\x1A\x07"
        "\x48\x4A\x5D\x3F\x3F\xB8\xC8\xF1\x5C\xE0\x56\xE5\xE5\xF8\xFE\xBE"
        "\x5E\x1F\xB5\x9D\x67\x40\x98\x0A\xA0\x6C\xA8\xA0\xC2\x0F\x57\x12"
        "\xB4\xCD\xE5\xD0\x32\xE9\x2A\xB8\x9F\x0A\xE1";

 unsigned char *Z_ref=
   "\xB4\xF0\x1B\xAB\x85\x19\x45\x9E\x87\xC6\x80\xB5\x63\xC6\x45\xF3"
   "\x05\x2D\x63\xA2\x55\x5D\x64\x9E\xB1\xD6\xAD\xEA\x45\xF4\x23\x1B"
   "\xB2\x9D\x16\x3E\x0C\x83\x02\xE5\xAC\x33\x43\x9C\xE8\x1F\x5C\xB7"
   "\x6E\x81\x61\x7C\x31\xF0\xEF\x5F\x0F\x03\x54\x94\x29\x7B\x6B\x9B"
   "\x6C\xD1\x9D\x75\xE2\x63\x3A\x8F\x8E\xC3\x3B\x3E\x2D\x71\x06\x35"
   "\xEF\xAC\xC0\x10\x96\x07\x1A\xF5\xA0\x63\xA6\xF5\xE9\x09\x87\xA8"
   "\x2F\xD3\xB1\xE6\xE0\x64\x8F\xE2\xCD\x43\xF6\x55\xC1\xC1\xB9\x48"
   "\x1D\xDB\xDD\xBF\x48\xD5\xA6\x1E\x08\x5B\xF3\x8E\xCD\xFD\x80\x65";


  
 unsigned char *Z=Hash(mess,251);
 check("message_0",Z,Z_ref);
 free(Z);
 
 /**************** Test vector of size 1024 bits=128 bytes  ****************************/
 /*** To check if the padding is correct in that case  ***/

  unsigned char *mess_1 = calloc(128,sizeof(unsigned char*));
  unsigned char *Z_ref_1=
    "\xC7\x74\xEE\xE8\x9C\xCC\xEB\x72\xDA\xF7\x65\xA0\xF6\x96\xF4\xE6\x12\x99\x4D\x29\x5E\xEC\xA7\x80\x74\xD0\x39\xAB\xE1\x33\xA4\xD6\x70\xCB\x06\x2E\xF9\x3F\xCF\x48\x02\x07\xB9\x39\x00\xAC\x1E\x28\x0F\xC9\xF1\x31\xD8\xBC\x13\x35\xB0\xBB\x33\x05\x14\x17\x75\x17\x86\x00\x79\x1D\x7D\xA8\xB3\x3E\xF1\x2E\x1B\x49\xC5\x05\x3D\x3E\x47\x1A\xE5\x6B\x75\x0F\xB7\x5C\x55\x91\xBD\x8F\xCF\xA0\xA2\x46\xBB\x34\x67\xF4\x77\x8F\x92\x4E\xA5\xFC\xF5\xBD\xD0\x6D\x59\xA5\x46\xDF\x55\x82\xF6\x23\x40\xEF\x58\x3C\x3C\xB5\x9F\xC4\xDB\x71";

 unsigned char *Z_1=Hash(mess_1,128);

 check("message_1",Z_1,Z_ref_1);
 free(mess_1);
 free(Z_1);

 /****************   Test vector of size 1852 bytes    *************************/
 /***    Just another random vector, Done to check message of longer lenght  ***/


  unsigned char *mess_2 = calloc(1852,sizeof(unsigned char*));
  unsigned char *Z_ref_2="\x19\xD3\x67\x10\xE7\x25\x94\x0C\xAA\x52\xD7\x49\x9E\x97\xE2\x5E\xA8\x19\xB2\xA3\x4F\x5F\x31\x75\x05\x27\xFF\x43\x2F\x5C\xE0\x6B\xCA\xB5\x51\xB4\xF7\x50\x7E\x4E\x00\xFA\xF7\x2E\xA1\x7D\xBD\xE1\x21\x65\x68\xEC\x5A\xA2\xB0\xFC\x01\xD2\xF9\x1F\x0A\x7E\x76\x0E\x0C\x95\x6C\xF8\x49\xCE\x07\x95\x13\x2D\x4E\x0F\xD6\x5D\x66\x65\x99\x8B\xF5\x1F\xDE\xBD\x51\xF7\xD5\x3F\xCF\x9F\x61\x77\x6F\xB6\xF2\xFD\xE6\xEE\xC1\x72\xB3\x0F\xA8\xBF\x51\x11\xA5\x18\xC9\x34\x05\x9A\x8C\x7F\xAD\xED\xD6\xD1\xD8\x9E\x06\x3F\x44\x71\x9B\x9C";
  
 unsigned char *Z_2=Hash(mess_2,1852);
 check("message_2",Z_2,Z_ref_2);

  free(mess_2);
  free(Z_2);

 
/**************** Test vector of size 385 bytes   ****************************/
/*** If the program pass the first two test vector, It should pass this one ***/



  unsigned char *mess_3 = calloc(385,sizeof(unsigned char*));
  unsigned char *Z_ref_3="\xDE\xA4\x69\xF5\x76\xD8\x02\xC1\x13\x92\xF1\x0F\xFC\xBA\x8A\x3A\x26\xB8\x62\xF7\xD2\x40\xDF\x5B\x0E\x5F\xC3\x5F\xA9\xF5\xC1\xBC\xBA\xDB\xC1\x3E\x94\x94\x9C\xB5\x84\xBC\x93\x36\x69\x8D\xB9\x0C\x66\xC2\xD3\x1B\xE1\xE6\x0D\x57\x06\x30\x47\xF6\x6B\x0D\x9A\x26\x0A\xF6\x94\x7E\xFF\x39\x04\x48\x3D\x1E\xAE\x56\x59\x48\x95\xD0\xF7\x67\x3F\x78\x1D\x76\x86\x02\x34\x41\x11\xBA\xD2\xF3\x29\x98\x1B\x3F\xBB\x27\x8B\x30\x9F\x36\xD9\xDE\xF6\x2C\xFC\xF6\xB1\xCD\xDA\xB3\xA9\xF3\x96\x2A\x24\x0A\xF5\x04\x77\x09\x3D\xAA\x45\x00";
  
 unsigned char *Z_3=Hash(mess_3,385);
 

 check("message_3",Z_3,Z_ref_3);

  free(mess_3);
  free(Z_3);
 
 
}
