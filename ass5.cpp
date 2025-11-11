#include <iostream>
#include <vector>
#include <algorithm>
#include <queue> // <-- ADDED THIS INCLUDE
using namespace std;

struct Process {
    int pid, bt, at, wt, tat, prio, remaining;
};

void printTable(vector<Process>& p) {
    cout << "\nPID\tAT\tBT\tWT\tTAT\n";
    // Sort by PID for a clean, consistent output table
    sort(p.begin(), p.end(), [](auto &a, auto &b){ return a.pid < b.pid; });
    for (auto &x : p)
        cout << x.pid << "\t" << x.at << "\t" << x.bt << "\t" << x.wt << "\t" << x.tat << endl;
}

void fcfs(vector<Process> p) {
    cout << "\n--- FCFS Scheduling ---\n";
    sort(p.begin(), p.end(), [](auto &a, auto &b){ return a.at < b.at; });
    int time = 0;
    for (auto &x : p) {
        if (time < x.at) time = x.at;
        x.wt = time - x.at;
        time += x.bt;
        x.tat = x.wt + x.bt;
    }
    printTable(p);
}

void sjfPreemptive(vector<Process> p) {
    cout << "\n--- SJF (Preemptive) Scheduling ---\n";
    int n = p.size(), complete = 0, t = 0, minm = 1e9;
    int shortest = 0, finish_time;
    bool check = false;
    for (auto &x : p) x.remaining = x.bt;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((p[j].at <= t) && (p[j].remaining < minm) && p[j].remaining > 0) {
                minm = p[j].remaining;
                shortest = j;
                check = true;
            }
        }

        if (!check) { t++; continue; }

        p[shortest].remaining--;
        minm = p[shortest].remaining == 0 ? 1e9 : p[shortest].remaining;

        if (p[shortest].remaining == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            p[shortest].wt = finish_time - p[shortest].bt - p[shortest].at;
            if (p[shortest].wt < 0) p[shortest].wt = 0;
            p[shortest].tat = p[shortest].bt + p[shortest].wt;
        }
        t++;
    }
    printTable(p);
}

void priorityNonPreemptive(vector<Process> p) {
    cout << "\n--- Priority (Non-Preemptive) Scheduling ---\n";
    sort(p.begin(), p.end(), [](auto &a, auto &b){
        return (a.prio == b.prio) ? a.at < b.at : a.prio < b.prio;
    });
    int time = 0;
    for (auto &x : p) {
        if (time < x.at) time = x.at;
        x.wt = time - x.at;
        time += x.bt;
        x.tat = x.wt + x.bt;
    }
    printTable(p);
}

// vvvvvvvvvvvv THIS FUNCTION IS NOW FIXED vvvvvvvvvvvv
void roundRobin(vector<Process> p, int quantum) {
    cout << "\n--- Round Robin (Preemptive) Scheduling ---\n";
    int n = p.size();
    for (auto &x : p) x.remaining = x.bt;

    // Sort by arrival time to handle arrivals correctly
    sort(p.begin(), p.end(), [](auto &a, auto &b){ return a.at < b.at; });

    queue<int> q; // Ready queue (stores indices of processes in p)
    int t = 0;           // Current time
    int complete = 0;
    int idx = 0;         // Index to track next process to arrive

    // Start time at the first process's arrival and add it to the queue
    t = p[0].at;
    q.push(0);
    idx = 1;

    while (complete != n) {
        if (q.empty()) {
            // CPU is idle. Jump time to the next process that arrives.
            t = p[idx].at;
            q.push(idx);
            idx++;
            continue; // Go back to the top of the loop
        }

        int i = q.front(); // Get process index from front of queue
        q.pop();

        // Run the process for the quantum or its remaining time, whichever is smaller
        int time_slice = min(quantum, p[i].remaining);
        p[i].remaining -= time_slice;
        t += time_slice;

        // Add all processes that arrived *while this process was running*
        while (idx < n && p[idx].at <= t) {
            q.push(idx);
            idx++;
        }

        if (p[i].remaining == 0) {
            // Process is complete
            complete++;
            p[i].tat = t - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            if (p[i].wt < 0) p[i].wt = 0; // Ensure waiting time is not negative
        } else {
            // Process is not finished, add it back to the end of the queue
            q.push(i);
        }
    }
    
    printTable(p); // printTable will sort by PID before printing
}
// ^^^^^^^^^^^^ THIS FUNCTION IS NOW FIXED ^^^^^^^^^^^^

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter AT, BT, Priority for P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].prio;
    }

    fcfs(p);
    sjfPreemptive(p);
    priorityNonPreemptive(p);
    int q;
    cout << "\nEnter Quantum for Round Robin: ";
    cin >> q;
    roundRobin(p, q);
    return 0;
}