#include "mini_shell.h"

int	ft_execute_built(t_cmd *cmd, t_env **env)
{
	int	pipex[2];

	ft_pipe(pipex);
	if (!ft_fork())
	{
		close(pipex[READ]);
		if (cmd->outfile)
			ft_outfile(cmd, STDOUT_FILENO);
		else
			dup2(pipex[WRITE], STDOUT_FILENO);
		close(pipex[WRITE]);
		ft_echo_env_pwd(cmd, env);
		exit(0);
	}
	close(pipex[WRITE]);
	return (pipex[READ]);
}

int	ft_builtin(t_cmd *cmd, t_env **env, int len)
{
	if (ft_strcmp(cmd->name_cmd, "echo") == 0 || \
		ft_strcmp(cmd->name_cmd, "env") == 0 || \
		ft_strcmp(cmd->name_cmd, "pwd") == 0)
	{
		if ((len == 1 || !cmd->next) && (cmd->outfile == NULL))
			ft_echo_env_pwd(cmd, env);
		else
			return (ft_execute_built(cmd, env));
	}
	else if (len == 1)
		ft_cd_exit_export_unset(cmd, env);
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
