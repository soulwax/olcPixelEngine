#include <iostream>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Main : public olc::PixelGameEngine
{
public:
    Main()
    {
        sAppName = "Main";
    }
    ~Main()
    {
        std::cout << "Destructor on " << "Main" << " called..." << std::endl;
    }
public: 
    bool OnUserCreate() override
    {
        // Called once at the start, so create things here
        return true;
    }
    
    bool OnUserUpdate(float fElapsedTime) override
    {
        // called once per frame
        for (int x = 0; x < ScreenWidth(); x++)
            for (int y = 0; y < ScreenHeight(); y++)
                Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));	
        return true;
    }
};


int main(int, char**) {
    Main demo;
    if (demo.Construct(256, 240, 4, 4))
        demo.Start();
    return 0;
    std::cout << "Hello, world!\n";
}
