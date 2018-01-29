
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

//
// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {
	
	ListNode * e;

	if (list->head == NULL) {
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	e = list->head;
	while (e != NULL) {
		printf("%d", e->value);
		e = e->next;
		if (e!=NULL) {
			printf(", ");
		}
	}
	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
	// Create new node
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {
	ListNode * element = list->head;
	while(element){
		if(element->value == value){
			return 1;
		}
		element = element->next;
	}
	return 0;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, int value) {
	ListNode * current = list->head;
	ListNode * previous= list->head;
	while(current){
		if(current->value == value){
			previous->next = previous->next->next;
			return 1;
		}
		previous = current;
		current = current->next;
	}
	return 0;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
	ListNode * element = (ListNode *) malloc(sizeof(ListNode));
	element->value = *value;
	int i = ith;
	ListNode * head = list->head;

	while(head){
		if(ith==0){// this will onyl happen when I reach the index
		//	printf("Currently at Index %d \n ", (i-ith));
		//	printf("value at this index is %d \n", head->value );
			*value = head->value;
			return 1;
		}
		head = head->next;
		ith--;

	}
	return 0;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	ListNode * head = list->head;
	while(head){
		if(ith==1){ //i am one element before the element to be deleted
			head->next = head->next->next;
			return 1;
		}
		head = head->next;
		ith--;
	}
	return 0;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	int i = 0;
	ListNode * head = list->head;
	while(head){
		head = head->next;
		i++;
	}
	return i;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
	ListNode * head = list->head;
	FILE * file = fopen(file_name, "w");
	if(file == NULL){
		return 0;
	}
	while(head){
//		fprintf(file, "%d\n", head->value);
		fprintf(file, "%d\n", head->value);
		head = head->next;
	}
	fclose(file);
	return 0;
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
	FILE * file = fopen(file_name, "r");
	if(file == NULL){
		return 0;
	}
	ListNode * head = list->head;
	ListNode * temp = head;
	char line[256];
	char c;
	int multiplier = 1;
	while((c=fgetc(file))!=EOF){
		if(c!='\n'){
			int value=c-'0';
			if(c == '-'){
				value = ((c=fgetc(file))-'0') * -1;
			}else if((c=fgetc(file))>=48 && c<=57){
				value = value*10 + c - '0';
			}
			//printf("Value: %d \n", value);
			llist_add(list, value);
		//fgetc(file);
		}
	}
	fclose(file);
	return 1;
}


//
// It sorts the list. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void llist_sort(LinkedList * list, int ascending) {
	ListNode* head = list->head;
	ListNode* temp = head;
		int swap_flag=1;
	while(swap_flag){
		temp = head;
		swap_flag = 0;
		while(temp->next){
			if(ascending){
				if(temp->value > temp->next->value){
					int swap = temp->value;
					temp->value = temp->next->value;
					temp->next->value = swap;
					swap_flag = 1;
				}
			}else{
				if(temp->value < temp->next->value){
					int swap = temp->value;
					temp->value = temp->next->value;
					temp->next->value = swap;
					swap_flag = 1;
				}
			}
			temp = temp->next;
		}
	}
}

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
	ListNode * head = list->head;
	if(head == NULL){
		return 0;
	}
	ListNode * temp = head->next;
	*value = head->value;
	free(head);
	list->head = temp;
	return 1;
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
  	ListNode* head = list->head;
	ListNode * prev;
	if(head == NULL)
		return 0;
	while(head->next){
	prev = head;
		head = head->next;
	}
	*value = head->value;
	prev->next = NULL;	
	//head->next = NULL;
	//*value = head->value;
	//printf("end val: %d\n", head->value);
	//free(head);
	return 1;
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
	llist_add(list, value);
}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {
	/*
	if(list->head == NULL){
		ListNode * e = (ListNode*) malloc(sizeof(ListNode));
		e->value = value;
		e->next=NULL;
		list->head = e;
		return;
	}
	*/
	ListNode* e = list->head;
	ListNode* prev = NULL;
	while(e!=NULL){
		prev = e;
		e = e->next;
	}
	ListNode* element = (ListNode*) malloc (sizeof(ListNode));
	element->value = value;
	element->next = NULL;
	if(prev==NULL){
		list->head = element;
	}else{
		prev->next= element;
	}

}

//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{
//list->head = NULL;
	if(list->head==NULL){
		return;
	}
	ListNode* head = list->head;
	ListNode* temp = head->next;

	while(head){
		temp=head->next;		
		//printf("Freeing head: %d\n", head->value);
		free(head);
		head=temp; 
		//head = temp;
		//head = head->next;
		//temp = temp->next;
	}
	list->head = NULL;
	//free(head);
	
}
