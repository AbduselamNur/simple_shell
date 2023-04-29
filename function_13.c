#include "main.h"
int main(int ac, char **av)
{
        inf_o inf[] = { INF_IN };
        int fd = 2;

        asm ("mov %1, %0\n\t"
                "add $3, %0"
                : "=r" (fd)
                : "r" (fd));

        if (ac == 2)
        {
                fd = open(av[1], O_RDONLY);
                if (fd == -1)
                {
                        if (errno == EACCES)
                                exit(126);
                        if (errno == ENOENT)
                        {
                                _eputs(av[0]);
                                _eputs(": 0: Can't open ");
                                _eputs(av[1]);
                                _eputchar('\n');
                                _eputchar(BUFSH);
                                exit(127);
                        }
                        return (EXIT_FAILURE);
                }
                inf->readfd = fd;
        }
        penv_list(inf);
        r_hist(inf);
        arg_loop(inf, av);
        return (EXIT_SUCCESS);
}
size_t l_len(const lists_t *head)
{
        size_t j = 0;

        while (head)
        {
                head = head->next;
                j++;
        }
        return (j);
}
lists_t *add_node_end(lists_t **h, const char *str, int n)
{
	lists_t *new, *on;

	if (!h)
		return (NULL);

	on = *h;
	new = malloc(sizeof(lists_t));
	if (!new)
		return (NULL);
	memset((void *)new, 0, sizeof(lists_t));
	new->n = n;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (on)
	{
		while (on->next)
			on = on->next;
		on->next = new;
	}
	else
		*h = new;
	return (new);
}
char **l_to_s(lists_t *head)
{
        lists_t *n = head;
        size_t i = l_len(head), k;
        char **tr;
        char *st;

        if (!head || !i)
                return (NULL);
        tr = malloc(sizeof(char *) * (i + 1));
        if (!tr)
                return (NULL);
        for (i = 0; n; n = n->next, i++)
        {
                st = malloc(_strlen(n->str) + 1);
                if (!st)
                {
                        for (k = 0; k < i; k++)
                                free(tr[i]);
                        free(tr);
                        return (NULL);
                }

                st = _strcpy(st, n->str);
                tr[i] = st;
        }
        tr[i] = NULL;
        return (tr);
}
size_t p_list_str(const lists_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}
