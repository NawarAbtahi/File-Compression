#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rle.h"

void compressFile(FILE *fp, char *encodedFilePath, char* filePath);
void decompressFile(char *encodedFilePath, char *decodedFilePath);

int main(){
  char filePath[150];
  char encodedFilePath[] = "files/compressed.rle";
  char decodedFilePath[] = "files/decompressed.txt";
  char EdecodedFilePath[150];
  FILE *fp;

  while(1){
    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif

    printf("~File Compression-Decompression~\n\n");
    printf("1. File Compression\n");
    printf("2. File Decompression\n");
    printf("3. Exit\n\n");

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice); 

    switch (choice) {
      case 1:
        printf("Enter file path: ");
        scanf("%s", filePath);

        fp = fopen(filePath, "rb");
        if(fp == NULL){
          printf("Unable to open file. No such file\n");
          printf("Press any key to continue...");
          getchar();
          getchar();
          break;
        }

        compressFile(fp, encodedFilePath, filePath);
        fclose(fp);
        getchar();  // clear newline
        getchar();
        break;

      case 2:
        printf("Enter file path: ");
        scanf("%s", EdecodedFilePath);
        decompressFile(EdecodedFilePath, decodedFilePath);
        getchar();  // clear newline
        getchar();
        break;
      case 3:
        exit(0);
      default:
        printf("Wrong Input!. Press any key to continue...");
        getchar();  // clear newline
        getchar();
    }
  }
  return 0;
}

void compressFile(FILE *fp, char *encodedFilePath, char* filePath){
  char* encode = RLEncodeFile(fp);

  int encode_len = strlen(encode);

  FILE *encodedFile = fopen(encodedFilePath, "wb");
  fprintf(encodedFile, "%s",encode);
  fclose(encodedFile);

  if(encode_len != 0 && encodedFile != NULL){
    printf("Compression of the file [%s] successful.\n", filePath);
    printf("Compressed file saved as [%s].\n", encodedFilePath);
    printf("Press any key to continue...");
  }
  else{
    printf("Error: File compression unsuccessful. File either has no data or unidentified error.\n");
    printf("Press any key to continue...");
  }
}

void decompressFile(char *encodedFilePath, char *decodedFilePath){
  FILE *encodedFile = fopen(encodedFilePath, "rb");

  if(encodedFile == NULL){
    printf("Unable to open file. No such file\n");
    printf("Press any key to continue...");
  }
  else{
    char *decode = RLDecodeFile(encodedFile);
    int decode_len = strlen(decode);
    fclose(encodedFile);

    FILE *decodedFile = fopen(decodedFilePath, "wb");
    fprintf(decodedFile, "%s", decode);
    fclose(decodedFile);

    if(decode_len != 0 && decodedFile != NULL){
      printf("Decompression of the file [%s] successful.\n", encodedFilePath);
      printf("Decompressed file saved as [%s].\n",decodedFilePath);
      printf("Press any key to continue...");
    }
    else{
      printf("Error: File decompression unsuccessful.\n");
      printf("Press any key to continue...");
    }
  }
}
