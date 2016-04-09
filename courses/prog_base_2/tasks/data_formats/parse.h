#ifndef PARSE_H_INCLUDED
#define PARSE_H_INCLUDED

#include <libxml/parser.h>
#include <libxml/tree.h>
#include "ScrumMaster.h"

void parse(master ** scrumMaster, const char * title);
void writeMaster(master * scrumMaster, xmlNode * SM);
void writeTeam(master * scrumMaster, xmlNode * xJ);

#endif
