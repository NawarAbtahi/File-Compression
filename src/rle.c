#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rle.h"

#define MAX_COUNTED_CHAR 1000


char* RLEncodeFile(FILE *fp){
  size_t bufferSize = 100;
  char* StoreTxt = malloc(bufferSize);
  size_t readBytes = fread(StoreTxt, 1, bufferSize - 1, fp);
  StoreTxt[readBytes - 1] = '\0';
  
  int countChar;
  int txt_len = strlen(StoreTxt);
  char countArray[MAX_COUNTED_CHAR];
  
  char *encodedTxt = (char* )malloc(sizeof(char) * (txt_len * 2 + 1));

  int i, countArrayIndex, encodedTxtIndex = 0;

  for(i = 0; i < txt_len; i++){
    encodedTxt[encodedTxtIndex++] = StoreTxt[i];

    countChar = 1;

    while(i + 1 < txt_len && StoreTxt[i] == StoreTxt[i + 1]){
      countChar++;
      i++;
    }
    
    if(countChar != 1){

      sprintf(countArray, "%d", countChar);

      for(countArrayIndex = 0; countArray[countArrayIndex]; countArrayIndex++, encodedTxtIndex++){
        encodedTxt[encodedTxtIndex] = countArray[countArrayIndex];
      }
    }
  }

  encodedTxt[encodedTxtIndex] = '\0';

  return encodedTxt;
}


//decoding the text
char* RLDecodeFile(FILE *fp){
  size_t bufferSize = 1000;
  char* StoreTxt = malloc(bufferSize);
  size_t readBytes = fread(StoreTxt, 1, bufferSize - 1, fp);

  StoreTxt[readBytes] = '\0';

  int txt_len = strlen(StoreTxt);
  char* decodedTxt = (char*)malloc(sizeof(char) * (txt_len * 3 + 1) );

  //make a2b2 to aabb
  
  int decodedTxtIndex = 0;

  for(int i = 0; i < txt_len;){
    if(isalpha(StoreTxt[i])){
      char storeChar = StoreTxt[i++];

      int getNum = 0;
      while(i < txt_len && isdigit(StoreTxt[i])){
        getNum = getNum * 10 + (StoreTxt[i] - '0');
        i++;
      }

      if(getNum == 0){
        getNum = 1;
      }

      for(int getNumIndex = 0; getNumIndex < getNum; getNumIndex++){
        decodedTxt[decodedTxtIndex++] = storeChar;
      }
    }  
  }

  decodedTxt[decodedTxtIndex] = '\0';

  return decodedTxt;
}
