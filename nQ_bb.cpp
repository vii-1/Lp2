#include <bits/stdc++.h>
using namespace std;

/* the only diff between n_queens and n_queens branch ans bound is here we optimize
the valid function time complexity from O(n) to O(1) by using the extra space*/

bool valid(vector<vector<int>> &matrix,int i, int j,vector<bool> &row,vector<bool> &ld,vector<bool> &rd){
    int n=matrix.size();

    if(row[i] || ld[i+j] || rd[j-i+n-1])
        return false;
    
    return true;
}

void print(vector<vector<int>> &mat){
    for(auto i:mat){
        for(auto j:i){
            cout<<j<<' ';
        }
        cout<<endl;
    }
}

bool n_queens(vector<vector<int>> &mat,int col,bool &f,vector<bool> &row,vector<bool> &ld,vector<bool> &rd){

    int n=mat.size();
    if(col>=n){
        print(mat);
        cout<<endl;
        f=1;
    }

    for(int i=0;i<n;i++){
        if(valid(mat,i,col,row,ld,rd)){
            mat[i][col]=1;
            row[i]=1;
            ld[i+col]=1;
            rd[col-i+n-1]=1;

            if(n_queens(mat,col+1,f,row,ld,rd)){
                return true;
            }else{
                mat[i][col]=0;
                row[i]=0;
                ld[i+col]=0;
                rd[col-i+n-1]=0;
            }
        }
    }

    return false;
}

int main()
{
    int n;
    cout<<"Enter the n for the matrix"<<endl;
    cin>>n;

    vector<vector<int>> matrix(n,vector<int>(n,0));
    bool f=0;

    vector<bool> row(n,false);
    vector<bool> ld(2*n-1,false);
    vector<bool> rd(2*n-1,false);

    n_queens(matrix,0,f,row,ld,rd);

    if(!f){
        cout<<"No solution exists"<<endl;
    }
}