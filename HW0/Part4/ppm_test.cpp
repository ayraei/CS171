#include <stdio>

using namespace std;

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
    
    return 0;
}
