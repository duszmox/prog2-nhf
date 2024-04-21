#include "szo.h"
#include <iostream>

int main()
{
    Szo s1("kukkendare");
    Szo s2("kukikkkaie");
    Match *match = s2.match(s1);
    for (int i = 0; i < s1.getLength(); i++)
    {
        if (match[i].getMatch() == MATCH)
        {
            std::cout << s1[i] << " ";
        }
        else if (match[i].getMatch() == PARTIAL)
        {
            std::cout << ". ";
        }
        else
        {
            std::cout << "_ ";
        }
    }
    std::cout << std::endl;
    delete[] match;
}