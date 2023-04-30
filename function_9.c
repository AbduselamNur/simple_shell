#include "main.h"
void _eputs(char *x)
{
        int n = 0;

        if (!x)
                return;
        for (n = 0; x[n] != '\0'; n++)
                _eputchar(x[n]);
}
int _eatoi(char *x)
{
	int i;
	unsigned long int a;
       a = 0;
       i = 0;

	if (*x == '+')
		x++;
	i = 0;
	while (x[i] != '\0')
	{
		if (x[i] >= '0' && x[i] <= '9')
		{
			a *= 10;
			a += (x[a] - '0');
			if (a > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	return (a);
}
void p_err(inf_o *var, char *x)
{
	_eputs(var->fn);
	_eputs(": ");
	p_d(var->lcount, STDERR_FILENO);
	_eputs(": ");
	_eputs(var->argv[0]);
	_eputs(": ");
	_eputs(x);
}
int p_d(int x, int y)
{
	int (*__putchar)(char) = _putchar;
	int i;
        int j;
	unsigned int p;
       unsigned int cr;
       j = 0;

	if (y == STDERR_FILENO)
		__putchar = _eputchar;
	if (x < 0)
	{
		p = -x;
		__putchar('-');
		j++;
	}
	else
		p = x;
	cr = p;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (p / i)
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
int _putfd(char ch, int n)
{
        static int x;
        static char v[WB_SIZE];

        if (ch == BUFSH || x >= WB_SIZE)
        {
                write(n, v, x);
                x = 0;
        }
        if (ch != BUFSH)
                v[x++] = ch;
        return (1);
}
