#include "main.h"
int stenv(inf_o *val, char *x, char *y)
{
        char *b = NULL;
        lists_t *n;
        char *k;

        if (!x || !y)
                return (0);

        b = malloc(_strlen(x) + _strlen(y) + 2);
        if (!b)
                return (1);
        _strcpy(b, x);
        _strcat(b, "=");
        _strcat(b, y);
        n = val->env;
        while (n)
        {
                k = st_wi(n->str, x);
                if (k && *k == '=')
                {
                        free(n->str);
                        n->str = b;
                        val->env_ch = 1;
                        return (0);
                }
                n = n->next;
        }
        add_node_end(&(val->env), b, 0);
        free(b);
        val->env_ch = 1;
        return (0);
}
char *conv_n(long int x, int y, int z)
{
        static char *r;
        static char b[50];
        char s = 0;
        char *p;
        unsigned long n = x;

        if (!(z & CONV_UNSIGN) && x < 0)
        {
                n = -x;
                s = '-';

        }
        r = z & CONV_LOW ? "0123456789abcdef" : "0123456789ABCDEF";
        p = &b[49];
        *p = '\0';

        do      {
                *--p = r[n % y];
                n /= y;
        } while (n != 0);

        if (s)
                *--p = s;
        return (p);
}
char **genvn(inf_o *var)
{
        if (!var->environ || var->env_ch)
        {
                var->environ = l_to_s(var->env);
                var->env_ch = 0;
        }

        return (var->environ);
}
void r_comm(char *v)
{
        int x;
        x = 0;

        while (v[x] != '\0')
        {
                if (v[x] == '#' && (!x || v[x - 1] == ' '))
                {
                        v[x] = '\0';
                        break;
                }
                x++;
        }
}
int _unsetenv(inf_o *var, char *x)
{
        lists_t *q;
        size_t i;
        char *k;
	q = var->env;
	i = 0;

        if (!q || !x)
                return (0);

        while (q)
        {
                k = st_wi(q->str, x);
                if (k && *k == '=')
                {
                        var->env_ch = delete_node_at_i(&(var->env), i);
                        i = 0;
                        q = var->env;
                        continue;
                }
                q = q->next;
                i++;
        }
        return (var->env_ch);
}
