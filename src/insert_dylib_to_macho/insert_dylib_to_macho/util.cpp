//
//  Created by oldman on 6/9/15.
//

#include "util.h"

namespace util {
    bool string_start_with(const std::string& str, const std::string& prefix) {
        if (str.length() < prefix.length()) {
            return false;
        }
        return str.substr(0, prefix.length()) == prefix;
    }
}
