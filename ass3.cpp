#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<utility>  

using namespace std;

int main() {

    vector<pair<int, pair<string,int>>> MNT;   // (MNTC, name ,MDTC);=
    vector<pair<int, string>> MDT; // (MDTC , Def);=
    vector<pair<int,string>> ALA; //(MDTC,ARG);
  
    
    ifstream a;
    a.open("apass1.asm");  
    
    string h;
    int i = 0;
    
    while(getline(a, h)) {  
        
        int x = h.length();
        
      
        if (h.find("%macro") != string::npos) {
            i++;
            string g = "";
            for(int j=7;j<x;j++){
            	if(h[j] == ' '){
            		break;
            	}
            	
            	g += h[j];
            }
            
            MNT.push_back(make_pair(i,make_pair(g,i)));
        }
    }
    
    a.close();
    
    a.open("apass1.asm");  
    
    
    
    for(auto d : MNT){
    	
    	string mac = d.second.first; // taking NAME of Macro
    	i = d.second.second; //taking MDTC of macro
    	
    	bool z = 0;
    	
    	while(getline(a, h)) {  
    	
    		if (h == "%endmacro") {
        		z = 0;
        		break;
        	}
		
		if(z == 1){MDT.push_back(make_pair(i,h));}
	      
		if (h.find(mac) != string::npos) {
			z = 1;
        	}
        	
        	
    	}
    	
    
    }

    a.close();


    a.open("apass1.asm");

    int z = 0;
    while(getline(a,h)){

        if(!h.find("%macro")){
            int w = 1;
            string g = "";
            for(int i=7;i<h.length();i++){
                if(w == 0){
                    g+=h[i];
                }

                if(h[i] == ' '){
                    w = 0;
                }


            }
            z++;
            ALA.push_back(make_pair(z,g));
        }

    }






    a.close();
    
    cout<<"MNT is as follows -->> \n";
    cout<<"MNTC --> MACRO --> MDTC \n";
    for(auto d : MNT){
    	cout<<d.first<<" --> "<<d.second.first<< " --> "<<d.second.second<< "\n";
    
    }
    
    cout<<"\n\nMDT is as follows -->> \n";
    cout<<"MDTC --> DEF \n";
    for(auto d : MDT){
    	cout<<d.first<<" --> "<<d.second<< "\n";
    
    }


    cout<<"\n\nALA is as follows -->> \n";
    cout<<"MDTC --> ARG \n";
    for(auto d : ALA){
    	cout<<d.first<<" --> "<<d.second<< "\n";
    
    }
    
    
    
    
    return 0;
}
