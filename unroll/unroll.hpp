#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class uncompress{

    public:

        uncompress(int argc,char **argv); // [unroll.cpp]

        //main [unroll.cpp]
        int main_uncompress();

        //arguments [arguments.cpp]
        int check_arguments();
        void print_help();

        //file check [file_check.cpp]
        void check_comp();
        int check_version_compatibility();

        //file name [file_name.cpp]
        void get_file_name();

        //uncompression algorithms [uncompression_algorithms.cpp]
        int classical_unroll();
        void get_output_filename();
        void get_marker();

    private:

        string file_name; // the file's name, if specified
        string output_filename; // the name of the output

        int argc; // the number of arguments given
        char **argv; // the arguments given

        vector<char> buffer; // the file contents in a buffer
        
        int compression_type; // the compression type to be used
        int byte_max; // used by classical roll function

        int max_version_compatible;// the maximum version of roll that is tolerated
        int unroll_version;// for checking if the roll version is compatible

        uint8_t rle_marker ; // used by classical roll for round

};
