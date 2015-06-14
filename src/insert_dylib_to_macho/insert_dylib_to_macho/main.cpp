//
//  Created by oldman on 6/8/15.
//

#include <iomanip>
#include <iostream>
#include <gflags/gflags.h>

#include "exception.h"
#include "macho_brief_info.h"
#include "util.h"
#include "workflow.h"


// insert_dylib_to_macho --src src_path --dest dest_path --dylib dylib_path

DEFINE_string(file, "", "full path of macho file to be modified");


void init_gflag_config(int& argc, char**& argv) {
    std::string usage("insert a dylib load command to a macho file, result is the dylib file name, e.g.\n");
    usage += std::string("\t") + argv[0] + " --file ./some.app/some\n";
    usage += std::string("the result is:\n");
    usage += std::string("\t{\"error\":0, \"filename\":\"a.dylib\"}");
    ::google::SetUsageMessage(usage);
    
    ::google::ParseCommandLineFlags(&argc, &argv, true);
    
    if (FLAGS_file.length() == 0) {
        throw Exception(ExceptionCode::kParamInvalid, "invalid param, please check the usage");
    }
}

bool is_64bit_macho_file(const std::string& file) {
    uint32_t magic_number = 0;
    util::read(file, 0, sizeof(magic_number), &magic_number);
    assert(magic_number == MH_MAGIC || magic_number == MH_CIGAM || magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64);
    if (magic_number == MH_MAGIC || magic_number == MH_CIGAM) {
        return false;
    } else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64) {
        return true;
    } else {
        throw Exception(ExceptionCode::kShouldNotOccur, util::build_string([&](std::ostringstream& ss) {
            ss << "invalid macho file, magic number is " << std::hex << magic_number;
        }));
    }
}

template <typename Workflow>
std::string run_workflow_and_get_dylib_name(Workflow& wf) {
    wf.run();
    return wf.fresh_dylib_name();
}

std::string build_success_result(const std::string& dylib_name) {
    return util::build_string([&](std::ostringstream& ss) {
      ss << "{\"error\":0, \"filename\":\"" << dylib_name << "\"}";
    });
}

std::string build_failed_result(const Exception& exception) {
    return util::build_string([&](std::ostringstream& ss) {
      ss << "{\"error\":" << (int)exception.code() << ", \"description\":\"" << exception.description() << "\"}";
    });
}

int main(int argc, char* argv[]) {
    
    try {
        init_gflag_config(argc, argv);
        
        std::string fresh_dylib_name;
        if (is_64bit_macho_file(FLAGS_file)) {
            Workflow<MachoBriefInfo64> workflow(FLAGS_file);
            fresh_dylib_name = run_workflow_and_get_dylib_name(workflow);
        } else {
            Workflow<MachoBriefInfo32> workflow(FLAGS_file);
            fresh_dylib_name = run_workflow_and_get_dylib_name(workflow);
        }
        std::cout << build_success_result(fresh_dylib_name);
        return 0;
    } catch (Exception& e) {
        std::cerr << build_failed_result(e);
        return (int)e.code();
    }
}

