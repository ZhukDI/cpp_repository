#include <iostream>
#include "Node.h"

Node::Node() : data(0), next(NULL), prev(NULL) {}

Node::Node(int value) : data(value), next(NULL), prev(NULL) {}