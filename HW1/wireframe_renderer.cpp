// Parse the scene description and put the data into Object structs.
//     reuse part3 of HW0 if possible

// Create transformation matrix for converting between WORLD COORDINATES and
// CAMERA COORDINATES. Also create PERSPECTIVE PROJECTION MATRIX.

// For each object-copy in the scene, transform each of its points by all the
// GEOMETRIC TRANSFORMATIONS that are to be applied to the object-copy.
// From there, transform all the points into NORMALIZED DEVICE COORDINATES (NDC)
// Remember to scale by the HOMOGENEOUS (w) COMPONENT to convert the resultant,
// *homogeneous* NDC to *Cartesian* NDC!

// Devise an appropriate mapping from NDC to SCREEN COORDINATES in a
// yres-by-xres PIXEL GRID. Remember to discard any points that were mapped
// to the outside of the perspective cube when you were converting from
// camera coordinates to NDC. Ignore the z-coordinates of the points during your
// mapping.

// Generalize BRESENHAM'S LINE ALGORITHM to draw lines in all octants.
// In class, we introduced the algorithm for rasterizing lines with slopes [0, 1].
// You need to generalize this algorithm so that it can rasterize lines of all
// slopes. EXPLAIN HOW YOU GENERALIZE AND IMPLEMENT IN README OR CODE COMMENTS
// Hint: The alg. doesn't change much for other slopes, just need clever "swaps"
// Once you have implemented it, you can use it to outline every face in the
// object-copy to draw the wireframe models. You can fill in the pixels of
// your output with whatever colors you like as long as the output looks approp.

// Output the pixel grid to standard output as a .ppm image file.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
using namespace Eigen;

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
    string name;
};

Object read_obj(char* filename);
vector<string> &split(const string &s, char delim, vector<string> &elems);

int main(int argc, char* argv[])
{
    // No filenames provided as arguments, print usage statement
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " scene_description_file.txt xres yres\n";
        exit(1);
    }
    
    // Output image resolution
    int xres = atoi(argv[2]);
    int yres = atoi(argv[3]);
    
    cout << "Reading file...\n";
    
    vector<Object> objects;
    Camera c;
    
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
vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
