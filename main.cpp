//
//  main.cpp
//  StableMatching
//
//  Created by ssyww on 20/2/22.
//  Copyright © 2020年 ViolaLee. All rights reserved.
//

#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

//0 stands for no stable matching, 1 stands for has a stable matching
int GS(int n, vector<vector<string> > boy, vector<vector<string> > girl, vector<vector<string> > &staMatch);
void inverse(int n, vector<string> girl, vector<int> &inverseGirl, vector<string> boyName);

int main(int argc, const char * argv[]) {
    int n = 0;
    cin >> n;
    string temp;
    char tempName[20];
    
//    string *boy = new string[n][n+1];
//    string *girl = new string[n][n+1];
    vector<vector<string> > boy;
    vector<vector<string> > girl;
    
    vector<vector<string> > stableMatch( n, vector<string>(2));//store the stable matches
    
    //prefer lists of all the boys
    for(int i=0; i<n; i++) {
        vector<string> t;
        for (int j=0; j<=n; j++) {
            cin >> tempName;
            temp = tempName;
            //cout << temp;
            t.push_back(temp);
        }
        boy.push_back(t);
        t.clear();
    }
    
    //prefer lists of all the girls
    for (int a=0; a<n; a++) {
        vector<string> t;
        for (int b=0; b<=n; b++) {
            cin >> tempName;
            temp = tempName;
            t.push_back(temp);
        }
        girl.push_back(t);
        t.clear();
    }
    
    //string test = boy[2][3];
    
    if (GS(n, boy, girl, stableMatch)) {
        for (int i=0; i<n; i++) {
            cout << stableMatch[i][0] << " " << stableMatch[i][1] << endl;
        }
        
    } else {
        cout << "impossible";
    }
    return 0;
}

//inverse the preference list of a girl
//index 0 is the girl's name, the preference list begins at the index 1
void inverse(int n, vector<string> girl, vector<int> &inverseGirl, vector<string> boyName){
    for (int i=1; i<=n; i++) {
        for (int j=0; j<n; j++) {
            if (girl[i] == boyName[j]) {
                inverseGirl[j] = i;
                break;
            }
        }
    }
}

//Propose-and-reject algorithm
int GS(int n, vector<vector<string> > boy, vector<vector<string> > girl, vector<vector<string> > &staMatch) {
    int isStable = 0;
    
    //a list of boy's name/girl's name
    vector<string> boyName(n);
    vector<string> girlName(n);
    for (int i=0; i<n; i++) {
        boyName[i] = boy[i][0];
        girlName[i] = girl[i][0];
    }
    
    //for all girls, get the inverse list
    vector<vector<int> > inverGirl(n, vector<int>(n));
    for (int i=0; i<n; i++) {
        vector<int> inverseGirl(n);
        inverse(n, girl[i], inverseGirl, boyName);
        inverGirl[i] = inverseGirl;
    }
    
    //if not match, the value is 0. Else the value is matched one's index.
    int *boyMatch = new int[n];
    int *girlMatch = new int[n];
    //initialize 0(all unmatched)
    for (int i=0; i<n; i++) {
        boyMatch[i] = 0;
        girlMatch[i] = 0;
    }
    
    //Maintain an array count[m] that counts the number of proposals made by man m
    int *count = new int[n];
    //initialize 0(all hasn't proposal)
    for (int i=0; i<n; i++) {
        count[i] = 0;
    }
    
    //keep all the free man in a queue. Use boyName's index to stand for the boy.
    queue<int> singleBoy;
    for (int i=0; i<n; i++) {
        singleBoy.push(i);
    }
    
    while (!singleBoy.empty()) {
        int boyID = singleBoy.front();
        string g = boy[boyID][count[boyID]+1];//1st girl on boy's list to whom boy has not yet proposed
        
        int girlIndex;
        //get the girl's index
        for (int i=0; i<n; i++) {
            if (girlName[i] == g) {
                girlIndex = i;
                break;
            }
        }
        
        if (girlMatch[girlIndex] == 0) {//if girl is free, assign g and b to be engaged
            boyMatch[boyID] = girlIndex + 1;
            girlMatch[girlIndex] = boyID + 1;
            
            count[boyID]++;
            singleBoy.pop();
        } else if (inverGirl[girlIndex][boyID] < inverGirl[girlIndex][girlMatch[girlIndex]-1]) {//if girl prefer b to her fiance b', assign g and b to be engaged, and b' to be free
            singleBoy.push(girlMatch[girlIndex] - 1);
            boyMatch[girlMatch[girlIndex]-1] = 0;
            boyMatch[boyID] = girlIndex + 1;
            girlMatch[girlIndex] = boyID + 1;
            
            count[boyID]++;
            singleBoy.pop();
        } else {//girl reject the boy
            count[boyID]++;
        }
    }
    
    for (int i=0; i<n; i++) {
        staMatch[i][0] = boyName[i];
        staMatch[i][1] = girlName[boyMatch[i]-1];
    }
    
    isStable = 1;
    
    return isStable;
}