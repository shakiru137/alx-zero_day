#include "simple_shell.h"
/**
 * _setenv - initialize a new environment variable or modify an existing one
 * @info: structure containing potential arguments used to maintain
 * constant function prototype.
 * @var: string enviroment variable property
 * @value: string enviroment variable value.
 *  Return: 0 Always.
 */
int _setenv(d_info *info, char *var, char *value)
{
	d_list *node;
	char *buf = NULL;
	char *p;

	if (var == NULL || value == NULL)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 1);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env_vars;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}

		node = node->next;
	}
	add_node_end(&(info->env_vars), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments used to maintain
 * constant function prototype.
 * Return: Always 0
 */
char **get_environ(d_info *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env_vars);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - to remove an environment variable
 * @info: structure containing potential arguments used to maintain
 * constant function prototype.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(d_info *info, char *var)
{
	d_list *node = info->env_vars;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed =
				delete_node_at_index(&(info->env_vars), i);
			i = 0;
			node = info->env_vars;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * *_strcat - function that concatenates two string
 * @dest: first variable
 * @src: second variable
 * Return: character
 */

char *_strcat(char *dest, char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
	{

	}
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strchr - function that locates a character in string.
 * @s: pointer pointing to string
 * @c: character to be located
 * Return: character specified.
 */

char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; s[i] >= '\0'; i++)
	{
		if (s[i] == c)
			return (&s[i]);
	}
	return (0);
}
