#include "simple_shell.h"
/**
 * list_len - function that determines length of linked list
 * @h: pointer to first node containing first address
 *
 * Return: Number of node present in the linked list
 */
size_t list_len(const d_list *h)
{
	size_t i = 0;

	while (h != NULL)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * print_list - function that prints all elements of a d_list linked list
 * @h: pointer to first node
 *
 * Return: Number of node present in the linked list
 */
size_t print_list(const d_list *h)
{
	size_t i = 0;

	while (h != NULL)
	{
		_puts(convertNumberToBase(h->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * get_node_index - function that gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(d_list *head, d_list *node)
{
	size_t i = 0;

	while (head != NULL)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * print_list_str - prints only the str element of a d_list linked list
 * @h: pointer to first node
 *
 * Return: Number of node present in the linked list
 */
size_t print_list_str(const d_list *h)
{
	size_t i = 0;

	while (h != NULL)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - function that deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(d_list **head, unsigned int index)
{
	unsigned int i = 0;
	d_list *node, *prev_node;

	if (head == NULL || *head == NULL)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
