//
//  Created by oldman on 6/8/15.
//

#ifndef __insert_dylib_to_macho__record__
#define __insert_dylib_to_macho__record__

#include <cstdlib>

template <typename T>
class Record {
public:
    Record() {};
    Record(uint32_t offset, T&& v) : offset(offset), value(v) {};
    ~Record() {};
    
    uint32_t offset;
    T value;
};

#endif /* defined(__insert_dylib_to_macho__record__) */
