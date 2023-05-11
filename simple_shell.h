#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/* These are all the header file needed for the project */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

/* operation command macros */
#define OPERATION_NORMALIZE 0    /* #define CMD_NORM	0 */
#define OPERATION_BITWISE_OR 1   /* #define CMD_OR	1 */
#define OPERATION_BITWISE_AN 2   /* #define CMD_AND	2 */
#define OPERATION_CHAIN 3        /* #define CMD_CHAIN	3 */

/* macros def to convert */
#define TO_LOWERCASE 1    /* #define CONVERT_LOWERCASE	1 */
#define TO_UNSIGNED 2     /* #define CONVERT_UNSIGNED	2 */

/* macros to input/output buffer */
#define INPUT_BUFFER_SIZE 1024	  /* #define READ_BUF_SIZE 1024 */
#define OUTPUT_BUFFER_SIZE 1024	  /* #define WRITE_BUF_SIZE 1024 */
#define FLUSH_BUFFER 1024	  /* #define BUF_FLUSH -1 */

/* SHELL history name and SIZE */
#define SHELL_HIST_FILE_NAME "shell_history.txt" /* #define HIST_FILE */
						   /* ".simple_shell_history" */
#define SHELL_MAX_REDORDS 4096			 /* #define HIST_MAX	4096 */

/* 1 if the system's getting() function is used */
#define SYSTEM_GETLINE_USED 0	  /* #define USE_GETLINE 0 */

/* 1 if strtok() function is used */
#define STRTOK_USED 0		  /* #define USE_STRTOK 0 */

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

extern char **envirom_var;	/* extern char **environ */

/**
 * struct liststr - node of a linked list that contains integer and a string
 * @num: integer value stored in the node
 * @str: string value stored in the node
 * @next: pointer to the next node in the linked list
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains information to be passed between functions
 * @arg: argument string
 * @args: argument list
 * @path: path of the executable
 * @argc: argument count
 * @line_count: current line number
 * @err_num: error number
 * @linecount_count: line count for history
 * @fname: file name
 * @env_list: list of enviroment variables
 * @history_list: list of commands in history
 * @alias_list: list of aliases
 * @environ: pointer to array of enviroment variables
 * @env_changed: indicates if enviroment variable have been changed
 * @status: exit status of the last executed command
 * @cmd_buffer: pointer to command buffer for memory management
 * @cmd_buf_type: type of command buffer (CMD_type, ||, &&, ;)
 * @readfd: read file descriptor
 * @histcount: number of commands in history
 */
typedef struct passinfo
{
	char *arg; /* char *arg; */
	char *args; /* char **argv; */
	char *path; /* char *path; */
	int argc; /* int argc; */
	unsigned int line_count; /* unsigned int line_count; */
	int err_num; /* int err_num; */
	int linecount_count; /* int linecount_flag; */
	char *fname; /* char *fname; */
	list_t *env_list; /* list_t *env; */
	list_t *history_list; /* list_t *history; */
	list_t *alias_list; /* list_t *alias; */
	char **environ; /* char **environ; */
	int env_changed; /* int env_changed; */
	int status; /* int status; */
	char *cmd_buffer; /* char **cmd_buf; */
	int cmd_buf_type; /* int cmd_buf_type; */
	int readfd; /* int readfd; */
	int histcount; /* int histcount; */
} info_t;

/**
 * struct built_in - struct for built-in shell commands
 * @command: the name of the built-in command
 * @function: a pointer to the function that implement the built-in command
 */
typedef struct built_in
{
	char *command;
	int (*function)(info_t *);
} built_in_t;
/* typedef struct builtin */
/* { */
/*	char *type; */
/*	int (*func)(info_t *); */
/* } builtin_table; */



/* hsh - main loop for simple shell */
int hsh(info_t *, char **);
/* int hsh(info_t *, char **); */

/* find_built_in - finds and executes built-in shell commands */
int find_built_in(info_t *);
/* int find_builtin(info_t *); */

/* find_cmd - finds the executable file for non-built-in commands */
void find_cmd(info_t *);
/* void find_cmd(info_t *); */

/* fork_cmd - creates a child process to execute the command */
void fork_cmd(info_t *);
/* void fork_cmd(info_t *); */


/* Function for parsing shell commands */

/* is_cmd checks if a given string is a valid shell command */
int is_cmd(info_t *, char *);
/* dup_chars creates a dupliacte string of specified portion of given string */
char *dup_chars(char *, int, int);
/* @find_path: finds the full path to a given xecutable file */
char *find_path(info_t *, char *, char *);


/* loop through the shell prompt and execute command */
int shell_prompt_loop(char **);
/* int loophsh(char **); */



/*  write a string to the standard error output */
void print_stderr(char *);
/* void _eputs(char *); */

/* write a character to the standard error output */
int print_char_stderr(char);
/* int _eputchar(char); */

/* write a character to a specified file descriptor */
int print_char_fd(char c, int fd);
/* int _putfd(char c, int fd); */

/* write a string to a specified file descriptor */
int print_string_fd(char *str, int fd);
/* int _putsfd(char *str, int fd); */



/* _strcpy copies a string from source to destination */
char *_strcpy(char *, char *);
/* _strdup duplicate a string */
char *_strdup(const char *);
/* _puts prints a string to  a stdout */
void _puts(char *);
/* _putchar writes a character to stdout */
int _putchar(char);



/* _strlen calculate the length of a string */
int _strlen(char *);
/* _strcmp compares two strings */
int _strcmp(char *, char *);
/* start_with check if a string starts with another string */
char *starts_with(const char *, const char *);
/* _strcat concatenate two strings */
char *_strcat(char *, char *);



/* str_to_words split string into words */
char **str_to_words(char *, char *);
/* char **strtow(char *, char *); */

/* str_to_words_single_delim split string into words using single delimiter */
char **str_to_words_single_delim(char *, char);
/* char **strtow2(char *, char); */



/* _strncat concatenates two string with minimum number */
char *_strncat(char *, char *, int);
/* _strncpy copies a string with minimum number */
char *_strncpy(char *, char *, int);
/* _strchr locate a character in a string */
char *_strchr(char *, char);



/* _memset fills memmory with a constant byte */
char *_memset(char *, char, unsigned int);
/* _realloc reallocates a memory block */
void *_realloc(void *, unsigned int, unsigned int);
/* ffree frees a 2-dimensional array of strings */
void ffree(char **);


/* free_block free a dynamically allocated block of memory */
int free_block(void **);
/* int bfree(void **); */


/* _atoi - converts a string to an integer */
int _atoi(char *);
/* _isalpha - checks if a character is an alphabetic character */
int _isalpha(int);
/* interactive - allows user to interact with the program */
int interactive(info_t *);
/* is_delim - checks if a character is a delimiter */
int is_delim(char, char *);



/* converts a string to an integer */
int _erratoi(char *);
/* int _erratoi(char *); */

/* prints an error message to stderr */
void printErrorMessage(info_t *, char *);
/* void print_error(info_t *, char *); */

/* prints a decimal number with a minimum width */
int printDecimalNumber(int, int);
/* int print_d(int, int); */

/* converts a long integer to a string in a given base */
char *convertNumberToBase(long int, int, int);
/* char *convert_number(long int, int, int); */

/* removes comments from a string */
void removeCommentsFromCode(char *);
/* void remove_comments(char *); */



/* terminates shell program and returns the exit status to operating system */
int exit_shell(info_t *);
/* int _myexit(info_t *); */

/* changes current working directory of the shell to directory specified */
int change_directory(info_t *);
/* int _mycd(info_t *); */

/* displays information about how to use the shell and its built-in commands */
int display_help(info_t *);
/* int _myhelp(info_t *); */



/* Displays the history of commands */
int get_history(info_t *);
/* int _myhistory(info_t *); */

/* Creates an alias for a command */
int create_alias(info_t *);
/* int _myalias(info_t *); */



/* retrieves input from a user and stores it the provided info_t struct */
ssize_t getInputSize(info_t *);
/* ssize_t get_input(info_t *); */

/* reads a line of input from a user and stores it in the provided buffer */
int getLine(info_t *, char **, size_t *);
/* int _getline(info_t *, char **, size_t *); */

/* handles the SIGINT signal */
void handleSIGINT(int);
/* void sigintHandler(int); */



/* Get the value of an environment variable. */
char *get_env(info_t *, const char *);
/* char *_getenv(info_t *, const char *); */

/* Print all environment variables */
int my_env(info_t *);
/* int _myenv(info_t *); */



/* clears the memory allocated for an info_t struct */
void clearInfo(info_t *);
/* void clear_info(info_t *); */

/* This function sets the values of an info_t struct */
void setInfo(info_t*, char**);
/* void set_info(info_t *, char **); */

/* frees the memory allocated for an array of info_t structs */
void freeInfo(info_t*, int);
/* void free_info(info_t *, int); */



/* Add or modify an environment variable */
int set_env_var(info_t *);
/* int _mysetenv(info_t *); */

/* Remove an environment variable */
int unset_env_var(info_t *);
/* int _myunsetenv(info_t *); */

/* Populate a linked list with environment variables */
int create_env_list(info_t *);
/* int populate_env_list(info_t *); */



list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
size_t print_list_str(const list_t *);
void free_list(list_t **);


/* retrieves the environment variables */
char **get_environ(info_t *);
/* removes an environment variable */
int _unsetenv(info_t *, char *);
/* sets a new environment variable or updates an existing one */
int _setenv(info_t *, char *, char *);
/* Build a list of command history entries from a string buffer */
int build_history_list(info_t *info, char *buf, int linecount);
/* Renumber the command history list */
int renumber_history(info_t *info);
/* Get the path to the history file */
char *get_history_file(info_t *info);
/* Write the command history to a file */
int write_history(info_t *info);
/* read_history - Read the command history from a file */
int read_history(info_t *info);



/*  Replaces a string with another string in place */
int replace_string(char **, char *);

/* Replaces an alias with its corresponding value in a given info struct */
int replace_alias(info_t *);

/* checks for the existence of a chain within a given range */
void chain_check(info_t *, char *, size_t *, size_t, size_t);
/* void check_chain(info_t *, char *, size_t *, size_t, size_t); */

/* Checks if a chain exists in a given info struct. */
int is_chain(info_t *, char *, size_t *);

/* Replaces variables with their corresponding values in a given info struct */
int replace_var(info_t *);
/* int replace_vars(info_t *); */




/* Get the number of elements in a linked list */
size_t list_length(const list_t *);
/* size_t list_len(const list_t *); */

/* Find the first node in a linked list whose */
/*`str` member starts with a given prefix */
list_t *node_starts_with(list_t *, char *, char);

/* Convert a linked list of strings to an array of strings */
char **list_to_string(list_t *);
/* char **list_to_strings(list_t *); */

/* Find the index of a node in a linked list. */
ssize_t get_node_index(list_t *, list_t *);

/* Print the contents of a linked list. */
size_t print_list_c(const list_t *);
/* size_t print_list(const list_t *); */


#endif
