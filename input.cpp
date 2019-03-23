// basic file operations
#include <iostream>
#include <fstream>
using namespace std;

void input_discrete(){ ///TLM TODO 2019!
    std::ifstream infile("thefile.txt");
    std::string line;
    while (std::getline(infile, line)){

        std::istringstream iss(line);
        int a, b;
        if (!(iss >> a >> b)) { break; } // error

        // process pair (a,b)
    }
}

int main () {
  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();
  return 0;
}