/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_hrdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:32:48 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/02 21:39:36 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	gather_usr_input(char *content, t_mshell *mshell)
{
	free(mshell->tkn->tkn);
	mshell->tkn->tkn = content;
	return (1);
}

int dup_expander___hrdoc(t_mshell *mshell, char *exptval, int n_tp)
{
    int i;

    i = 0;
    free(mshell->expd->types[n_tp]);
    mshell->expd->types[n_tp] = NULL;
    mshell->expd->types[n_tp] = malloc(sizeof(char) * (ft_strlen(exptval) + 1));
    if (!mshell->expd->types[n_tp])
        return (0);
    while (exptval[i])
    {
        mshell->expd->types[n_tp][i] = exptval[i];
        i++;
    }
    mshell->expd->types[n_tp][i] = '\0';
    return (1);
}

int	lens_types_expd__hrdoc(char *usr_input)
{
	int	cuts;
	int	i;

	i = 0;
	cuts = 0;
	while (usr_input[i])
	{
		if (usr_input[i] == EXPAND)
		{
            i += 1;
			while (usr_input[i] && usr_input[i] != DOUBLE_QUOTE
                && usr_input[i] != SINGLE_QUOTE && usr_input[i] != EXPAND && usr_input[i] != '\n' && usr_input[i] != ' ')
				i++;
			cuts++;
		}
        else if (usr_input[i] != EXPAND)
        {
			while (usr_input[i] && usr_input[i] != EXPAND)
               i++;
			cuts++;
        }
	}
	return (cuts);
}

char *join_types_expanded__hrdoc(t_mshell *mshell)
{
	char	*new_token;
	int		n_tp;
	int		i0;
	int		i1;

	n_tp = 0;
	i1 = 0;
	alloc_new_token_for_join(mshell, &i0, &n_tp, &i1);
	n_tp = 0;
	new_token = malloc(sizeof(char) * (i1 + 1));
	if (!new_token)
		return (NULL);
	i1 = 0;
	while (mshell->expd->types[n_tp])
	{
		i0 = 0;
		while (mshell->expd->types[n_tp][i0])
		{
			new_token[i1] = mshell->expd->types[n_tp][i0];
			i0++;
			i1++;
		}
        free(mshell->expd->types[n_tp]);
		n_tp++;
	}
	new_token[i1] = '\0';
    free(mshell->expd->types);
	return (new_token);
}


int check_expander__hrdoc(char *expander, t_mshell *mshell, int n_tp)
{
 	t_expt	*head;

	head = mshell->expt;
	while (mshell->expt->next)
	{
		if (!ft_strcmp(expander, mshell->expt->exptvar))
		{
			if (!dup_expander___hrdoc(mshell, mshell->expt->value, n_tp))
                return (0);
			mshell->expt = head;
			return (1);
		}
		mshell->expt = mshell->expt->next;
	}
    free(mshell->expd->types[n_tp]);
    mshell->expd->types[n_tp] = "";
	mshell->expt = head;
	return (1);
}

int make_expands_types__hrdoc(t_mshell *mshell, int n_tp)
{
    if (mshell->expd->types[n_tp][0] == EXPAND && !mshell->expd->types[n_tp][0 + 1])
        return (1);
    else if (mshell->expd->types[n_tp][0] == EXPAND)
        check_expander__hrdoc(&mshell->expd->types[n_tp][1], mshell, n_tp);
    return (1);
}

int types_expd_cut__hrdoc(t_mshell *mshell, char *usr_input, int n_tp)
{
    int tmp_i;
    int i;
    int j;

    i = 0;
    tmp_i = 0;
    while (usr_input[i])
    {
        if (usr_input[i] == EXPAND)
        {
            tmp_i = i;
            i += 1;
            while (usr_input[i] && usr_input[i] != DOUBLE_QUOTE
                && usr_input[i] != SINGLE_QUOTE && usr_input[i] != EXPAND && usr_input[i] != '\n' && usr_input[i] != ' ')
                i++;
            mshell->expd->types[n_tp] = malloc(sizeof(char) * (i - tmp_i) + 1);
            if (!mshell->expd->types[n_tp])
                return (0);
            j = 0;
            while (tmp_i <= (i - 1))
            {
                mshell->expd->types[n_tp][j] = usr_input[tmp_i];
                tmp_i++;
                j++;
            }
            mshell->expd->types[n_tp][j] = '\0';
            n_tp++;
        }
        else if (usr_input[i] != EXPAND)
        {
            while (usr_input[i] && usr_input[i] != EXPAND)
               i++;
            mshell->expd->types[n_tp] = malloc(sizeof(char) * (i - tmp_i) + 1);
            if (!mshell->expd->types[n_tp])
                return (0);
            j = 0;
            while (tmp_i <= (i - 1))
            {
                mshell->expd->types[n_tp][j] = usr_input[tmp_i];
                tmp_i++;
                j++;
            }
            mshell->expd->types[n_tp][j] = '\0';
            n_tp++;
        }
    }
    return (1);
}

int hrdoc_expander(char **usr_input, t_mshell *mshell)
{
    int n_tp;

    n_tp = lens_types_expd__hrdoc((*usr_input));
    mshell->expd->types = malloc(sizeof(char *) * (n_tp + 1));
    if (!mshell->expd->types)
        return (0);
    mshell->expd->types[n_tp] = NULL;
    n_tp = 0;
    types_expd_cut__hrdoc(mshell, (*usr_input), n_tp);
    while (mshell->expd->types[n_tp])
    {
        make_expands_types__hrdoc(mshell, n_tp);
        n_tp++;
    }
    free((*usr_input));
    (*usr_input) = NULL;
    (*usr_input) = join_types_expanded__hrdoc(mshell);
    if (!usr_input)
        return (0);
    return (1);
}

int execute_hrdoc(t_mshell *mshell, int expander)
{
    char    *usr_input;
    int     line;
    int     p;

    p = -42;
    line = 0;
    p = pipe(mshell->tkn->pipe_fd_hrdoc);
    if (p == -1)
        return (dprintf(2, "\tpipe: creation failure\n"));
    while (1)
    {
        usr_input = readline("> ");
        if (!check_eof(usr_input))
        {
            close(mshell->tkn->pipe_fd_hrdoc[1]);
			return (dprintf(STDERR_FILENO, "minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", line, mshell->tkn->tkn), 1);
        }
        if (!ft_strcmp(usr_input, mshell->tkn->tkn))
        {
            if (usr_input)
                free(usr_input);
            close(mshell->tkn->pipe_fd_hrdoc[1]);
            break ;
        }
        if (expander == -42)
            hrdoc_expander(&usr_input, mshell);
        write(mshell->tkn->pipe_fd_hrdoc[1], usr_input, ft_strlen(usr_input));
        write(mshell->tkn->pipe_fd_hrdoc[1], "\n", 1);
        line++;
        free(usr_input);
    }
    return (1);
}