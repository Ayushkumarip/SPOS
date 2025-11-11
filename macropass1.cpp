#include <bits/stdc++.h>
using namespace std;

struct MNT {
    string name;
    int mdtIndex;
};

int main() {
    ifstream fin("macroip.txt");
    ofstream mdt("mdt.txt"), mnt("mnt.txt"), inter("intermediate.txt");

    vector<MNT> mntTable;
    string line;
    bool inMacro = false;
    int mdtIndex = 1;

    while (getline(fin, line)) {
        stringstream ss(line);
        string first;
        ss >> first;

        if (first == "MACRO") {
            // next line contains macro header
            getline(fin, line);
            stringstream header(line);
            string macroName;
            header >> macroName;
            mntTable.push_back({macroName, mdtIndex});
            inMacro = true;
            continue;
        }

        if (inMacro) {
            if (line == "MEND") {
                mdt << "MEND\n";
                mdtIndex++;
                inMacro = false;
            } else {
                mdt << line << "\n";
                mdtIndex++;
            }
        } else {
            inter << line << "\n";
        }
    }

    for (auto &m : mntTable)
        mnt << m.name << " " << m.mdtIndex << "\n";

    cout << "PASS 1 done.\n";
}
