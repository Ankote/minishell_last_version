/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:21:32 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 17:55:00 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_child_process(int pid, t_list *list, int *stdin, int *fd)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (list->infile == -1)
			(close(fd[0]), close(fd[1]));
		if (list->infile == 1)
			(dup2(*stdin, STDIN_FILENO), close(*stdin));
		close(fd[0]);
		if (list->outfile != 1)
			dup2(list->outfile, 1);
		else if (list->next)
			(dup2(fd[1], 1), close(fd[1]));
		close(fd[1]);
		if (list->infile != -1 && check_if_builtin(list) == 1)
			main_execution(list);
		exit(g_dep.exit_status);
	}
}

void	ft_loop(t_list *list, int *fd, int *stdin, int *pid)
{
	if (list->infile == -1)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (list->infile != 0)
		dup2(list->infile, 0);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		g_dep.exit_status = ERROR;
		exit(g_dep.exit_status);
	}
	*pid = fork();
	ft_child_process(*pid, list, stdin, fd);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	ft_next_exec(t_list *list)
{
	t_list	*copy;
	int		stdin;
	int		fd[2];
	int		pid;

	stdin = dup(0);
	copy = list;
	while (list)
	{
		ft_loop(list, fd, &stdin, &pid);
		list = list->next;
	}
	while (copy)
	{
		if (copy->infile > 2)
			close(copy->infile);
		if (copy->outfile > 2)
			close(copy->outfile);
		copy = copy->next;
	}
	waitpid(pid, &g_dep.exit_status, 0);
	g_dep.exit_status = WEXITSTATUS(g_dep.exit_status);
	(close(0), dup2(stdin, 0), close(stdin));
	while (wait(NULL) != -1)
		;
}

void	child_process_single(t_list *list, int pid)
{
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (list->infile == -1 || list->outfile == -1)
			exit(1);
		if (list->outfile != 0)
			dup2(list->outfile, 1);
		if (list->infile != 0)
			dup2(list->infile, 0);
		main_execution(list);
	}
}

void	ft_exec(t_list *list)
{
	int	pid;

	if (ft_listsize(list) == 1)
	{
		if (!list->args)
			return ;
		if (check_if_builtin(list) == 1)
		{
			pid = 0;
			child_process_single(list, pid);
			waitpid(pid, &g_dep.exit_status, 0);
			if (g_dep.exit_status == 2)
				g_dep.exit_status = 130;
			else if (g_dep.exit_status == 3)
				g_dep.exit_status = 131;
			else
				g_dep.exit_status = WEXITSTATUS(g_dep.exit_status);
			while (wait(NULL) != -1)
				;
		}
	}
	else
		ft_next_exec(list);
}
