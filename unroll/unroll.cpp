#include "unroll.hpp"


//contructor

uncompress::uncompress( int argc, char **argv  ){

    this->argc = argc;
    this->argv = argv;
    this -> compression_type = 1;// default compression types
    this -> output_filename = "output.roll";// default output file name
    this -> max_version_compatible = 2;
    this -> rle_marker = 0x04; // default 

}

// main


int uncompress::main_uncompress(){

    if (this->check_arguments()){

        this-> print_help();

    }else{

        return 1;
    }

    this->get_file_name(); // get file name of arguments

    ifstream in_file( this -> file_name , ios::binary); // open file

    if (!in_file) { //checking file
        std::cerr << "\n[error] cannot find file\n" << std::endl;
        return 1;
    }

    //getting file size
    in_file.seekg(0, std::ios::end); 
    streampos size = in_file.tellg();
    in_file.seekg(0, std::ios::beg);

    vector<char> buffer(size);//creating a buffer for the data
    in_file.read(buffer.data(), size);

    //get simple info from file
    if ( this->check_version_compatibility() == -1 ){ return 1; }
    // get the compression type
    this->check_comp() ;

    this-> buffer = buffer;

    switch (this->compression_type)
    {
    case 2:
        // ...
        break;
    
    default:
        this->classical_unroll();
    }

    in_file.close();

    return 1;

}


