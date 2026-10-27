#include <iostream>
#include "app/CLIApp.hpp"

int main()
{
    std::cout << "[SYSTEM] Synapse Engine initialized.\n";

    CLIApp app;
    app.run();
    return 0; 
}