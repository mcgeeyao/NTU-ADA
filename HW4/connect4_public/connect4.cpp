#include "connect4.h"
#include <vector>
using namespace std;

vector<vector<int>> board(6,vector<int> (7,0));
int moves=0;
vector<int> order={3,2,4,1,5,0,6};

int LegalRow(vector<vector<int>>& board,int col){
    int row=5;
    while(row>=0 and board[row][col]!=0)row--;
    return row;
}   

vector<int> LegalMoves(vector<vector<int>>& board){
    vector<int> legalmoves;
    for(auto i:order)
        if (board[0][i]==0)
            legalmoves.push_back(i);
    return legalmoves;
}
    

void MakeMove(vector<vector<int>>& board,int col,int row,int player){
    board[row][col]=player;
    moves++;
}
    

void UnmakeMove(vector<vector<int>>& board,int col,int row){
    board[row][col]=0;
    moves--;
}

bool IsWinning(vector<vector<int>> &board,int player){
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++)
            if (board[i][j]==player and board[i][j+1]==player and board[i][j+2]==player and board[i][j+3]==player)
                return true;
    }    
    for(int i=0;i<3;i++){
        for(int j=0;j<7;j++)
            if(board[i][j]==player and board[i+1][j]==player and board[i+2][j]==player and board[i+3][j]==player)
                return true;
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++)
            if(board[i][j]==player and board[i+1][j+1]==player and board[i+2][j+2]==player and board[i+3][j+3]==player)
                return true;
    }
    for(int i=3;i<6;i++){
        for(int j=0;j<4;j++)
            if(board[i][j]==player and board[i-1][j+1]==player and board[i-2][j+2]==player and board[i-3][j+3]==player)
                return true;
    }
    return false;
}
// vector<vector<int>> evaluationTable = {{3, 4, 5, 7, 5, 4, 3}, 
//                                           {4, 6, 8, 10, 8, 6, 4},
//                                           {5, 8, 11, 13, 11, 8, 5}, 
//                                           {5, 8, 11, 13, 11, 8, 5},
//                                           {4, 6, 8, 10, 8, 6, 4},
//                                           {3, 4, 5, 7, 5, 4, 3}};


// int evaluation2(vector<vector<int>> &board) {
//     int utility = 128;
//     int sum = 0;
//     for (int i = 0; i < 6; i++)
//         for (int j = 0; j <7; j++)
//             if (board[i][j] == 1)
//                 sum += evaluationTable[i][j];
//             else if (board[i][j] == 2)
//                 sum -= evaluationTable[i][j];
//     return utility + sum;
// }
int evaluation(vector<vector<int>> &board){
    if (IsWinning(board, 2))
        return -1000;
    else if (IsWinning(board, 1))
        return 1000;
    else if (moves==42)
        return 0;
    vector<pair<int,int>> list;
    int score=0;
    for(int i=0;i<6;i++){
        for(int j=0;j<4;j++){
            int x=0,y=0;
            if(board[i][j]==1)x++;
            if(board[i][j]==2)y++;
            if(board[i][j+1]==1)x++;
            if(board[i][j+1]==2)y++;
            if(board[i][j+2]==1)x++;
            if(board[i][j+2]==2)y++;
            if(board[i][j+3]==1)x++;
            if(board[i][j+3]==2)y++;
            list.push_back(make_pair(x,y));
        }
    }    
    for(int i=0;i<3;i++){
        for(int j=0;j<7;j++){
            int x=0,y=0;
            if(board[i][j]==1)x++;
            if(board[i][j]==2)y++;
            if(board[i+1][j]==1)x++;
            if(board[i+1][j]==2)y++;
            if(board[i+2][j]==1)x++;
            if(board[i+2][j]==2)y++;
            if(board[i+3][j]==1)x++;
            if(board[i+3][j]==2)y++;
            list.push_back(make_pair(x,y));
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            int x=0,y=0;
            if(board[i][j]==1)x++;
            if(board[i][j]==2)y++;
            if(board[i+1][j+1]==1)x++;
            if(board[i+1][j+1]==2)y++;
            if(board[i+2][j+2]==1)x++;
            if(board[i+2][j+2]==2)y++;
            if(board[i+3][j+3]==1)x++;
            if(board[i+3][j+3]==2)y++;
            list.push_back(make_pair(x,y));
        }
    }
    for(int i=3;i<6;i++){
        for(int j=0;j<4;j++){
            int x=0,y=0;
            if(board[i][j]==1)x++;
            if(board[i][j]==2)y++;
            if(board[i-1][j+1]==1)x++;
            if(board[i-1][j+1]==2)y++;
            if(board[i-2][j+2]==1)x++;
            if(board[i-2][j+2]==2)y++;
            if(board[i-3][j+3]==1)x++;
            if(board[i-3][j+3]==2)y++;
            list.push_back(make_pair(x,y));
        }
    }
    for(auto pii:list){
        int x=pii.first,y=pii.second;
        if(x==0 and y==0)score+=0;
        else if(x==1 and y==0)score+=1;
        else if(x==2 and y==0)score+=2;
        else if(x==3 and y==0)score+=5;
        else if(x==0 and y==1)score-=1;
        else if(x==0 and y==2)score-=2;
        else if(x==0 and y==3)score-=5;
    }
    return score;


}

int minimax(int depth,int alpha,int beta,bool myturn,vector<vector<int>>& board){
    if(depth==0 or moves==42)return evaluation(board);

	if(myturn){
        int maxEval = -1000;
		for(int i:LegalMoves(board)){
            int row=LegalRow(board,i);
            MakeMove(board,i,row,1);
            if (IsWinning(board, 1)){
                UnmakeMove(board,i,row);
                return 1000;
            }
            int eval = minimax( depth - 1, alpha, beta ,false,board);
            UnmakeMove(board,i,row);
			maxEval = max(maxEval, eval);
			alpha = max(alpha, eval);
			if(beta <= alpha)break;
        }
		return maxEval;
    }else{
        int minEval = 1000;
		for(int i:LegalMoves(board)){
            int row=LegalRow(board,i);
            MakeMove(board,i,row,2);
            if (IsWinning(board, 2)){
                UnmakeMove(board,i,row);
                return -1000;
            }
            int eval = minimax( depth - 1, alpha, beta ,true,board);
            UnmakeMove(board,i,row);
			minEval = min(minEval, eval);
			beta = min(beta, eval);
			if(beta <= alpha)break;
        }
		return minEval;
    }
		
}
	
int myDecision(vector<vector<int>>& board){
    int maxEval = -10000;
    int move=-1;
    for(int i:LegalMoves(board)){
        int row=LegalRow(board,i);
        MakeMove(board,i,row,1);
        if (IsWinning(board, 1)){
            UnmakeMove(board,i,row);
            return i;
        }
        int eval = minimax(4, -10000, 10000 ,false,board);
        UnmakeMove(board,i,row);
        if(maxEval<eval){
            maxEval=eval;
            move=i;
        }
    }
    return move;
}


int decide(int yp_move) {
    if (yp_move == -1) {
        for(int i=0;i<6;i++){
            for(int j=0;j<7;j++){
                board[i][j]=0;
            }
        }
        board[5][3]=1;
        MakeMove(board,3,5,1);
        return 3;
    }
    else {
        MakeMove(board,yp_move,LegalRow(board,yp_move),2);
        int md=myDecision(board);
        MakeMove(board,md,LegalRow(board,md),1);
        return md;
    }
    return 0;
}
