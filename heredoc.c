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

void ft_heredoc_write(char *ln, int file, t_env **envs)
{
    char *var;
    int start = 0, j = 0;
    while (ln[j])
    {
        if (ln[j] == '$')
        {
            j++;
            start = j;
            while (ln[j] && ln[j] != ' ' && ln[j] != '"' && ln[j] != '\'')
                j++;
            var = ft_substr(ln, start, j - start);
            if (var)
            {
                t_env *env_node = find_env_node(envs, var);
                if (env_node)
                    ft_putstr_fd(env_node->value, file);
                free(var);
            }
        }
        else
            write(file, &ln[j++], 1);
    }
    write(file, "\n", 1);
}

void ft_heredoc(t_cmd *current, int file, t_env **envs)
{
    char *line;
    int i;

    i = 0;
    g_minishell.heredoc = 0;
     if (!current->dl_hd)
    {
        perror("Error con el delimitador");
        return;
    }
    while ((line = readline("> ")))
    {
        if (g_minishell.heredoc) // Si Ctrl+C se presionó, salir del loop
        {
            free(line);
            break;
        }

        if (ft_strncmp(line, current->dl_hd[i], ft_strlen(line) + 1) == 0)
            i++;

        if (!current->dl_hd[i]) // Si se llegó al delimitador final, salir
        {
            free(line);
            break;
        }

        if (!current->dl_hd[i + 1]) // Si estamos listos para escribir
            ft_heredoc_write(line, file, envs);

        free(line);
    }
}



char *ft_temp_name(void)
{
    char *name;
    char *num;
    int i = 0;

    while (i != 2147483647)
    {
        num = ft_itoa(i);
        if (!num)
            return (NULL);
        name = ft_strjoin("/tmp/hd_", num);
        free(num);  // Liberamos `num` inmediatamente después de usarlo
        if (!name)
            return (NULL);
        if (access(name, F_OK) != 0)  // Si el archivo no existe
            return (name);
        free(name);
        i++;
    }
    return (NULL);
}

void	ft_init_heredoc(t_cmd *current, t_env **envs)
{

	int fd;

	//g_minishell.signal_heredoc = 1;  // Indicamos que estamos en heredoc
	signal(SIGINT, sigint_heredoc_handler);  // Activamos el manejador de señales para heredoc
    g_minishell.signal_heredoc = 1;
	while (current)
	{
		if (current->infile && current->infile[0][1] == '<'
				&& current->infile[0][0] == '<')
		{
			current->pth_hd = ft_temp_name();
			if (!current->pth_hd)
			{
				perror("Error creando archivo temporal");
				return;
			}
			fd = open(current->pth_hd, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (fd < 0)
			{
				perror("Error al abrir archivo temporal");
				return;
			}
			ft_heredoc(current, fd, envs);
			// 🔴 Si `Ctrl+C` interrumpió heredoc, salimos del bucle
			if (g_minishell.heredoc)
			{  // Resetear flag de interrupción
				break;
			}
            close(fd);
		}
		current = current->next;
	}
	signal(SIGINT, main_signal);
	g_minishell.signal_heredoc = 0;
}

