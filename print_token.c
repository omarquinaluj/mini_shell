static void printtokens(t_cmd **cmds)
{
 	t_cmd *aux = *cmds;
 	int i = 0;
 	while (aux){
 		printf("--------------\n");
 		printf("cabeza = %s\n", aux->name_cmd);
 		i = 0;
 		while(aux->args[i])
 		{
 			printf("argumentos[%d] = %s\n", i, aux->args[i]);
 			i++;
 		}
 		printf("--------------\n");
 		i++;
 		aux = aux->next;
 		}
}