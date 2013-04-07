//
//  utility.h
//  CubicVR2
//
//  Created by Charles J. Cliffe on 2013-02-25.
//  Copyright (c) 2013 Charles J. Cliffe. All rights reserved.
//

#ifndef CubicVR2_utility_h
#define CubicVR2_utility_h

#include <string>
#include <fstream>
#include <cerrno>

namespace CubicVR {
    
    struct util {
        static std::string loadTextFile(const std::string fn)
        {
            std::ifstream inp(fn.c_str(), std::ios::in | std::ios::binary);
            if (inp)
            {
                std::string contents;
                inp.seekg(0, std::ios::end);
                contents.resize(inp.tellg());
                inp.seekg(0, std::ios::beg);
                inp.read(&contents[0], contents.size());
                inp.close();
                return(contents);
            }
            return "";
        }
    };
}


#endif
