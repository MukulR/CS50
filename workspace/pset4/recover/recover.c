#include <stdio.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;


int main(int argc, string argv[]){
    if(argc != 2){
        fprintf(stderr, "Expected image to extract JPEGs\n");
        return 1;
    }

    FILE *outptr = NULL;
    FILE *inptr = fopen(argv[1], "rb");
    if (inptr == NULL) {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    BYTE byteArray[512];
    int bytesRead = fread(byteArray, 1, 512, inptr);
    int filecount = 0;
    char filename[8];
    int i = 0;
    while(bytesRead > 0){
        while(i < bytesRead){
            if(byteArray[i] != 0xff && outptr == NULL){
                i++;
                continue;
            }
            if(i + 3 < bytesRead && byteArray[i] == 0xff && byteArray[i + 1] == 0xd8 && byteArray[i + 2] == 0xff && (byteArray[i + 3] & 0xf0) == 0xe0){
                if (outptr != NULL) {
                    fclose(outptr);
                    filecount++;
                }
                sprintf(filename, "%03i.jpg", filecount);
                outptr = fopen(filename, "wb");

                fwrite(&byteArray[i], 1, 1, outptr);
                fwrite(&byteArray[i + 1], 1, 1, outptr);
                fwrite(&byteArray[i + 2], 1, 1, outptr);
                fwrite(&byteArray[i + 3], 1, 1, outptr);
                i = i + 4;
            } else {
                fwrite(&byteArray[i], 1, 1, outptr);
                i++;
            }
        }
        i = 0;
        bytesRead = fread(byteArray, 1, 512, inptr);
    }
    return 0;
}