#include "monty.h"

/**
 * main_op - handles the opcode and its arguments
 * @argv: opcode with arguments
 * @count: the number of opcodes + arguments
 * Return: Nothing
 */
void main_op(char **argv, int count)
{
	char **av, *choice;
	int j = 0, value;
	stack_t *top = NULL;

	for (j = 0; j <= count; j++)
	{
		av = _token(argv[j]);
		if (av[0] != NULL)
		{
			choice = av[0];
			if (strcmp(choice, "pall") != 0)
			{
				if (atoi(av[1]))
					value = atoi(av[1]);
			}
			if (strcmp(choice, "push") == 0)
			{
				if (value)
					push(value, &top);
				else
				{
					printf("l %d:", j + 1);
					write(STDERR_FILENO, "usage: push integer\n",
							strlen("usage: push integer\n"));
					exit(EXIT_FAILURE);
				}
			}
			else if (strcmp(choice, "pall") == 0)
				pall(top);
		}
	}
	free(av);
}


/**
 * pall - displays all the values in the stack
 * @top: the top most element in the stack
 * Return: Nothing
 */
void pall(stack_t *top)
{
	while (top != NULL)
	{
		printf("%d\n", top->n);
		top = top->next;
	}
}

/**
 * push - adds elements to the stack
 * @value: the data
 * @top: the postive of the previous top element
 * Return: Nothing
 */
void push(int value, stack_t **top)
{
	stack_t *temp = *top;
	stack_t *ptr = malloc(sizeof(stack_t));

	if (ptr == NULL)
		return;
	if (temp != NULL)
	{
		temp->prev = ptr;
	}

	ptr->n = value;
	ptr->next = temp;
	ptr->prev = NULL;

	*top = ptr;
}
