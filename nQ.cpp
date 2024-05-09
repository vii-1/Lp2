#include <bits/stdc++.h>
using namespace std;

bool valid(vector<vector<int>> &matrix,int i, int j){
    
    int n = matrix.size();

    // check in row
    for(int k=0;k<n;k++){
        if(matrix[i][k])
            return false;
    }
    
    // check for diagonal
    int r=i,k=j;
    while(r>=0 && k>=0){
        if(matrix[r][k]){
            return false;
        }
        r--,k--;
    }

    r=i,k=j;
    while(r<n && k>=0){
        if(matrix[r][k]){
            return false;
        }
        r++,k--;
    }

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

bool n_queens(vector<vector<int>> &mat,int col,bool &f){

    int n=mat.size();
    if(col>=n){
        print(mat);
        cout<<endl;
        f=1;
    }

    for(int i=0;i<n;i++){
        if(valid(mat,i,col)){
            mat[i][col]=1;

            if(n_queens(mat,col+1,f)){
                return true;
            }else{
                mat[i][col]=0;
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
    n_queens(matrix,0,f);

    if(!f){
        cout<<"No solution exists"<<endl;
    }
}