/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:53:17 by rakropp           #+#    #+#             */
/*   Updated: 2024/10/14 10:39:10 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	how_many_overwrite(t_data *data, char **str)
{
	int	c;
	int	i;
	int	t;

	c = 0;
	t = 0;
	while (data->env[c])
	{
		i = 0;
		while (str[i])
		{
			if (ms_strncmp(data->env[c], str[i], ms_strlen(str[i])) == '=')
				t++;
			i++;
		}
		c++;
	}
	return (t);
}

void	env_free(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
	env = NULL;
}

int	how_much_less(t_data *data, char **str)
{
	int	c;
	int	i;
	int	t;

	c = 0;
	t = 0;
	while (data->env[c])
	{
		i = 0;
		while (str[i])
		{
			if (ms_strncmp(data->env[c], str[i], ms_strlen(str[i])) == 0)
				t++;
			i++;
		}
		c++;
	}
	return (c - t);
}

char	**rm_env(t_data *data, char **str) // needs to check if the ones counted acctully can be removed
{
	int		c;
	int		i;
	int		t;
	int		g;
	char	**ret;

	c = 0;
	i = 0;
	ret = malloc((how_much_less(data, str) + 1)* sizeof(char *));
	if (!ret)
		ms_error(data, "eidexe/envp.c 46: failloc :(", ENOMEM);
	while (data->env[c])
	{
		t = 0;
		g = 0;
		while (str[t])
		{
			if ((ms_strncmp(data->env[c], str[t], ms_strlen(str[t]))) == 0)
				g++;
			t++;
		}
		if (g == 0)
			ret[i++] = ms_strdup(data->env[c++]); // malloc check
		else
			c++;
	}
	ret[i] = NULL;
	env_free(data->env);
	return (ret);
}

char	**add_env(t_data *data, char **str) // needs to overwrite existing values
{
	int		c;
	int		i;
	int		t;
	char	**ret;

	c = 0;
	i = 0;
	t = 0;
	while (data->env[c])
		c++;
	while (str[i])
	{
		if (str[i][0] == ' ')
			i++;
		else
		{
			t++;
			i++;
		}
	}
	ret = malloc((c + t + 1) * sizeof(char *));
	if (!ret)
		ms_error(data, "eidexe/envp.c 92: failloc :(", ENOMEM);
	c = 0;
	i = 0;
	while (data->env[c])
	{
		ret[c] = ms_strdup(data->env[c]);
		c++;
	}
	while (str[i])
	{
		if (str[i][0] == ' ')
			i++;
		else
			ret[c++] = ms_strdup(str[i++]);
	}
	ret[c] = NULL;
	env_free(data->env);
	return (ret);
}

void	ms_cpy_env(t_data *data, char **arg)
{
	int		c;

	c = 0;
	while (arg[c])
		c++;
	data->env = malloc((c + 1) * sizeof(char *));
	if (!data->env)
		ms_error(data, "eidexe/envp.c 121: failloc :(", ENOMEM);
	c = 0;
	while (arg[c])
	{
		data->env[c] = ms_strdup(arg[c]);
		c++;
	}
	data->env[c] = NULL;
}

void	ms_envp(t_data *data, char **envp)
{
	data->env = NULL;
	ms_cpy_env(data, envp);
}
