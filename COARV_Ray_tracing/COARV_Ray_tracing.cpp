
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    int nx = 400; // Image width
    int ny = 200; // Image height
    string output_name = "ch1";

    ofstream fichier("../../Images/" + output_name + ".ppm"); // Open a file in writing mode

    if (!fichier) {
        cerr << "Error : " + output_name + ".ppm  cannot be written or created" << endl;
        return 1;
    }

    // We write the header of the ppm file (ASCII P3 format)
    fichier << "P3\n" << nx << " " << ny << "\n255\n";

    // We generate the image
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);

            // We write the image with the 3 colors for each pixels in the ppm file
            fichier << ir << " " << ig << " " << ib << "\n";
        }
    }

    fichier.close(); // We close the ppm file

    cout << "Image is saved under '" + output_name + ".ppm'" << endl;
    return 0;
}
