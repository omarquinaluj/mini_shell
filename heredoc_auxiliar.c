#include "mini_shell.h"

void	auxiliar_heredoc(char **line, t_cmd *current, int file, t_env **envs)
{
	signal(SIGINT, sigint_heredoc_handler);
	g_sig = 0;
	*line = readline("> ");
	while (*line)
	{
		if (g_sig == 2)
			break ;
		if (line && current->dl_hd[0]
			&& ft_strncmp(*line, current->dl_hd[0],
				ft_strlen(current->dl_hd[0]) + 1) == 0)
			break ;
		ft_heredoc_write(*line, file, envs);
		free (*line);
		*line = readline("> ");
	}
	free (*line);
	exit(0);
}

void	auxiliar_heredoc_write(int *j, int *start, char *line)
{
	(*j)++;
	*start = *j;
	while (line[*j] && line[*j] != ' '
		&& line[*j] != '"' && line[*j] != '\'')
		(*j)++;
}