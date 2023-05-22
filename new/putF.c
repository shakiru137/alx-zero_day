#include "simple_shell.h"
/**
 * _putsfd - function that prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (str == NULL)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}

/**
 * _eputchar - function that writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[OUTPUT_BUFFER_SIZE];

	if (i >= OUTPUT_BUFFER_SIZE || c == FLUSH_BUFFER)
		write(2, buf, i), i = 0;
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}

/**
 * _eputs - function that prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (str == NULL)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _putfd - functon that writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[OUTPUT_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= OUTPUT_BUFFER_SIZE)
		write(fd, buf, i), i = 0;
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}
