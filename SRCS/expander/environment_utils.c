/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdeel-o < abdeel-o@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:09:10 by abdeel-o          #+#    #+#             */
/*   Updated: 2023/05/28 15:16:31 by abdeel-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

//calc the length of a string until the first occurrence of the character '=' 
int	len_until_eq(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while(s[len] && s[len] != '=')
		len++;
	return (len);
}

//checks whether a given environment variable has a value 
bool	has_a_value(char *var)
{
	if (!var)
		return (false);
	while (*var)
	{
		if (*var == '=')
			return (true);
		var++;
	}
	return (false);
}

//compares the key portion of an environment variable with a target string and returns a int value indicating whether they are equal or not.
int	fry_compare(char *var, char *target)
{
	int		eq_len;
	char	*key;
	bool	result;

	eq_len = len_until_eq(var);
	if (!eq_len)
		return (false);
	key = ft_substr(var, 0, eq_len);
	if (!key)
		return (false);
	result = ft_strncmp(key, target, ft_strlen(target));
	return (free(key), result);
}

//retrieves the value of an environment variable identified by the given target name from the list of environment variables.
char	*retrieve_env_var(char *target)
{
	int		i;
	char	**k_v;
	t_envp	*envp;

	i = 0;
	if (!target)
		return (NULL);
	if (ft_strchr(target, '?'))
		return (ft_itoa(g_gen.e_status));
	envp = g_gen.envp;
	while (envp->env_vars[i])
	{
		if (has_a_value(envp->env_vars[i]) && fry_compare(envp->env_vars[i], target) == 0)
		{
			k_v = ft_split(envp->env_vars[i], '=');
			// free(target);
			return (free(k_v[0]), k_v[1]);
		}
		i++;
	}
	// free(target);
	return (ft_strdup(""));
}
