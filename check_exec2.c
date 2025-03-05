#include "mini_shell.h"

void	ft_check_exec(t_cmd *current, char **envp)
{
	char	*aux;
	int		i;

	while (current)
	{
		aux = ft_calloc(sizeof(char), 1);
		if (!aux)
			return ;
		i = 0;
		while (current->args[i])
		{
			if ((current->args[i + 1]) && (current->args[i][0] == '<'
				|| current->args[i][0] == '>'))
				ft_break_redir(current, current->args, &i);
			else
			{
				aux = ft_strjoin_gnl(aux, current->args[i]);
				aux = ft_strjoin_gnl(aux, " ");
				i++;
			}
		}
		current->cmd = ft_split(aux, 32);
		free(aux);
		ft_breack_check(current, envp);
		current = current->next;
	}
}
