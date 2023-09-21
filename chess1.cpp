#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <math.h>
#include <map>
#include <algorithm>
#include <cstring>
#include <queue>
#include <stdio.h>
#include <cstdio>
#include <set>

using namespace std;
typedef long long ll;
typedef long double ld;

int wkx =7;
int wky = 4;
int bkx = 0;
int bky = 4;
int board_state = 1; // is state at the start of the game
bool checktest = false;
vector< vector<string> > spaces 
    {
    {"BR","BN","BB","BQ","BK","BB","BN","BR"},
    {"BP","BP","BP","BP","BP","BP","BP","BP"},
    {"  ","  ","  ","  ","  ","  ","  ","  "},
    {"  ","  ","  ","  ","  ","  ","  ","  "},
    {"  ","  ","  ","  ","  ","  ","  ","  "},
    {"  ","  ","  ","  ","  ","  ","  ","  "},
    {"WP","WP","WP","WP","WP","WP","WP","WP"},
    {"WR","WN","WB","WQ","WK","WB","WN","WR"}
    };

int let_to_num(char c){
    if (c == 'a')
        return 0;
    else if (c == 'b')
        return 1;
    else if (c == 'c')
        return 2;
    else if (c == 'd')
        return 3;
    else if (c == 'e')
        return 4;
    else if (c == 'f')
        return 5;
    else if (c == 'g')
        return 6;
    else if (c == 'h')
        return 7;
    else{
        return -1;
    }
}

void display_board(char c, vector< vector<string> > spaces){
    //cout<< "    0    1    2    3    4    5    6    7" << endl;
    int top= 8;
    //display top line
    cout<<"  ";
    while(top--){
        cout<< " --- "; 
    }
    //display side line and pieces
    cout<< endl;
    for (int i = 0; i < spaces.size(); i++){
        cout<< (8-i) <<"|";
        for(int j = 0; j < 8; j++){
            cout<< "  "<< spaces[i][j] << " ";
        }
        cout<<"| "<<endl<<"  ";
        int inbetween = 8;
        while(inbetween--){
            cout<< " --- "; 
        }
        cout<<endl; 
    }
    cout<< "    a    b    c    d    e    f    g    h" << endl;
    
}

//checks if move is valid
bool move_checker(int x, int y, int x1, int y1){
    string piece = spaces[x][y];
    //to make sure king checkmated isn't going out of bounds
    if(x1 > 7 || x1 <0 || y1<0 || y1 > 7){
        return false;
    }
    //if spot is empty
    if (piece == "  "){
        if(!checktest) cout << "NO PIECE AT THAT SPOT"<< endl;
        return false;
    }
    //else if trying to capture own piece
    else if (piece[0] == (spaces[x1][y1])[0]){
        cout << "CAN'T CAPTURE YOUR OWN PIECE"<<endl;
        return false;
    }
    else{
        if (piece == "WP"){//done
            if (spaces[x1][y1] == "  " && y == y1 &&(x-x1) == 1){
                if(x1 == 0){
                    if(!checktest) cout<< "What piece do you want to change to: "<<endl;
                    string transform;
                    cin>> transform;
                    spaces[x][y] = transform;
                }
                return true;
            } 
            else if(spaces[x1][y1] == "  " && y == y1 &&(x-x1) == 2 && x == 6 && spaces[x-1][y]=="  "){
                return true;
            }
            else if(spaces[x1][y1] != "  " && (x-x1)==1 && abs(y-y1) == 1){
                if(x1 == 0){
                    if(!checktest) cout<< "What piece do you want to change to: "<<endl;
                    string transform;
                    cin>> transform;
                    spaces[x][y] = transform;
                }
                return true;
            }
            else{
                return false;
            }
        }
        else if (piece == "BP"){//done
            if (spaces[x1][y1] == "  " && y == y1 && (x1-x) == 1){
                if(x1 == 7){
                    if(!checktest) cout<< "What piece do you want to change to: "<<endl;
                    string transform;
                    cin>> transform;
                    spaces[x][y] = transform;
                }
                return true;
            } 
            else if(spaces[x1][y1] == "  " && y == y1 && (x1-x) == 2 && x == 1 && spaces[x+1][y]=="  "){
                return true;
            }
            else if(spaces[x1][y1] != "  " && (x1-x)==1 && abs(y-y1) == 1){
                if(x1 == 7){
                    if(!checktest) cout<< "What piece do you want to change to: "<<endl;
                    string transform;
                    cin>> transform;
                    spaces[x][y] = transform;
                }
                return true;
            }
            else{
                return false;
            }
        }
        else if (piece == "WR"){//done
            if(x == x1 && y != y1){
                // cout<<"horizontal move"<<endl;
                if(y>y1){
                    swap(y, y1);
                }
                for(int i = y + 1; i<y1; i++ ){
                    if (spaces[x][i] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }
                }
                return true;
            }
            else if(x!=x1 && y == y1){
                //cout<<"vertical move"<<endl;
                if(x>x1){
                    swap(x, x1);
                }
                for(int i = x + 1; i<x1; i++ ){
                    if (spaces[i][y] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }
                }
                return true;
            }
            else{
                return false;
            }
        }
        else if (piece == "BR"){//done
            if(x == x1 && y != y1){
                //cout<<"horizontal move"<<endl;
                if(y>y1){
                    swap(y, y1);
                }
                for(int i = y + 1; i<y1; i++ ){
                    if (spaces[x][i] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }
                }
                return true;
            }
            else if(x!=x1 && y == y1){
                //cout<<"vertical move"<<endl;
                if(x>x1){
                    swap(x, x1);
                }
                for(int i = x + 1; i<x1; i++ ){
                    if (spaces[i][y] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }
                }
                return true;
            }
            else{
                return false;
            }
        }
        else if (piece == "WB"){//done
            if(x + y == x1 + y1){
                //cout<<"forward slash"<<endl;
                if(y>y1){
                    swap(y, y1);
                    swap(x, x1);
                }
                while (y+1<y1){
                    x--; 
                    y++;
                    if (spaces[x][y] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }   
                }
                return true;
            }
            else if(x - y == x1 - y1){
                //cout<<"backslash"<<endl;
                if(y>y1){
                    swap(y, y1);
                    swap(x, x1);
                }
                while (y+1<y1){
                    x++; 
                    y++;
                    if (spaces[x][y] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }   
                }
                return true;
            }
            
            else{
                return false;
            }
        }
        else if (piece == "BB"){//done
            if(x + y == x1 + y1){
                //cout<<"forward slash"<<endl;
                if(y>y1){
                    swap(y, y1);
                    swap(x, x1);
                }
                while (y+1<y1){
                    x--; 
                    y++;
                    if (spaces[x][y] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }   
                }
                return true;
            }
            else if(x - y == x1 - y1){
                //cout<<"backslash"<<endl;
                if(y>y1){
                    swap(y, y1);
                    swap(x, x1);
                }
                while (y+1<y1){
                    x++; 
                    y++;
                    if (spaces[x][y] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }   
                }
                return true;
            }
            
            else{
                return false;
            }
        }
        else if (piece == "BK"){//done
            // up-down movement
            if (y == y1 && (x1-x) == 1){
                wkx = x1;
                wky = y1;
                return true;
            } 
            else if(y == y1 &&(x-x1) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            // left-right movement
            else if(x == x1 && (y-y1) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            else if(x == x1 && (y1-y) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            // diagonal movement
            else if((x1-x) == 1 && (y1-y) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            else if((x-x1) == 1 && (y-y1) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            else if((x1-x) == 1 && (y-y1) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            else if((x-x1) == 1 && (y1-y) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            else{
                return false;
            }
        }
        else if (piece == "WK"){//done
            // up-down movement
            if (y == y1 && (x1-x) == 1){
                wkx = x1;
                wky = y1;
                return true;
            } 
            else if(y == y1 &&(x-x1) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            // left-right movement
            else if(x == x1 && (y-y1) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            else if(x == x1 && (y1-y) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            // diagonal movement
            else if((x1-x) == 1 && (y1-y) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            else if((x-x1) == 1 && (y-y1) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            else if((x1-x) == 1 && (y-y1) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            else if((x-x1) == 1 && (y1-y) == 1){
                wkx = x1;
                wky = y1;
                return true;
            }
            else{
                return false;
            }
        }
        else if (piece == "WQ"){//done
            if(x == x1 && y != y1){
                //cout<<"horizontal move"<<endl;
                if(y>y1){
                    swap(y, y1);
                }
                for(int i = y + 1; i<y1; i++ ){
                    if (spaces[x][i] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }
                }
                return true;
            }
            else if(x!=x1 && y == y1){
                //cout<<"vertical move"<<endl;
                if(x>x1){
                    swap(x, x1);
                }
                for(int i = x + 1; i<x1; i++ ){
                    if (spaces[i][y] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }
                }
                return true;
            }
            else if(x + y == x1 + y1){
                //cout<<"forward slash"<<endl;
                if(y>y1){
                    swap(y, y1);
                    swap(x, x1);
                }
                while (y+1<y1){
                    x--; 
                    y++;
                    if (spaces[x][y] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }   
                }
                return true;
            }
            else if(x - y == x1 - y1){
                //cout<<"backslash"<<endl;
                if(y>y1){
                    swap(y, y1);
                    swap(x, x1);
                }
                while (y+1<y1){
                    x++; 
                    y++;
                    if (spaces[x][y] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }   
                }
                return true;
            }
            
            else{
                return false;
            }
        }
        else if (piece == "BQ"){//done
            if(x == x1 && y != y1){
                //horizontal move"
                if(y>y1){
                    swap(y, y1);
                }
                for(int i = y + 1; i<y1; i++ ){
                    if (spaces[x][i] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }
                }
                return true;
            }
            else if(x!=x1 && y == y1){
                //vertical move
                if(x>x1){
                    swap(x, x1);
                }
                for(int i = x + 1; i<x1; i++ ){
                    if (spaces[i][y] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }
                }
                return true;
            }
            else if(x + y == x1 + y1){
                //cout<<"forward slash"<<endl;
                if(y>y1){
                    swap(y, y1);
                    swap(x, x1);
                }
                while (y+1<y1){
                    x--; 
                    y++;
                    if (spaces[x][y] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }   
                }
                return true;
            }
            else if(x - y == x1 - y1){
                // cout<<"backslash"<<endl;
                if(y>y1){
                    swap(y, y1);
                    swap(x, x1);
                }
                while (y+1<y1){
                    x++; 
                    y++;
                    if (spaces[x][y] != "  "){
                        if(!checktest) cout<< "PIECE BLOCKING YOUR MOVE"<< endl;
                        return false;
                    }   
                }
                return true;
            }
            
            else{
                return false;
            }
        }
        else if (piece == "WN"){//done
            if (abs(y - y1) == 2 && abs(x-x1) == 1){
                return true;
            } 
            else if(abs(y - y1) == 1 && abs(x-x1) == 2){
                return true;
            }
            else{
                return false;
            }
        }
        else if (piece == "BN"){//done
            if (abs(y - y1) == 2 && abs(x-x1) == 1){
                return true;
            } 
            else if(abs(y - y1) == 1 && abs(x-x1) == 2){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
}

bool iswhitechecked(){
    bool trigger = false;
    for(int startx = 0; startx<8; startx++){
        for(int starty = 0; starty<8; starty++){
            if( (spaces[startx][starty])[0] =='B'){
                if (move_checker(startx,starty,wkx,wky) == true){
                    if(!checktest) cout<< "WHITE KING UNDER CHECK"<<endl;
                    return true;
                }
                
            }
        }
    }
    return false;
}

bool isblackchecked(){
    bool trigger = false;
    for(int startx = 0; startx<8; startx++){
        for(int starty = 0; starty<8; starty++){
            if( (spaces[startx][starty])[0] =='B'){
                if (move_checker(startx,starty,bkx,bky) == true){
                    if(!checktest) cout<< "BLACK KING UNDER CHECK"<<endl;
                    return true;
                }
                
            }
        }
    }
    return false;
}

bool iswhitecheckmated(bool check){
    int count = 0;
    if (check == true){
        // one step up
        if (move_checker(wkx,wky, wkx-1, wky) == true){
            if (iswhitechecked() == false){
                return false;
            }
            else{
                count+=1;
            }
        }
        //up-right
        else if (move_checker(wkx,wky, wkx-1, wky+1) == true){
            if (iswhitechecked() == false){
                return false;
            }
            else{
                count+=1;
            }
        }
        //right
        else if (move_checker(wkx,wky, wkx, wky+1) == true){
            if (iswhitechecked() == false){
                return false;
            }
            else{
                count+=1;
            }
        }
        // right down
        else if (move_checker(wkx,wky, wkx+1, wky+1) == true){
            if (iswhitechecked() == false){
                return false;
            }
            else{
                count+=1;
            }
        }
        //down
        else if (move_checker(wkx,wky, wkx+1, wky) == true){
            if (iswhitechecked() == false){
                return false;
            }
            else{
                count+=1;
            }
        }
        //left-down
        else if (move_checker(wkx,wky, wkx+1, wky-1) == true){
            if (iswhitechecked() == false){
                return false;
            }
            else{
                count+=1;
            }
        }
        //left
        else if (move_checker(wkx,wky, wkx, wky-1) == true){
            if (iswhitechecked() == false){
                return false;
            }
            else{
                count+=1;
            }
        }
        //up-left
        else if (move_checker(wkx,wky, wkx-1, wky-1) == true){
            if (iswhitechecked() == false){
                return false;
            }
            else{
                count+=1;
                if (count == 8){
                    return true;
                }
            }
        }
        else{
            return true;
        }
    }
    else{
        return false;
    }
}

void move(){
    int row, col, row1, col1;
    while(1){
        cout<< "What spot do you want to move a piece from (letter then number): ";
        string spot;
        cin>>spot;
        col = let_to_num(spot[0]);
        row = spot[1] - 48;
        row = 8 - row;
        if(row > 7 || row <0 || col<0 || col > 7){
            cout<<"WRONG ENTRY! TRY AGAIN!"<<endl;
        }
        else{
            break;
        }
    }
    
    while(1){
        cout<< "What spot do you want to move the piece to (letter then number): ";
        string spot1;
        cin>>spot1;
        col1 = let_to_num(spot1[0]);
        row1 = spot1[1] - 48;
        row1 = 8 - row1;
        if(row1 > 7 || row1 <0 || col1<0 || col1 > 7){
                cout<<"WRONG ENTRY! TRY AGAIN!"<<endl;
            }
            else{
                break;
            }
    }
    if (row == row1 && col == col1){
        cout<< "Piece will not be moved, make another move";
    }
    else{
        if (move_checker(row, col, row1, col1) == true){
            cout<< "piece moved"<<endl;
            spaces[row1][col1] = spaces[row][col];
            spaces[row][col] = "  ";
        }
        else{cout<< "Move not valid, piece not moved"<<endl;}
    }
    
    
}
int main(){
    char c;
    cout<< "White(w) or Black(b): ";
    cin>>c;
    display_board(c, spaces);
    cout<<endl;
    while(1){
        move(); 
        display_board(c, spaces);     
        checktest = true;
        if(iswhitecheckmated(iswhitechecked())){
            cout<<endl<<"################################"<<endl<<"    CHECKMATE! BLACK WINS      "<<endl<<"################################"<<endl;
            break;
        }
        else{
            cout<<"No checkmate"<<endl;
        }
        checktest = false;
        cout<<endl;
        // check = isblackchecked();
        // isblackchecked(check);
    }
    return 0;
}