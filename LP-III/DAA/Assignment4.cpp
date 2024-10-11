#include<bits/stdc++.h>
using namespace std;

bool isSafe(int r , int c , vector<vector<int>>&board , int n )
{
    int i = r ; 
    int j = c;

    //upperleft
    while(i>=0 && j>=0)
    {
        if(board[i][j] == 1)
        {
            return false;
        }
        i--;
        j--;
    }
    i = r ;
    j =c ;

    //lowerleft
    while(i<n && j>=0 )
    {
        if(board[i][j] == 1)
        {
            return false;
        }
        i++;
        j--;
    }

    //left
    i = r ; 
    j = c;
    while(j>=0)
    {
        if(board[i][j] == 1)
        {
            return false;
        }
        j--;
    }

    //upperright
    i = r ; 
    j = c ;
    while(i>=0 && j<n)
    {
        if(board[i][j] == 1)
        {
            return false;
        }
        i--;
        j++;
    }

    //lowerright
    i = r ;
    j= c ;
    while(i<n && j<n)
    {
        if(board[i][j] == 1)
        {
            return false;
        }
        i++;
        j++;
    }

    //right
    i = r ; 
    j = c ;
    while(j<n)
    {
        if(board[i][j] == 1)
        {
            return false;
        }
        j++;
    }

    return true;
}
void solve(int col , int col1 , vector<vector<int>>&board , int n, int& cnt)
{
    if(col==n)
    {   
        cnt ++;
        for(auto c : board)
        {
            for(auto x : c)
            {
                cout<<x;
            }
            cout<<endl;
        }
        cout<<endl;
    }

    if(col==col1)
    {
        solve(col+1, col1 ,board , n, cnt);
    }

    for(int i = 0 ;i<n ;i++)
    {
        if(isSafe(i,col,board ,n))
        {
            board[i][col] = 1;
            solve(col+1 , col1 , board , n, cnt);
            board[i][col] =0;
        }
    }
}
int main()
{
    cout<<"Enter the size of matrix : ";
    int n ; 
    cin>>n;
    int cnt=0;
    if(n<4)
    {
        cout<<"No possible input for n less than 4"<<endl;
    }
    vector<vector<int>>board(n , vector<int>(n,0));
    cout<<"Enter the first queen at the given row and column : "<<endl;
    cout<<"Enter row : ";
    int r ; 
    cin>>r;
    cout<<"Enter column : ";
    int c ; 
    cin>>c;

    board[r][c] = 1;
    solve(0,c,board,n,cnt);
    if(cnt == 0)
    {
        cout<<"No possible solution for the given input"<<endl;
    }
}