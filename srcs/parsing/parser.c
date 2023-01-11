/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:25:09 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/11 15:57:11 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int sort_kinds(char read)
{
	if (read == SINGLE_QUOTE || read == DOUBLE_QUOTE)
		return (TREAT_QUOTE);
	if (read == PIPE_LINE)
		return (TREAT_PIPE);
	if (read == REDIR_L)
		return (TREAT_REDIR_L);
	if (read == REDIR_R)
		return (TREAT_REDIR_R);
	if (read == HYPHEN)
		return (TREAT_REDIR_R);
	if ((read >= 9 && read <= 13) || read == 32)
		return (TREAT_SPACE);
	return (TREAT_PRINTABLE);
}

int	parse_output(t_mshell *mshell)
{
	int (*parse[6])(t_mshell *mshell, int *i);
	int i;

	i = 0;
	parse[TREAT_PIPE] = treat_pipe;
	parse[TREAT_SPACE] = treat_space;
	parse[TREAT_QUOTE] = treat_quote;
	parse[TREAT_HYPHEN] = treat_hyphen;
	parse[TREAT_REDIR_R] = treat_redir_r;
	parse[TREAT_REDIR_L] = treat_redir_l;
	parse[TREAT_PRINTABLE] = treat_printable;
	while (mshell->rdline_outp[i])
	{
		if (!parse[sort_kinds(mshell->rdline_outp[i])](mshell, &i))
			return(0);
	}
	return (1);
	(void)mshell;
}


// PARSE DOC:

	// Gerer les single quotes :
	// Gerer l'expand :
	// Checker les double quotes :
	// Tokeniser l'output de readline :

	// Si il y a un pipe, nous reproduisons l'operation dans le :
	// maillon '->next' de notre structure ou nous stockerons la 
	// ligne a execute parsee

	// Une fois arrive au bout de notre file nous avons la 'rl_output' :
	// tokenise et decoupe pour l'exec
/*
Nous parcourons la chaine de caractere 'rl_readline' passee en parametre;

Nous appelons un tableau de fonction qui reconnaitra le type de caractere;
{
	si c'est un caractere special:
	[
		|       ->  
		<       ->
		>       ->
		"       ->
		-       -> 
	   SPACE	->
	]
	si c'est un caractere imprimable, nous le joignons au char *read.
}

 
	


WORD ->	REDIR ->	BUILT-IN ->	WORD ->			 	WORD
lol 	<< 			echo		"lol echo << lol"	mdr

*/