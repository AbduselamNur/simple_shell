#include "main.h"
char **strtok1(char *sr, char *a)
{
        int i, j, z, m, count = 0;
        char **v;

        if (sr == NULL || sr[0] == 0)
                return (NULL);
        if (!a)
                a = " ";
        for (i = 0; sr[i] != '\0'; i++)
                if (!is_delim(sr[i], a) && (is_delim(sr[i + 1], a) || !sr[i + 1]))
                        count++;

        if (count == 0)
                return (NULL);
        v = malloc((1 + count) * sizeof(char *));
        if (!v)
                return (NULL);
        for (i = 0, j = 0; j < count; j++)
        {
                while (is_delim(sr[i], a))
                        i++;
                z = 0;
                while (!is_delim(sr[i + z], a) && sr[i + z])
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
                        v[j][m] = sr[i++];
                v[j][m] = 0;
        }
        v[j] = NULL;
        return (v);
}
char *ghist_file(inf_o *inf)
{
        char *b, *d;

        d = genv(inf, "HOME=");
        if (!d)
                return (NULL);
        b = malloc(sizeof(char) * (_strlen(d) + _strlen(H_F) + 2));
        if (!b)
                return (NULL);
        b[0] = 0;
        _strcpy(b, d);
        _strcat(b, "/");
        _strcat(b, H_F);
        return (b);
}
int w_hist(inf_o *var)
{
	ssize_t a;
	char *fname = ghist_file(var);
	lists_t *n = NULL;

	if (!fname)
		return (-1);

	a = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (a == -1)
		return (-1);
	for (n = var->hist; n; n = n->next)
	{
		_putsfd(n->str, a);
		_putfd('\n', a);
	}
	_putfd(BUFSH, a);
	close(a);
	return (1);
}
int r_hist(inf_o *inf)
{
	int i, l = 0, lc = 0;
	ssize_t f, rlen, fs = 0;
	struct stat s;
	char *b = NULL, *fname = ghist_file(inf);

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
	b = malloc(sizeof(char) * (fs + 1));
	if (!b)
		return (0);
	rlen = read(f, b, fs);
	b[fs] = 0;
	if (rlen <= 0)
		return (free(b), 0);
	close(f);
	for (i = 0; i < fs; i++)
		if (b[i] == '\n')
		{
			b[i] = 0;
			b_hist_list(inf, b + l, lc++);
			l = i + 1;
		}
	if (l != i)
		b_hist_list(inf, b + l, lc++);
	free(b);
	inf->hcount = lc;
	while (inf->hcount-- >= H_M)
		delete_node_at_i(&(inf->hist), 0);
	re_hist(inf);
	return (inf->hcount);
}
char **strtok2(char *sr, char a)
{
        int i, j, z, m, count = 0;
        char **v;

        if (sr == NULL || sr[0] == 0)
                return (NULL);
        i = 0;
        for (i = 0; sr[i] != '\0'; i++)
        {
                if ((sr[i] != a && sr[i + 1] == a) ||
                    (sr[i] != a && !sr[i + 1]) || sr[i + 1] == a)
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
                while (sr[i] == a && sr[i] != a)
                        i++;
                z = 0;
                while (sr[i + z] != a && sr[i + z] && sr[i + z] != a)
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
                        v[j][m] = sr[i++];
                v[j][m] = 0;
        }
        v[j] = NULL;
        return (v);
}
