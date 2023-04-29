#include "main.h"
char *char_dp(char *q, int r, int it)
{
        static char c[1024];
        int x = 0, k = 0;

        for (k = 0, x = r; x < it; x++)
        {
                if (q[x] != ':')
                        c[k++] = q[x];
        }
        c[k] = 0;
        return (c);
}
char *fd_p(inf_o *var, char *q, char *c)
{
	int x = 0, cr = 0;
	char *s;

	if (!q)
		return (NULL);
	if ((_strlen(c) > 2) && st_wi(c, "./"))
	{
		if (iscmd(var, c))
			return (c);
	}
	while (1)
	{
		if (!q[x] || q[x] == ':')
		{
			s = char_dp(q, cr, x);
			if (!*s)
				_strcat(s, c);
			else
			{
				_strcat(s, "/");
				_strcat(s, c);
			}
			if (iscmd(var, s))
				return (s);
			if (!q[x])
				break;
			cr = x;
		}
		x++;
	}
	return (NULL);
}
char *_strncpy(char *dest, char *src, int n)
{
	int x = 0;
	int y;
	char *s = dest;

	while (src[x] != '\0' && x < n)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		for (y = x; y < n; y++)
			dest[y] = '\0';
	}
	return (s);
}
char *_strncat(char *dest, char *src, int n)
{
        int x = 0;
	int y = 0;

        char *s = dest;

        while (dest[x] != '\0')
                x++;
        while (src[y] != '\0' && y < n)
        {
                dest[x] = src[y];
                x++;
                y++;
        }
        if (y < n)
                dest[x] = '\0';
        return (s);
}
char *_strcpy(char *dest, char *src)
{
        int x = 0;

        if (dest == src || src == 0)
                return (dest);
        for (x = 0; src[x]; x++)
        {
                dest[x] = src[x];
        }
        dest[x] = 0;
        return (dest);
}
