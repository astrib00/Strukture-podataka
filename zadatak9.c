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

position createNode(int number)
{
	position p = NULL;

	p = (position)malloc(sizeof(Node));

	if( NULL == p){
		printf("Memory allocation failed.\n");
	return NULL;
}
	else
		return p;
}

position insert(position current, position el);
void printInOrder(position current);
position find(position current, int number);
position deleteNode (position current, int number);
position findMAX(position current);
position findMin(position current);

int main(void)
{
	position root = NULL;
	position el = createNode(16);
	root = insert(root, el);
	
	
	
	
	return EXIT_SUCCESS;
}

position insert(position current, position el)
{
	if(current == NULL)
		return el;

	if(current->number > el->number)
	{
		current->left = insert(current->left, el);
	}else if(current->number < el->number) {
		current->right = insert(current->right, el); 
	}else {
		printf("Duplicated element %d", el->number);
		free(el);
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
