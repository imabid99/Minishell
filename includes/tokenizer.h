/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obeaj <obeaj@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:32:16 by obeaj             #+#    #+#             */
/*   Updated: 2022/05/09 17:25:55 by obeaj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define UNEXPECTED_TOK "minishell : syntax error near unexpected token : "
# define UNCLOSED_PAR "minishell :  Unclosed parethesis"
# define UNCLOSED_DQ "minishell :  Unclosed double quotes"
# define UNCLOSED_SQ "minishell :  Unclosed simple quotes"
# define SPACES "\t \v \f \r"

typedef enum s_tok
{
	PP = 1 << 0,
	OR = 1 << 1,
	AND = 1 << 2,
	LTH = 1 << 3,
	GTH = 1 << 4,
	GGTH = 1 << 5,
	HDOC = 1 << 6,
	BG = 1 << 7,
	SC = 1 << 8,
	DR = 1 << 9,
	QT = 1 << 10,
	DQT = 1 << 11,
	OPR = 1 << 12,
	CPR = 1 << 13,
	TLD = 1 << 14,
	STR = 1 << 15,
	CMDBEG = 1 << 16,
	CMDEND = 1 << 17,
	DSC = 1 << 18,
	NL = 1 << 19,
	WSC = 1 << 20,
	VAR = 1 << 21,
	WC = 1 << 22,
	BIND = (OR | AND | PP),
	BFG = (BG | SC),
	WORD = (STR | QT | DQT | WSC | VAR | WC | TLD),
	REDIR = (HDOC | LTH | GGTH | GTH),
	RED = (LTH | GGTH | GTH),
	NO_EXP = (WSC | BIND | BFG | CMDBEG),
}	t_tok;

typedef struct s_group
{
	char			*data;
	struct s_group	*next;
}	t_group;

typedef struct s_token
{
	t_tok			tok;
	char			*data;
	t_group			**group;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_tokenizer
{
	t_tok	tok1;
	t_tok	tok2;
	char	*s;
}	t_tokenizer;

typedef struct s_split
{
	t_token	**right;
	t_token	**left;
	t_tok	tok;
}	t_split;

typedef struct s_tok_util
{
	t_token	*first;
	t_token	*right;
	t_token	*left;
	int		count[2];
}	t_tok_util;

t_token	**tokenizer(char **line, char *charset);
void	print_error(char *str, char *data);
void	add_token_back(t_token **tok, t_token *newtok);
t_token	**del_token(t_token **tok, t_token *token);
void	del_token_0(t_token *token);
t_token	*new_token(t_tok tok, char *data);
t_token	**token_init(t_token **token);
int		peek(char **line, char *toks);
void	tokenize_0(char **line, t_token **tok);
void	tokenize_1(char **line, t_token **tok);
void	tokenize_2(char **line, t_token **tok);
void	tokenize_3(char **line, t_token **tok, int len);
void	bslash_util(int *len, char **line, t_token **tok, char **s);
char	*tokenize_6(char **line, t_token **tok);
char	*tokenize_4(char **line, t_token **tok, int q);
void	tokenize_5(char **line, t_token **tok);
t_token	**concat_words(t_token **tokens);
t_token	**tokens(char **line, char *charset);
int		check_par_match(t_token **tokens);
int		check_quotes_match(t_token **tokens);
int		check_parethesis(t_token **tokens);
int		check_binders(t_token **tokens);
int		check_redirect(t_token **tokens);
int		syntax_analyse(t_token **tokens);
t_token	**quotes_filter(t_token **tokens);
t_token	**lexer(char **line, char **env);
#endif