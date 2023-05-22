#include "simple_shell.h"
/**
 * clearInfo - functiton that initializes the d_info struct
 * @info: pointer to the d_info struct
 */
void clearInfo(d_info *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setInfo - initializes the d_info struct
 * @info: pointer to the d_info struct
 * @av: argument vector
 */
void setInfo(d_info *info, char **av)
{
	int i = 0;

	info->filename = av[0];
	if (info->arg)
	{
		info->argv = str_to_words(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * sigintHandler - Signal handler for SIGINT (Ctrl-C)
 * @sig_num: The signal number (unused)
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH_BUFFER);
}

/**
 * read_buf - function that reads a buffer
 * @info: pointer to the d_info struct
 * @buf: buffer
 * @i: size
 *
 * Return: r OR i
 */
ssize_t read_buf(d_info *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, INPUT_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * input_buf - buffers chained commands
 * @info: pointer to the d_info struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(d_info *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*free_block((void **)info->cmd_buffer);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if SYSTEM_GETLINE_USED
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}

			info->flag_of_linecunt = 1;
			removeCommentsFromCode(*buf);
			build_history_list(info, *buf, info->histcount++);
			if (_strchr(*buf, ';')) /* is this a command chain? */
			{
				*len = r;
				info->cmd_buffer = buf;
			}
		}
	}
	return (r);
}

