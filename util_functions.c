#include "cub.h"

void ft_puterrmsg(char *msg)
{
	int i;

	i = 0;
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (dstsize > 0)
	{
		while (i + 1 < (dstsize) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < (n - 1)) && (s1[i] == s2[i]) && (s1[i] || s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

t_parse	*create_struct(void)
{
	t_parse *stc;

	stc = malloc(sizeof(t_parse *));
	if (!stc)
		stc = NULL;
	return (stc);
}

char	*create_array(int size)
{
	char	*tab;

	tab = malloc((sizeof(char) * size) + 1);
	if (!tab)
		tab = NULL;
	return (tab);
}

char	**create_2d_array(int size)
{
	char **tab;

	tab = malloc((sizeof(char *) * size) + 1);
	if(!tab)
		tab = NULL;
	return (tab);
}