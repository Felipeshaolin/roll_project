#include "unroll.hpp"

//uncompression algorithms
int uncompress::classical_unroll(){

    this->get_output_filename(); // create the output file name
    int size = this->buffer[7]; // file_name size

    this->get_marker();

    ofstream out_file(this->output_filename, ios::app | ios::binary);   

    // variables used in the uncompression
    bool different = false;
    unsigned int index =  7 + size;
    unsigned int rep = 0; //used as temp to repeat letters


    while( true ){
    //for (int index = 7 + size ; index < this->buffer.size() ; index ++  ){

        // if we find a marker we change our status
        if (this->buffer[index] == (char)this->rle_marker ){ different != different; index ++; }
    
        // if it is different then we need to write to the file
        if (different){ out_file.write( (const char *)this->buffer[index], 1 ); }

        //if it is not different we will write the letter n number of times
        if (!different){
                rep == (unsigned int)this->buffer[index];
                for (int i = 0; i < rep ; i++){

                    out_file.write( ( const char * ) this->buffer[index+1], 1 );
                }
            }

        // increment the index
        if (index < this->buffer.size()){ index ++; }else{ break; }
    }

    out_file.close();
    return 1;

}

// gets the output_filename from file
void uncompress::get_output_filename(){

    int size = this->buffer[7];

    for (int index = 7 ; index <= 7 + size ; index ++ ){

        this->output_filename += this->buffer[index];

    }

}

void uncompress::get_marker(){

    this->rle_marker == (uint8_t) this->buffer[6];

}