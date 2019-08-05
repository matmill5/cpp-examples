////////////////////////////////////////////////////////////////////////////////
//  main.cpp
//  Profiler
//
//  Created by Jonathan Maletic.
//  Copyright 2019 Kent State University. All rights reserved.
//  Spr 2019
//  Requires main.cpp first, followed by other files.
//
//  Modified by:
//
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "ASTree.hpp"

////////////////////////////////////////////////////////////////////////////////
// Simple function to exercise/test copy-ctor, dtor, swap, assignment.
//
#include "profile.hpp";
profile main_cpp(main.cpp);

void testCopyAssign(srcML p) {main_cpp.count(__Line__, "testCopyAssign"); 

    std::cout << "The orginal code: " <<std::endl; main_cpp.count(__LINE__); 

    std::cout << "------------------------------------------------" <<std::endl; main_cpp.count(__LINE__); 

    std::cout << p; main_cpp.count(__LINE__); 
   //Should print out same code as printed in main.
    std::cout << "------------------------------------------------" <<std::endl; main_cpp.count(__LINE__); 

    std::cout << "No code: " <<std::endl; main_cpp.count(__LINE__); 

    p = srcML() main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 
      //Should print out nothing.
    std::cout << p; main_cpp.count(__LINE__); 

    std::cout << "------------------------------------------------" <<std::endl; main_cpp.count(__LINE__); 

}

////////////////////////////////////////////////////////////////////////////////
// Reads a srcML file into an internal data structure.
// Then prints out the data structure.
//
int main(int argc, char *argv[]) {main_cpp.count(__Line__, "main"); 

    if (argc < 2) {
        std::cerr << "Error: Input file(s) are required." << std::endl; main_cpp.count(__LINE__); 

        std::cerr << "       The main must be the first argument followed by "; main_cpp.count(__LINE__); 

        std::cerr << "any other .cpp files.  For example:" << std::endl; main_cpp.count(__LINE__); 

        std::cerr << "profiler main.cpp.xml file1.cpp.xml file2.cpp.xml"; main_cpp.count(__LINE__); 

        std::cerr << std::endl << std::endl; main_cpp.count(__LINE__); 

        return(1);
    }
    
    srcML                     code;           //Source code to be profiled.
    std::vector<std::string>  file;           //List of file names (foo.cpp.xml)
    std::vector<std::string>  profileName;    //List of profile names (foo_cpp)
    
    for (int i = 1; i < argc; ++i) {
        std::string filename;
        filename = argv[i]; main_cpp.count(__LINE__); 

        file.push_back(filename) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 

        filename = filename.substr(0, filename.find(".xml") main_cpp.count(__LINE__); 
) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 
      //Remove .xml
        std::replace(filename.begin() main_cpp.count(__LINE__); 
, filename.end() main_cpp.count(__LINE__); 
, '.', '_') main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 
  //. => _
        profileName.push_back(filename) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 

    }
    
    std::ifstream inFile(file[0].c_str() main_cpp.count(__LINE__); 
);    //Read in the main.
    inFile >> code; main_cpp.count(__LINE__); 

    inFile.close() main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 

    
    code.mainHeader(profileName) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 
             //Add in main header info
    code.mainReport(profileName) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 
             //Add in the report
    code.funcCount(profileName[0]) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 
           //Count funciton invocations
    code.lineCount(profileName[0]) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 
           //Count line invocations
    
    std::string outFileName = "p-" + file[0];
    outFileName = outFileName.substr(0, outFileName.find(".xml") main_cpp.count(__LINE__); 
) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 

    std::ofstream outFile(outFileName.c_str() main_cpp.count(__LINE__); 
);
    outFile << code << std::endl; main_cpp.count(__LINE__); 

    outFile.close() main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 


    for (unsigned i = 1; i < file.size() main_cpp.count(__LINE__); 
; ++i) {  //Read rest of the files.
        inFile.open(file[i].c_str() main_cpp.count(__LINE__); 
) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 

        inFile >> code; main_cpp.count(__LINE__); 

        inFile.close() main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 

        
        code.fileHeader(profileName[i]) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 
       //Add in file header info
        code.funcCount(profileName[i]) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 
        //Count funciton invocations
        code.lineCount(profileName[i]) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 
        //Count line invocations
        
        outFileName = "p-" + file[i]; main_cpp.count(__LINE__); 

        outFileName = outFileName.substr(0, outFileName.find(".xml") main_cpp.count(__LINE__); 
) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 

        outFile.open(outFileName.c_str() main_cpp.count(__LINE__); 
) main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 

        outFile << code << std::endl; main_cpp.count(__LINE__); 

        outFile.close() main_cpp.count(__LINE__); 
; main_cpp.count(__LINE__); 

    }
    std::cout << main_cpp <<std::endl;

	return 0;
}



