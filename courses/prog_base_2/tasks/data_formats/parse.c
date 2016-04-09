#include <libxml/parser.h>
#include <libxml/tree.h>
#include "parse.h"

void parse(master ** scrumMaster, const char * title)
{
    char line[100];
    char text[10000] = "";
    FILE * fr = fopen(title, "r");

    while(fgets(line, 100, fr))
    {
        strcat(text, line);
    }

    xmlDoc * xDoc = xmlReadMemory(text, strlen(text), title, NULL, 0);
    int i = 0;

    if(NULL == xDoc)
    {
        printf("Error parsing xml from memory");
    }
    else
    {
        xmlNode * SMs = xmlDocGetRootElement(xDoc);
        xmlNode * SM = SMs->children;
        for(i = 0, SM = SMs->children; NULL != SM; SM = SM->next)
        {
            if(XML_ELEMENT_NODE == SM->type)
            {
                writeMaster(scrumMaster[i++], SM);
            }
        }
    }
}

void writeMaster(master * scrumMaster, xmlNode * SM)
{
    char * name;
    char * surname;
    char * company;
    char * year;
    char * date;
    char * count;
    char * score;

    for(xmlNode * xJ = SM->children; NULL != xJ; xJ = xJ->next)
    {
        if(XML_ELEMENT_NODE == xJ->type)
        {
            if(strcmp(xJ->name, "name") == 0)
                name = xmlNodeGetContent(xJ);
            if(strcmp(xJ->name, "surname") == 0)
                surname = xmlNodeGetContent(xJ);
            if(strcmp(xJ->name, "date") == 0)
                date = xmlNodeGetContent(xJ);
            if(strcmp(xJ->name, "count") == 0)
                count = xmlNodeGetContent(xJ);
            if(strcmp(xJ->name, "score") == 0)
                score = xmlNodeGetContent(xJ);
            if(strcmp(xJ->name, "company") == 0)
            {
                year = xmlGetProp(xJ, "year");
                company = xmlNodeGetContent(xJ->children);
            }

            if(strcmp(xJ->name, "teams") == 0)
            {
                writeTeam(scrumMaster, xJ);
            }
        }
        master_set(scrumMaster, name, surname, company, atoi(year), date, atoi(count), atof(score));
    }
}

void writeTeam (master * scrumMaster, xmlNode * xJ)
{
    int i = 0;
    char * nameTeam;
    char * nameProject;

    for(xmlNode * xJC = xJ->children; NULL != xJC; xJC = xJC->next)
    {
        if(XML_ELEMENT_NODE == xJC->type)
        {
            if(strcmp(xJC->name, "team") == 0)
            {
                for(xmlNode * xJCC = xJC->children; NULL != xJCC; xJCC = xJCC->next)
                {
                    if(XML_ELEMENT_NODE == xJCC->type)
                    {
                        if(strcmp(xJCC->name, "nameTeam") == 0)
                            nameTeam = xmlNodeGetContent(xJCC);
                        if(strcmp(xJCC->name, "nameProject") == 0)
                            nameProject = xmlNodeGetContent(xJCC);
                    }
                    team_set(scrumMaster, nameTeam, nameProject, i);
                }
            }
            i++;
        }
    }
}
