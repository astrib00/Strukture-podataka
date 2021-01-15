#include<stdio.h>
#include<stdlib.h>

struct _node;
typedef struct _node *position;
typedef struct _node
{
	int number;
	position left;
	position right;
} Node;

position createNode(int number);
position insert(position current, position el);
void printInOrder(position current);
position find(position current, int number);
position deleteNode (position current, int number);
position findMAX(position current);
position findMin(position current);

int main(void)
{
	position root = NULL;   
	  

	int number, br, wantedNumber;

	char sign = 0;
	while (sign != 'e') {

		printf("\nOperacija:\n");
		printf("i - insert\np- print\nf- find element\nd- delete\ne- end\n");
		scanf(" %c", &sign);

		switch (sign) {

		case 'i':

			printf("Unesite nekakav broj: ");
			scanf("%d", &br);
			printf("\n");
			root = insert(root, br);
			break;

		case 'p':

			printInOrder(root);
			break;

		case 'd':
			printf("Unesite broj koji zelite ukloniti:");
			scanf("%d", &br);
			printf("\n");
			root = deleteNode(root, br);

			break;

		case'f':
			printf("Unesite broj koji zelite pronaci:");
			scanf("%d", &br);
			printf("\n");
			wantedNumber = find(root, br);
			if (wantedNumber != NULL)
				printf("Broj %d uspjesno je pronaden.\n", br);
			break;

		default:
			break;
		}

	}

	
	return EXIT_SUCCESS;
}

position insert(position current, int el)
{
	if(current == NULL)
	{
		current = (position)malloc(sizeof(Node));

		current->number = el;
		current->left = NULL;
		current->right = NULL;
	}

	else if(current->number > el) {
		current->left = insert(current->left, el);
	}
	else if(current->number < el){
		current->right = insert(current->right, el);
	}
	else {
		printf("GRESKA!!!Dupliciran clan!\n");
		//free(el);
	}

	return current;
}

void printInOrder(position current)
{
	if(current == NULL) return;

	printInOrder(current->left);
	printf("%d ", current->number);
	printInOrder(current->right);
}

position find(position current, int number)
{
	if(current == NULL) return NULL;

	if(current->number == number)
	{
		return current;
	}else if (current->number > number)
	{
		return find(current->left, number);
	}else /* if (current->number < number) */ {
		return find(current->right, number);
	}
}

position deleteNode (position current, int number)
{
	if(current == NULL) return NULL;

	if(current->number == number) {
		if(current->left == NULL && current->right == NULL) {
			free(current);
			return NULL;
		}

		if(current->left != NULL) {
			position tmp = findMax(current->left);
			current->number = tmp->number;
			current->left = deleteNode(current->left, tmp->number);
		}else if (current->right != NULL) {
			position tmp = findMax(current->right);
			current->number = tmp->number;
			current->right = deleteNode(current->right, tmp->number);
		}
	
	} else if(current->number < number) {
		current->left = deleteNode(current->left, number);
	}else /* if(current->number > number)*/ {

		current->right = deleteNode(current->right, number);
	}

	return current;
}

position findMax(position current)
{
	if( NULL == current) return NULL;

	while(current->right != NULL) current = current->right;

}

position findMin(position current)
{
	if(NULL == current)
		return NULL;
	while(current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

position createNode(int number)
{
	position p = NULL;

	p = (position)malloc(sizeof(Node));

	if( NULL == p){
		printf("Greska u alokaciji memorije.\n");
	return NULL;
}
	else
		p->number = number;
		p->left = NULL;
		p->right = NULL;
}
