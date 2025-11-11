#include <iostream>
#include <vector>
using namespace std;

void firstFit(vector<int> blocks, vector<int> process) {
    cout << "\n--- First Fit ---\n";
    vector<int> alloc(process.size(), -1);
    for (int i = 0; i < process.size(); i++) {
        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= process[i]) {
                alloc[i] = j;
                blocks[j] -= process[i];
                break;
            }
        }
    }
    for (int i = 0; i < process.size(); i++)
        cout << "Process " << i + 1 << " -> "
             << (alloc[i] == -1 ? "Not Allocated" : "Block " + to_string(alloc[i] + 1)) << endl;
}

void bestFit(vector<int> blocks, vector<int> process) {
    cout << "\n--- Best Fit ---\n";
    vector<int> alloc(process.size(), -1);
    for (int i = 0; i < process.size(); i++) {
        int best = -1;
        for (int j = 0; j < blocks.size(); j++)
            if (blocks[j] >= process[i])
                if (best == -1 || blocks[j] < blocks[best])
                    best = j;
        if (best != -1) {
            alloc[i] = best;
            blocks[best] -= process[i];
        }
    }
    for (int i = 0; i < process.size(); i++)
        cout << "Process " << i + 1 << " -> "
             << (alloc[i] == -1 ? "Not Allocated" : "Block " + to_string(alloc[i] + 1)) << endl;
}

void worstFit(vector<int> blocks, vector<int> process) {
    cout << "\n--- Worst Fit ---\n";
    vector<int> alloc(process.size(), -1);
    for (int i = 0; i < process.size(); i++) {
        int worst = -1;
        for (int j = 0; j < blocks.size(); j++)
            if (blocks[j] >= process[i])
                if (worst == -1 || blocks[j] > blocks[worst])
                    worst = j;
        if (worst != -1) {
            alloc[i] = worst;
            blocks[worst] -= process[i];
        }
    }
    for (int i = 0; i < process.size(); i++)
        cout << "Process " << i + 1 << " -> "
             << (alloc[i] == -1 ? "Not Allocated" : "Block " + to_string(alloc[i] + 1)) << endl;
}

void nextFit(vector<int> blocks, vector<int> process) {
    cout << "\n--- Next Fit ---\n";
    vector<int> alloc(process.size(), -1);
    int pos = 0;
    for (int i = 0; i < process.size(); i++) {
        int count = 0;
        while (count < blocks.size()) {
            if (blocks[pos] >= process[i]) {
                alloc[i] = pos;
                blocks[pos] -= process[i];
                break;
            }
            pos = (pos + 1) % blocks.size();
            count++;
        }
    }
    for (int i = 0; i < process.size(); i++)
        cout << "Process " << i + 1 << " -> "
             << (alloc[i] == -1 ? "Not Allocated" : "Block " + to_string(alloc[i] + 1)) << endl;
}

int main() {
    int nb, np;
    cout << "Enter number of memory blocks: ";
    cin >> nb;
    vector<int> blocks(nb);
    cout << "Enter block sizes: ";
    for (int i = 0; i < nb; i++) cin >> blocks[i];

    cout << "Enter number of processes: ";
    cin >> np;
    vector<int> process(np);
    cout << "Enter process sizes: ";
    for (int i = 0; i < np; i++) cin >> process[i];

    firstFit(blocks, process);
    bestFit(blocks, process);
    worstFit(blocks, process);
    nextFit(blocks, process);

    return 0;
}

