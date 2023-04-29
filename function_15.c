#include "main.h"
int unst_alias(inf_o *inf, char *s)
{
	char *p, i;
	int t;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	i = *p;
	*p = 0;
	t = delete_node_at_i(&(inf->alias),
		get_node_i(inf->alias, node_starts_with(inf->alias, s, -1)));
	*p = i;
	return (t);
}
int st_alias(inf_o *inf, char *s)
{
	char *p;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unst_alias(inf, s));

	unst_alias(inf, s);
	return (add_node_end(&(inf->alias), s, 0) == NULL);
}
int p_alias(lists_t *n)
{
	char *p = NULL, *s = NULL;

	if (n)
	{
		p = _strchr(n->str, '=');
		for (s = n->str; s <= p; s++)
			_putchar(*s);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
int malias(inf_o *inf)
{
	int j = 0;
	char *p = NULL;
	lists_t *n = NULL;

	if (inf->argc == 1)
	{
		n = inf->alias;
		while (n)
		{
			p_alias(n);
			n = n->next;
		}
		return (0);
	}
	for (j = 1; inf->argv[j]; j++)
	{
		p = _strchr(inf->argv[j], '=');
		if (p)
			st_alias(inf, inf->argv[j]);
		else
			p_alias(node_starts_with(inf->alias, inf->argv[j], '='));
	}

	return (0);
}
