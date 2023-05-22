#include "simple_shell.h"
/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(d_info *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			freeInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printErrorMessage(info, "Permission denied\n");
		}
	}
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(d_info *info)
{
	d_list *node = info->history;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next;
	}
	return (info->histcount = i);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(d_info *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->flag_of_linecunt == 1)
	{
		info->linecount++;
		info->flag_of_linecunt = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printErrorMessage(info, "not found\n");
		}
	}
}

/**
 * find_built_in - finds a built-in command
 * @info: pointer to the parameter and return info structure
 *
 * Return:
 *	-1 if built-in command is not found,
 *	0 if built-in command executed successfully,
 *	1 if built-in command found but not successful,
 *	2 if built-in command signals exit()
 */
int find_built_in(d_info *info)
{
	int i;
	int built_in_ret = -1;


	/* Array of built-in commands and their functions */
	built_in_table builtintbl[] = {
		{"exit", exit_shell},
		{"env_vars", ENV_VARS},
		{"help", get_help},
		{"history", get_history},
		{"setenv", mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", change_dir},
		{"alias", get_alias},
		{NULL, NULL}
	};

	/* Iterate through the built-in table to find a match forthe command */
	for (i = 0; builtintbl[i].type != NULL; i++)
	{
		/* Compare the command with the current entry in the table */
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->linecount++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	}

	return (built_in_ret);
}
