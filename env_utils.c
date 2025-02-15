#include "mini_shell.h"

// estructur hecha de momento para esto
/*typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;
*/

size_t	count_envs(t_env *envs)
{
	size_t	i;
	t_env	*tmp;

	i = 0;
	tmp = envs;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**format_env(t_env *envs)
{
	size_t	i;
	t_env	*tmp;
	char	*key;
	char	**output;

	i = count_envs(envs);
	output = malloc(sizeof(char *) * (i + 1));
	if (!output)
		return (NULL);
	i = 0;
	tmp = envs;
	while (tmp)
	{
		key = ft_strjoin(tmp->key, "=");
		output[i] = ft_strjoin(key, tmp->value);
		free(key);
		i++;
		tmp = tmp->next;
	}
	output[i] = NULL;
	return (output);
}

int	ft_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	perror("There is no PATH defined in the enviroment\n"); //mejorable
	return (i);
}



// aqui esta mas o menos el if que seria para remplazar el key
/*if (ft_strchr(token, '$'))
		token = ft_replace_env_var();*/