#include <iostream>

#include <vector>

#include "knyplainarray.h"

using namespace std;

struct Position
{
    int x, y;
};

class KnyCore
{
public:
    KnyCore()
    {
        cout << endl
             << "Ways-graph init (Floid's algorythm), please wait..." << endl;

        initGraph();
    }

    static int height()
    { return m_plainArray.height; }
    static int width()
    { return m_plainArray.width; }

    static int size()
    { return m_plainArray.arr.size(); }

    static int fromPos(int x, int y)
    { return y * width() + x; }
    static int fromPos(const Position& pos)
    { return fromPos(pos.x, pos.y); }

    static Position toPos(int i)
    { return {i % width(), i / width()}; }

    static char at(int i)
    { return m_plainArray.arr[i]; }
    static char at(const Position& pos)
    { return m_plainArray.arr[fromPos(pos)]; }
    static char at(int x, int y)
    { return m_plainArray.arr[fromPos(x, y)]; }

    static void printArray()
    {
        for (int y = 0; y < height(); y++) {
            for (int x = 0; x < width(); x++) {
                cout << at(x, y) << " ";
            }
            cout << endl;
        }
    }

    int moveCost(char cell)
    {
        switch (cell) {
        case '.':   return 1;
        case 'L':   return 5;
        case 'S':   return 1;
        case 'T':   return 1;
        case 'W':   return 2;
        default:    return -1;
        }
    }

private:
    void initTeleports()
    {
        vector<int> lst;

        for (int i = 0; i < size(); i++) {
            char cell = at(i);
            if (cell == 'T')
                lst.push_back(i);
        }

        for (int i = 0; i < lst.size(); i++) {
            for (int j = 0; j < lst.size(); j++) {
                if (i != j) {
                    int t1 = lst[i];
                    int t2 = lst[j];

                    m_graph[t1 + t2 * size()] = 1;
                    m_graph[t2 + t1 * size()] = 1;
                }
            }
        }
    }

    vector<int> validMoveList(const Position& pos)
    {
        int x = pos.x;
        int y = pos.y;

        int h = height();
        int w = width();

        vector<int> lst;

        auto pushIfNotRB = [&lst](int x, int y) {
            int cell = at(x, y);

            if (cell != 'R' && cell != 'B') {
                lst.push_back(fromPos(x, y));
            }
        };

        if (x > 0) { pushIfNotRB(x - 1, y); }
        if (y > 0) { pushIfNotRB(x, y - 1); }

        if (x < (w - 1)) { pushIfNotRB(x + 1, y); }
        if (y < (h - 1)) { pushIfNotRB(x, y + 1); }

        if (x > 0 && y > 0) { pushIfNotRB(x - 1, y - 1); }

        if (x > 0 && y < (h - 1)) { pushIfNotRB(x - 1, y + 1); }
        if (y > 0 && x < (w - 1)) { pushIfNotRB(x + 1, y - 1); }

        if (x < (w - 1) && y < (h - 1)) { pushIfNotRB(x + 1, y + 1); }

        return lst;
    }

    vector<int> validHorseMoveList(const Position& pos)
    {
        int x = pos.x;
        int y = pos.y;

        int h = height();
        int w = width();

        vector<int> lst;

        if (x > 0 && y > 1) {
            int dst = fromPos(x - 1, y - 2);
            bool dstOk = at(dst) != 'B' && at(dst) != 'R';
            if (dstOk) {
                bool notB1 = at(x - 1, y) != 'B' && at(x - 1, y - 1) != 'B';
                bool notB2 = at(x, y - 1) != 'B' && at(x, y - 2) != 'B';
                if (notB1 || notB2)
                    lst.push_back(dst);
            }
        }

        if (x > 1 && y > 0) {
            int dst = fromPos(x - 2, y - 1);
            bool dstOk = at(dst) != 'B' && at(dst) != 'R';
            if (dstOk) {
                bool notB1 = at(x - 1, y) != 'B' && at(x - 2, y) != 'B';
                bool notB2 = at(x, y - 1) != 'B' && at(x - 1, y - 1) != 'B';
                if (notB1 || notB2)
                    lst.push_back(dst);
            }
        }

        ////////

        if (x < (h - 1) && y > 1) {
            int dst = fromPos(x + 1, y - 2);
            bool dstOk = at(dst) != 'B' && at(dst) != 'R';
            if (dstOk) {
                bool notB1 = at(x + 1, y) != 'B' && at(x + 1, y - 1) != 'B';
                bool notB2 = at(x, y - 1) != 'B' && at(x, y - 2) != 'B';
                if (notB1 || notB2)
                    lst.push_back(dst);
            }
        }

        if (x < (h - 2) && y > 0) {
            int dst = fromPos(x + 2, y - 1);
            bool dstOk = at(dst) != 'B' && at(dst) != 'R';
            if (dstOk) {
                bool notB1 = at(x + 1, y) != 'B' && at(x + 2, y) != 'B';
                bool notB2 = at(x, y - 1) != 'B' && at(x + 1, y - 1) != 'B';
                if (notB1 || notB2)
                    lst.push_back(dst);
            }
        }

        ////////

        if (x < (h - 1) && y < (w - 2)) {
            int dst = fromPos(x + 1, y + 2);
            bool dstOk = at(dst) != 'B' && at(dst) != 'R';
            if (dstOk) {
                bool notB1 = at(x, y + 1) != 'B' && at(x, y + 2) != 'B';
                bool notB2 = at(x + 1, y) != 'B' && at(x + 1, y + 1) != 'B';
                if (notB1 || notB2)
                    lst.push_back(dst);
            }
        }

        if (x < (h - 2) && y < (w - 1)) {
            int dst = fromPos(x + 2, y + 1);
            bool dstOk = at(dst) != 'B' && at(dst) != 'R';
            if (dstOk) {
                bool notB1 = at(x + 1, y) != 'B' && at(x + 2, y) != 'B';
                bool notB2 = at(x, y + 1) != 'B' && at(x + 1, y + 1) != 'B';
                if (notB1 || notB2)
                    lst.push_back(dst);
            }
        }

        ////////

        if (x > 0 && y < (w - 2)) {
            int dst = fromPos(x - 1, y + 2);
            bool dstOk = at(dst) != 'B' && at(dst) != 'R';
            if (dstOk) {
                bool notB1 = at(x, y + 1) != 'B' && at(x, y + 2) != 'B';
                bool notB2 = at(x - 1, y) != 'B' && at(x - 1, y + 1) != 'B';
                if (notB1 || notB2)
                    lst.push_back(dst);
            }
        }

        if (x > 1 && y < (w - 1)) {
            int dst = fromPos(x - 2, y + 1);
            bool dstOk = at(dst) != 'B' && at(dst) != 'R';
            if (dstOk) {
                bool notB1 = at(x - 1, y) != 'B' && at(x - 2, y) != 'B';
                bool notB2 = at(x, y + 1) != 'B' && at(x - 1, y + 1) != 'B';
                if (notB1 || notB2)
                    lst.push_back(dst);
            }
        }

        return lst;
    }

    void initGraph()
    {
        // init m_graph
        for (int i = 0; i < size(); i++) {
            for (int j = 0; j < size(); j++) {
                int k = i * size() + j;
                m_graph[k] = i == j ? 0 : -1;
            }
        }

        for (int i = 0; i < size(); i++) {
            char cell = at(i);
            int cost = moveCost(cell);

            auto lst = validMoveList(toPos(i));
            auto lstHorse = validHorseMoveList(toPos(i));
            lst.insert(lst.end(), lstHorse.begin(), lstHorse.end());

            for (int k = 0; k < lst.size(); k++) {
                int j = lst[k];

                int ij = i * size() + j;
                m_graph[ij] = cost;

                //int ji = j * size() + i;
                //m_graph[ji] = cost;
            }
        }

        initTeleports();

        // init m_ways
        for (int i = 0; i < size(); i++) {
            for (int j = 0; j < size(); j++) {
                int ij = i * size() + j;
                m_ways[ij] = i;
            }
        }

        // Floid algorythm
        for (int m = 0; m < size(); m++) {
            for (int i = 0; i < size(); i++) {
                for (int j = 0; j < size(); j++) {
                    int ij = i + j * size();
                    int im = i + m * size();
                    int mj = m + j * size();

                    if (i != j && m_graph[im] != -1 && m_graph[mj] != -1) {
                        if (m_graph[ij] == -1) {
                            m_graph[ij] = m_graph[im] + m_graph[mj];
                            m_ways[ij] = m_ways[im];
                        } else {
                            if (m_graph[ij] > m_graph[im] + m_graph[mj]) {
                                m_graph[ij] = m_graph[im] + m_graph[mj];
                                m_ways[ij] = m_ways[im];
                            }
                        }
                    }
                }
            }
        }
    }

public:
    static void printNewArray()
    {
        for (int y = 0; y < height(); y++) {
            for (int x = 0; x < width(); x++) {
                cout << m_travel[x + y * width()] << " ";
            }
            cout << endl;
        }
    }

    void printArrayWithTravel(int x1, int y1, int x2, int y2)
    {
        bool x1_ok = x1 >= 0 && x1 < width();
        bool x2_ok = x2 >= 0 && x1 < width();
        bool y1_ok = y1 >= 0 && y1 < height();
        bool y2_ok = y2 >= 0 && y1 < height();
        if (!x1_ok || !x2_ok || !y1_ok || !y2_ok) {
            cerr << "Wrong parameters!" << endl;
            return;
        }

        for (int i = 0; i < size(); i++)
            m_travel[i] = m_plainArray.arr[i];

        int startNode = fromPos(x1, y1);
        int endNode = fromPos(x2, y2);
        int count = 0;
        while (startNode != endNode && count < (size() * size())) {
            if (endNode < 0)
                break;

            if (m_travel[endNode] != 'T')
                m_travel[endNode] = 'o';
            endNode = m_ways[endNode + startNode * size()];
            ++count;
        }

        m_travel[fromPos(x1, y1)] = 'S';
        m_travel[fromPos(x2, y2)] = 'E';

        printNewArray();
        cout << "Total step count: " << to_string(count) << endl;
    }

private:
    static KnyPlainArray m_plainArray;

    static const int m_gSize = m_plainArray.arr.size() * m_plainArray.arr.size();

    static std::array<int, m_gSize> m_graph;
    static std::array<int, m_gSize> m_ways;

    static std::array<char, m_plainArray.arr.size()> m_travel;
};

std::array<int, KnyCore::m_gSize> KnyCore::m_graph;
std::array<int, KnyCore::m_gSize> KnyCore::m_ways;
std::array<char, KnyCore::m_plainArray.arr.size()> KnyCore::m_travel;

int main(int argc, char *argv[])
{
    KnyCore core;

    cout << "Source board:" << endl;
    core.printArray();

    cout << endl;
    cout << "Travel 1:" << endl;
    core.printArrayWithTravel(0, 0, 31, 0);

    cout << endl;
    cout << "Travel 2:" << endl;
    core.printArrayWithTravel(31, 0, 10, 31);

    return 0;
}
