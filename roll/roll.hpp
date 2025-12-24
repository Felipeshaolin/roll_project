#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>  // for std::find

using namespace std;

class compress{

    public:

    compress(int argc,char **argv);

    //main
    int main_compress();
    
    //arguments
    int check_comp();
    int check_arguments();
    void print_help();

    //file name
    void create_output_filename();
    string get_file_name();
    string get_output_name();
    
    //compresion argorithms ans sub-functions

    //rle
    int check_byte_max_value();
    int classical_roll();
    int check_rlecompatible();

    // ...

    private:

    string file_name; // the file's name, if specified
    string output_filename; // the name of the output
    bool output_decided; // bool for knowing if output was choosen or not

    int argc; // the number of arguments given
    char **argv; // the arguments given

    vector<char> buffer; // the file contents in a buffer
    
    int compression_type; // the compression type to be used
    int byte_max; // used by classical roll function

    int roll_version;// for checking if the roll version is compatible

    uint8_t rle_marker ; // used by classical roll for round

};