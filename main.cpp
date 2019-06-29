#include <fstream>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <iostream>

const char* cpupath = "/proc/cpuinfo";


std::vector<std::string> split(std::string str, char c = ' ')
{
    std::vector<std::string> result;

    const char* c_str = str.c_str();

    do
    {
        const char *begin = c_str;

        while(*c_str != c && *c_str)
            c_str++;

        result.push_back(std::string(begin, c_str));
    } while (0 != *c_str++);

    return result;
}

void strReplace(std::string& input, std::string original, std::string replacement)
{
    int pos = input.find_first_of(original);
    
    //printf("pos: %i\noriginal: %s\nreplacement: %s\n", pos, original, replacement);

    if (pos != -1)
    {
        input.replace(pos, replacement.length(), replacement);
    }
    
}

int main()
{
    std::ifstream cpuinfo(cpupath, std::ios::binary);

    if (!cpuinfo.is_open())
    {
        printf("Cannot open file: %s\n", cpupath);
        return 1;
    }


    std::vector<std::string> contain;

    std::string container;

    while(getline(cpuinfo, container))
    {
        strReplace(container, ":", "\n\r");

        if (container == "")
        {
            break;
        }

        std::vector<std::string> tokens = split(container,'\n');
        for (int i = 0; i < tokens.size(); i++)
        {
            contain.push_back(tokens[i]);
        }

        //contain.push_back(container);
    }

    for (int i = 0; i < contain.size(); i++)
    {
        printf("%s\n", contain[i].c_str());
    }
    
    return 0;
}
