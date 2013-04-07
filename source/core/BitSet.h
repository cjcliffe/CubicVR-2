//////////////////////////////////////////////////////////////////////////////////////////
//	BITSET.h
//	class declaration for set of bits to represent many true/falses
//	Downloaded from: www.paulsprojects.net
//	Created:	8th August 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef __CubicVR2__BitSet__
#define __CubicVR2__BitSet__

#include <iostream>

#include "memory.h"
#include <stdio.h>
#include <string>

using namespace std;

namespace CubicVR {

    class BitSet
    {
    public:
        BitSet() : numBytes(0), bits(NULL)
        {}
        ~BitSet()
        {
            if(bits)
                delete [] bits;
            bits=NULL;
        }
        
        bool init(int numberOfBits)
        {
            //Delete any memory allocated to bits
            if(bits)
                delete [] bits;
            bits=NULL;
            
            //Calculate size
            numBytes=(numberOfBits>>3)+1;
            
            //Create memory
            bits=new unsigned char[numBytes];
            if(!bits)
            {
//                Logger::log(LOG_ERROR,"BITSET: Unable to allocate space for a bitset of %d bits", numberOfBits);
                
                cout << "BITSET: Unable to allocate space for a bitset of " << numberOfBits << " bits" << endl;
                
                return false;
            }
            
            clearAll();
            
            return true;
        }
        
        inline void clearAll()
        {
            memset(bits, 0, numBytes);
        }
        
        inline void setAll()
        {
            memset(bits, 0xFF, numBytes);
        }
        
        inline void clear(int bitNumber)
        {
            bits[bitNumber>>3] &= ~(1<<(bitNumber & 7));
        }
        
        inline void set(int bitNumber)
        {
            bits[bitNumber>>3] |= 1<<(bitNumber&7);
        }
        
        inline unsigned char isSet(int bitNumber)
        {
            return bits[bitNumber>>3] & 1<<(bitNumber&7);
        }
        
    protected:
        int numBytes;	//size of bits array
        unsigned char * bits;
    };

}
#endif /* defined(__CubicVR2__BitSet__) */
