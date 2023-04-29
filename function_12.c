#include "main.h"
lists_t *node_starts_with(lists_t *n, char *pre, char c)
{
        char *p = NULL;

        while (n)
        {
                p = st_wi(n->str, pre);
                if (p && ((c == -1) || (*p == c)))
                        return (n);
                n = n->next;
        }
        return (NULL);
}
int delete_node_at_i(lists_t **h, unsigned int i)
{
        lists_t *n, *old;
        unsigned int j = 0;

        if (!h || !*h)
                return (0);

        if (!i)
        {
                n = *h;
                *h = (*h)->next;
                free(n->str);
                free(n);
                return (1);
        }
        n = *h;
        while (n)
        {
                if (j == i)
                {
                        old->next = n->next;
                        free(n->str);
                        free(n);
                        return (1);
                }
                i++;
                old = n;
                n = n->next;
        }
        return (0);
}
lists_t *add_node(lists_t **h, const char *str, int n)
{
        lists_t *new;

        if (!h)
                return (NULL);
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
        new->next = *h;
        *h = new;
        return (new);
}
ssize_t get_node_i(lists_t *head, lists_t *n)
{
        size_t j = 0;

        while (head)
        {
                if (head == n)
                        return (j);
                head = head->next;
                j++;
        }
        return (-1);
}
void sinthand(__attribute__((unused))int si)
{
         _puts("\n");
         _puts("$ ");
         _putchar (BUFSH);
}
void fr_list(lists_t **h_ptr)
{
        lists_t *n, *h, *new;

        if (!*h_ptr || !h_ptr)
                return;
        h = *h_ptr;
        n = h;
        while (n)
        {
                new = n->next;
                free(n->str);
                free(n);
                n = new;
        }
        *h_ptr = NULL;
}
size_t p_list(const lists_t *head)
{
        size_t j = 0;

        while (head)
        {
                _puts(conv_n(head->n, 10, 0));
                _putchar(':');
                _putchar(' ');
                _puts(head->str ? head->str : "(nil)");
                _puts("\n");
                head = head->next;
                j++;
        }
        return (j);
}
