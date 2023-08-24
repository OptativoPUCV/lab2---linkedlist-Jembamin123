#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* newList =(List*)malloc(sizeof(List));
  if(newList==NULL){
    exit(EXIT_FAILURE);
  }
  newList->head = NULL;
  return newList;
}

void * firstList(List * list) {
  if(list->head !=NULL){
    list->current =list->head;
    return list->current->data;
  }
  return NULL;
}

void * nextList(List * list) {
  if(list->current !=NULL && list->current->next !=NULL){
    list->current = list->current->next;
    return list->current->data;
  }
  return NULL;
}

void * lastList(List * list) {
  if(list->tail !=NULL){
    list->current =list->tail;
    return list->current->data;
  }
  else{
    return NULL;
  }
}

void * prevList(List * list) {
  if(list->current !=NULL && list->current->prev !=NULL) {
    list->current = list->current->prev;
    return list->current->data;
  }
  else{
      return NULL;
    }
}

void pushFront(List * list, void * data) {
  Node* newNode=createNode(data);
  newNode->next=list->head;

  list->head=newNode;
  list->tail=newNode;
}

void pushBack(List * list, void * data) {
  Node* newNode=createNode(data);
  newNode->current=list->head;

  list->head=newNode;
  list->tail=newNode;
}
//===================================================================
void pushCurrent(List * list, void * data) {
  Node* newNode=createNode(data);
  newNode=list->current;
}
//===================================================================
void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}
void * popCurrent(List * list) {
    if(list->current ==NULL){
      return NULL;
    }
    Node* currentNode =list->current;
    void* data =currentNode->data;

    if(currentNode->prev != NULL){
      currentNode->prev->next = currentNode->next;
    } 
    else{
      list->head =currentNode->next;
    }
  
    if(currentNode->next !=NULL){
      currentNode->next->prev = currentNode->prev;
    } 
    else{
      list->tail =currentNode->prev;
    }
  
    if(currentNode->prev ==NULL && currentNode->next ==NULL){
      list->head =NULL;
      list->tail =NULL;
    }
  
    list->current =currentNode->next;
    free(currentNode);
    return data;
}

void cleanList(List * list) {
    while (list->head !=NULL){
      popFront(list);
    }
}