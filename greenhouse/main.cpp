#include "ramus/Core/App.hpp"

int main() 
{
    ramus::App::Config config { "Ramus Greenhouse", 1600, 900 };
    ramus::App app(config); 
    if (app.Init()) 
    {
        app.Run();
    }

    return 0;
}