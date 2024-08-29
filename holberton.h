#ifndef _HOLBERTON_
#define _HOLBERTON_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings that are the "environment" */
extern char **environ;

/**
 * struct data - struct that contains all important data on runtime
 * @av: argument vector
 * @input: command written or inputted by user
 * @args: tokens of the command line
 * @status: previous or last status of the shell
 * @counter: count lines or lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @seperator: ; | &
 * @next: next node
 * Description: single linked list to store seperators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list for storing command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of our variable
 * @val: value of our variable
 * @len_val: length of our variable value
 * @next: next node
 * Description: a single linked list to store variables and its value
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Struct for builtin command args
 * @name: Name of of the builtin command like cd, env, exit
 * @f: pointer function data type
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/* aux_lists functions */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* aux_lists2 functions */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* aux_str functions */
char *_strcat(char *dest, const char *src);
char *strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* aux_mem functions */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2 functions */
char *strdup(const char *s);
int _strlen(const char *s);
char *_strtok(char str[], const char *delim);
int cmp_chars(char str[], const char *delim);
int _isdigit(const char *s);

/* aux_str3 functions */
void rev_string(char *s);

/* shell_loop functions */
char *without_comment(char *in);
void shell_loop(data_shell *datash);

/* read_line function */
char *read_line(int *i_eof);

/* check_syntax_error functions */
int repeated_char(char *input, int i);
void print_syntax_error(data_shell *datash, char *input, int i, int bool);
int check_syntax_error(data_shell *datash, char *input);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);

/* split functions */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);

/* rep_var functions */
void check_env(r_var **h, char *in, data_shell *data);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_shell *datash);

/* get_line function */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line function */
int exec_line(data_shell *datash);

/* cmd_exec functions */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *datash);
int check_error_cmd(char *dir, data_shell *datash);
int cmd_exec(data_shell *datash);

/* env1 functions */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);

/* env2 functions */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);

/* cd functions*/
void cd_dot(data_shell *datash);
void cd_to(data_shell *datash);
void cd_previous(data_shell *datash);
void cd_to_home(data_shell *datash);

/* cd_shell function */
int cd_shell(data_shell *datash);

/* get_builtin function */
int (*get_builtin(char *cmd))(data_shell *datash);

/* _exit functions */
int exit_shell(data_shell *datash);

/* aux_stdlib functions */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* aux_error1 functions */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *datash);
char *error_not_found(data_shell *datash);
char *error_exit_shell(data_shell *datash);

/* aux_error2 functions */
char *error_get_alias(char **args);
char *error_env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data_shell *datash);


/* get_error functions */
int get_error(data_shell *datash, int eval);

/* get_sigint functions */
void get_sigint(int sig);

/* aux_help functions */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* aux_help2 functions */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help functions */
int get_help(data_shell *datash);

#endif
