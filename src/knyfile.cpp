#include "knyfile.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

KnyFile::KnyFile(const std::string& name)
    : m_name(name)
{ }

bool KnyFile::read(std::istream& in)
{
    string knyLine, srcLine;

    while (getline(in, srcLine)) {
        for (int j = 0; j < srcLine.length(); ++j) {
            char cell = srcLine[j];

            switch (cell) {
            case '.':
            case 'B':
            case 'E':
            case 'L':
            case 'R':
            case 'S':
            case 'T':
            case 'W':
                knyLine.push_back(cell);
            default:
                break;
            }
        }

        if (m_maxLength < knyLine.length())
            m_maxLength = knyLine.length();

        m_map.push_back(knyLine);
        knyLine.clear();
    }

    return true;
}

void KnyFile::generateHpp(std::ostream& out)
{
    string uname = m_name;
    ::transform(uname.begin(), uname.end(), uname.begin(), ::toupper);

    out << "#ifndef " << uname << "_H" << endl
        << "#define " << uname << "_H" << endl
        << endl
        << "#include <array>" << endl
        << endl
        << "struct " << m_name << endl
        << "{" << endl
        << "\tstatic constexpr int height = " << to_string(m_map.size()) << ";" << endl
        << "\tstatic constexpr int width = " << to_string(m_maxLength) << ";" << endl
        << endl
        << "\tstatic std::array<char, " << to_string(m_maxLength * m_map.size()) << "> arr;" << endl
        << "};" << endl
        << endl
        << "#endif // " << uname << "_H" << endl;
}

void KnyFile::generateCpp(std::ostream& out)
{
    string lname = m_name;
    ::transform(lname.begin(), lname.end(), lname.begin(), ::tolower);

    out << "#include \"" << lname << ".h\"" << endl
        << endl
        << "std::array<char, " << to_string(m_maxLength * m_map.size()) << "> " << m_name << "::arr = {" << endl;

    auto printBoardHeader = [this, &out]() {
        out << "\t/*        ";
        for (int x = 0; x < m_maxLength; x++) {
            out << " [" << std::setw(2) << to_string(x) << "]";
        }
        out << "         */" << endl;
    };

    printBoardHeader();

    int y = 0;
    list<string>::iterator mapIterator = m_map.begin();
    list<string>::iterator mapIteratorEnd = m_map.end();
    while (mapIterator != mapIteratorEnd) {
        string& knyLine = *mapIterator;

        auto printYNum = [&y, &out]() {
            out << "/* [" << std::setw(2) << to_string(y) << "] */";
        };

        out << "\t";
        printYNum();

        for (int i = 0; i < knyLine.length(); i++) {
            out << " '" << knyLine[i] << "',";
        }

        int extraCells = m_maxLength - knyLine.length();
        for (int i = 0; i < extraCells; i++) {
            out << "'.',";
        }

        out << " ";
        printYNum();
        out << endl;

        ++y;
        ++mapIterator;
    }

    printBoardHeader();

    out << "};" << endl;
}
