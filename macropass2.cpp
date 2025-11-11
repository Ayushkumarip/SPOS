#include <bits/stdc++.h>
using namespace std;

struct MNT {
    string name;
    int mdtIndex;
};

int main() {
    ifstream inter("intermediate.txt"), mdt("mdt.txt"), mnt("mnt.txt");
    ofstream out("output.txt");

    vector<MNT> mntTable;
    string line;
    while (getline(mnt, line)) {
        string name; int idx;
        stringstream ss(line);
        ss >> name >> idx;
        mntTable.push_back({name, idx});
    }

    vector<string> MDT;
    while (getline(mdt, line))
        MDT.push_back(line);

    while (getline(inter, line)) {
        stringstream ss(line);
        string word; ss >> word;
        bool expanded = false;

        for (auto &m : mntTable) {
            if (word == m.name) {
                string arg; ss >> arg;
                for (int i = m.mdtIndex - 1; i < (int)MDT.size(); i++) {
                    if (MDT[i] == "MEND") break;
                    string temp = MDT[i];
                    size_t pos = temp.find("&ARG1");
                    if (pos != string::npos)
                        temp.replace(pos, 6, arg);
                    out << temp << "\n";
                }
                expanded = true;
                break;
            }
        }
        if (!expanded) out << line << "\n";
    }

    cout << "PASS 2 done.\n";
}
