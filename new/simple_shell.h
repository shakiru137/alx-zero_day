#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

extern char **environ;

/* for convertNumberToBase() */
#define TO_LOWERCASE 1
#define TO_UNSIGNED 2
#define SHELL_HIST_FILE_NAME "shell_history.txt"
#define SHELL_MAX_REDORDS 4096

/* macros to input/output buffer */
#define INPUT_BUFFER_SIZE 1024
#define OUTPUT_BUFFER_SIZE 1024
#define FLUSH_BUFFER -1

#define ARRAY_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* 1 if the system's getline() function is used */
#define SYSTEM_GETLINE_USED 0

/* operation command macros */
#define OPERATION_NORMALIZE 0
#define OPERATION_BITWISE_OR 1
#define OPERATION_BITWISE_AND 2
#define OPERATION_CHAIN 3

/**
 * struct listis - node of a linked list that contains integer and a string
 * @number: integer value stored in the node
 * @str: string value stored in the node
 * @next: pointer to the next node in the linked list
 */
typedef struct listis
{
	int number;
	char *str;
	struct listis *next;
} d_list;

/**
 * struct passinfo - contains information to be passed between functions
 * @arg: argument string
 * @argv: argument list
 * @path: path of the executable
 * @argc: argument count
 * @linecount: current line number
 * @error_num: error number for exit()
 * @flag_of_linecunt: line count for history
 * @filename: program filename
 * @env_vars: list of enviroment variables
 * @environ: pointer to array of enviroment variables
 * @history: list of commands in history
 * @alias: list of aliases
 * @env_changed: indicates if enviroment variable have been changed
 * @status: exit status of the last executed command
 * @cmd_buffer: pointer to command buffer for memory management
 * @cmd_buff_type: type of command buffer (CMD_type, ||, &&, ;)
 * @readfd: read file descriptor
 * @histcount: number of commands in history
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int linecount;
	int error_num;
	int flag_of_linecunt;
	char *filename;
	d_list *env_vars;
	d_list *history;
	d_list *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buffer;
	int cmd_buff_type;
	int readfd;
	int histcount;
} d_info;

/**
 * struct builtin - struct for built-in shell commands
 * @type: the name of the built-in command
 * @func: a pointer to the function that implement the built-in command
 */
typedef struct builtin
{
	char *type;
	int (*func)(d_info *);
} built_in_table;

/* Function for parsing shell commands */
int is_cmd(d_info *, char *);
char *dup_chars(char *, int, int);
char *find_path(d_info *, char *, char *);

/* shell_loop - main loop for simple shell */
int shell_loop(d_info *, char **);
/* find_built_in - finds and executes built-in shell commands */
int find_built_in(d_info *);
/* find_cmd - finds the executable file for non-built-in commands */
void find_cmd(d_info *);
/* fork_cmd - creates a child process to execute the command */
void fork_cmd(d_info *);

/* loop through the shell prompt and execute command */
int loop_shell_prompt(char **);

/* _strlen calculate the length of a string */
size_t _strlen(const char *);
/* _strcmp compares two strings */
int _strcmp(char *, char *);
/* start_with check if a string starts with another string */
char *starts_with(const char *, const char *);
/* _strcat concatenate two strings */
char *_strcat(char *, char *);

/*  write a string to the standard error output */
void _eputs(char *);
/* write a character to the standard error output */
int _eputchar(char);
/* write a character to a specified file descriptor */
int _putfd(char c, int fd);
/* write a string to a specified file descriptor */
int _putsfd(char *str, int fd);

/* _strncpy copies a string with minimum number */
char *_strncpy(char *, char *, int);
/* _strncat concatenates two string with minimum number */
char *_strncat(char *, char *, int);
/* _strchr locate a character in a string */
char *_strchr(char *, char);

/* _strcpy copies a string from source to destination */
char *_strcpy(char *, char *);
/* _strdup duplicate a string */
char *_strdup(const char *);
/* _puts prints a string to  a stdout */
void _puts(char *);
/* _putchar writes a character to stdout */
int _putchar(char);

/* _memset fills memmory with a constant byte */
char *_memset(char *, char, unsigned int);
/* ffree frees a 2-dimensional array of strings */
void ffree(char **);
/* _realloc reallocates a memory block */
void *_realloc(void *, unsigned int, unsigned int);

/* str_to_words split string into words */
char **str_to_words(char *, char *);
/* str_to_words_single_delim split string into words using single delimiter */
char **str_to_words_single_delim(char *, char);
/* free_block free a dynamically allocated block of memory */
int free_block(void **);

/* interactive - allows user to interact with the program */
int interactive(d_info *);
/* is_delim - checks if a character is a delimiter */
int is_delim(char, char *);
/* _isalpha - checks if a character is an alphabetic character */
int _isalpha(int);
/* _atoi - converts a string to an integer */
int _atoi(char *);

/* converts a string to an integer */
int _erratoi(char *);
/* prints an error message to stderr */
void printErrorMessage(d_info *, char *);
/* prints a decimal number with a minimum width */
int printDecimalNumber(int, int);
/* converts a long integer to a string in a given base */
char *convertNumberToBase(long int, int, int);
/* removes comments from a string */
void removeCommentsFromCode(char *);

/* Displays the history of commands */
int get_history(d_info *);
/* Displays the history of commands */
int get_alias(d_info *);

/* terminates shell program and returns the exit status to operating system */
int exit_shell(d_info *);
/* changes current working directory of the shell to directory specified */
int change_dir(d_info *);
/* displays information about how to use the shell and its built-in commands */
int get_help(d_info *);

/* retrieves input from a user and stores it the provided p_info struct */
ssize_t get_input(d_info *);
/* reads a line of input from a user and stores it in the provided buffer */
int _getline(d_info *, char **, size_t *);
/* handles the SIGINT signal */
void sigintHandler(int);

void clearInfo(d_info *);
void setInfo(d_info *, char **);
void freeInfo(d_info *, int);

char *_getenv(d_info *, const char *);
int ENV_VARS(d_info *);
int mysetenv(d_info *);
int _myunsetenv(d_info *);
int populate_env_list(d_info *);

char **get_environ(d_info *);
int _unsetenv(d_info *, char *);
int _setenv(d_info *, char *, char *);

char *get_history_file(d_info *info);
int write_history(d_info *info);
int read_history(d_info *info);
int build_history_list(d_info *info, char *buf, int linecount);
int renumber_history(d_info *info);

d_list *add_node(d_list **, const char *, int);
d_list *add_node_end(d_list **, const char *, int);
size_t print_list_str(const d_list *);
int delete_node_at_index(d_list **, unsigned int);
void free_list(d_list **);

int is_chain(d_info *, char *, size_t *);
void check_chain(d_info *, char *, size_t *, size_t, size_t);
int replace_alias(d_info *);
int replace_vars(d_info *);
int replace_string(char **, char *);
int unset_alias(d_info *info, char *str);
int print_alias(d_list *node);
ssize_t input_buf(d_info *info, char **buf, size_t *len);
ssize_t read_buf(d_info *info, char *buf, size_t *i);

size_t list_len(const d_list *);
char **list_to_strings(d_list *);
size_t print_list(const d_list *);
d_list *node_starts_with(d_list *, char *, char);
ssize_t get_node_index(d_list *, d_list *);

#endif /* SIMPLE_SHELL_H */
