#include "main.h"
void cls_inf(inf_o *var)
{
        var->arg = NULL;
        var->argv = NULL;
        var->path = NULL;
        var->argc = 0;
}
int iscmd(inf_o *inf, char *mychar)
{
        struct stat t;

        (void)inf;
        if (!mychar || stat(mychar, &t))
                return (0);

        if (t.st_mode & S_IFREG)
        {
                return (1);
        }
        return (0);
}
void st_inf(inf_o *var, char **c)
{
        int i = 0;

        var->fn = c[0];
        if (var->arg)
        {
                var->argv = strtok1(var->arg, " \t");
                if (!var->argv)
                {

                        var->argv = malloc(sizeof(char *) * 2);
                        if (var->argv)
                        {
                                var->argv[0] = _strdup(var->arg);
                                var->argv[1] = NULL;
                        }
                }
                for (i = 0; var->argv && var->argv[i]; i++)
                        ;
                var->argc = i;

                re_alias(var);
                re_vars(var);
        }
}
void fr_inf(inf_o *var, int x)
{
        ffr(var->argv);
        var->argv = NULL;
        var->path = NULL;
        if (x)
        {
                if (!var->cmdb)
                        free(var->arg);
                if (var->env)
                        fr_list(&(var->env));
                if (var->hist)
                        fr_list(&(var->hist));
                if (var->alias)
                        fr_list(&(var->alias));
                ffr(var->environ);
                        var->environ = NULL;
                bfr((void **)var->cmdb);
                if (var->readfd > 2)
                        close(var->readfd);
                _putchar(BUFSH);
        }
}
int bfr(void **q)
{
        if (q && *q)
        {
                free(*q);
                *q = NULL;
                return (1);
        }
        return (0);
}
