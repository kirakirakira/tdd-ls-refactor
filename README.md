tdd-linked-list
===============

In this example you will implement a simple singly-linked linked list.  The linked list itself is just a pointer to the first node in the list (the 'head' or 'front').  Each node in the list points to the next node so that any number of nodes can be contained in the list.

This linked list is unique in that the client (the code that wants to add to the list) is responsible for allocating the memory for the nodes in the list instead of being malloc'ed in the linked list implementation.  This allows a library module to contains an indeterminately long list without a statically sized array or a heap.

A basic header file, an empty source file, and a test file have been provided for you:

/Source/LinkedList.h -> Provided header file (incomplete)
/Source/LinkedList.c -> Provided source file (empty)
/Testing/Tests/LinkedList_Test.cpp -> Starter tests and first failing test

You will need to edit all of these files to complete the exercise.  To make it easier to get started there are some tests provided that are commented out.  You should un-comment (and complete) these tests one-by-one to finish most of the exercise, but these tests are not sufficient and you should write more if you have time.
