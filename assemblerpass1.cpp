#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("ass1ip.txt");
    ofstream inter("intermediate.txt"), sym("symtab.txt");

    map<string, string> OPTAB = {
        {"START", ""}, {"MOVER", "04"}, {"ADD", "01"},
        {"SUB", "02"}, {"MOVEM", "05"}, {"END", ""}
    };

    string line;
    int locctr = 0, start = 0;

    while (getline(fin, line)) {
        if (line.empty()) continue;

        // Replace commas with spaces
        replace(line.begin(), line.end(), ',', ' ');
        stringstream ss(line);
        vector<string> tok;
        string temp;
        while (ss >> temp) tok.push_back(temp);

        // START
        if (tok[0] == "START") {
            start = stoi(tok[1]);
            locctr = start;
            inter << "START " << start << "\n";
        }
        // END
        else if (tok[0] == "END") {
            inter << "END\n";
            break;
        }
        // LABEL + OPCODE (e.g., LOOP SUB CREG, D)
        else if (OPTAB.find(tok[0]) == OPTAB.end()) {
            string label = tok[0];
            string opcode = tok[1];
            string operand = (tok.size() > 3) ? tok[3] : tok.back();
            sym << label << " " << locctr << "\n";
            inter << locctr << " " << opcode << " " << operand << "\n";
            locctr += 3;
        }
        // NO LABEL (e.g., MOVER AREG, B)
        else {
            string opcode = tok[0];
            string operand = (tok.size() > 2) ? tok[2] : tok.back();
            inter << locctr << " " << opcode << " " << operand << "\n";
            locctr += 3;
        }
    }

    cout << "PASS 1 complete. (intermediate.txt & symtab.txt created)\n";
}
