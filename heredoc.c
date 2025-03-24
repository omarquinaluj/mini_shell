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

void ft_heredoc(t_cmd *current, int file, t_env **envs)
{
    char *line;
    int i = 0;

    if (!current->dl_hd)
    {
        perror("Error con el delimitador");
        return;
    }
    
    // Aquí iniciamos el ciclo de lectura de las líneas
    while ((line = readline("> ")))
    {
        if (g_sig)  // Si la señal fue recibida, salimos del ciclo
            break;
        
        if (ft_strncmp(line, current->dl_hd[i], ft_strlen(line) + 1) == 0)
            i++;
        
        if (!current->dl_hd[i])  // Si hemos llegado al final del delimitador, salimos
            break;
        
        if (!current->dl_hd[i + 1])  // Si el próximo delimitador está vacío, procesamos la línea
            ft_heredoc_write(line, file, envs);
        
        free(line);
    }
    free(line);
    
    // Si g_sig es 1, significa que la señal SIGINT interrumpió el proceso
    if (g_sig)
    {
        close(file);          // Cerramos el archivo
        unlink(current->pth_hd);  // Borramos el archivo temporal
        free(current->pth_hd);    // Liberamos el puntero
        current->pth_hd = NULL;
    }
}

// Función para manejar la escritura de líneas en un archivo durante el heredoc
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
            if (!var)
            {
                perror("Error en ft_substr");
                return;
            }

            t_env *env_node = find_env_node(envs, var);
            if (env_node)
                ft_putstr_fd(env_node->value, file);
            
            free(var);
        }
        else
            write(file, &ln[j++], 1);
    }
    write(file, "\n", 1);
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
        {
            perror("Error en ft_itoa");
            return NULL;
        }
        name = ft_strjoin("/tmp/hd_", num);
        free(num);
        if (!name)
        {
            perror("Error en ft_strjoin");
            return NULL;
        }
        if (access(name, F_OK) != 0) // Si el archivo no existe, lo retornamos
            return name;
        free(name);
        i++;
    }
    return NULL;
}

void ft_init_heredoc(t_cmd *current, t_env **envs)
{
    int fd;

    signal(SIGINT, sigint_heredoc_handler);  // Manejamos SIGINT para heredar líneas
    while (current)
    {
        if (current->infile && current->infile[0][1] == '<' && current->infile[0][0] == '<')
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
            ft_heredoc(current, fd, envs);  // Llamamos a la función para procesar el heredoc
            if (g_sig)  // Si la señal fue capturada, hacemos limpieza
            {
                //close(fd);
                //unlink(current->pth_hd);
                //free(current->pth_hd);
                //current->pth_hd = NULL;
                break;
            }
            close(fd);
        }
        current = current->next;
    }
    signal(SIGINT, main_signal);  // Restablecemos el manejador de SIGINT
}
