#ifndef __DSHLIB_H__
#define __DSHLIB_H__

// Constants for command structure sizes
#define EXE_MAX 64
#define ARG_MAX 256
#define CMD_MAX 8
// Longest command that can be read from the shell
#define SH_CMD_MAX EXE_MAX + ARG_MAX

typedef struct command
{
    char exe[EXE_MAX];
    char args[ARG_MAX];
} command_t;

typedef struct command_list
{
    int num;
    command_t commands[CMD_MAX];
} command_list_t;

// Special character #defines
#define SPACE_CHAR ' '
#define SPACE_STRING " "
#define PIPE_CHAR '|'
#define PIPE_STRING "|"

#define SH_PROMPT "dsh> "
#define EXIT_CMD "exit"
#define EXIT_CMD_BYTES 4
#define DRAGON_CMD "dragon"
#define DRAGON_CMD_BYTES 6

// Standard Return Codes
#define OK 0
#define WARN_NO_CMDS -1
#define ERR_TOO_MANY_COMMANDS -2
#define ERR_CMD_OR_ARGS_TOO_BIG -3
#define ERR_ALLOCATION_FAILED -4

// starter code
#define M_NOT_IMPL "The requested operation is not implemented yet!\n"
#define EXIT_NOT_IMPL 3
#define NOT_IMPLEMENTED_YET 0

// prototypes
int build_cmd_list(char *cmd_line, command_list_t *clist);
void print_cmd_list (command_list_t *clist);
int encode_dragon_ascii (char *ascii_art, uint8_t *x);
void decode_dragon_ascii (uint8_t *x, size_t length);

// output constants
#define CMD_OK_HEADER "PARSED COMMAND LINE - TOTAL COMMANDS %d\n"
#define CMD_WARN_NO_CMD "warning: no commands provided\n"
#define CMD_ERR_PIPE_LIMIT "error: piping limited to %d commands\n"
#define MALLOC_FAILURE "error: memory allocation failed\n"

// drexel dragon
#define DRAGON_ASCII_ART \
    "                                                                        @%%%%                       \n"\
    "                                                                     %%%%%%                         \n"\
    "                                                                    %%%%%%                          \n"\
    "                                                                 % %%%%%%%           @              \n"\
    "                                                                %%%%%%%%%%        %%%%%%%           \n"\
    "                                       %%%%%%%  %%%%@         %%%%%%%%%%%%@    %%%%%%  @%%%%        \n"\
    "                                  %%%%%%%%%%%%%%%%%%%%%%      %%%%%%%%%%%%%%%%%%%%%%%%%%%%          \n"\
    "                                %%%%%%%%%%%%%%%%%%%%%%%%%%   %%%%%%%%%%%% %%%%%%%%%%%%%%%           \n"\
    "                               %%%%%%%%%%%%%%%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%     %%%            \n"\
    "                             %%%%%%%%%%%%%%%%%%%%%%%%%%%%@ @%%%%%%%%%%%%%%%%%%        %%            \n"\
    "                            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%                \n"\
    "                            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%              \n"\
    "                            %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@%%%%%%@              \n"\
    "      %%%%%%%%@           %%%%%%%%%%%%%%%%        %%%%%%%%%%%%%%%%%%%%%%%%%%      %%                \n"\
    "    %%%%%%%%%%%%%         %%@%%%%%%%%%%%%           %%%%%%%%%%% %%%%%%%%%%%%      @%                \n"\
    "  %%%%%%%%%%   %%%        %%%%%%%%%%%%%%            %%%%%%%%%%%%%%%%%%%%%%%%                        \n"\
    " %%%%%%%%%       %         %%%%%%%%%%%%%             %%%%%%%%%%%%@%%%%%%%%%%%                       \n"\
    "%%%%%%%%%@                % %%%%%%%%%%%%%            @%%%%%%%%%%%%%%%%%%%%%%%%%                     \n"\
    "%%%%%%%%@                 %%@%%%%%%%%%%%%            @%%%%%%%%%%%%%%%%%%%%%%%%%%%%                  \n"\
    "%%%%%%%@                   %%%%%%%%%%%%%%%           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%              \n"\
    "%%%%%%%%%%                  %%%%%%%%%%%%%%%          %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%      %%%%  \n"\
    "%%%%%%%%%@                   @%%%%%%%%%%%%%%         %%%%%%%%%%%%@ %%%% %%%%%%%%%%%%%%%%%   %%%%%%%%\n"\
    "%%%%%%%%%%                  %%%%%%%%%%%%%%%%%        %%%%%%%%%%%%%      %%%%%%%%%%%%%%%%%% %%%%%%%%%\n"\
    "%%%%%%%%%@%%@                %%%%%%%%%%%%%%%%@       %%%%%%%%%%%%%%     %%%%%%%%%%%%%%%%%%%%%%%%  %%\n"\
    " %%%%%%%%%%                  % %%%%%%%%%%%%%%@        %%%%%%%%%%%%%%   %%%%%%%%%%%%%%%%%%%%%%%%%% %%\n"\
    "  %%%%%%%%%%%%  @           %%%%%%%%%%%%%%%%%%        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  %%% \n"\
    "   %%%%%%%%%%%%% %%  %  %@ %%%%%%%%%%%%%%%%%%          %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    %%% \n"\
    "    %%%%%%%%%%%%%%%%%% %%%%%%%%%%%%%%%%%%%%%%           @%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    %%%%%%% \n"\
    "     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%              %%%%%%%%%%%%%%%%%%%%%%%%%%%%        %%%   \n"\
    "      @%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                  %%%%%%%%%%%%%%%%%%%%%%%%%               \n"\
    "        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                      %%%%%%%%%%%%%%%%%%%  %%%%%%%          \n"\
    "           %%%%%%%%%%%%%%%%%%%%%%%%%%                           %%%%%%%%%%%%%%%  @%%%%%%%%%         \n"\
    "              %%%%%%%%%%%%%%%%%%%%           @%@%                  @%%%%%%%%%%%%%%%%%%   %%%        \n"\
    "                  %%%%%%%%%%%%%%%        %%%%%%%%%%                    %%%%%%%%%%%%%%%    %         \n"\
    "                %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                      %%%%%%%%%%%%%%            \n"\
    "                %%%%%%%%%%%%%%%%%%%%%%%%%%  %%%% %%%                      %%%%%%%%%%  %%%@          \n"\
    "                     %%%%%%%%%%%%%%%%%%% %%%%%% %%                          %%%%%%%%%%%%%@          \n"\
    "                                                                                 %%%%%%%@           \n\0"
#define DRAGON_ASCII_ART_LEN 960

#define SPACE 0b00
#define PERCENT 0b01 
#define AT 0b10
#define NEWLINE 0b11

#endif

