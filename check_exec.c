/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:43:18 by owmarqui          #+#    #+#             */
/*   Updated: 2025/03/25 08:24:10 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_check_path(t_cmd *current, char **envp)
{
	int		i;
	char	**env_path;
	char	*path;
	char	*path_cmd;

	i = ft_path(envp);
	env_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (env_path[++i])
	{
		path = ft_strjoin(env_path[i], "/");
		path_cmd = ft_strjoin(path, current->cmd[0]);
		free(path);
		if (access(path_cmd, X_OK) == 0)
		{
			current->pth_cmd = ft_strdup(path_cmd);
			free(path_cmd);
			ft_free_double(env_path);
			return (0);
		}
		free(path_cmd);
	}
	ft_free_double(env_path);
	return (1);
}

int	ft_check_cmd(t_cmd *current, char **envp)
{
	if (access(current->cmd[0], X_OK) != 0)
		return (ft_check_path(current, envp));
	else
	{
		current->pth_cmd = ft_strdup(current->cmd[0]);
		if (!current->pth_cmd)
			return (1);
		return (0);
	}
}

void	ft_breack_check(t_cmd *crt, char **envp, t_shell *shell)
{
	if (((crt->cmd && !crt->cmd[0]) || (ft_check_cmd(crt, envp) != 0))
		&& (!(is_builtin(crt) || (is_arrows(crt)))))
		error_st(crt->name_cmd, "command not found", 127, shell);
	else if (crt->infile && (!crt->infile[0] || !crt->infile[1]))
		perror ("falla el infile");//status = 127;
	else if (crt->outfile && (!crt->outfile[0] || !crt->outfile[1]))
		perror ("falla el outfile");//status = 127;
	else if (crt->infile && crt->infile[0][1] == '<'
		&& crt->infile[0][0] == '<')
		if (crt->dl_hd && !crt->dl_hd[0])
			perror ("falla el heredoc, el dl");//status = 127;		
}

void	ft_break_dl(t_cmd *current, int *i)//funciones para heredoc
{
	char	*aux;
	int		j;

	aux = ft_calloc(sizeof(char), 1);
	if (!aux)
		return ;
	j = 0;
	while (current->dl_hd && current->dl_hd[j])
	{
		aux = ft_strjoin_gnl(aux, current->dl_hd[j]);
		aux = ft_strjoin_gnl(aux, " ");
		free(current->dl_hd[j]);
		j++;
	}
	free(current->dl_hd);
	aux = ft_strjoin_gnl(aux, current->args[*i + 1]);
	aux = ft_strjoin_gnl(aux, " ");
	current->dl_hd = ft_split(aux, 32);
	free(aux);
}

void	ft_break_redir(t_cmd *current, char **args, int *i)
{
	char	*aux;
	int		file;

	aux = ft_strjoin(args[*i], " ");
	aux = ft_strjoin_gnl(aux, args[*i + 1]);
	if (current->args[*i][0] == '<')
	{
		if (current->args[*i][1] == '<')
			ft_break_dl(current, i);
		else if (access(args[*i + 1], F_OK) == -1)
			perror (args[*i]);
		current->infile = ft_split(aux, 32);
	}
	if (current->args[*i][0] == '>')
	{
		current->outfile = ft_split(aux, 32);
		file = ft_open(args[*i + 1], O_WRONLY | O_CREAT | O_TRUNC);
		close(file);
	}
	(*i) += 2;
	free(aux);
	if ((current->args[*i]) && (current->args[*i + 1])
		&& (current->args[*i][0] == '<' || current->args[*i][0] == '>'))
		ft_break_redir(current, args, i);
}
