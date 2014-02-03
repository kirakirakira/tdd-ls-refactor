/*!
 * @file
 * @brief Singly-linked list data structure.
 *
 * Copyright (c) 2014 - General Electric - All rights reserved.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedListNode_t
{
   struct LinkedListNode_t *next;
} LinkedListNode_t;

typedef struct
{
   LinkedListNode_t *head;
} LinkedList_t;

void LinkedList_Init(LinkedList_t *instance);

// TODO
// Count -- Get the number of elements in the list
// PushFront -- Add element to the head (front) of the list
// PushBack -- Add element to the tail (back) of the list
// PopFront -- Remove and return the element at the head (front) of the list
// PopBack -- Remove and return the element at the tail (back) of the list
// Remove -- Remove a specific element from the list given its pointer
// At -- Returns the element at a specified index

#endif
