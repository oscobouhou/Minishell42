/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exprt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:51:12 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/03 00:52:01 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *b, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)b)[i++] = 0;
}

char	*ft_strdup(char *str)
{
	size_t	i;
	char	*s;
	size_t	size;

	i = 0;
	size = ft_strlen(str) + 1;
	s = malloc(size * sizeof(char));
	if (!s)
		return (NULL);
	while (i < size -1)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void	fill_s1(char *str, char *s1, int *i)
{
	while (s1[*i])
	{
		str[*i] = s1[*i];
		(*i)++;
	}
}

char	*ft_strjoin(char *s1, char *s2, int upend)
{
	char	*str;
	int		i;
	int		n;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s2));
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	n = 0;
	if (s1)
		fill_s1(str, s1, &i);
	while (s2[n])
	{
		str[i] = s2[n];
		n++;
		i++;
	}
	str[i] = '\0';
	if (upend == 1)
		free(s1);
	return (str);
}

char	*ft_charcat(char *str, char c)
{
	int		len;
	char	*new_str;
	int		i;

	i = 0;
	len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = 0;
	return (new_str);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == 0)
		return (((char *)&s[i]));
	return (NULL);
}

char	*ft_substr(char *s, int start, size_t len)
{
	char			*str;
	unsigned int	j;

	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str = malloc(1);
		str[0] = '\0';
		return (str);
	}
	if ((ft_strlen(s) - start) <= (int)len)
		str = (char *)malloc(ft_strlen(s) - start + 1);
	else
		str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (s[start] && j < len)
			str[j++] = s[start++];
	str[j] = 0;
	return (str);
}

char	*ft_subsecure(char *s, int *i, char **str)
{
	char	*stri;
	int		j;

	j = 0;
	stri = ft_substr(s, (i[0] - i[1]), i[1]);
	if (!stri)
	{
		while (j <= i[2])
			free(str[j++]);
		free(str);
	}
	return (stri);
}

int	wordn(char *s, char c)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (s[i[0]])
	{
		if (s[i[0]] != c)
		{
			i[1]++;
			while (s[i[0]] != c && s[i[0]])
				i[0]++;
		}
		while (s[i[0]] == c && s[i[0]])
			i[0]++;
	}
	return (i[1]);
}

char	**ft_split(char *s, char c)
{
	int		i[3];
	char	**str;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	str = malloc(sizeof(char *) * (wordn(s, c) + 1));
	if (!str)
		return (NULL);
	while (i[2] < wordn(s, c))
	{
		while (s[i[0]] == c && s[i[0]])
			i[0]++;
		while (s[i[0]] != c && s[i[0]])
		{
			i[0]++;
			i[1]++;
		}
		str[i[2]++] = ft_subsecure(s, i, str);
		if (!str)
			return (NULL);
		i[1] = 0;
	}
	str[i[2]] = NULL;
	return (str);
}

//=====================================================================================

int	env_len(t_mshell *mshell)
{
	t_env	*env;
	int		i;

	if (!mshell->env)
		return (0);
	i = 0;
	env = mshell->env;
	while (env->next)
	{
		env = env->next;
		i++;
	}
	return (i + 1);
}

char	**copy_env_in_tab(t_mshell *mshell)
{
	t_env	*env;
	char	**env_tab;
	int		i;

	i = env_len(mshell);
	if (!i)
		return (0);
	env_tab = malloc(sizeof(char *) * (i + 1));
	env_tab[i] = NULL;
	if (!env_tab)
		return (NULL);
	env = mshell->env;
	i = 0;
	while (env)
	{
		env_tab[i] = ft_charcat(env->envar, '=');
		if (!env_tab[i])
			return (NULL);                                          //free previous in new function that takes i so it can free the already malloc lines
		env_tab[i] = ft_strjoin(env_tab[i], env->value, 1);
		if (!env_tab[i])
			return (NULL);                                          //free
		i++;
		env = env->next;
	}
	env = mshell->env;
	return (env_tab);

}

//=====================================================================================

void	print_export(t_mshell *mshell)
{
	t_expt	*env;

	env = mshell->expt;
	while (env->next)
	{
		ft_putstr("declare -x ");
		ft_putstr(env->exptvar);
		if (env->value)
		{
			ft_putchar('=');
			ft_putstr("\"");
			ft_putstr(env->value);
			ft_putstr("\"");
		}
		ft_putchar('\n');
		env = env->next;
	}
}

t_expt *search_exprt_pos(char *val, t_expt *head)
{
	t_expt *prev;
	int cmp;

	prev = NULL;
	while (head->next)
	{
		cmp = ft_strcmp(val, head->exptvar);
		if (cmp <= 0)
			return prev;
		prev = head;
		head = head->next;
	}
	return prev;
}

t_env *search_env_pos(char *val, t_env *head)
{
	t_env *prev;
	int cmp;

	prev = NULL;
	while (head->next)
	{
		cmp = ft_strcmp(val, head->envar);
		if (cmp <= 0)
			return prev;
		prev = head;
		head = head->next;
	}
	return prev;
}

int	check_arg(char *current_arg)
{
	int i;
	
	i = 0;
	if (!current_arg)
		return (0);
	if (!ft_isalpha(*current_arg) || *current_arg == '_')
		return (0);
	while (ft_isalnum(current_arg[i]) || current_arg[i] == '_')
		i++;
	if (current_arg[i] == '\0')
		return (2);
	if (current_arg[i] == '+' && current_arg[i + 1] == '=')
		return (1);
	if (current_arg[i] == '=')
		return (1);
	return (0);
}


//=====================================================================================

t_env	*create_env_node(char *var)
{
	t_env	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->envar = ft_strdup(var);
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}


void	append_to_env(t_env **head, t_env *new_node)
{
	t_env	*last;

	if (!head)
		return ;
	if (*head)
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;
}


int	add_new_envar(char **to_add, t_mshell *mshell)
{
	t_env		*new_node;
	
	new_node = create_env_node(to_add[0]);
	new_node->value = ft_strdup(to_add[1]);
	if (!new_node->value)
		return (0);
	if (!new_node)
		return (0);
	append_to_env(&mshell->env, new_node);
	return (1);
}


int	manage_env(char **to_export, t_mshell *mshell)
{
	int			plus_index;
	t_env	*environment;

	environment = mshell->env;
	plus_index = 0;
	if (ft_strchr(to_export[0], '+') != NULL)
	{
		plus_index = ft_strlen(to_export[0]) - 1;
		to_export[0][plus_index] = '\0';
	}
	while (environment && ft_strcmp(environment->envar, to_export[0]) != 0)
		environment = environment->next;
	if (environment && plus_index == 0)
	{
		environment->value = to_export[1];
		return (1);
	}
	if (environment && plus_index)
	{
		environment->value = ft_strjoin(environment->value, to_export[1], 1);
		if (!environment->value)
			return (0);
	}
	if (!environment)
		if (add_new_envar(to_export, mshell) == 0)
			return (0);
	return (1);
}

//======================================================================================

t_expt	*create_expt_node(char *var)
{
	t_expt	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->exptvar = ft_strdup(var);
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}


void	append_to_expt(t_expt **head, t_expt *new_node)
{
	t_expt  *pos;

	pos = search_exprt_pos(new_node->exptvar, *head);
	if (!head)
		return ;
	if (pos)
	{
		new_node->next = pos->next;
		pos->next = new_node;
	}
	else
		*head = new_node;
}


int	add_new_exptar(char **to_add, t_mshell *mshell)
{
	t_expt		*new_node;

	new_node = create_expt_node(to_add[0]);
	if (!new_node)
		return (0);
	if (to_add[1])
	{
		new_node->value = ft_strdup(to_add[1]);
		if (!new_node->value)
			return (free(new_node), 0);
	}
	append_to_expt(&mshell->expt, new_node);
	return (1);
}


int	manage_expt(char **to_export, t_mshell *mshell)
{
	int			plus_index;
	t_expt	*export;

	export = mshell->expt;
	plus_index = 0;
	if (to_export[0] && ft_strchr(to_export[0], '+') != NULL)
	{
		plus_index = ft_strlen(to_export[0]) - 1;
		to_export[0][plus_index] = '\0';
	}
	while (export && export->exptvar && ft_strcmp(export->exptvar, to_export[0]) != 0)
		export = export->next;
	if (export && export->exptvar && to_export[1] && plus_index == 0)
	{
		if (export->value)
			free(export->value);
		export->value = to_export[1];
		return (1);
	}
	if (export && export->exptvar && plus_index)
	{
		export->value = ft_strjoin(export->value, to_export[1], 1);
		if (!export->value)
			return (0);
	}
	if (!export || !export->exptvar)
		if (add_new_exptar(to_export, mshell) == 0)
			return (0);
	return (mshell->exprtc++, 1);
}

//======================================================================================

int	do_exprt(t_mshell *mshell)
{
	char	**export_split;
	t_tkn *args;

	if (mshell->exec->start_exec->next == NULL ||mshell->exec->start_exec->next->tkn == NULL)
		return (print_export(mshell), 1);
	args = mshell->exec->start_exec->next;
	while (args != NULL && args->tkn != NULL)
	{
		if (!check_arg(args->tkn))
		{
			ft_putstr("minishell: export: '");
			ft_putstr(args->tkn);
			ft_putstr("': not a valid identifier\n");
			args = args->next;
			continue ;
		}
		export_split = ft_split(args->tkn, '=');
		if (manage_expt(export_split, mshell) != 1)
				return (ft_putstr("Shit, i coulnt export in export\n"), 0);
		if (ft_strchr(args->tkn, '='))
		{	
			if (!export_split)
				return (0);
			if (manage_env(export_split, mshell) != 1)
				return (0);
		}
		args = args->next;
	}
	return (1);
}
