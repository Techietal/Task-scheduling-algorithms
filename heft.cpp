#include <bits/stdc++.h>
using namespace std;

bool mycomp(pair<long,int> a,pair<long,int> b) {
    if(a.second == b.second) return a.first < b.first;
    return a.second > b.second;
}

long calrp(int tind,vector<int> &fin,vector<vector<int>> commc,vector<double> mw,vector<long> &rup) {
    long k = 0,maxi = 0;
    for(int i = 0;i < fin.size(); i++) {
        if(commc[tind][i] != -1) {
            if(fin[i] == 0) {
                rup[i] = calrp(i,fin,commc,mw,rup);
                fin[i] = 1;
            }
            k = commc[tind][i] * 10000 + rup[i];
            maxi = max(maxi,k);
        }
    }
    return maxi + mw[tind] * 10000;
}

void cal(vector<int> &fin,vector<vector<int>> commc,vector<double> mw,vector<long> &rup) {
    for(int i = 0;i < fin.size();i++) {
        if(fin[i] == 0) {
            rup[i] = calrp(i,fin,commc,mw,rup);
            fin[i] = 1;
        }
    }
}

void performphase(vector<int> &aft, vector<int> &ast, vector<int> &pros, vector <int> &avail,vector<vector<int>> &commc, vector<int> &seq,vector<vector<int>> &compc) {
    for(int i = 0;i < seq.size();i++) {
        int ans1, ans2, ans3,min_eft = INT_MAX;
        for(int j = 0;j < avail.size();j++) {
            int st,est = 0,eft = 0,max_est = 0, pro;
            int fg = 0;
            for(int k = 0;k < seq.size();k++) {
                if(commc[k][seq[i] - 1] != -1) {
                    fg = 1;
                    if(pros[k] != j + 1) {
                        est = max(avail[j] ,commc[k][seq[i] - 1] + aft[k]);
                    }
                    else est = max(avail[j] , aft[k]);
                }
                else if(!fg) est = avail[j];
                if(max_est < est) {
                    max_est = est;
                }
            }
            eft = max_est + compc[seq[i] - 1][j];
            if(eft < min_eft  || (eft == min_eft && abs(avail[pro - 1] - avail[j]) > abs((eft - max_est) - (ans1 - ans2)))) {
                pro = j + 1;
                st = max_est;
                min_eft = eft;
                ans1 = min_eft;
                ans2 = st;
                ans3 = pro;
            }
        }
        aft[seq[i] - 1] = ans1;
        ast[seq[i] - 1] = ans2;
        pros[seq[i] - 1] = ans3;
        avail[ans3 - 1] = ans1;
     }
}

int main() {
    int n,p;
    cin >> n;
    cin >> p;
    vector<vector<int>> compc(n,vector<int> (p));
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < p;j++) cin >> compc[i][j];
    }
    vector<int> seq(n);
    vector<vector<int>> commc(n,vector<int> (n));
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++) cin >> commc[i][j];
    }
    vector<double> mw(n);
    vector<int> fin(n,0);
    for(int i = 0;i < n;i++) {
        double y = 0;
        for(int j = 0;j < p;j++) {
            y += compc[i][j];
        }
        mw[i] = (y/p);
    }
    vector<long> rup(n);
    for(int i = 0;i < n;i++) {
        int count = 0;
        for(int j = 0;j < n;j++) {
            if(commc[i][j] == -1) count++;
        }
        if(count == n) {
            rup[i] = mw[i] * 10000;
            fin[i] = 1;
        }
    }
    cal(fin,commc,mw,rup);
    for(int i = 0;i < n;i++) {
        double h = (double )rup[i]/10;
        rup[i] = round(h);
    }
    vector<pair<int,long>> pseq;
    for(int i = 0;i < n;i++) pseq.push_back(pair<int,long> (i + 1,rup[i]));
    sort(pseq.begin(),pseq.end(),mycomp);
    for(int i = 0;i < n;i++) {
        seq[i] = pseq[i].first;
    }
    for(int i = 0;i < n;i++) cout << seq[i] << " ";
    cout << endl;
    vector<int> aft(n,0),ast(n,0),pros(n,0),avail(p,0);
    performphase(aft,ast,pros,avail,commc,seq,compc);
    cout << "Tasks\tAST\tAFT\tProcessor\n";
    for(int i = 0;i < n;i++) {
        cout << i + 1 << "\t" << ast[i] << "\t" << aft[i] << "\t" << pros[i] <<endl;
    }
}