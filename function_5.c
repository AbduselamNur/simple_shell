#include "main.h"
int ischain(inf_o *val, char *x, size_t *s)
{
        size_t i = *s;

        if (x[i] == '|' && x[i + 1] == '|')
        {
                x[i] = 0;
                i++;
                val->cmdb_type = OR;
        }
        else if (x[i] == '&' && x[i + 1] == '&')
        {
                x[i] = 0;
                i++;
                val->cmdb_type = AND;
        }
        else if (x[i] == ';')
        {
                x[i] = 0;
                val->cmdb_type = CHAIN;
        }
        else
                return (0);
        *s = i;
        return (1);
}
int re_string(char **x, char *y)
{
        free(*x);
        *x = y;
        return (1);
}
void chchain(inf_o *val, char *v, size_t *x, size_t a, size_t b)
{
        size_t k = *x;

        if (val->cmdb_type == AND)
        {
                if (val->stat)
                {
                        v[a] = 0;
                        k = b;
                }
        }
        if (val->cmdb_type == OR)
        {
                if (!val->stat)
                {
                        v[a] = 0;
                        k = b;
                }
        }

        *x = k;
}
int re_alias(inf_o *var)
{
        int x;
        lists_t *a;
        char *p;
	x = 0;

        for (x = 0; x < 10; x++)
        {
                a = node_starts_with(var->alias, var->argv[0], '=');
                if (!a)
                        return (0);
                free(var->argv[0]);
                p = _strchr(a->str, '=');
                if (!p)
                        return (0);
                p = _strdup(p + 1);
                if (!p)
                        return (0);
                var->argv[0] = p;
        }
        return (1);
}
void *_realloc(void *pt, unsigned int x, unsigned int n)
{
        char *p;

        if (!pt)
                return (malloc(n));
        if (!n)
                return (free(pt), NULL);
        if (n == x)
                return (pt);
        p = malloc(n);
        if (!p)
                return (NULL);
        x = x < n ? x : n;
        while (x--)
                p[x] = ((char *)pt)[x];
        free(pt);
        return (p);
}
