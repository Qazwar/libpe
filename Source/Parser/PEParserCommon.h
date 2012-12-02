#pragma once

LIBPE_NAMESPACE_BEGIN

enum PEParserType {
    PE_PARSER_TYPE_DISK_FILE        = 1,
    PE_PARSER_TYPE_MAPPED_FILE,

#ifdef LIBPE_WINOS
    PE_PARSER_TYPE_MAPPED_RESOURCE,
    PE_PARSER_TYPE_LOADED_MODULE,
#endif
};


LIBPE_NAMESPACE_END