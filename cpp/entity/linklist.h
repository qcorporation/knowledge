#include <iostream>
#include <string.h>

template<typename T>
class SLL {
public:

    class Node {
        T data_;
        Node* next_;
    };

    SLL(){}
    Node* head_ = {};
};