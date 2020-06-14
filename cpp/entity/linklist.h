#include <iostream>
#include <sstream>
#include <string.h>
#include <assert.h>

#include "perf.h"

template <typename Any>
class SLL : public Perf
{
    struct Node
    {
        Node(const Any &t) : data(t) {}
        Any data;
        Node *next = {};
    };
    Node *head = {};

    bool has_loop()
    {
        if (nullptr == head || nullptr == head->next || nullptr == head->next->next)
        {
            return false;
        }

        Node *inc, *d_inc;
        inc = head->next;
        d_inc = head->next->next;
        uint64_t counter = 0;
        while (nullptr != inc && ++counter)
        {
            if (inc == d_inc)
            {
                // loop found!
                std::cout << "loop found! @ " << inc->data << std::endl;
                std::cout << "number of iterations until found: " << counter << std::endl;
                return true;
            }
            inc = inc->next;
            if (nullptr == d_inc->next || nullptr == d_inc->next->next)
            {
                return false;
            }
            d_inc = d_inc->next->next;
        }
        return false;
    }

public:
    SLL() {}
    SLL(const SLL &other)
    {
    }

    ~SLL()
    {
        clear();
    }

    void push_front(const Any &data)
    {
        if (nullptr == head)
        {
            head = new Node(data);
        }
        else
        {
            Node *node = new Node(data);
            node->next = head;
            head = node;
        }
    }

    void push_back(const Any &data)
    {
        if (nullptr == head)
        {
            head = new Node(data);
        }
        else
        {
            Node *curr_node = head;
            while (nullptr != curr_node->next)
            {
                curr_node = curr_node->next;
            }

            curr_node->next = new Node(data);
        }
    }

    void pop()
    {
        if (nullptr == head)
            return;

        Node *holder = head;
        head = head->next;
        delete holder;
    }

    void pop_back()
    {
        if (nullptr == head)
            return;
        if (nullptr == head->next)
        {
            delete head;
            head = nullptr;
            return;
        }

        Node *curr_node = head;
        while (nullptr != curr_node->next->next)
            curr_node = curr_node->next;

        delete curr_node->next;
        curr_node->next = nullptr;
    }

    void clear()
    {
        if (!has_loop())
        {
            while (head)
                pop();
        }
    }

    bool contains(const Any &entry)
    {
        const Node *curr_node = head;
        while (curr_node)
        {
            if (curr_node->data == entry)
            {
                return true;
            }
            curr_node = curr_node->next;
        }
        return false;
    }

    void to_string() const
    {
        const Node *curr_node = head;
        while (curr_node)
        {
            std::cout << curr_node->data << (curr_node->next ? ", " : "\n");
            curr_node = curr_node->next;
        }
    }

    bool force_loop(uint32_t idx)
    {
        assert(nullptr != head);

        Node *loop_node = head;
        while (--idx)
        {
            if (nullptr == loop_node->next)
            {
                return false;
            }
            loop_node = loop_node->next;
        }

        Node *end_node = loop_node;
        while (nullptr != end_node->next)
        {
            end_node = end_node->next;
        }

        end_node->next = loop_node;
        return true;
    }

    void reverse_iter()
    {
        start_timer();

        // nothing to do if there is just one entry
        if (nullptr == head || nullptr == head->next)
            return;

        Node *prev{}, *curr{}, *next{};
        curr = head;
        while (curr->next)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = curr;
        curr->next = prev;

        end_timer();
        std::cout << "reverse_iter took: " << diff<nanoseconds>() << "ns\n";
    }

    void reverse_node(Node *prev, Node *curr)
    {
        if (nullptr == curr)
        {
            head = prev;
            return;
        }

        Node *next = curr->next;
        curr->next = prev;
        reverse_node(curr, next);
    }

    void reverse_recurse()
    {
        start_timer();
        Node *prev{}, *curr = head;
        reverse_node(prev, curr);

        end_timer();
        std::cout << "reverse_recurse took: " << diff<nanoseconds>() << "ns\n";
    }
};

template <typename T>
class DLL
{
private:
    struct Node
    {
        Node(const T &data) : data(data) {}
        T data;
        Node *next{};
        Node *prev{};
    };

    Node *head{};
    Node *tail{};

public:
    DLL() {}
    void push_back(T data)
    {
        if (nullptr == tail)
        {
            head = tail = new Node(data);
        }
        else
        {
            tail->next = new Node(data);
            tail->next->prev = tail;
        }
    }

    void push_front(T data)
    {
        if (nullptr == head)
        {
            head = tail = new Node(data);
        }
        else
        {
            Node *new_node = new Node(data);
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }
};