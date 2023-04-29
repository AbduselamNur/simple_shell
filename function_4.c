#include "main.h"
int menv(inf_o *val)
{
        p_list_str(val->env);
        return (0);
}
int msetenv(inf_o *val)
{
        if (val->argc != 3)
        {
                _eputs("Incorrect number of arguments\n");
                return (1);
        }
        if (stenv(val, val->argv[1], val->argv[2]))
                return (0);
        return (1);
}
int penv_list(inf_o *val)
{
        lists_t *i = NULL;
        size_t x;

        for (x = 0; environ[x]; x++)
                add_node_end(&i, environ[x], 0);
        val->env = i;
        return (0);
}
int munsetenv(inf_o *val)
{
        int x;
	x = 1;

        if (val->argc == 1)
        {
                _eputs("Too few arguments.\n");
                return (1);
        }
        while (x <= val->argc)
        {
                _unsetenv(val, val->argv[x]);
                x++;
        }

        return (0);
}
char *genv(inf_o *val, const char *na)
{
        lists_t *x = val->env;
        char *v;

        while (x)
        {
                v = st_wi(x->str, na);
                if (v && *v)
                        return (v);
                x = x->next;
        }
        return (NULL);
}
int is_delim(char ch, char *x)
{
	while (*x)
		if (*x++ == ch)
			return (1);
	return (0);
}
