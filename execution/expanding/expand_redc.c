
#include "../../minishell.h"

bool	has_qoute(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

bool	has_dollar(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			return (true);
		i++;
	}
	return (false);
}
char	*remove_qoutes(char *arg, t_c *c)
{
	char	*new;
	int		i;
	char	qoute;

	new = ft_strdup("", c->garbage);
	i = 0;
	while (arg[i])
	{
		if (ft_chrstr(arg[i], "\'\""))
		{
			qoute = arg[i];
			i++;
			while (arg[i] && arg[i] != qoute)
			{
				new = ft_addchr(new, arg[i], c);
				i++;
			}
			if (arg[i] == qoute)
				i++;
			continue ;
		}
		new = ft_addchr(new, arg[i], c);
		i++;
	}
	return (new);
}
char	*expand(char *arg,t_c *c)
{
	char	*new;
	int		i;
	int		j;
	char	*cut;
	char	*pid;
	char	*txpandat;

	new = ft_strdup("", c->garbage);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			j = i + 1;
			if (ft_isdigit(arg[j]) || ft_chrstr(arg[j], "$#@!^&*?"))
				j++;
			else if (ft_isalnum(arg[j]) || arg[j] == '_')
			{
				while (arg[j] && (ft_isalnum(arg[j]) || arg[j] == '_'))
				{
					j++;
				}
			}
			cut = ft_substr(arg, i, j - i, c->garbage);
			if (ft_chrstr('?', cut))
			{
				new = ft_addstr(new, ft_itoa(set_status(c->status, 0),
							c->garbage), c);
			}
			else if (!ft_strcmp("$", cut))
			{
				new = ft_addstr(new, cut, c);
			}
			else if (!ft_strcmp("$$", cut))
			{
				pid = ft_strip('\n', c->pid, c->garbage);
				new = ft_addstr(new, pid, c);
			}
			else
			{
				txpandat = ft_getenv(ft_strip('$', cut, c->garbage), c->ft_env);
				if (txpandat)
				{
					new = ft_addstr(new, txpandat, c);
				}
			}
			i = j;
			continue ;
		}
		else if(qoutes)
		new = ft_addchr(new, arg[i], c);
		i++;
	}
	return (new);
}


char	**expander(char *args, t_c *c)
{
	int		i;
	char	**new;
	int		j;

	new = NULL;
	head = NULL;
	i = 0;

	if (has_qoute(args) && !has_dollar(args))
		args = remove_qoutes(args, c);
	else
	{
		args = expand(args, NULL, c);
	}
	return (new);
}