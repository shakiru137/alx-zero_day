#include "simple_shell.h"
/**
 * list_to_strings - function that returns an array of strings of the list->str
 * @head: pointer to first node of the list
 *
 * Return: array of strings
 */
char **list_to_strings(d_list *head)
{
	char **strs;
	char *str;
	d_list *node = head;
	size_t i = list_len(head), j;

	if (head == NULL || !i)
		return (NULL);

	strs = malloc(sizeof(char *) * (i + 1));
	if (strs == NULL)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (str == NULL)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * node_starts_with - function that return node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or NULL
 */
d_list *node_starts_with(d_list *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * add_node - function that adds a node to the begining of the list
 * @head: pointer to the first address of the list
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
d_list *add_node(d_list **head, const char *str, int num)
{
	d_list *new_head;

	if (head == NULL)
		return (NULL);
	new_head = malloc(sizeof(d_list));
	if (new_head == NULL)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(d_list));
	new_head->number = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - function that adds a node to the end of the list
 * @head: pointer to containing the address of the first node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
d_list *add_node_end(d_list **head, const char *str, int num)
{
	d_list *new_node, *node;

	if (head == NULL)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(d_list));
	if (new_node == NULL)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(d_list));
	new_node->number = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}

		return (new_node);
}
/**
 * free_list - function that frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: Nothing
 */
void free_list(d_list **head_ptr)
{
	d_list *node, *next_node, *head;

	if (head_ptr == NULL || *head_ptr == NULL)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
