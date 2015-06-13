//
//  Created by oldman on 6/8/15.
//

#include <iostream>
#include <gflags/gflags.h>

#include "macho_brief_info.h"
#include "runner.h"


// insert_dylib_to_macho --src src_path --dest dest_path --dylib dylib_path

DEFINE_string(src, "", "full path of source macho file");
DEFINE_string(dest, "", "full path of the result to be saved");
DEFINE_string(dylib, "", "full path of the dylib to be inserted");


int main(int argc, const char * argv[]) {
    
    Runner<MachoBriefInfo64> runner("/Users/oldman/Desktop/intrude/src/insert_dylib_to_macho/test");
    return 0;
}
