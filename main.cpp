#ifndef CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "test.cpp"
#include "readinandparse.h"

  int main(int argc, char *argv[]){
            char* comp = argv[1];
            if(argc == 1){
                cout<< "Please enter a file in the command line" << endl;
            }
            else if(argc >= 1 && (strcmp(comp,"-t") ==0)){
                int result = Catch::Session().run();
                return(result < 0xff ? result : 0xff);
            }
            else{

               readInAndParse rp;

               //passes command line parameters to readInput
               rp.readInput(argv[1], argv[2]);




           }
            return 0;
    }


#endif
