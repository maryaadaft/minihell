#include "minishell.h"

void	print_tokens(t_token *tok)
{
	while (tok)
	{
		printf("type: %d | value: %s\n", tok->token_type, tok->value);
		tok = tok->next;
	}
}

void	print_redirs(t_redir *redir)
{
	while (redir)
	{
		printf("  redir type: %d | file: %s\n", redir->type, redir->file);
		redir = redir->next;
	}
}

void	print_cmds(t_cmd *cmd)
{
    while (cmd)
    {
        int i = 0;
        while (cmd->args && cmd->args[i])
        {
            printf("  arg[%d]: %s\n", i, cmd->args[i]);
            i++;
        }
        print_redirs(cmd->redirs);
        cmd = cmd->next;                 
    }
}
