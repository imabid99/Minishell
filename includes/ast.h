/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:50:38 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/05 00:51:22 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

/*** DATA ***/

typedef enum e_asttype{
	AST_PIPE =		(1 << 0),
	AST_SC =		(1 << 1),
	AST_AND =		(1 << 2),
	AST_OR =		(1 << 3),
	AST_GTH	=		(1 << 5),
	AST_GGTH =		(1 << 6),
	AST_LTH =		(1 << 7),
	AST_HDOC =		(1 << 8),
	AST_EXEC =		(1 << 9),
	AST_ARG =		(1 << 10),
	AST_DATA =		(1 << 11),
	AST_BG =		(1 << 12),
	AST_SUB =		(1 << 13),
	AST_REDIR =		(AST_HDOC | AST_LTH | AST_GTH | AST_GGTH),
	AST_RED =		(AST_LTH | AST_GTH | AST_GGTH),
	AST_NOD = (AST_SUB | AST_OR | AST_AND | AST_PIPE | AST_SC | AST_BG
		| AST_REDIR)
}	t_asttype;

#endif
