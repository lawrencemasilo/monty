#include "monty.h"

/**
 * main - Enter point
 * @argc: commandline argument count
 * @argv: array of commandline arguments
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char **op_av, *buffer;
	int count;

	if ((argv[1] == NULL) || (argc > 2))
	{
		write(STDERR_FILENO, "USAGE: monty file\n",
				strlen("USAGE: monty file\n"));
		exit(EXIT_FAILURE);
	}
	if (argv[1] != NULL)
	{
		buffer = _read(argv);
		if (buffer == NULL)
		{
			write(STDERR_FILENO, "USAGE: monty file\n",
					strlen("USAGE: monty file\n"));
			exit(EXIT_FAILURE);
		}
		op_av = tokenize(buffer, "$\n");
		count = line_count(argv);
		main_op(op_av, count);
	}
	free(buffer);
	free(op_av);
	return (0);
}

/**
 * _token - tokenises a str
 * @argv: the str
 * Return: tokenised array
 */
char **_token(char *argv)
{
	char *token, **av;
	int i = 0;

	av = malloc(sizeof(char *) * sizeof(argv) + 1);
	if (av == NULL)
	{
		write(STDERR_FILENO, "Error: malloc failed\n",
				strlen("Error: malloc failed\n"));
		exit(EXIT_FAILURE);
	}
	token = strtok(argv, " ");
	while (token != NULL)
	{
		av[i] = token;
		token = strtok(NULL, "\n");
		i++;
	}
	av[i] = NULL;

	return (av);
}

/**
 * _read - opens a file and reads the file
 * @argv: array of commandline arguments
 * Return: the buffer with read content
 */
char *_read(char **argv)
{
	char *buffer;
	int fd;
	ssize_t readn;

	buffer = malloc(sizeof(char *) * 1024);
	if (buffer == NULL)
	{
		write(STDERR_FILENO, "Error: malloc failed\n",
				strlen("Error: malloc failed\n"));
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(STDERR_FILENO, "Error: Can't open ",
				strlen("Error: Can't open "));
		printf("%s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	readn = read(fd, buffer, 1024);
	if (readn == -1)
	{
		printf("read failed");
		exit(EXIT_FAILURE);
	}
	return (buffer);
}

/**
 * tokenize - tokenizes a the buffer
 * @buffer: the buffer
 * @delim: delimiter
 * Return: double pointer array with the tokenized strings
 */
char **tokenize(char *buffer, char *delim)
{
	char *token = NULL, **op_av, buf_copy[1024], *token2 = NULL;
	int cmd_count = 0, i = 0;

	strcpy(buf_copy, buffer);
	token = strtok(buffer, delim);
	while (token != NULL)
	{
		token = strtok(NULL, delim);
		cmd_count++;
	}
	op_av = malloc(sizeof(char *) * cmd_count + 1);
	if (op_av == NULL)
	{
		write(STDERR_FILENO, "Error: malloc failed\n",
				strlen("Error: malloc failed\n"));
		exit(EXIT_FAILURE);
	}
	token2 = strtok(buf_copy, delim);
	while (token2 != NULL)
	{
		op_av[i] = token2;
		token2 = strtok(NULL, delim);
		i++;
	}
	op_av[i] = NULL;
	if (op_av == NULL)
	{
		return (NULL);
	}
	return (op_av);
}

/**
 * line_count - counts the number of commands
 * @argv: array of commandline arguments
 * Return: the count
 */
int line_count(char **argv)
{
	char *buffer, *token;
	int count = 0;

	buffer = _read(argv);
	token = strtok(buffer, "$\n");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, "$\n");
	}
	return (count);
}
