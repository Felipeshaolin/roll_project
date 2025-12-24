#include "unroll.hpp"
// file check

//a function to get the type of compression
void uncompress::check_comp(){

    for ( int index = 1 ; index <= this -> argc  ; index ++ ){

        if (this->argv[index] == "-c"){ // only option for now

            this->compression_type = 1;
            return ;

        }

        //...
    }

    this->compression_type = 1;

    
}

int uncompress::check_version_compatibility(){
    
    // check if "ROLL" is present in the start of the file
    if ( (this->buffer[0] == 'R') && (this->buffer[1] == 'O') && (this->buffer[2] == 'L') && (this->buffer[3] == 'L') ) { cout << "[error] not a ROLL file" << endl; ;return -1;} 

    // check if roll version is old
    if ( (int)this->buffer[4] > this->max_version_compatible ) { cout << "[error] this ROLL file is too new, use a newer version of unroll with version > " << this->max_version_compatible << endl; return -1;}

    return 1;

}
