#include "main.h"
int stenv(inf_o *inf, char *l, char *i)
{
        char *b = NULL;
        lists_t *n;
        char *k;

        if (!l || !i)
                return (0);

        b = malloc(_strlen(l) + _strlen(i) + 2);
        if (!b)
                return (1);
        _strcpy(b, l);
        _strcat(b, "=");
        _strcat(b, i);
        n = inf->env;
        while (n)
        {
                k = st_wi(n->str, l);
                if (k && *k == '=')
                {
                        free(n->str);
                        n->str = b;
                        inf->env_ch = 1;
                        return (0);
                }
                n = n->next;
        }
        add_node_end(&(inf->env), b, 0);
        free(b);
        inf->env_ch = 1;
        return (0);
}
char *conv_n(long int m, int bs, int f)
{
        static char *r;
        static char b[50];
        char s = 0;
        char *p;
        unsigned long n = m;

        if (!(f & CONV_UNSIGN) && m < 0)
        {
                n = -m;
                s = '-';

        }
        r = f & CONV_LOW ? "0123456789abcdef" : "0123456789ABCDEF";
        p = &b[49];
        *p = '\0';

        do      {
                *--p = r[n % bs];
                n /= bs;
        } while (n != 0);

        if (s)
                *--p = s;
        return (p);
}
char **genvn(inf_o *inf)
{
        if (!inf->environ || inf->env_ch)
        {
                inf->environ = l_to_s(inf->env);
                inf->env_ch = 0;
        }

        return (inf->environ);
}
void r_comm(char *b)
{
        int i = 0;

        while (b[i] != '\0')
        {
                if (b[i] == '#' && (!i || b[i - 1] == ' '))
                {
                        b[i] = '\0';
                        break;
                }
                i++;
        }
}
int _unsetenv(inf_o *inf, char *l)
{
        lists_t *n = inf->env;
        size_t i = 0;
        char *k;

        if (!n || !l)
                return (0);

        while (n)
        {
                k = st_wi(n->str, l);
                if (k && *k == '=')
                {
                        inf->env_ch = delete_node_at_i(&(inf->env), i);
                        i = 0;
                        n = inf->env;
                        continue;
                }
                n = n->next;
                i++;
        }
        return (inf->env_ch);
}
