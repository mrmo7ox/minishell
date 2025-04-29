#include "./minishell.h"

static int	is_separator(char ch, char c)
{
	return (ch == c);
}

static size_t	ft_count_words(char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_separator(str[i], c))
			i++;
		if (str[i] == '\0')
			break ;
		count++;
		while (str[i] && !is_separator(str[i], c))
			i++;
	}
	return (count);
}

static	char	*ft_word_maker(char *str, size_t *index, char c)
{
	char	*word;
	size_t	i;
	size_t	len;
	size_t	j;

	i = *index;
	len = 0;
	j = 0;
	while (str[i] && is_separator(str[i], c))
		i++;
	while (str[i + len] && !is_separator(str[i + len], c))
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	while (j < len)
		word[j++] = str[i++];
	word[j] = '\0';
	*index = i;
	return (word);
}

static void	free_split(char **split, size_t current)
{
	size_t	i;

	i = 0;
	while (i < current)
		free(split[i++]);
	free (split);
}

char	**ft_split_test(char const *str, char c)
{
	char	**strs;
	size_t	i;
	size_t	index;
	size_t	len;

	if (str == NULL)
		return (NULL);
	i = 0;
	index = 0;
	len = ft_count_words((char *)str, c);
	strs = malloc(sizeof(char *) * (len + 1));
	if (strs == NULL)
		return (NULL);
	while (i < len)
	{
		strs[i] = ft_word_maker((char *)str, &index, c);
		if (!strs[i])
		{
			free_split(strs, i);
			return (NULL);
		}
		i++;
	}
	strs[i] = NULL;
	return (strs);
}