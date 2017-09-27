#ifndef KNYFILE_H
#define KNYFILE_H

#include <iostream>
#include <list>
#include <string>

class KnyFile
{
public:
    KnyFile(const std::string& name);

    bool read(std::istream& in);
    void generateHpp(std::ostream& out);
    void generateCpp(std::ostream& out);

private:
    std::string m_name;
    std::list<std::string> m_map;
    int m_maxLength = 0;
};

#endif // KNYFILE_H
