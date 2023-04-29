#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>



#define RB_SIZE 1024
#define WB_SIZE 1024
#define BUFSH -1
#define H_F	".shell_hist"
#define H_M	4096
#define NORM	0
#define OR		1
#define AND		2
#define CHAIN	3
#define USE_GETLINE 0
#define USE_STRTOK 0
#define CONV_LOW	1
#define CONV_UNSIGN	2





extern char **environ;

typedef struct lists
{
	int n;
	char *str;
	struct lists *next;
} lists_t;
typedef struct psinf
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int lcount;
	int err_n;
	int lcount_f;
	char *fn;
	lists_t *env;
	lists_t *hist;
	lists_t *alias;
	char **environ;
	int env_ch;
	int stat;

	char **cmdb;
	int cmdb_type;
	int readfd;
	int hcount;
} inf_o;

#define INF_IN \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

typedef struct builtin
{
	char *type;
	int (*func)(inf_o *);
} builtin_t;
ssize_t get_input(inf_o *);
int _getline(inf_o *, char **, size_t *);
void sinthand(int);
char **strtok1(char *, char *);
char **strtok2(char *, char);
int loophsh(char **);
char *genv(inf_o *val, const char *na);
int menv(inf_o *val);
int msetenv(inf_o *val);
int munsetenv(inf_o *val);
int penv_list(inf_o *val);
char **genvn(inf_o *);
int _unsetenv(inf_o *, char *);
int stenv(inf_o *, char *, char *);
void cls_inf(inf_o *var);
void st_inf(inf_o *var, char **c);
void fr_inf(inf_o *var, int x);
int bfr(void **q);
int mhist(inf_o *);
int malias(inf_o *);
int mexit(inf_o *);
int mcd(inf_o *);
int mhp(inf_o *);
int _eatoi(char *);
void p_err(inf_o *, char *);
int p_d(int, int);
char *conv_n(long int, int, int);
void r_comm(char *);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int f);
int _putsfd(char *s, int f);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int);
char *_strchr(char *, char);
char *ghist_file(inf_o *val);
int w_hist(inf_o *val);
int r_hist(inf_o *val);
int b_hist_list(inf_o *val, char *b, int lc);
int re_hist(inf_o *val);
char *_memset(char *x, char v, unsigned int n);
void ffr(char **x);
void *_realloc(void *pt, unsigned int x, unsigned int n);
int ischain(inf_o *val, char *x, size_t *s);
void chchain(inf_o *val, char *v, size_t *x, size_t a, size_t b);
int re_alias(inf_o *val);
int re_vars(inf_o *val);
int re_string(char **x, char *y);
lists_t *add_node(lists_t **, const char *, int);
lists_t *add_node_end(lists_t **, const char *, int);
size_t p_list_str(const lists_t *);
int delete_node_at_i(lists_t **, unsigned int);
void fr_list(lists_t **);
size_t l_len(const lists_t *);
char **l_to_s(lists_t *);
size_t p_list(const lists_t *);
lists_t *node_starts_with(lists_t *, char *, char);
ssize_t get_node_i(lists_t *, lists_t *);
int iscmd(inf_o *, char *mychar);
char *char_cp(char *, int, int);
char *fd_p(inf_o *var, char *q, char *c);
int arg_loop(inf_o *, char **);
int f_built(inf_o *);
void f_cmd(inf_o *);
void fr_cmd(inf_o *);
int interactive(inf_o *);
int is_delim(char ch, char *x);
int _isalpha(int x);
int _atoi(char *ch);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char ch);
int _strlen(char *);
int _strcmp(char *x, char *y);
char *st_wi(const char *x, const char *n);
char *_strcat(char *, char *);

#endif /*SHELL_H*/
