#include "simple_shell.h"
/**
 * *_strncat - function that concatenates two strings
 * @dest: array to copy to
 * @src: array to copy from
 * @n: n string to be concatenate.
 * Return: pointer to dest.
 */

char *_strncat(char *dest, char *src, int n)
{
	int i = 0;
	int j = 0;

	while (dest[i] != '\0')
	{
		i++;
	}
	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}

	return (dest);
}

/**
 * *_strncpy - function that copy a string
 * @dest: array to copy to
 * @src: array to copy from
 * @n: n string to be copied
 * Return: dest.
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/**
 * _strcmp - function that compare two strings
 * @s1: first string variable
 * @s2: second string variable
 * Return: int value.
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int j = 0;

	while (s1[i] != '\0' && s2[j] != '\0')
	{
		if (s1[i] != s2[j])
		{
			return (s1[i] - s2[j]);
		}
		i++;
		j++;
	}
	return (0);
}

/**
 * _strlen - Returns the length of a string.
 * @s: The string to get the length of
 * Return: The length of @str.
 */

size_t _strlen(const char *s)
{
	size_t length = 0;

	while (*s++)
		length++;

	return (length);
}

/**
 * starts_with - function that checks if needle starts with haystack
 * @haystack: pointer to string to search
 * @needle: pointer to substring to find
 * Return: address of next char of haystack or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

