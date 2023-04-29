#include "main.h"
int _strlen(char *s)
{
        int x = 0;

        if (!s)
                return (0);

        while (*s++)
                x++;
        return (x);
}
char *_strdup(const char *str)
{
	int v = 0;
	char *z;

	if (str == NULL)
		return (NULL);
	while (*str++)
		v++;
	z = malloc(sizeof(char) * (v + 1));
	if (!z)
		return (NULL);
	for (v++; v--;)
		z[v] = *--str;
	return (z);
}
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	for (x = 0; str[x] != '\0'; x++)
	{
		_putchar(str[x]);
	}
}
char *st_wi(const char *x, const char *n)
{
        while (*n)
                if (*n++ != *x++)
                        return (NULL);
        return ((char *)x);
}
int _putchar(char ch)
{
	static int x;
	static char b[WB_SIZE];

	if (ch == BUFSH || x >= WB_SIZE)
	{
		write(1, b, x);
		x = 0;
	}
	if (ch != BUFSH)
		b[x++] = ch;
	return (1);
}
