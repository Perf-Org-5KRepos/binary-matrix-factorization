// Copyright (C) 2019, International Business Machines
// Corporation.  All Rights Reserved.

// This program is distributed under the terms of the
// Eclipse Public License - v 2.0

#include "VOL_matrix.hpp"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

void readInputData(string fname, int& n, int& m, VOL_matrix& x)
{
    
    ifstream infile(fname.c_str());
    if (!infile){
        printf("Could not open file %s", fname.c_str());
        abort();
    }
    
    // read the header line
    string header;
    if(infile) {
        getline(infile,header);
    }
    
    // read n and m
    string s;
    getline( infile, s );
    printf("%s\n",s.c_str());
    istringstream ss( s );
    int counter=1;
    while (ss) {
        string s;
        if (!getline( ss, s, ',' )) break;
        if(counter==1)
            n = atoi(s.c_str());
        else if(counter==2)
            m = atoi(s.c_str());
        counter++;
    }
    
    // resize x
    assert(n>0 && m>0);
    x.allocate(n, m);
    
    // read the header line
    if(infile) {
        getline(infile,header);
    }
    
    // read the matrix entries
    int numbPos=0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            string s;
            if (!getline( infile, s )) break;
            
            istringstream ss( s );
            int counter=1;
            int iInd=-1;
            int jInd=-1;
            int xVal=-1;
            while (ss) {
                string s;
                if (!getline( ss, s, ',' )) break;
                if(counter==1)
                    iInd = atoi(s.c_str());
                else if(counter==2)
                    jInd = atof(s.c_str());
                else if(counter==3)
                    xVal = atof(s.c_str());
                counter++;
            }
            
            x(iInd, jInd)=xVal;
            if ( xVal > 0) ++numbPos;
        }
    }
    printf("%d positives elements\n", numbPos);
    
    infile.close();
    
}
