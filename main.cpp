// reading a text file
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main (int argc, char **argv) {
    // user input:
    ifstream infile;
    streampos begin,end;
    string infilename;

    cout << "Please enter the input file name> " << flush;
    cout << "Default is fifi.dat" << endl;
    while (true){

        getline( cin, infilename );
        if (infilename.length()>1){

            cout << "Opening " << infilename <<endl;
        }
        else{

            infilename = "fifi.dat";
            cout << "Opening " << infilename <<endl;
        }
        infile.open( infilename.c_str() );
        if (infile) break;
        cout << "Invalid file. Please enter a valid input file name> " << flush;
    }

    //my bs:
    // if (argc>1){
    //     nElem = atoi(argv[1]);
    //     nElem = 1 << nElem; 
    // }
    // else{
    //     //int nElem = 1 << 24;
    //     nElem = 1 << 5;
    //     //int nElem = 1000000;
    // }
    // printf("Vector size %d\n", nElem);

    string line;
    if (infile.is_open()){
        // begin = infile.tellg();
        // infile.seekg (0, ios::end);
        // end = infile.tellg();
        // infile.seekg (0, ios::beg);

        while ( getline (infile,line) ){

            cout << line << '\n';
        }
        infile.close();
    }

    else cout << "Unable to open file"; 

    return 0;
}