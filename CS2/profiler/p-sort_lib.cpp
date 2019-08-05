/**
 * @brief  Application to run sorting algorithms on random int data
 *
 * @author Dale Haverstock
 * @date   2012-04-19
 */

// sort library
//

//==============================================================================
#include "sort_lib.h"
#include <vector>

//==============================================================================
// Make shorter type names
typedef std::vector<int>::size_type Vec_Idx;

//==============================================================================
// Function declarations, uppercase so those stand out
void quick_sort(std::vector<int>& data, int left, int right);
void SWAP(int& n1, int& n2);
bool LESS_THAN(int n1, int n2);
bool GREATER_THAN(int n1, int n2);

//==============================================================================
#include "profile.hpp";
extern profilesort_lib_cpp;

void quick_sort(std::vector<int>& data)
{sort_lib_cpp.count(__Line__, "quick_sort"); 

    // Do nothing if empty vector
    if (data.size() == 0 sort_lib_cpp.count(__LINE__); 
)
        { return; }

    // Do the sort
    quick_sort(data, 0, data.size() - 1 sort_lib_cpp.count(__LINE__); 
) sort_lib_cpp.count(__LINE__); 
; sort_lib_cpp.count(__LINE__); 

}

//==============================================================================
// The unsigned ints cause problems here, jdx may go to -1.
// Subscripts are cast so there are no warnings.
void quick_sort(std::vector<int>& data, int left, int right)
{sort_lib_cpp.count(__Line__, "quick_sort"); 

      // Calculate the pivot
      int pivot = data[Vec_Idx((left + right) / 2) sort_lib_cpp.count(__LINE__); 
];

      // Partition
      int idx = left, jdx = right;
      while (idx <= jdx) {
            while (LESS_THAN(data[Vec_Idx(idx) sort_lib_cpp.count(__LINE__); 
], pivot) sort_lib_cpp.count(__LINE__); 
) {
                idx++; sort_lib_cpp.count(__LINE__); 

            }
            while (GREATER_THAN(data[Vec_Idx(jdx) sort_lib_cpp.count(__LINE__); 
], pivot) sort_lib_cpp.count(__LINE__); 
) {
                jdx--; sort_lib_cpp.count(__LINE__); 

            }

            if (idx <= jdx)
            {
                  SWAP(data[Vec_Idx(idx) sort_lib_cpp.count(__LINE__); 
], data[Vec_Idx(jdx) sort_lib_cpp.count(__LINE__); 
]) sort_lib_cpp.count(__LINE__); 
; sort_lib_cpp.count(__LINE__); 

                  idx++; sort_lib_cpp.count(__LINE__); 

                  jdx--; sort_lib_cpp.count(__LINE__); 

            }
      }

      // Recurse
      if (left < jdx)
            { quick_sort(data, left, jdx) sort_lib_cpp.count(__LINE__); 
; sort_lib_cpp.count(__LINE__); 
 }

      if (idx < right)
            { quick_sort(data, idx, right) sort_lib_cpp.count(__LINE__); 
; sort_lib_cpp.count(__LINE__); 
 }
}

//==============================================================================
void selection_sort(std::vector<int>& data)
{sort_lib_cpp.count(__Line__, "selection_sort"); 

    // Do nothing if empty vector (note unsigned 0 - 1 is a big number)
    if (data.size() == 0 sort_lib_cpp.count(__LINE__); 
)
        { return; }

    // Index of last element in vector, also last in unsorted part
    Vec_Idx last = data.size() - 1 sort_lib_cpp.count(__LINE__); 
;

    // Do the sort
    while (last > 0)
    {
        // Find greatest in unsorted part
        Vec_Idx idx_of_greatest = 0;
        for (Vec_Idx idx = 0; idx <= last; ++idx)
        {
            if ( LESS_THAN(data[idx_of_greatest], data[idx]) sort_lib_cpp.count(__LINE__); 
 )
            {
                // Remember as new greatest so far
                idx_of_greatest = idx; sort_lib_cpp.count(__LINE__); 

            }
        }

        // Swap last in unsorted with greatest in unsorted part
        SWAP(data[last], data[idx_of_greatest]) sort_lib_cpp.count(__LINE__); 
; sort_lib_cpp.count(__LINE__); 


        // Increase sorted part
        --last; sort_lib_cpp.count(__LINE__); 

    }
}

//==============================================================================
void bubble_sort(std::vector<int>& data)
{sort_lib_cpp.count(__Line__, "bubble_sort"); 

    // Go through vector repeatedly
    for(Vec_Idx limit = data.size() sort_lib_cpp.count(__LINE__); 
; limit > 0; limit--)
    {
        // Go through vector once, swap element and next element if out of order
        for(Vec_Idx idx = 0; idx < limit - 1; idx++)
        {
            if( LESS_THAN(data[idx + 1], data[idx]) sort_lib_cpp.count(__LINE__); 
 )
            {
                SWAP(data[idx],data[idx + 1]) sort_lib_cpp.count(__LINE__); 
; sort_lib_cpp.count(__LINE__); 

            }
        }
    }
}

//==============================================================================
// This is here so the number of calls can be counted.
void SWAP(int& n1, int& n2)
{sort_lib_cpp.count(__Line__, "SWAP"); 

    std::swap(n1, n2) sort_lib_cpp.count(__LINE__); 
; sort_lib_cpp.count(__LINE__); 

}

//==============================================================================
// This is here so the number of calls can be counted.
bool LESS_THAN(int n1, int n2)
{sort_lib_cpp.count(__Line__, "LESS_THAN"); 

    return n1 < n2;
}

//==============================================================================
// This is here so the number of calls can be counted.
bool GREATER_THAN(int n1, int n2)
{sort_lib_cpp.count(__Line__, "GREATER_THAN"); 

    return n1 > n2;
}


