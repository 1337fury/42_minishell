/*************************[TEST MY WORK]*********************************/
	// printf("expander head is : %p\n", expander->head);
	// printf("expander head type is : %d\n", expander->head->type);
	// printf("expander head family is : %p\n", expander->head->family);
	// printf("expander head family head is : %p\n", expander->head->family->head);
	// printf("expander head family head type is : %d\n", expander->head->family->head->type);
	// printf("expander head family head input src is : %d\n", expander->head->family->head->in);
	// printf("expander head family head output dest is : %d\n", expander->head->family->head->out);
	// if (expander->head->family->head->data)
	// {
	// 	int i = 0;
	// 	while (expander->head->family->head->data[i])
	// 	{
	// 		printf("expander head family head data[%d] is : %s\n", i, expander->head->family->head->data[i]);
	// 		i++;
	// 	}
	// 	printf("\n\n");
	// }

	// printf("expander 2 node is : %p\n", expander->head->next);
	// printf("expander 2 node type is : %d\n", expander->head->next->type);
	// printf("\n\n");

	// printf("expander 3 node is : %p\n", expander->head->next->next);
	// printf("expander 3 node type is : %d\n", expander->head->next->next->type);
	// printf("expander 3 node family is : %p\n", expander->head->next->next->family);
	// printf("expander 3 node family head is : %p\n", expander->head->next->next->family->head);
	// printf("expander 3 node family head type is : %d\n", expander->head->next->next->family->head->type);
	// printf("expander 3 node family head input src is : %d\n", expander->head->next->next->family->head->in);
	// printf("expander 3 node family head output dest is : %d\n", expander->head->next->next->family->head->out);
	// if (expander->head->next->next->family->head->data)
	// {
	// 	int i = 0;
	// 	while (expander->head->next->next->family->head->data[i])
	// 	{
	// 		printf("expander 3 node family head data[%d] is : %s\n", i, expander->head->next->next->family->head->data[i]);
	// 		i++;
	// 	}
	// 	printf("\n\n");
	// }
	/*************************[TEST MY WORK]*********************************/


	/**/
		t_node *currs;

		if (lexer)
		{
			currs = lexer->head;
			while (currs)
			{
				printf("type : %d\n", currs->type);
				printf("data : %s\n", currs->value);
				currs = currs->next;
			}
		}
		/**/


		"ls" '-'l'a'