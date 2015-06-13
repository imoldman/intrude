//
//  Created by oldman on 6/8/15.
//

#ifndef __insert_dylib_to_macho__macho_brief_info__
#define __insert_dylib_to_macho__macho_brief_info__

#include "record.h"
#include "loader.h"

class MachHeader : public mach_header {};
class MachHeader64 : public mach_header_64 {};
class SegmentCommand : public segment_command {};
class SegmentCommand64 : public segment_command_64 {};
class SectionHeader : public section {};
class SectionHeader64 : public section_64 {};
class DylibCommand : public dylib_command {};
class LoadCommand : public load_command {};

class MachoBriefInfo32
{
public:
    typedef MachHeader MachHeader;
    typedef SegmentCommand SegmentCommand;
    typedef DylibCommand DylibCommand;
    typedef LoadCommand LoadCommand;
    typedef SectionHeader SectionHeader;
    static const uint32_t kAlignBase = 4;
    
    Record<MachHeader> mach_header;
    std::vector<Record<LoadCommand>> commands;
    std::vector<Record<SectionHeader>> section_headers;
};

class MachoBriefInfo64
{
public:
    typedef MachHeader64 MachHeader;
    typedef SegmentCommand64 SegmentCommand;
    typedef DylibCommand DylibCommand;
    typedef LoadCommand LoadCommand;
    typedef SectionHeader64 SectionHeader;
    static const uint32_t kAlignBase = 8;

    Record<MachHeader> mach_header;
    std::vector<Record<LoadCommand>> commands;
    std::vector<Record<SectionHeader>> section_headers;
};

#endif /* defined(__insert_dylib_to_macho__macho_brief_info__) */
