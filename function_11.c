#include "main.h"
ssize_t in_buf(inf_o *inf, char **b, size_t *l)
{
         ssize_t s = 0;
         size_t ls = 0;

        if (!*l)
        {
                free(*b);
                *b = NULL;
                signal(SIGINT, sinthand);
#if USE_GETLINE
                s = getline(b, &ls, stdin);
#else
                s = _getline(inf, b, &ls);
#endif
                if (s > 0)
                {
                        if ((*b)[s - 1] == '\n')
                        {
                                (*b)[s - 1] = '\0';
                                s--;
                        }
                        inf->lcount_f = 1;
                        r_comm(*b);
                        b_hist_list(inf, *b, inf->hcount++);
                        {
                                *l = s;
                                inf->cmdb = b;
                        }
                }
        }
        return (s);
}
int arg_loop(inf_o *inf, char **av)
{
        ssize_t f = 0;
        int t = 0;

        while (f != -1 && t != -2)
        {
                cls_inf(inf);
                if (interactive(inf))
                        _puts("$ ");
                _eputchar(BUFSH);
                f = get_input(inf);
                if (f != -1)
                {
                        st_inf(inf, av);
                        t = f_built(inf);
                        if (t == -1)
                                f_cmd(inf);
                }
                else if (interactive(inf))
                        _putchar('\n');
                fr_inf(inf, 0);
        }
        w_hist(inf);
        fr_inf(inf, 1);
        if (!interactive(inf) && inf->stat)
                exit(inf->stat);
        if (t == -2)
        {
                if (inf->err_n == -1)
                        exit(inf->stat);
                exit(inf->err_n);
        }
        return (t);
}
ssize_t read_b(inf_o *inf, char *b, size_t *i)
{
         ssize_t s = 0;

        if (*i)
                return (0);
        s = read(inf->readfd, b, RB_SIZE);
        if (s >= 0)
                *i = s;
        return (s);
}
int _getline(inf_o *inf, char **pr, size_t *l)
{
         static char b[RB_SIZE];
         static size_t i, ls;
         size_t j;
         ssize_t s = 0, x = 0;
         char *p = NULL, *np = NULL, *c;

         p = *pr;
        if (p && l)
                x = *l;
        if (i == ls)
                i = ls = 0;
         s = read_b(inf, b, &ls);
        if (s == -1 || (s == 0 && ls == 0))
                return (-1);
         c  = _strchr(b + i, '\n');

         j = c ? 1 + (unsigned int)(c - b) : ls;

        np = _realloc(p, x, x ? x + j : j + 1);
        if (!np)
                return (p ? free(p), -1 : -1);
        if (x)
                _strncat(np, b + i, j + i);
        else
                _strncpy(np, b + i, j - i + 1);

        x += j - i;
        i = j;
        p = np;

        if (l)
                *l = x;
        *pr = p;
return (x);
}
ssize_t get_input(inf_o *inf)
{
         static char *b;
         static size_t i, j, l;
         ssize_t s = 0;
         char **bs = &(inf->arg), *p;

         _putchar(BUFSH);
         s = in_buf(inf, &b, &l);
        if (l)
        {
                j = i;
                p = b + i;
                chchain(inf, b, &j, i, l);
                while (j < l)
                {
                        i = l = 0;
                        inf->cmdb_type = NORM;
                }
                 *bs = p;
                return (_strlen(p));
        }
        *bs = b;
        return (s);
}

