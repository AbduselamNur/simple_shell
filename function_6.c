#include "main.h"
void ffr(char **x)
{
        char **a = x;

        if (!x)
                return;
        while (*x)
                free(*x++);
        free(a);
}
int re_vars(inf_o *val)
{
        int i = 0;
        lists_t *x;

        for (i = 0; val->argv[i]; i++)
        {
                if (val->argv[i][0] != '$' || !val->argv[i][1])
                        continue;

                if (!_strcmp(val->argv[i], "$?"))
                {
                        re_string(&(val->argv[i]),
                                _strdup(conv_n(val->stat, 10, 0)));
                        continue;
                }
                if (!_strcmp(val->argv[i], "$$"))
                {
                        re_string(&(val->argv[i]),
                                _strdup(conv_n(getpid(), 10, 0)));
                        continue;
                }
                x = node_starts_with(val->env, &val->argv[i][1], '=');
                if (x)
                {
                        re_string(&(val->argv[i]),
                                _strdup(_strchr(x->str, '=') + 1));
                        continue;
                }
                re_string(&val->argv[i], _strdup(""));
        }
        return (0);
}
int re_hist(inf_o *var)
{
        lists_t *n = var->hist;
        int i = 0;

        while (n)
        {
                n->n = i++;
                n = n->next;
        }
        return (var->hcount = i);
}
char *_memset(char *x, char b, unsigned int n)
{
        unsigned int a = 0;

        while (a < n)
        {
                x[a] = b;
               a++;
        }
        return (x);
}
int b_hist_list(inf_o *var, char *v, int l)
{
        lists_t *n = NULL;

        if (var->hist)
                n = var->hist;
        add_node_end(&n, v, l);

        if (!var->hist)
                var->hist = n;
        return (0);
}
