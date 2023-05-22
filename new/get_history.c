#include "simple_shell.h"
/**
 * get_history_file - function that gets the history file
 * @info: pointer to the parameter struct
 * Return: allocated string containg history file
 */
char *get_history_file(d_info *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (dir == NULL)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) +
				_strlen(SHELL_HIST_FILE_NAME) + 2));
	if (buf == NULL)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, SHELL_HIST_FILE_NAME);
	return (buf);
}

/**
 * shell_loop - function that creates the main shell loop
 * @info: pointer to the parameter and return info structure
 * @av: the argument vector from main()
 *
 * Return:
 *	0 on success
 *	1 if an error occurs
 */
int shell_loop(d_info *info, char **av)
{
	ssize_t input_status = 0;  /* Status of input reading */
	int builtin_ret = 0;  /* Return value of built-in command execution */

	/* Main shell loop */
	while (input_status != -1 && builtin_ret != -2)
	{
	clearInfo(info);  /* Clear the info structure for each iteration */
	/* Display the prompt if the shell is running in interactive mode */
	if (interactive(info))
		_puts("$ ");
	_eputchar(FLUSH_BUFFER);  /* Flush the buffer */
	input_status = get_input(info);  /* Read user input */
	if (input_status != -1)
	{
	setInfo(info, av);  /* Set the info structure with input information */
	builtin_ret = find_built_in(info); /* Check if the cmd is a built-in */
	if (builtin_ret == -1)
		find_cmd(info);  /* Execute a non-built-in command */
	}
	else if (interactive(info))
	{
	_putchar('\n'); /* Print a newline if d shell is in interactive mode */
	}
	freeInfo(info, 0);  /* Free allocated memory in the info structure */
	}
	write_history(info);  /* Write command history to a file */
	freeInfo(info, 1);  /* Free remaining memory in the info structure */
	/* Handle shell termination conditions and exit */
	if (!interactive(info) && info->status)
	exit(info->status);
	if (builtin_ret == -2)
		if (info->error_num == -1)
			exit(info->status);
	exit(info->error_num);
	return (builtin_ret);
}

/**
 * read_history - function that reads history from file
 * @info: pointer to the parameter struct
 * Return: histcount on success, 0 if errror occur.
 */
int read_history(d_info *info)
{
	int i, linecount = 0, last = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= SHELL_MAX_REDORDS)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * write_history - function that creates a file, or appends to an existing file
 * @info: pointer the parameter struct
 * Return: 1 on success, -1 otherwise
 */
int write_history(d_info *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	d_list *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(FLUSH_BUFFER, fd);
	close(fd);
	return (1);
}

/**
 * build_history_list - function that adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: pointer to buffer
 * @linecount: var of the history linecount
 *
 * Return: Always 0
 */
int build_history_list(d_info *info, char *buf, int linecount)
{
	d_list *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}
