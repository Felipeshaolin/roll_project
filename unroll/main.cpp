#include "unroll.hpp"

int main(int argc, char **argv){

    uncompress object = uncompress(argc,argv);
    object.main_uncompress();

    return 1;
}