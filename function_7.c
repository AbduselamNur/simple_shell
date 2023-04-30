#include "main.h"
char **strtok1(char *x, char *y)
{
        int i;
	int j;
	int z;
	int m;
	char **w;
	int count = 0;

        if (x == NULL || x[0] == 0)
                return (NULL);
        if (!y)
                y = " ";
        for (i = 0; x[i] != '\0'; i++)
                if (!is_delim(x[i], y) && (is_delim(x[i + 1], y) || !x[i + 1]))
                        count++;

        if (count == 0)
                return (NULL);
        w = malloc((1 + count) * sizeof(char *));
        if (!w)
                return (NULL);
        for (i = 0, j = 0; j < count; j++)
        {
                while (is_delim(x[i], y))
                        i++;
                z = 0;
                while (!is_delim(x[i + z], y) && x[i + z])
                        z++;
                w[j] = malloc((z + 1) * sizeof(char));
                if (!w[j])
                {
                        for (z = 0; z < j; z++)
                                free(w[z]);
                        free(w);
                        return (NULL);
                }
                for (m = 0; m < z; m++)
                        w[j][m] = x[i++];
                w[j][m] = 0;
        }
        w[j] = NULL;
        return (w);
}
char *ghist_file(inf_o *val)
{
        char *v;
	char *c;

        c = genv(val, "HOME=");
        if (!c)
                return (NULL);
        v = malloc(sizeof(char) * (_strlen(c) + _strlen(H_F) + 2));
        if (!v)
                return (NULL);
        v[0] = 0;
        _strcpy(v, c);
        _strcat(v, "/");
        _strcat(v, H_F);
        return (v);
}
int w_hist(inf_o *var)
{
	ssize_t x;
	char *fn = ghist_file(var);
	lists_t *n = NULL;

	if (!fn)
		return (-1);

	x = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (x == -1)
		return (-1);
	for (n = var->hist; n; n = n->next)
	{
		_putsfd(n->str, x);
		_putfd('\n', x);
	}
	_putfd(BUFSH, x);
	close(x);
	return (1);
}
int r_hist(inf_o *val)
{
	int i;
	int l = 0;
	int  lc = 0;
	ssize_t f;
	ssize_t rlen;
        ssize_t fs = 0;
	struct stat s;
	char *v = NULL, *fname = ghist_file(val);

	if (!fname)
		return (0);

	f = open(fname, O_RDONLY);
	free(fname);
	if (f == -1)
		return (0);
	if (!fstat(f, &s))
		fs = s.st_size;
	if (fs < 2)
		return (0);
	v = malloc(sizeof(char) * (fs + 1));
	if (!v)
		return (0);
	rlen = read(f, v, fs);
	v[fs] = 0;
	if (rlen <= 0)
		return (free(v), 0);
	close(f);
	for (i = 0; i < fs; i++)
		if (v[i] == '\n')
		{
			v[i] = 0;
			b_hist_list(val, v + l, lc++);
			l = i + 1;
		}
	if (l != i)
		b_hist_list(val, v + l, lc++);
	free(v);
	val->hcount = lc;
	while (val->hcount-- >= H_M)
		delete_node_at_i(&(val->hist), 0);
	re_hist(val);
	return (val->hcount);
}
char **strtok2(char *x, char y)
{
        int i, j, z, m, count = 0;
        char **v;

        if (x == NULL || x[0] == 0)
                return (NULL);
        i = 0;
        for (i = 0; x[i] != '\0'; i++)
        {
                if ((x[i] != y && x[i + 1] == y) ||
                    (x[i] != y && !x[i + 1]) || x[i + 1] == y)
                        count++;
        }
        if (count == 0)
                return (NULL);
        v = malloc((1 + count) * sizeof(char *));
        if (!v)
                return (NULL);
        i = 0;
        j = 0;
        for (i = 0, j = 0; j < count; j++)
        {
                while (x[i] == y && x[i] != y)
                        i++;
                z = 0;
                while (x[i + z] != y && x[i + z] && x[i + z] != y)
                        z++;
                v[j] = malloc((z + 1) * sizeof(char));
                if (!v[j])
                {
                        for (z = 0; z < j; z++)
                                free(v[z]);
                        free(v);
                        return (NULL);
                }
                for (m = 0; m < z; m++)
                        v[j][m] = x[i++];
                v[j][m] = 0;
        }
        v[j] = NULL;
        return (v);
}
