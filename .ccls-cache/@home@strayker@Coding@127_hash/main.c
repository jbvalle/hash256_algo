#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define SHA256_DIGEST_LENGTH 32
#define SEED_LENGTH 5
#define MAX_CHAPTERS 51
#define MAX_PAGES 3
#define MAX_WORD_RANGE 5
int main() {

    char input_string[100];
    int chapter = 0;
    int page = 0;
    int direction = 0;
    int seed[SEED_LENGTH];

    for(int i = 0; i < SEED_LENGTH; i++) seed[i] = 0;

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
            chapter = (tmp % MAX_CHAPTERS) + 1;
        }

        //determine page
        if(i == 1){
            page = (tmp % MAX_PAGES) + 1;
        }

        //determine direction
        if(i == 2){
            direction = (tmp % 2);
        }

        //determine seed
        if(i > 2){

            seed[i - 3] = (tmp % MAX_WORD_RANGE) + 1;
        }

        printf(" -> tmp: %d", tmp);
        printf("\n");
    }

    printf("Chapter : %d\nPage : %d\nDirection : %d", chapter, page, direction);

    for(int i = 0; i < SEED_LENGTH; i++){
        printf("\n%d : [%d]", i , seed[i]);
    }

    return 0;
}

