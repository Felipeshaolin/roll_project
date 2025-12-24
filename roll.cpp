
#include "roll.hpp"

using namespace std;

// what roll can do for now
//
// -h : for help
// -f : for using a file
// -c : classical compressing method (default)
//
//compression types:
//
// classic (my weird and uniptimized compression algorhtm) ( 1 )
// 
//      in this compression type the file will have a variable size header,
// and each duplicated byte will be written as a number and then the value.
// for exemple:
//
//  255 255 255 255 -> 04 255  # 4x compression rate !!!!
//
// this algorithm is NOT good in cases where all the items are equal or where
// a big number of the value are repeated, because the amount of bytes taken 
// will far exceed the original count.
//
// ... to be continued ...
//

//constructor 


compress::compress(int argc,char ** argv){

    this -> compression_type = 1;// default compression types
    this -> argc = argc;
    this -> argv = argv;
    this -> output_filename = "output.roll";// default output file name
    this -> output_decided = false;
    this -> roll_version = 2;
    this -> rle_marker = 0x04; // default

}


// main


int compress::main_compress(){

    if (this->check_arguments()){

        this-> print_help();
        this -> compression_type = this -> check_comp(); // get the compression type

    }else{

        return 1;
    }

    this -> file_name = get_file_name(); // get file name

    ifstream in_file( this -> file_name , ios::binary); // open file

    this->create_output_filename(); // create the output file name

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

    this-> buffer = buffer;

    if (compression_type == 1){

        classical_roll();
    }

    in_file.close();

    return 1;

}




// arguments

//a function to get the type of compression
int compress::check_comp(){

    for ( int index = 1 ; index <= this -> argc  ; index ++ ){

        if (this->argv[index] == "-c"){ // only option for now

            return 1;

        }

        //...
    }

    return 1;
}

// a function to check if there are arguments
int compress::check_arguments(){

    if (this->argc == 1){
        
        cout << "\n[error] no arguments present \n use -h for help\n" << endl;
        return 0;
    }
    return 1;
}

void compress::print_help() {

    for ( int index = 1 ; index < this->argc ; index ++ ){

        if (string(this->argv[index]) == "-h"){

            cout << "roll version : " << this->roll_version << endl;
            cout << "\nUsage: roll [OPTION]... -o [FILE]... -f [FILE]..." << endl;
            cout << "-f    used for choosing the file_name of the file to compress" << endl;
            cout << "-c    run lenght encoding, default compression algorithm\n       most of the time this algorithm is not eficient at all." << endl;
            cout << "-h    shows help" << endl;
            cout << "-o    specifies the output file's name,the default is the parent file's name" << endl;

        }
    }

}


// algorithms




// ###  #    ####
// # #  #    #
// ##   #    ####
// # #  #    #
// #  # #### ####



int compress::check_byte_max_value() {

    if (this->buffer.empty()) return 0;

    char temp = this->buffer[0];
    int max_count = 1;
    int current_count = 1;

    for (size_t i = 1; i < this->buffer.size(); i++) {
        if (this->buffer[i] == temp) {
            current_count++;
        } else {
            if (current_count > max_count)
                max_count = current_count;

            temp = this->buffer[i];
            current_count = 1;
        }
    }

    // Check last run
    if (current_count > max_count)
        max_count = current_count;

    if (max_count>255){

        cout << "[error] a file with more than 255 repetitions TODO: implement this" << endl;
        return -1 ;// error code
    }

    return max_count;
}

//returns a value that classical roll can use as a marker or, if not possible, will simply return -1
int compress::check_rlecompatible(){

    uint8_t good_marker = 0; 

    while(true){


        if ( find(this->buffer.begin(), this->buffer.end(), (char)good_marker) != this->buffer.end()) {}
        else{
        
            return good_marker;

        }
    }

}


// a function for run lenght encoding
int compress::classical_roll(){

    int comp = this->check_rlecompatible(); // a temporary variable
    if ( comp != -1){ this->rle_marker = comp; } else{ cout << " [error] no compatible markers for this file, used another compression algorithm " << endl; return 1; } // to see if the file is compretible

    this -> byte_max = check_byte_max_value(); // used to find the maximal number of repetitions of a byte on a file

    if ( this->byte_max == -1){ return 1; }

    ofstream out_file(this->output_filename, ios::app | ios::binary);


    //header

        out_file.write("ROLL",sizeof("ROL")); // file signature

        int tempo = this->roll_version;
        out_file.write((char *) &tempo, 1);// roll version

        tempo = this->compression_type;
        out_file.write((char *) &tempo, 1);// compression type

        tempo = this->rle_marker;
        out_file.write((char *) &tempo, 1);// the marker used

        tempo = this->file_name.size();
        if (tempo > 255){ cout << "[error] filename to big "; out_file.clear(); out_file.close(); return 1; } // if file name bigger than 255 then declare error and close file
        out_file.write((char *) &tempo, 1); // filename size (max 255)
        out_file.write( this->file_name.c_str() , tempo ); // write the filename into the file

    //file contents

        bool start_of_file = true;

        uint8_t temp;
        int numb_of_equal = 1;
        int numb_of_different = 0;

        int index = 0;
        uint8_t marker = this -> rle_marker ;

        bool in_literal = false;   // Whether we are inside {marker ... marker}

        while (index < (int)this->buffer.size())
        {
            char curr = this->buffer[index];

            // --- Count run of equal characters ---
            int run_start = index;
            while (index < (int)this->buffer.size() &&
                this->buffer[index] == curr)
            {
                index++;
            }
            int run_len = index - run_start;

            // --- Case 1: repeating block (length > 1) ---
            if (run_len > 1)
            {
                // Close literal block if we were in one
                if (in_literal) {
                    out_file.write((char*)&marker, 1);
                    in_literal = false;
                }

                // Write RLE block: [count][char]
                uint8_t len8 = (uint8_t)run_len;
                temp = (uint8_t)curr;
                out_file.write((char*)&len8, 1);
                out_file.write((char*)&temp, 1);
            }
            else
            {
                // --- Case 2: single-character literal block ---

                // Open literal block if this is the first char in it
                if (!in_literal) {
                    out_file.write((char*)&marker, 1);
                    in_literal = true;
                }

                // Write literal char
                temp = (uint8_t)curr;
                out_file.write((char*)&temp, 1);
            }
        }

        // Close literal block if left open
        if (in_literal) {
            out_file.write((char*)&marker, 1);
        }

    out_file.close();
    return 1;

}


//file name


void compress::create_output_filename(){

    if (!this->output_decided){

        this->output_filename = this->file_name;
        int output_filename_size  = this->file_name.size(); // filename string size


        for (int letter_index = output_filename_size ; letter_index > 0; letter_index -= 1){

            if ( this->output_filename[letter_index] == '.' ){ // search fro the '.' character

                this->output_filename.erase(letter_index); // remove the file extension
                this->output_filename += ".roll";
                
            }
        }
    }
}

// a function to find the file name in  the argumants
string compress::get_file_name(){

    for ( int index = 1 ; index < this->argc ; index ++ ){

        if (string(this->argv[index]) == "-o"){

            this->output_filename = this->argv[index + 1];
            this->output_decided = true;

        }

        if (string(this->argv[index]) == "-f"){

            return this->argv[index + 1];
        }
    }

    // Check if filename is empty
    cout << "\n[error] No file provided. Use -f option with a file name." << endl;
        
    return "";

}
