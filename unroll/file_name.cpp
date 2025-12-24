#include "unroll.hpp"

// file name
void uncompress::get_file_name(){
    
    for ( int index = 1 ; index < this->argc ; index ++ ){

        if (string(this->argv[index]) == "-f"){

            this->file_name = this->argv[index + 1];
        }
    }

    // Check if filename is empty
    cout << "\n[error] No file provided. Use -f option with a file name." << endl;

}
