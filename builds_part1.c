/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builds_part1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owmarqui <owmarqui@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:08:44 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/06 14:08:46 by owmarqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_wait_last_builtin(pid_t pid, t_shell *shell)
{
	int	status;

	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = 128 + WTERMSIG(status);
	}
}

int	ft_outfile2(t_cmd *ps)
{
	int	fd;

	if (!ps->outfile || !ps->outfile[0])
		return (0);

	if (ps->outfile[0][0] == '>' && ps->outfile[0][1] == '>')
		fd = ft_open(ps->outfile[1], O_WRONLY | O_CREAT | O_APPEND);
	else
		fd = ft_open(ps->outfile[1], O_WRONLY | O_CREAT | O_TRUNC);

	if (fd == -1)
		return (-1);

	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}


int	ft_infile2(t_cmd *ps)
{
	int	fd;

	if (!ps->infile || !ps->infile[0])
		return (0);

	if (ps->infile[0][0] == '<' && ps->infile[0][1] == '<')
		fd = ft_open(ps->pth_hd, O_RDONLY);
	else
		fd = ft_open(ps->infile[1], O_RDONLY);

	if (fd == -1)
		return (-1);

	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	revise_files(t_cmd *cmd, t_shell *shell)
{
	if (cmd->infile)
	{
		if (ft_infile2(cmd) == -1)
		{
			shell->exit_status = 1;
			return (1);
		}
	}
	if (cmd->outfile)
	{
		if (ft_outfile2(cmd) == -1)
		{
			return (1);
		}
	}
	return (0);
}
int	ft_execute_built(t_cmd *cmd, t_env **env, t_shell *shell)
{
	pid_t	pid;
	int		pipex[2];

	ft_pipe(pipex);
	pid = fork();
	if (pid == 0)
	{
		close(pipex[READ]);
		if (revise_files(cmd, shell) == 1)
			exit(1);
		if (!cmd->outfile)
			dup2(pipex[WRITE], STDOUT_FILENO);
		close(pipex[WRITE]);
		ft_echo_env_pwd(cmd, env, shell);
		exit(0);
	}
	close(pipex[WRITE]);
	return (pid);
}

int	ft_builtin(t_cmd *cmd, t_env **env, int len, t_shell *shell)
{
	pid_t	pid;

	pid = -1;
	if (ft_strcmp(cmd->name_cmd, "echo") == 0 || \
		ft_strcmp(cmd->name_cmd, "env") == 0 || \
		ft_strcmp(cmd->name_cmd, "pwd") == 0)
	{
		if ((len == 1 || !cmd->next) && (cmd->outfile == NULL && cmd->infile == NULL))
			ft_echo_env_pwd(cmd, env, shell);
		else
			pid = ft_execute_built(cmd, env, shell);
	}
	else if (len == 1)
		ft_cd_exit_export_unset(cmd, env, shell);
	ft_wait_last_builtin(pid, shell);
	return (STDIN_FILENO);
}

int	is_builtin(t_cmd *cmd)
{
	if (cmd->name_cmd == NULL)
		return (0);
	else if (ft_strcmp(cmd->name_cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->name_cmd, "unset") == 0)
		return (1);
	return (0);
}
