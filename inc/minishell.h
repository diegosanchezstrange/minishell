#ifndef MINISHELL_H
# define MINISHELL_H

#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef enum	e_pstates
{
	P_NEUTRAL	= 0,
	P_D_QUOTE	= 1,
	P_S_QUOTE	= 2
}				t_pstates;

typedef struct s_pstatus
{
	char		*data;
	int			curr;
	t_pstates	state;
}		t_pstatus;

// parser
char	**ft_get_tokens(char *line);

#endif
