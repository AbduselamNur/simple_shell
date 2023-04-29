#include "main.h"
int f_built(inf_o *inf)
{
        int j, t = -1;
        builtin_t builts[] = {
                {"exit", mexit},
                {"env", menv},
                {"help", mhp},
                {"history", mhist},
                {"setenv", msetenv},
                {"unsetenv", munsetenv},
                {"cd", mcd},
                {"alias", malias},
                {NULL, NULL}
        };


        for (j = 0; builts[j].type; j++)
        {
                if (_strcmp(inf->argv[0], builts[j].type) == 0)
                {
                        inf->lcount++;
                        t = builts[j].func(inf);
                        break;
                }
        }
        return (t);
}
int _eputchar(char c)
{
	static int i;
	static char b[WB_SIZE];

	if (c == BUFSH || i >= WB_SIZE)
	{
		write(2, b, i);
		i = 0;
	}
	if (c != BUFSH)
		b[i++] = c;
	return (1);
}
void fr_cmd(inf_o *inf)
{
        pid_t child_pid;

        child_pid = fork();
        if (child_pid == -1)
        {
                perror("Error:");
                return;
        }
        if (child_pid == 0)
        {
                if (execve(inf->path, inf->argv, genvn(inf)) == -1)
                {
                        fr_inf(inf, 1);
                        if (errno == EACCES)
                                exit(126);
                        exit(1);
                }
        }
        else
        {
                wait(&(inf->stat));
                if (WIFEXITED(inf->stat))
                {
                        inf->stat = WEXITSTATUS(inf->stat);
                        if (inf->stat == 126)
                                p_err(inf, "Permission denied\n");
                }
        }
}
int _putsfd(char *s, int f)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _putfd(*s++, f);
	}
	return (i);
}
void f_cmd(inf_o *inf)
{
        char *p = NULL;
        int j, k;

        inf->path = inf->argv[0];
        if (inf->lcount_f == 1)
        {
                inf->lcount++;
                inf->lcount_f = 0;
        }
        for (j = 0, k = 0; inf->arg[j]; j++)
        {
                if (!is_delim(inf->arg[j], " \t\n"))
                        k++;
        }
        if (!k)
                return;

        p = fd_p(inf, genv(inf, "PATH="), inf->argv[0]);
        if (p)
        {
                inf->path = p;
                fr_cmd(inf);
        }
        else
        {
                if ((interactive(inf) || genv(inf, "PATH=")
                        || inf->argv[0][0] == '/') && iscmd(inf, inf->argv[0]))
                        fr_cmd(inf);
                else if (*(inf->arg) != '\n')
                {
                        inf->stat = 127;
                        p_err(inf, "not found\n");
                }
        }
}
