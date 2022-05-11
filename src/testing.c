/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:10:46 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/06 12:53:16 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	main(int ac, char **av, char **env)
{
	char	**line;
	char	*s;
	t_token	**toks;
	t_token	*first;
	
	(void)av;
	(void)ac;

	line = malloc(sizeof(char *));
	s = *line;
	*line = readline("obeaj->");
	toks = lexer(line, env);
	if (!toks)
		return 0;
	first = *toks;
	t_cmd **cmd;
	cmd = parsing(toks);
	if (!cmd)
		return 0;
	while (*cmd) 
	{
		printf ("%d\n", (*cmd)->type);
		if ((*cmd)->type & AST_EXEC)
			printf ("%s\n", (*cmd)->argv[0]);	
		if ((*cmd)->type & AST_REDIR)
			printf ("%s\n", (*cmd)->file);	
		*cmd = (*cmd) -> right;	
	}
	// print_tree(*cmd);
	// while (first)
	// {
	// 	printf("%s ----> %u\n", first->data, first->tok);
	// 	if (first -> tok & WC && first -> group)
	// 	{
	// 		while (*first -> group)
	// 		{
	// 			printf("######## %s ###########\n", (*first->group)-> data);
	// 			(*first -> group) = (*first -> group)-> next;
	// 		}
	// 	}
	// 	first = first-> next;
	// }
	// free(line);
	// free_tokens(toks);
	// free_glob();
	// free(*cmd);
	// free(cmd);
}
*/