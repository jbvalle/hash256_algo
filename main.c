#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define SHA256_DIGEST_LENGTH 32

int main() {

    char input_string[100];
    int chapter = 0;
    int page = 0;
    int seed[6];

    for(int i = 0; i < 6; i++) seed[i] = 0;

    printf("Enter a string to encrypt and decrypt: ");
    fgets(input_string, 100, stdin);
    // Remove newline character from input string
    input_string[strcspn(input_string, "\n")] = 0;

    // Calculate SHA-256 hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(input_string, strlen(input_string), hash);


    printf("Blocked Hashed:\n");
    for(int i = 0; i < 8; i++){

        int tmp = 0;

        for(int j = 0; j < 4; j++){

            printf("[%02x]", hash[i * 4 + j]);

            tmp += hash[i * 4 + j];

        }


        //determine chapter
        if(i == 0){
            chapter = (tmp % 51) + 1;
        }

        //determine page
        if(i == 1){
            page = (tmp % 3) + 1;
        }

        //determine seed
        if(i > 1){

            seed[i - 2] = (tmp % 10) + 1;
        }

        printf(" -> tmp: %d", tmp);
        printf("\n");
    }

    printf("Chapter : %d\nPage : %d", chapter, page);;

    for(int i = 0; i < 6; i++){
        printf("\n%d : [%d]", i , seed[i]);
    }

    return 0;
}

