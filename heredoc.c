/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:55:39 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/20 12:00:45 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_heredoc_write(char *line, int file, t_env **envs)
{
	t_env	*env_node;
	char	*var;
	int		start;
	int		j;

	start = 0;
	j = 0;
	while (line[j])
	{
		if (line[j] == '$')
		{
			auxiliar_heredoc_write(&j, &start, line);
			var = ft_substr(line, start, j - start);
			if (!var)
				return (perror("Error en ft_substr"));
			env_node = find_env_node(envs, var);
			if (env_node)
				ft_putstr_fd(env_node->value, file);
			free(var);
		}
		else
			write(file, &line[j++], 1);
	}
	write(file, "\n", 1);
}

void	ft_heredoc(t_cmd *current, int file, t_shell *shell)
{
	char	*line;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
		auxiliar_heredoc(&line, current, file, shell);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			shell->exit_status = 128 + SIGINT;
			close(file);
		}
		else if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
}

char	*ft_temp_name(void)
{
	char	*name;
	char	*num;
	int		i;

	i = 0;
	while (i != 2147483647)
	{
		num = ft_itoa(i);
		if (!num)
			return (perror("Error en ft_itoa"), NULL);
		name = ft_strjoin("/tmp/hd_", num);
		free(num);
		if (!name)
			return (perror("Error en ft_strjoin"), NULL);
		if (access(name, F_OK) != 0)
			return (name);
		free(name);
		i++;
	}
	return (NULL);
}

void	ft_init_heredoc(t_cmd *current, t_shell *shell)
{
	int	fd;

	signal(SIGINT, sigint_heredoc_handler);
	while (current)
	{
		if (current->infile && current->infile[0][1] == '<' &&
			current->infile[0][0] == '<')
		{
			current->pth_hd = ft_temp_name();
			if (!current->pth_hd)
			{
				perror("Error creando archivo temporal");
				return ;
			}
			fd = open(current->pth_hd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd < 0)
			{
				perror("Error al abrir archivo temporal");
				return ;
			}
			ft_heredoc(current, fd, shell);
			close(fd);
		}
		current = current->next;
	}
}
