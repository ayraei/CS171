#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <Eigen/Dense>
#include <Eigen/LU>

using namespace Eigen;
using namespace std;

MatrixXd read_trans(char* filename);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

int main(int argc, char** argv)
{

    // No filenames provided as arguments, print usage statement
    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " filename\n";
        exit(1);
    }
    
    std::cout << "Reading file...\n";
    
    //vector<MatrixXd> matrices;
    MatrixXd mIn(4,4);
    MatrixXd mCurr(4,4);
    
    
    // Read files in
    for (int i = 1; i < argc; i++)
    {
        //matrices.push_back(read_obj(argv[i]));
        mIn = read_trans(argv[1]);
        cout << mIn.inverse() << "\n";
    }
    
    return 0;
}

MatrixXd read_trans(char* filename)
{
    ifstream f;
    f.open(filename);
    string line;
    MatrixXd mIn(4,4);
    MatrixXd curr(4,4);
    MatrixXd output(4,4);
    curr = MatrixXd::Identity(4,4);
    
    // Iterate over every line in the file
    while (getline(f, line))
    {
        vector<string> toks;
        split(line, ' ', toks);
        
        // Line contains translation information
        if (!toks[0].compare("t"))
        {
            mIn << 1, 0, 0, stof(toks[1]),
                   0, 1, 0, stof(toks[2]),
                   0, 0, 1, stof(toks[3]),
                   0, 0, 0, 1;
            output = mIn*curr;
            curr = output;
        }
        // Line contains scaling information
        else if (!toks[0].compare("s"))
        {
            mIn << stof(toks[1]), 0, 0, 0,
                   0, stof(toks[2]), 0, 0,
                   0, 0, stof(toks[3]), 0,
                   0, 0, 0, 1;
            output = mIn*curr;
            curr = output;
        }
        // Line contains rotation information
        else if (!toks[0].compare("r"))
        {
            float rx = stof(toks[1]);
            float ry = stof(toks[2]);
            float rz = stof(toks[3]);
            
            float ang = stof(toks[4]);
            float s = sin(ang);
            float c = cos(ang);
            
            mIn << c+rx*rx*(1-c), rx*ry*(1-c)-rz*s, rx*rz*(1-c)+ry*s, 0,
                   ry*rx*(1-c)+rz*s, c+ry*ry*(1-c), ry*rz*(1-c)-rx*s, 0,
                   rz*rx*(1-c)-ry*s, rz*ry*(1-c)+rx*s, c+rz*rz*(1-c), 0,
                   0, 0, 0, 1;
            output = mIn*curr;
            curr = output;
        }
        // Unrecognized line, exit
        else
        {
            cout << "Unparseable line encountered:\n";
            cout << line;
            exit(1);
        }
    }
    
    f.close();
    
    return curr;
}

/*
 * This method tokenizes a string by a given delimiter.
 * Found on StackOverflow.
 */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
