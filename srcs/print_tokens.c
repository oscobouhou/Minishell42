/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:28:32 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/05 18:34:42 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void what_token(int token)
{
	if (token == WORD)
		dprintf(2, "WORD");
	if (token == PIPE)
		dprintf(2, "PIPE");
	if (token == SQ_WORD)
		dprintf(2, "SQ_WORD");
	if (token == DQ_WORD)
		dprintf(2, "DQ_WORD");
	if (token == RDIR_R)
		dprintf(2, "RDIR_R");
	if (token == RDIR_L)
		dprintf(2, "RDIR_L");
	if (token == BUILTIN)
		dprintf(2, "BUILTIN");
	if (token == APPEND)
		dprintf(2, "APPEND");
	if (token == HRDOC)
		dprintf(2, "HRDOC");
	if (token == DLIM_HRDOC)
		dprintf(2, "DLIM_HRDOC");
	if (token == _FILE)
		dprintf(2, "_FILE");
	if (token == _CMD)
		dprintf(2, "_CMD");
	if (token == _ARG)
		dprintf(2, "_ARG");
}

void	print_tokens(t_mshell *mshell)
{
	mshell->tkn = mshell->head_tkn;
	while (mshell->tkn)
	{
		dprintf(2, "content: %s			---			type: ", mshell->tkn->tkn);
		what_token(mshell->tkn->type);
		dprintf(2, "\n");
		mshell->tkn = mshell->tkn->next;
	}
	mshell->tkn = mshell->head_tkn;
}


/* pour le langage C, il y a les caractères d'escape comme \n, \t , ...
il y a aussi les caractères de couleur, qui permettent au flux sortant sur l'écran d'avoir une couleur bien spécifique.

la format de ces caractères est le suivant :
<ESC>[{attr};{fg};{bg}m

<ESC> : c'est le caractères \[[ pour le langage C
{attr} : l'attribut pour le font (mode en MSDOS)
{fg} : couleur du text
{bg}: couleur de fond text

un exemple :
printf("\[[0;31;40mIn Color");


voici un lien qui, si t'as pas compris :
http://www.linuxjournal.com/article/8603


https://dev.to/tenry/terminal-colors-in-c-c-3dgc#:~:text=In%20order%20to%20make%20the,%22%5C033%5B0m%22%20.&text=The%20terminal%2Dcolors.

https://gist.github.com/vratiu/9780109

 */