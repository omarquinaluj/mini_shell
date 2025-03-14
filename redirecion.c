/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexander <alexander@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 08:20:35 by alexander         #+#    #+#             */
/*   Updated: 2025/03/03 12:40:34 by alexander        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

char	*custom_strtok(char *str, const char *delim)
{
	static char	*saved_str;
	char *token_start;

	saved_str = NULL;
	if (str)
		saved_str = str;
	if (!saved_str || *saved_str == '\0')
		return (NULL);

	token_start = saved_str;
	while (*saved_str && strchr(delim, *saved_str))
		saved_str++;
	if (*saved_str == '\0')
		return (NULL);

	token_start = saved_str;
	while (*saved_str && !strchr(delim, *saved_str))
		saved_str++;

	if (*saved_str)
	{
		*saved_str = '\0';
		saved_str++;
	}
	return token_start;
}

char	*find_executable(char *command)
{
	char		*path_copy;
	char		*dir;
	char		*path;
	int			aux;
	static char	full_path[256];

	aux = access(command, X_OK);
	if (aux == 0)
		return (command);

	path = getenv("PATH");
	if (!path)
		return (NULL);
	path_copy = strdup(path);
	dir = custom_strtok(path_copy, ":");

	while (dir)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = custom_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

int	handle_heredoc(const char *delimiter)
{
	int		pipe_fd[2];
	int		aux;
	char	buffer[1024];

	aux = pipe(pipe_fd);
	if (aux == -1)
	{
		perror("pipe");
		return (-1);
	}
	printf("[heredoc] Introduce líneas. Finaliza con '%s'.\n", delimiter);
	while (1)
	{
		printf("heredoc> ");
		fflush(stdout);
		if (!fgets(buffer, sizeof(buffer), stdin))
			break ;
		buffer[strcspn(buffer, "\n")] = 0;
		if (strcmp(buffer, delimiter) == 0)
			break ;
		write(pipe_fd[1], buffer, strlen(buffer));
		write(pipe_fd[1], "\n", 1);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	execute_command(char *command)
{
	char	*args[64];
	char	*input_file;
	char	*output_file;
	char	*heredoc_delim;
	char	*token;
	int		append;
	int		i;
	char	*exec_path
	pid_t	pid;
	int		fd;
	int		heredoc_fd;

	*input_file = NULL;
	*output_file = NULL;
	*heredoc_delim = NULL;
	append = 0;
	i = 0;
	token = custom_strtok(command, " ");
	while (token != NULL)
	{
		if (strcmp(token, ">>") == 0)
		{
			append = 1;
			token = custom_strtok(NULL, " ");
			output_file = token;
		}
		else if (strcmp(token, ">") == 0)
		{
			append = 0;
			token = custom_strtok(NULL, " ");
			output_file = token;
		}
		else if (strcmp(token, "<<") == 0)
		{
			token = custom_strtok(NULL, " ");
			heredoc_delim = token;
		}
		else if (strcmp(token, "<") == 0)
		{
			token = custom_strtok(NULL, " ");
			input_file = token;
		}
		else
		{
			args[i++] = token;
		}
		token = custom_strtok(NULL, " ");
	}
	args[i] = NULL;
	exec_path = find_executable(args[0]);
	if (!exec_path)
	{
		fprintf(stderr, "Comando no encontrado: %s\n", args[0]);
		return ;
	}

	pid = fork();
	if (pid == 0) 
	{ // Proceso hijo
		if (output_file)
		{
			fd = open(output_file, O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), 0644);
			if (fd < 0)
			{
				perror("open output file");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if (input_file)
		{
			fd = open(input_file, O_RDONLY);
			if (fd < 0)
			{
				perror("open input file");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (heredoc_delim)
		{
			heredoc_fd = handle_heredoc(heredoc_delim);
			if (heredoc_fd != -1)
			{
				dup2(heredoc_fd, STDIN_FILENO);
				close(heredoc_fd);
			}
		}
		execve(exec_path, args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{// Proceso padre
		wait(NULL);
	}
	else
	{
		perror("fork");
	}
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <comando>", argv[0]);
        return EXIT_FAILURE;
    }
    
    char command[256];
    strcpy(command, argv[1]);
    for (int i = 2; i < argc; i++) {
        strcat(command, " ");
        strcat(command, argv[i]);
    }
    
    execute_command(command);
    return 0;
}
