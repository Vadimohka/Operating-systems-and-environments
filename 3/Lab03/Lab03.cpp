#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <cstdio>


int get_number() {
	int number;

	char c;

	while (1) {
		if (!scanf_s("%d", &number) || getchar() != '\n') {
			while ((c = getchar()) != '\n' && c != EOF);
		}
		else return number;
	}
}

struct Node {
	void* value;
	struct Node* next;
	struct Node* prev;
};

struct List {
	size_t list_size;
	struct Node* head;
	struct Node* tail;
};

struct List* create_list() {
	struct List* tmp = (struct List*) malloc(sizeof(struct List));
	tmp->list_size = 0;
	tmp->head = NULL;
	tmp->tail = NULL;
	return tmp;
}

void push_back(struct List* list, void* data) {
	struct Node* tmp = (struct Node*) malloc(sizeof(struct Node));
	tmp->value = data;
	tmp->next = NULL;
	tmp->prev = list->tail;

	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;

	if (list->head == NULL) {
		list->head = tmp;
	}
	list->list_size++;
}

void print_list(struct Node* node) {
	void* tmp = node->value;
	printf("%d ", *((int*)tmp));
	if (node->next != NULL) {
		print_list(node->next);
	}
}

int is_empty(struct List* list) {
	return list->list_size == 0 ? 1 : 0;
}

void fill_list(struct List* list) {
	while (1)
	{
		char data[256];

		char isRepeat;
		printf("\nFill list?(Y/n)");
		scanf_s("%c", &isRepeat);
		if (isRepeat != 'Y' && isRepeat != 'y')
			break;
		printf("\nEnter string: ");
		std::cin >> data;
		push_back(list, data);
	}
}

int main() {
	struct List* list = create_list();
	fill_list(list);

	if (!is_empty(list)) {
		printf("List: \t\t\t\t");
		print_list(list->head);
	}
	return 0;
}
