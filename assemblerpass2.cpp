#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream inter("intermediate.txt"), sym("symtab.txt");
    ofstream out("output.txt");

    // --- Load Symbol Table ---
    map<string, string> SYMTAB;
    string symb, addr;
    while (sym >> symb >> addr)
        SYMTAB[symb] = addr;

    // --- Operation Table ---
    map<string, string> OPTAB = {
        {"MOVER", "04"}, {"ADD", "01"},
        {"SUB", "02"}, {"MOVEM", "05"}
    };

    string line;
    while (getline(inter, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<string> tok;
        string t;
        while (ss >> t) tok.push_back(t);

        if (tok[0] == "START" || tok[0] == "END")
            continue;

        // Each instruction line has: loc opcode operand
        if (tok.size() >= 3) {
            string loc = tok[0];
            string opcode = tok[1];
            string operand = tok[2];

            string opCode = OPTAB[opcode];
            string opAddr = SYMTAB.count(operand) ? SYMTAB[operand] : operand;

            out << loc << " " << opCode << " " << opAddr << "\n";
        }
    }

    cout << "PASS 2 complete — output.txt generated successfully.\n";
}
