#include "main.h"
int _strcmp(char *x, char *y)
{
	while (*x && *y)
	{
		if (*x != *y)
			return (*x - *y);
		x++;
		y++;
	}
	if (*x == *y)
		return (0);
	else
		return (*x < *y ? -1 : 1);
}
int _isalpha(int x)
{
        if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
                return (1);
        else
                return (0);
}
int _atoi(char *ch)
{
        int x, t;
       int n = 1, v = 0;
        unsigned int r = 0;

        for (x = 0;  ch[x] != '\0' && v != 2; x++)
        {
                if (ch[x] == '-')
                        n *= -1;

                if (ch[x] >= '0' && ch[x] <= '9')
                {
                        v = 1;
                        r *= 10;
                        r += (ch[x] - '0');
                }
                else if (v == 1)
                        v = 2;
        }

        if (n == -1)
                t = -r;
        else
                t = r;

        return (t);
}
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
int interactive(inf_o *var)
{
        return (isatty(STDIN_FILENO) && var->readfd <= 2);
}
