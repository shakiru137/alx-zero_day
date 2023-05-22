#include "simple_shell.h"
/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	d_info info = {0};
	int fd = 2;
	int exit_status;

	asm volatile(
			"mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd)
			);

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				fprintf(stderr, "%s: 0: Can't open %s\n",
						av[0], av[1]);
				fflush(stderr);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info.readfd = fd;
	}

	populate_env_list(&info);
	read_history(&info);
	exit_status = shell_loop(&info, av);
	freeInfo(&info, 1);

	if (!interactive(&info) && info.status)
		exit(info.status);
	if (exit_status == -2)
		exit(info.error_num);
	return (EXIT_SUCCESS);
}

