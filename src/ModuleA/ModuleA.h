#pragma once

#ifdef MODULEA_EXPORTS
#define MODULEA_API __declspec(dllexport)
#else
#define MODULEA_API __declspec(dllimport)
#endif

namespace ModuleA {
    class MODULEA_API Calculator {
    public:
        int Add(int a, int b);
        int Subtract(int a, int b);
    };
}
