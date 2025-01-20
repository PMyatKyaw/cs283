#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SZ 50

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int);
//add additional prototypes here

// Reverse the buffer
int reverse_buff(char *, int);
// Count each word in the buffer
int write_buff(char *, int);
// Find a word in the buffer
int find_str_buff (char*, int, int, char*);
// Find and replace a word in the buffer
int replace_buff(char*, int, int, char*, char*);

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);
}

int setup_buff(char *buff, char *user_str, int len){
    int word_count = 0; // buff counter
    int i = 0;  // user_str counter
    int addSpace = 0; // bool for adding space

    while (*(user_str + i) != '\0') {
        if (word_count >= len) {
            printf("The user supplied string is too large\n");
            exit(-1);
        }

        // If character is ' ' or '\t' or '\n'
        if (*(user_str + i) == 32 || *(user_str + i) == 9 || *(user_str + i) == 10) {
            if (!addSpace) {
                ++i;

            } else if (addSpace) {
                addSpace = 0;
                *(buff + word_count) = ' ';
                ++word_count; ++i;
            }
  
        } else {
            *(buff + word_count) = *(user_str + i);
            addSpace = 1;
            ++word_count, ++i;
        }
    }

    // Last added buffer is space
    if (*(buff + (word_count - 1)) == ' ') {
        --word_count;
    }
    int new_word_count = word_count;
    
    // Add '.' until end of buffer
    while (new_word_count !=  BUFFER_SZ) {
        *(buff + new_word_count) = '.';
        ++new_word_count;
    } 

    return word_count; //for now just so the code compiles. 
}

void print_buff(char *buff, int len){
    printf("Buffer:  [");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    putchar(']');
    putchar('\n');
}

int count_words(char *buff, int len){
    int i = 0;
    int counter = 0; // Word Counter
    while (i < len) {
        if (*(buff + i) == ' ') {++counter;}
        ++i;    
    }
    ++counter;

    return counter;
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS
int reverse_buff(char *buff, int str_buff_len) {
    size_t first = 0;                   // First character in buffer
    size_t last = str_buff_len - 1;     // Last character in buffer
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

    for (int i = 0; i < len + 1; i++) {
        if ((*(buff + i) == ' ' || *(buff+i) == '.') && (tmpCounter != 0)) {
            ++nWords; 
            printf("%d. ", nWords);

            for (int j = i - tmpCounter; j < i; j++) {
                putchar(*(buff+j));
            }
            printf("(%d)\n", tmpCounter);

            tmpCounter = 0;

        } else {
            ++tmpCounter;
        }
    }

    printf("\nNumber of words returned: %d\n", nWords);
    return nWords;
}

int find_str_buff (char* buff, int buff_len, int user_str_len, char* find_str) {
    for (int i = 0; i < user_str_len; i++){

        // If first character of the string is the same
        if (*(buff + i) == *find_str) {
            int j = 0;

            // Check the remaining character to see whether they are the same
            while (*(find_str + j) != '\0') {

                // Overflow error in buffer while searching for str
                if( i + j >= buff_len) {
                    return 0;
                }

                if (*(buff + i + j) != *(find_str + j)) {
                    break;
                }
                ++j;
            }

            if (*(find_str+j) == '\0') {
                return i;
            }
        } 
    }

    return 0;
}

int replace_buff(char* buff, int buff_len, int user_str_len, char* find_str, char* replace_str) {

    int findStartIndex = 0;     // The first character of the word to be replaced, if found
    int find_len = 0;           // The to be replaced character count
    int replace_len = 0;        // The replacing character count
    int len_diff = 0;           // The count difference of above two

    findStartIndex = find_str_buff(buff, buff_len, user_str_len, find_str);

    while (*(find_str + find_len) != '\0') { ++find_len; }
    while (*(replace_str + replace_len) != '\0') { ++replace_len; }
    len_diff = replace_len - find_len;
    
    if (findStartIndex) {           // if word is found
        if(len_diff > 0) {          // len_diff is positive meaning the replacement word is bigger
            if (user_str_len + len_diff > buff_len) {
                return -1;
            }

            for (int i = user_str_len - 1; i >= (findStartIndex + find_len); i--) {
                *(buff + i+ len_diff) = *(buff + i);
            }
            memcpy(buff + findStartIndex, replace_str, replace_len);
            return findStartIndex;

        } else if (len_diff < 0) {  // len_diff is negative meaning the replacement word is smaller
            memcpy(buff + findStartIndex, replace_str, replace_len);

            for (int i = findStartIndex + replace_len; i < buff_len + len_diff; i++) {
                *(buff + i) = *(buff + i - len_diff);
            }

            // Fill Up the reminding buffer at the end with '.'
            for (int i = buff_len + len_diff; i < buff_len; i++) {
                *(buff + i) = '.';
            }
            return findStartIndex;

        } else {                    // len_diff is zero meaning the replacement word has same length
                                    // with word that is to be replaced
            memcpy(buff + findStartIndex, replace_str, replace_len);
            return findStartIndex;
        }

    } else {                        // Word not found in buffer
        return -1;
    }
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
    //      This if statement checks the user include additional
    //      string after inputting "-[]". That string is necessary for
    //      the code to do the required processing of "-[]"
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    // Allocate buffer
    buff = (char*) malloc(BUFFER_SZ);
    if (!buff) {
        exit(99);
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);   // Process buffer to required format
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ);
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

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
            if (argc < 5){
                printf("usage: -x \"string\" \"string1\" \"string2\" \n");
                exit(1);
            }

            rc = replace_buff(buff, BUFFER_SZ, user_str_len, argv[3], argv[4]);
            if (rc < 0){
                printf("Not Implemented!\n");
                exit(2);
            }
            break;

        default:
            usage(argv[0]);
            exit(1);
    }

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
//          I think it is a good practice to pass in that preprocesser derivative because
//          while the programmer writes a lot of code, it is difficult to keep track of all
//          the constants if they were to blindly put different constants in a function.
//          Putting that constant as a parameter make it more readable. 
//          Another reason would be the programmer using the function with different sizes
//          rather than the given preprocesser derivative. If the programmer were to straight
//          up use the constant, that constant would be tied to the function
//          and that is not a good programming practice. There might be cases where the
//          programmer might want to use different values.