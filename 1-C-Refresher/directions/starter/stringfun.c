#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
//add additional prototypes here
int reverse_buff(char *, int);
int write_buff(char *, int);


int setup_buff(char *buff, char *user_str, int len){
    int word_count = 0; // buff counter
    int i = 0;  // user_str counter
    int addSpace = 0; // bool for adding space

    while (*(user_str + i) != '\0') {
        if (word_count >= len) {
            printf("The user supplied string is too large\n");
            exit(-1);
        }

        if (*(user_str + i) == 32 || *(user_str + i) == 9 || *(user_str + i) == 10) {
        
            if (!addSpace) {
                ++i;
            } else if (addSpace) {
                // printf("space added\n");
                addSpace = 0;
                *(buff + word_count) = ' ';
                // printf("%c\n", *(buff + word_count));

                ++word_count; ++i;
            }
  
        } else {
            *(buff + word_count) = *(user_str + i);
            // printf("%c\n", *(buff + word_count));
            addSpace = 1;

            ++i; ++word_count;
        }
    }
    // printf("Word Count: %d\n", word_count);

    // Last added buffer is space
    if (*(buff + (word_count - 1)) == ' ') {
        --word_count;
    }
    int new_word_count = word_count;

    // printf("Word Count: %d\n", word_count);

    while (new_word_count !=  BUFFER_SZ) {
        *(buff + new_word_count) = '.';
        ++new_word_count;
    } 

    // for (size_t j = 0; j < word_count; j++) {
    //      printf("%c", *(buff + j));
    // }
    // printf("\n");
    
      
    //TODO: #4:  Implement the setup buff as per the directions
    return word_count; //for now just so the code compiles. 
}

void print_buff(char *buff, int len){
    printf("Buffer:  ");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar('\n');
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){
    int i = 0;
    int counter = 0;
    while (i < len) {
        if (*(buff + i) == ' ') {++counter;}
        ++i;    
    }
    ++counter;

    return counter;
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS
int reverse_buff(char *buff, int str_buff_len) {
    size_t first = 0;
    size_t last = str_buff_len - 1;
    char tmp;

    while (first < last) {
        tmp = *(buff + first);
        *(buff + first) = *(buff + last);
        *(buff + last) = tmp; 
        ++first; --last;
    }

    return first;
}

int write_buff(char *buff, int len) {
    int tmpCounter = 0;
    int nWords = 0;

    printf("Word Print\n----------\n");
    // printf("Len : %d\n", len);

    for (int i = 0; i < len + 1; i++) {

        if ((*(buff + i) == ' ' || *(buff+i) == '.') && (tmpCounter != 0)) {
            // printf("%d\n", i);
            ++nWords; printf("%d. ", nWords);

            for (int j = i - tmpCounter; j < i; j++) {
                putchar(*(buff+j));
            }
            printf("(%d)\n", tmpCounter);

            tmpCounter = 0;

        } else {
            ++tmpCounter;
        }
    }

    return nWords;
}

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    //      The first if condition (argc < 2) will always be true if
    //      argv[1] does not exist. As C checks the condition left to
    //      right in this case, the program never reaches the second
    //      condition.
    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    //      This if statement checks the user input whether they include additional
    //      string after inputting "-[]"
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3
    buff = (char*) malloc(BUFFER_SZ);
    if (!buff) {
        exit(99);
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  //you need to implement
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options

        case 'r':
            rc = reverse_buff(buff, user_str_len);
            if (rc < 0){
                printf("Error reversing buffer, rc = %d", rc);
                exit(2);
            }
            break;

        case 'w':
            rc = write_buff(buff, user_str_len);
            if (rc < 0){
                printf("Error writing buffer, rc = %d", rc);
                exit(2);
            }
            break;

        case 'x':

            break;

        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff,BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          PLACE YOUR ANSWER HERE