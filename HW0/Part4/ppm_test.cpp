#include <stdio.h>
#include <iostream>

using namespace std;

string green();
string blue();
bool inCircle(int r, int x, int y);

int main(int argc, char** argv)
{
    // Check correct number of input arguments. Assumes arguments are ints
    if(argc != 3)
    {
        cout << "Usage: " << argv[0] << " xres yres" << endl;
        exit(1);
    }
    
    int xres = atoi(argv[1]);
    int yres = atoi(argv[2]);
    int r;
    
    // Set the correct radius of the circle
    if(yres < xres)
        r = yres / 2;
    else
        r = xres / 2;
    
    // Initialization lines for the PPM file
    cout << "P3\n" << xres << " " << yres << endl;
    cout << "255\n";
    
    // Iterate through each pixel, where (0,0) is the center of the image
    for(int i = -yres/2; i <= yres/2; i++)
    {
        for(int j = -xres/2; j <= xres/2; j++)
        {
            if(i == 0 || j == 0)
                continue;
            if(inCircle(r, i, j))
            {
                cout << blue() << endl;
            }
            else
            {
                cout << green() << endl;
            }
        }
    }
    
    return 0;
}

// Returns the RGB value for green
string green()
{
    return "0 255 0";
}

// Returns the RGB value for blue
string blue()
{
    return "0 0 255";
}

// Returns whether the point (x, y) falls within a circle of radius r
bool inCircle(int r, int x, int y)
{
    return (x*x + y*y) <= r*r;
}
