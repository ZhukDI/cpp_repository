#pragma once

#include "globals.h"

struct Node
{
	int data;
	Node* next;
	Node* prev;

	Node();
	Node(int);
};