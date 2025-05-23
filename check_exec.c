/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:43:18 by owmarqui          #+#    #+#             */
/*   Updated: 2025/05/08 13:14:40 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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
		perror ("falla el infile");
	else if (crt->outfile && (!crt->outfile[0] || !crt->outfile[1]))
		perror ("falla el outfile");
	else if (crt->infile && crt->infile[0][1] == '<'
		&& crt->infile[0][0] == '<')
		if (crt->dl_hd && !crt->dl_hd[0])
			perror ("falla el heredoc, el dl");
}

void	ft_break_dl(t_cmd *current, int *i)
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

void	ft_process_single_redir(t_cmd *current, char **args, int *i)
{
	char	*aux;
	int		file;

	aux = ft_strjoin(args[*i], " ");
	aux = ft_strjoin_gnl(aux, args[*i + 1]);
	if (current->args[*i][0] == '<')
	{
		if (current->args[*i][1] == '<')
			ft_break_dl(current, i);
		if (current->infile)
			ft_free_double(current->infile);
		current->infile = ft_split(aux, 32);
	}
	if (current->args[*i][0] == '>')
	{
		if (current->outfile)
			ft_free_double(current->outfile);
		current->outfile = ft_split(aux, 32);
		file = ft_open(args[*i + 1], O_WRONLY | O_CREAT | O_TRUNC);
		close(file);
	}
	(*i) += 2;
	free(aux);
}

void	ft_break_redir(t_cmd *current, char **args, int *i)
{
	ft_process_single_redir(current, args, i);
	if ((current->args[*i]) && (current->args[*i + 1])
		&& (current->args[*i][0] == '<' || current->args[*i][0] == '>'))
		ft_break_redir(current, args, i);
}
