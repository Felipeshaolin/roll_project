#include "unroll.hpp"

// arguyments

// a function to check if there are arguments
int uncompress::check_arguments(){

    if (this->argc == 1){
        
        cout << "\n[error] no arguments present \n use -h for help\n" << endl;
        return 0;
    }
    return 1;
}

void uncompress::print_help() {

    for ( int index = 1 ; index < this->argc ; index ++ ){

        if (string(this->argv[index]) == "-h"){

            cout << "unroll version : " << this->unroll_version << endl;
            cout << "compatible with unroll version <=" << this->max_version_compatible << "\n" << endl;
            cout << "\nUsage: roll [OPTION]... -o [FILE]... -f [FILE]..." << endl;
            cout << "-f    used for choosing the file_name of the file to compress" << endl;
            cout << "-c    run lenght encoding, default compression algorithm\n       most of the time this algorithm is not eficient at all." << endl;
            cout << "-h    shows help" << endl;
            cout << "-o    specifies the output file's name,the default is the parent file's name" << endl;

        }
    }

}
