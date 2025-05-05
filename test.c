#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// -------------------- Utils --------------------
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	strcpy(dup, s);
	return (dup);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}

char	*ft_substr(const char *s, int start, int len)
{
	char	*sub;

	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	strncpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}

char	*ft_itoa(int n)
{
	char	buffer[12];

	sprintf(buffer, "%d", n);
	return (ft_strdup(buffer));
}

char	*ft_strjoin_free(char *s1, char *s2, int free_s1)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	len1 = strlen(s1);
	len2 = strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	strcpy(res, s1);
	strcat(res, s2);
	if (free_s1)
		free(s1);
	free(s2);
	return (res);
}

// -------------------- Core Expanding --------------------

char	*get_env_value(const char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

char	*expand_if_needed(char *line, t_env *env_list, int exit_status)
{
	int		i;
	int		in_single;
	int		in_double;
	char	*result;
	char	*code;
	int		start;
	char	*key;
	char	*val;
			char c[2] = {line[i], 0};

	i = 0;
	in_single = 0;
	in_double = 0;
	result = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
		}
		else if (line[i] == '"' && !in_single)
		{
			in_double = !in_double;
			i++;
		}
		else if (line[i] == '$' && !in_single)
		{
			i++;
			if (line[i] == '?')
			{
				code = ft_itoa(exit_status);
				result = ft_strjoin_free(result, code, 1);
				i++;
			}
			else
			{
				start = i;
				while (isalnum(line[i]) || line[i] == '_')
					i++;
				key = ft_substr(line, start, i - start);
				val = get_env_value(key, env_list);
				result = ft_strjoin_free(result, ft_strdup(val), 1);
				free(key);
			}
		}
		else
		{
			result = ft_strjoin_free(result, ft_strdup(c), 1);
			i++;
		}
	}
	return (result);
}

// -------------------- Test Main --------------------

t_env	*create_env(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

int	main(void)
{
	char	input[1024];
	t_env	*env_list;
	size_t	len;
	char	*expanded;

	env_list = NULL;
	// Fake environment: USER=test, HOME=/home/user
	env_list = create_env("USER", "test");
	env_list->next = create_env("HOME", "/home/user");
	printf("Enter line to expand: ");
	if (!fgets(input, sizeof(input), stdin))
		return (1);
	// remove trailing newline
	len = strlen(input);
	if (len > 0 && input[len - 1] == '\n')
		input[len - 1] = '\0';
	expanded = expand_if_needed(input, env_list, 42);
	printf("Expanded: %s\n", expanded);
	free(expanded);
	free(env_list->next);
	free(env_list);
	return (0);
}
