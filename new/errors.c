#include "simple_shell.h"
/**
 * printErrorMessage - function that prints an error message
 * @info: pointer to the parameter & return info struct
 * @scset: pointer to string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise -1 if error.
 */
void printErrorMessage(d_info *info, char *scset)
{
	_eputs(info->filename);
	_eputs(": ");
	printDecimalNumber(info->linecount, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(scset);
}

/**
 * _erratoi - function converts a string to an integer
 * @s: pointer to the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise -1 if err occu
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
		if (s[i] >= '0' && s[i] <= '9')
			result *= 10, result += (s[i] - '0');
				if (result > INT_MAX)
					return (-1);
				else
					return (-1);
	return (result);
}
