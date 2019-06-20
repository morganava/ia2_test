// windows
#include <windows.h>
#include <oleacc.h>
#include <initguid.h>

// c++
#include <cstdint>
#include <cstdio>
#include <string>
#include <regex>
#include <iostream>
#include <memory>

#include "logger.hpp"
#include "com_ptr.hpp"
#include "interfaces.hpp"
#include "bstr.hpp"
#include "dumper.hpp"

namespace rap
{
    void SelectItemAtPoint(int x, int y)
    {
        try
        {
            POINT point = {(LONG)x, (LONG)y};
            HWND hw = WindowFromPoint(point);
            printf("HWND: %p\n", hw);

            com_ptr<IAccessible> pIA;

            THROW_IF_FAILED(AccessibleObjectFromWindow(hw, OBJID_CLIENT, IID_IAccessible, (void**)&pIA));
            dump_ia(pIA);
        }
        catch(...) {}
    }

    int main(int argc, char** argv)
    {
        LOG_IF_FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED));


        // event loop
        const std::regex pointRegex("^\\s*([0-9]+)\\s*[,]{0,1}\\s*([0-9]+)\\s*$");
        puts("Ready!");
        for (std::string line; []() -> bool {printf("$ "); return true;}() && std::getline(std::cin, line);)
        {
            if (line == "quit") {
                return 0;
            }

            if (line == "mouse") {
                POINT p;
                if (GetCursorPos(&p))
                {
                    printf("POINT : { x : %i, y : %i }\n", (int32_t)p.x, (int32_t)p.y);
                    SelectItemAtPoint(p.x, p.y);
                }
                else
                {
                    fprintf(stderr, "Could not read cursor position\n");
                }
                continue;
            }

            std::smatch matches;
            if (std::regex_match(line, matches, pointRegex))
            {
                int x = atoi(matches[1].str().c_str());
                int y = atoi(matches[2].str().c_str());

                SelectItemAtPoint(x, y);
            } else
            {
                fprintf(stderr, "Could not parse '%s' as POINT\n", line.c_str());
            }
        }

        return 0;
    }
}

int main(int argc, char** argv)
{
    return rap::main(argc, argv);
}
