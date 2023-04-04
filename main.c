#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define SHA256_DIGEST_LENGTH 32
#define SEED_LENGTH 3
#define MAX_CHAPTERS 51
#define MAX_PAGES 3
#define MAX_WORD_RANGE 12
#define MAX_LINE_RANGE 12
#define SEED_STARTING_BLOCK 4
int main() {

    char input_string[100];
    int chapter = 0;
    int page = 0;
    int direction_page = 0;
    int line = 0;
    int direction_line = 0;

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

        //determine direction_page
        if(i == 2){
            direction_page = (tmp % 2);
        }

        //determine line
        if(i == 3){
            line = (tmp % MAX_LINE_RANGE) + 1;
        }

        //determine line direction
        if(i == 4){
            direction_line = (tmp % 2);
        }

        //determine seed
        if(i > SEED_STARTING_BLOCK){

            seed[i - (SEED_STARTING_BLOCK + 1)] = (tmp % MAX_WORD_RANGE) + 1;
        }

        printf(" -> tmp: %d", tmp);
        printf("\n");
    }

    printf("Chapter : %d\nPage : %d\nPage Direction : %d\nLine : %d\nLine Direction : %d\n", chapter, page, direction_page, line, direction_line);

    for(int i = 0; i < SEED_LENGTH; i++){
        printf("\n%d : [%d]", i , seed[i]);
    }

    return 0;
}

