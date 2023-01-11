/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 15:25:09 by oboutarf          #+#    #+#             */
/*   Updated: 2023/01/11 01:09:49 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_output(t_mshell *mshell)
{
	// char *read;
	// void *parsing[]

/* 	while ()
	{
		treat_quotes(mshell);
		
	} */
	// Gerer les single quotes :
	// Gerer l'expand :
	// Checker les double quotes :
	// Tokeniser l'output de readline :

	// Si il y a un pipe, nous reproduisons l'operation dans le :
	// maillon '->next' de notre structure ou nous stockerons la 
	// ligne a execute parsee

	// Une fois arrive au bout de notre file nous avons la 'rl_output' :
	// tokenise et decoupe pour l'exec
	(void)mshell;
}
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