#include "simple_shell.h"
/**
 * _puts - Function that print a string
 * @str: Pointer variable
 * Return: void
 */

void _puts(char *str)
{
	while (*str)
	{
		_putchar(*str);
		str++;
	}
}

/**
 * _strdup - function that duplicates a string
 * @str: pointer to string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * *_strcpy - Entry point
 * Description: Copies string pointed to by src
 * @dest: Character
 * @src: Character
 * Return: char
 */
char *_strcpy(char *dest, char *src)
{
	char *p = dest;

	while (*src != '\0')
	{
		*p++ = *src++;
	}
	*p = '\0';
	return (dest);
}


/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[OUTPUT_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= OUTPUT_BUFFER_SIZE)
		write(1, buf, i), i = 0;
	if (c != FLUSH_BUFFER)
		buf[i++] = c;

	return (1);
}
