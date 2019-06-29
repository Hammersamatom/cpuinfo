#include <fstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <iostream>

const char cpupath[] = {"/proc/cpuinfo"};

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

    int i = 0;

    while(getline(cpuinfo, container))
    {
        //strReplace(container, "\n", "\r");
        strReplace(container, ":", "\n\r");
        contain.push_back(container);
        
        printf("%i --- %s\n", i, container.c_str());
        i++;
    }

    //for (int i = 0; i < contain.size(); i++)
    //{
    //    printf("%s\n", contain[i].c_str());
    //}
    
    return 0;
}