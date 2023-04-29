#include "main.h"
int mhp(inf_o *inf)
{
        char **i;

        i = inf->argv;
        _puts("help call works. Function not yet implemented \n");
        if (0)
                _puts(*i);
        return (0);
}
int mcd(inf_o *inf)
{
        char *s, *d, b[1024];
        int r;

        s = getcwd(b, 1024);
        if (!s)
                _puts("TODO: >>getcd failure emsg here<<\n");
        if (!inf->argv[1])
        {
                d = genv(inf, "HOME=");
                if (!d)
                        r = /* TODO: what should this be? */
                                chdir((d = genv(inf, "PWD=")) ? d : "/");
                else
                        r = chdir(d);
        }
        else if (_strcmp(inf->argv[1], "-") == 0)
        {
                if (!genv(inf, "OLDPWD="))
                {
                        _puts(s);
                        _putchar('\n');
                        return (1);
                }
                _puts(genv(inf, "OLDPWD=")), _putchar('\n');
                r = /* TODO: what should this be? */
                        chdir((d = genv(inf, "OLDPWD=")) ? d : "/");
        }
        else
                r = chdir(inf->argv[1]);
        if (r == -1)
        {
                p_err(inf, "can't cd to ");
                _eputs(inf->argv[1]), _eputchar('\n');
        }
        else
        {
                stenv(inf, "OLDPWD", genv(inf, "PWD="));
                stenv(inf, "PWD", getcwd(b, 1024));
        }
        return (0);
}
char *_strchr(char *s, char c)
{
        do {
                if (*s == c)
                        return (s);
        } while (*s++ != '\0');

        return (NULL);
}
int mexit(inf_o *inf)
{
        int x;

        if (inf->argv[1])
        {
                x = _eatoi(inf->argv[1]);
                if (x == -1)
                {
                        inf->stat = 2;
                        p_err(inf, "Illegal number: ");
                        _eputs(inf->argv[1]);
                        _eputchar('\n');
                        return (1);
                }
                inf->err_n = _eatoi(inf->argv[1]);
                return (-2);
        }
        inf->err_n = -1;
        return (-2);
}
int mhist(inf_o *inf)
{
        p_list(inf->hist);
        return (0);
}
