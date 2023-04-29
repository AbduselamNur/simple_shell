#include "main.h"
void _eputs(char *s)
{
        int i = 0;

        if (!s)
                return;
        for (i = 0; s[i] != '\0'; i++)
                _eputchar(s[i]);
}
int _eatoi(char *str)
{
	int i = 0;
	unsigned long int l = 0;

	if (*str == '+')
		str++;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			l *= 10;
			l += (str[i] - '0');
			if (l > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	return (l);
}
void p_err(inf_o *inf, char *str)
{
	_eputs(inf->fn);
	_eputs(": ");
	p_d(inf->lcount, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(str);
}
int p_d(int in, int f)
{
	int (*__putchar)(char) = _putchar;
	int i, j = 0;
	unsigned int s, cr;

	if (f == STDERR_FILENO)
		__putchar = _eputchar;
	if (in < 0)
	{
		s = -in;
		__putchar('-');
		j++;
	}
	else
		s = in;
	cr = s;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (s / i)
		{
			__putchar('0' + cr / i);
			j++;
		}
		cr %= i;
	}
	__putchar('0' + cr);
	j++;

	return (j);
}
int _putfd(char c, int f)
{
        static int i;
        static char b[WB_SIZE];

        if (c == BUFSH || i >= WB_SIZE)
        {
                write(f, b, i);
                i = 0;
        }
        if (c != BUFSH)
                b[i++] = c;
        return (1);
}
