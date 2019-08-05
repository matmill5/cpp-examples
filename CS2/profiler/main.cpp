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
void testCopyAssign(srcML p) {
    std::cout << "The orginal code: " <<std::endl;
    std::cout << "------------------------------------------------" <<std::endl;
    std::cout << p;   //Should print out same code as printed in main.
    std::cout << "------------------------------------------------" <<std::endl;
    std::cout << "No code: " <<std::endl;
    p = srcML();      //Should print out nothing.
    std::cout << p;
    std::cout << "------------------------------------------------" <<std::endl;
}

////////////////////////////////////////////////////////////////////////////////
// Reads a srcML file into an internal data structure.
// Then prints out the data structure.
//
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error: Input file(s) are required." << std::endl;
        std::cerr << "       The main must be the first argument followed by ";
        std::cerr << "any other .cpp files.  For example:" << std::endl;
        std::cerr << "profiler main.cpp.xml file1.cpp.xml file2.cpp.xml";
        std::cerr << std::endl << std::endl;
        return(1);
    }
    
    srcML                     code;           //Source code to be profiled.
    std::vector<std::string>  file;           //List of file names (foo.cpp.xml)
    std::vector<std::string>  profileName;    //List of profile names (foo_cpp)
    
    for (int i = 1; i < argc; ++i) {
        std::string filename;
        filename = argv[i];
        file.push_back(filename);
        filename = filename.substr(0, filename.find(".xml"));      //Remove .xml
        std::replace(filename.begin(), filename.end(), '.', '_');  //. => _
        profileName.push_back(filename);
    }
    
    std::ifstream inFile(file[0].c_str());    //Read in the main.
    inFile >> code;
    inFile.close();
    
    code.mainHeader(profileName);             //Add in main header info
    code.mainReport(profileName);             //Add in the report
    code.funcCount(profileName[0]);           //Count funciton invocations
    code.lineCount(profileName[0]);           //Count line invocations
    
    std::string outFileName = "p-" + file[0];
    outFileName = outFileName.substr(0, outFileName.find(".xml"));
    std::ofstream outFile(outFileName.c_str());
    outFile << code << std::endl;
    outFile.close();

    for (unsigned i = 1; i < file.size(); ++i) {  //Read rest of the files.
        inFile.open(file[i].c_str());
        inFile >> code;
        inFile.close();
        
        code.fileHeader(profileName[i]);       //Add in file header info
        code.funcCount(profileName[i]);        //Count funciton invocations
        code.lineCount(profileName[i]);        //Count line invocations
        
        outFileName = "p-" + file[i];
        outFileName = outFileName.substr(0, outFileName.find(".xml"));
        outFile.open(outFileName.c_str());
        outFile << code << std::endl;
        outFile.close();
    }
	testCopyAssign(code);
	return 0;
}


