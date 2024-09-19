/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:24:53 by yzioual           #+#    #+#             */
/*   Updated: 2023/11/06 11:35:54 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words_count(const char *s, char delim)
{
	int	i;
	int	in_word;
	int	count;

	if (s == NULL)
		return (-1);
	count = 0;
	i = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] <= 32 || s[i] == delim)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

/*
static void	free_string_array(char** arr, int size)
{
	int	i;

	i = -1;
	while (size > 0 && arr[++i] != NULL)
		free(arr[i]);
    	free(arr);
}
*/

char	**ft_split(const char *s, char delim)
{
	int		i;
	int		k;
	int		word_len;
	int		words_count;
	int		temp;
	int		start;
	char	**result;

	if (s == NULL)
		return (NULL);
	words_count = ft_words_count(s, delim);
	result = malloc(sizeof(char *) * (words_count + 1));
	if (result == NULL)
		return (NULL);
	k = -1;
	i = 0;
	temp = 0;
	while (++k < words_count)
	{
		while (s[i] && (s[i] <= 32 || s[i] == delim))
			i++;
		start = i;
		while (s[i] && s[i] > 32 && s[i] != delim)
			i++;
		word_len = i - start;
		result[k] = malloc(sizeof(char) * (word_len + 1));
		if (result[k] == NULL)
			return (NULL);
		temp = -1;
		while (++temp < word_len)
			result[k][temp] = s[start + temp];
		result[k][temp] = '\0';	
	}
	result[words_count] = NULL;
	return (result);
}

/*
#include <stdio.h>

int	main()
{
    char str1[] = "Hello,World";
    char delim1 = ',';
    char** result1 = ft_split(str1, delim1);
    printf("Test Case 1:\n");
    for (int i = 0; result1[i] != NULL; ++i) {
        printf("%s\n", result1[i]);
    }
    free_string_array(result1, 2);
    printf("\n");

    // Test Case 2: Multiple Delimiters
    char str2[] = "apple,orange,,banana";
    char delim2 = ',';
    char** result2 = ft_split(str2, delim2);
    printf("Test Case 2:\n");
    for (int i = 0; result2[i] != NULL; ++i) {
        printf("%s\n", result2[i]);
    }
    free_string_array(result2, 4);
    printf("\n");

    // Test Case 3: No Delimiter
    char str3[] = "ThisIsAStringWithoutDelimiter";
    char delim3 = ',';
    char** result3 = ft_split(str3, delim3);
    printf("Test Case 3:\n");
    for (int i = 0; result3[i] != NULL; ++i) {
        printf("%s\n", result3[i]);
    }
    free_string_array(result3, 1);
    printf("\n");

    // Test Case 4: Empty String
    char str4[] = "";
    char delim4 = ',';
    char** result4 = ft_split(str4, delim4);
    printf("Test Case 4:\n");
    for (int i = 0; result4[i] != NULL; ++i) {
        printf("%s\n", result4[i]);
    }
    free_string_array(result4, 1);
    printf("\n");

    // Test Case 5: Delimiter at the beginning and end
    char str5[] = ",apple,orange,banana,";
    char delim5 = ',';
    char** result5 = ft_split(str5, delim5);
    printf("Test Case 5:\n");
    for (int i = 0; result5[i] != NULL; ++i) {
        printf("%s\n", result5[i]);
    }
    free_string_array(result5, 5);
    printf("\n");


    return 0;
}
*/
