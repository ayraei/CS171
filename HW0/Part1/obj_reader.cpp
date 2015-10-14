#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

struct Vertex
{
    float x;
    float y;
    float z;
};

struct Face
{
    int v1;
    int v2;
    int v3;
};

struct Object
{
    vector<Vertex> vertices;
    vector<Face> faces;
};

Object read_obj(char* filename);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

int main(int argc, char* argv[])
{
    // No filenames provided as arguments, print usage statement
    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " file1 [file2] [file3] ...\n";
        exit(1);
    }
    
    cout << "Reading files...\n";
    
    vector<Object> objects;
    
    // Read files in
    for (int i = 1; i < argc; i++)
    {
        objects.push_back(read_obj(argv[i]));
    }
    
    // Print file contents back out
    for (int i = 1; i < argc; i++)
    {
        cout << "\n" << argv[i] << ":\n\n";
        // Print vertices
        for (int j = 1; j < objects[i-1].vertices.size(); j++)
        {
            printf("v %f %f %f\n", objects[i-1].vertices[j].x,
                   objects[i-1].vertices[j].y,
                   objects[i-1].vertices[j].z);
        }
        // Print faces
        for (int j = 0; j < objects[i-1].faces.size();j++)
        {
            printf("f %d %d %d\n", objects[i-1].faces[j].v1,
                   objects[i-1].faces[j].v2,
                   objects[i-1].faces[j].v3);
        }
    }
    
    return 0;
}

/*
 * This method reads in an .obj file specified by filename and stores its
 * contents in an Object struct that it returns.
 */
Object read_obj(char* filename)
{
    ifstream f;
    f.open(filename);
    string line;
    Object o;
    // to 1-index vertices
    o.vertices.push_back(Vertex());
    
    // Iterate over every line in the obj file
    while (getline(f, line))
    {
        vector<string> toks;
        split(line, ' ', toks);
        
        // Line contains vertex information
        if (!toks[0].compare("v"))
        {
            Vertex v;
            v.x = stof(toks[1]);
            v.y = stof(toks[2]);
            v.z = stof(toks[3]);
            
            o.vertices.push_back(v);
        }
        // Line contains face information
        else if (!toks[0].compare("f"))
        {
            Face f;
            f.v1 = stoi(toks[1]);
            f.v2 = stoi(toks[2]);
            f.v3 = stoi(toks[3]);
            
            o.faces.push_back(f);
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
    
    return o;
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
