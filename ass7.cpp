#include <bits/stdc++.h>
using namespace std;

int main() {
    int n=0, frameCount =0, pageFaults = 0;
    cout << " Enter No of pages:";
    cin>> n;
    
    vector<int> pages(n,0);   
    cout<< "Enter page reference string:";
    for(int i=0; i<n; i++) cin>> pages[i];

    cout<< "Enter no. of frames:";
    cin>> frameCount;

    // vector<int> frames;
    queue<int> q;

    for (int i =0; i<n; i++){
        int page = pages[i];
        bool found = false;

        queue<int> q2 = q;
        while (!q2.empty()){
            int f = q2.front();
            q2.pop();
            if ( page == f ) found = true ;
        }

        if( !found){
            pageFaults++;
            q.push(page);
            
            while(q.size() > frameCount) q.pop();
        }

        cout<< "After page"<<page<<" : ";

        queue<int> q3 = q;
        while (!q3.empty()){
            int f = q3.front();
            q3.pop();
            cout<< f<<" ";
        }
        cout<<endl;
    }

    cout<< "\nTOtal page fault = "<<pageFaults<<endl;

    return 0;
}