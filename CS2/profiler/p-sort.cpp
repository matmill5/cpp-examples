/**
 * @brief  Application to run sorting algorithms on random int data
 *
 * @author Dale Haverstock
 * @date   2012-04-19
 */

//==============================================================================
#include "sort_lib.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>

//==============================================================================
// Using declarations
using std::string;
using std::vector;
using std::cout;
using std::cerr;

//==============================================================================
// Function declarations
void process_command_line(Options& opts, int argc, char* argv[]);
void generate_random_data(vector<int>& data, int size, int seed, int mod);
void output_data(const vector<int>&);
void output_usage_and_exit(const string& cmd);
void output_error_and_exit(const string& msg);

//==============================================================================
#include "profile.hpp";
profile sort_cpp(sort.cpp);
profile simple_cpp(simple.cpp);

int main(int argc, char* argv[])
{sort_cpp.count(__Line__, "main"); 

    // Options container
    Options opts;

    // Get values from the command line, opts may be changed
    process_command_line(opts, argc, argv); sort_cpp.count(__LINE__); 


    // Generate data
    vector<int> data;
    generate_random_data(data, opts._data_size, opts._seed, opts._mod); sort_cpp.count(__LINE__); 


    // Output data before sorting
    if(opts._output_data)
        { cout << "\nData Before: "; sort_cpp.count(__LINE__); 
 output_data(data); sort_cpp.count(__LINE__); 
 } 

    // Sort, if a sort was specified, there is no default
    if (opts._quick_sort)     { quick_sort(data); sort_cpp.count(__LINE__); 
      }
    if (opts._selection_sort) { selection_sort(data); sort_cpp.count(__LINE__); 
  }
    if (opts._bubble_sort)    { bubble_sort(data); sort_cpp.count(__LINE__); 
     }
    if ( !opts._quick_sort      &&
         !opts._selection_sort  &&
         !opts._bubble_sort  )
        { output_error_and_exit("No sort specified."); sort_cpp.count(__LINE__); 
 }

    // Output data after sorting
    if(opts._output_sorted_data)
        { cout << "\nData After: "; sort_cpp.count(__LINE__); 
 output_data(data); sort_cpp.count(__LINE__); 
 }
    std::cout << sort_cpp <<std::endl;
    std::cout << simple_cpp <<std::endl; 

    return 0;
}

//==============================================================================
void generate_random_data(vector<int>& vec, int size, int seed, int mod)
{sort_cpp.count(__Line__, "generate_random_data"); 

    // Resize vector
    vec.resize(size); sort_cpp.count(__LINE__); 


    // Set random number generator seed
    srandom(static_cast<unsigned int>(seed));

    // Put random values in vector
    for (vector<int>::size_type idx = 0; idx < vec.size(); ++idx)
    {
        if(mod) { vec[idx] = random() % mod; sort_cpp.count(__LINE__); 
 }
        else    { vec[idx] = random(); sort_cpp.count(__LINE__); 
       }
    }
}

//==============================================================================
void output_data(const vector<int>& vec)
{sort_cpp.count(__Line__, "output_data"); 

    // Number of columns, column width
    const int cols  =  7;
    const int width = 10;

    // Output vector elements
    for (vector<int>::size_type idx = 0; idx < vec.size(); ++idx)
    {
        // Output newline to end row
        if ( ! (idx % cols) )
           { cout  << "\n"; sort_cpp.count(__LINE__); 
 }

        cout << std::setw(width) << vec[idx] << " "; sort_cpp.count(__LINE__); 

    }

    cout << '\n'; sort_cpp.count(__LINE__); 

}

//==============================================================================
// Note:
//   * No check for C-string to int conversion success
//
void process_command_line(Options& opts, int argc, char* argv[])
{sort_cpp.count(__Line__, "process_command_line"); 

    // Useage message if no command line args
    if (argc == 1)
        { output_usage_and_exit(argv[0]); sort_cpp.count(__LINE__); 
 }

    // Go through the argumets
    for (int idx = 1; idx < argc; ++idx)
    {
        // Standard library string from C-string
        string opt(argv[idx]);

        // Process the option
        if (opt == "-h")   { output_usage_and_exit(argv[0]); sort_cpp.count(__LINE__); 
 }
        if (opt == "-qs")  { opts._quick_sort         = true; sort_cpp.count(__LINE__); 
  }
        if (opt == "-ss")  { opts._selection_sort     = true; sort_cpp.count(__LINE__); 
  }
        if (opt == "-bs")  { opts._bubble_sort        = true; sort_cpp.count(__LINE__); 
  }
        if (opt == "-od")  { opts._output_data        = true; sort_cpp.count(__LINE__); 
  }
        if (opt == "-osd") { opts._output_sorted_data = true; sort_cpp.count(__LINE__); 
  }
        if (opt == "-sz")
        {
            if (idx + 1 < argc) { ++idx; sort_cpp.count(__LINE__); 
 opts._data_size = atoi(argv[idx]); sort_cpp.count(__LINE__); 
 }
            else                { output_error_and_exit("Value for -sz option is missing."); sort_cpp.count(__LINE__); 
 }
        }
        if (opt == "-rs")
        {
            if (idx + 1 < argc) { ++idx; sort_cpp.count(__LINE__); 
 opts._seed = atoi(argv[idx]); sort_cpp.count(__LINE__); 
 }
            else                { output_error_and_exit("Value for -rs option is missing."); sort_cpp.count(__LINE__); 
 }
        }
        if (opt == "-mod")
        {
            if (idx + 1 < argc) { ++idx; sort_cpp.count(__LINE__); 
 opts._mod = atoi(argv[idx]); sort_cpp.count(__LINE__); 
 }
            else                { output_error_and_exit("Value for -mod option is missing."); sort_cpp.count(__LINE__); 
 }
        }
        if ( (opt != "-h")   &&
             (opt != "-qs")  &&
             (opt != "-ss")  &&
             (opt != "-bs")  &&
             (opt != "-od")  &&
             (opt != "-osd") &&
             (opt != "-sz")  &&
             (opt != "-rs")  &&
             (opt != "-mod") )
        {
           output_error_and_exit(string("Error: Bad option: ") + opt); sort_cpp.count(__LINE__); 

        }
    }
}

//==============================================================================
void output_usage_and_exit(const string& cmd)
{sort_cpp.count(__Line__, "output_usage_and_exit"); 

    cout << 
       "Usage: " << cmd << " [options]\n"
       "  Options:\n"
       "     -sz  int  The number of data items\n"
       "     -rs  int  The random number generator seed\n"
       "     -mod int  The mod value for random numbers\n"
       "     -od       Output data to be sorted\n"
       "     -osd      Output sorted data\n"
       "     -qs       Use quick sort\n"
       "     -ss       Use selection sort\n"
       "     -bs       Use bubble sort\n"
       "     -h        This message\n"
       "\n"
       "  A sort must be specified, there is no default sort.\n"
       "  If more than 1 sort is specified then the first sort\n"
       "  specified from the following order will be done.\n"
       "     1. quick\n"
       "     2. selection\n"
       "     3. bubble\n"; sort_cpp.count(__LINE__); 


    exit(0); sort_cpp.count(__LINE__); 

}

//==============================================================================
void output_error_and_exit(const string& msg)
{sort_cpp.count(__Line__, "output_error_and_exit"); 

    cerr << "Error: " << msg << "\n"; sort_cpp.count(__LINE__); 


    exit(1); sort_cpp.count(__LINE__); 

}


