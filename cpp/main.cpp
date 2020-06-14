#include <vector>
#include "entity/linklist.h"

int main()
{

    for (int range = 2; range < 500; range += 10)
    {
        std::cout << "--------- stats @ " << range << "-------------\n";
        int count = 0;
        SLL<int> list;
        while (count++ < range)
        {
            list.push_back(count);
        }

        list.reverse_iter();
        list.reverse_recurse();
        std::cout << "\n\n";
    }
}