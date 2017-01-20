#include "HighLevel.h"

#include <fstream>

void LinkerScript::CreateSizeScript(SectionList& sections, std::string name)
{
    /* open up text file, write first line */
    std::ofstream script (name, std::ios::out | std::ios::trunc);
    script << "SECTIONS {" << std::endl;

    /* section number */
    unsigned int num = 1;

    /* iterate through all sections, write contents to script */
    for (auto& sect : sections)
    {
        script << "wiimake_section_" << std::dec << num << " :\n{\n\t"
            << sect.path << "\n}\n_sizeof_wmake_section_" << num <<
            "=SIZEOF(wiimake_section_" << num << ");\n";

        num++; //increment here to avoid warning -Wsequence-point
    }

    /* write final line of linker script and close file */
    script << "}" << std::endl;
    script.close();
}

void LinkerScript::CreateFinalScript(SectionList& sections, std::string name)
{
    /* open up text file, write first line */
    std::ofstream script (name, std::ios::out | std::ios::trunc);
    script << "SECTIONS {" << std::endl;
    
    /* section number */
    unsigned int num = 1;

    /* iterate through all sections, write contents to script */
    for (auto& sec : sections)
    {
        script << "wiimake_section_" << std::dec << num++ << " 0x" 
            << std::hex << sec.address << " :\n{\n\t" << sec.path << "\n}\n";
    }

    /* write final line of linker script and close file */
    script << "}" << std::endl;
    script.close();
}

