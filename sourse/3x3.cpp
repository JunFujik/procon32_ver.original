#include <iostream>
#include <vector>
std::string move_string;   //交換操作（提出）
int change_non = 0;    //交換回数（提出）
int move_x, move_y;

int my_do(int choose_x, int choose_y, std::vector<std::vector<int>>& X, std::vector<std::vector<int>>& Y) {
move_x = X[choose_y + 1][choose_x], move_y = Y[choose_y + 1][choose_x];
X[choose_y + 1][choose_x] = X[choose_y][choose_x], Y[choose_y + 1][choose_x] = Y[choose_y][choose_x]; //move_x,yにchoose_y,yが重なった
X[choose_y][choose_x] = move_x, Y[choose_y][choose_x] = move_y;
choose_y++;
change_non++;
move_string.push_back('D');
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << X[i][j];
            std::cout << Y[i][j];
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
return choose_y;
}
int my_up(int choose_x, int choose_y, std::vector<std::vector<int>>& X, std::vector<std::vector<int>>& Y) {
move_x = X[choose_y - 1][choose_x], move_y = Y[choose_y - 1][choose_x];
X[choose_y - 1][choose_x] = X[choose_y][choose_x], Y[choose_y - 1][choose_x] = Y[choose_y][choose_x]; //move_x,yにchoose_y,yが重なった
X[choose_y][choose_x] = move_x, Y[choose_y][choose_x] = move_y;
choose_y--;
change_non++;
move_string.push_back('U');
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << X[i][j];
            std::cout << Y[i][j];
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
return choose_y;
}
int my_le(int choose_x, int choose_y, std::vector<std::vector<int>>& X, std::vector<std::vector<int>>& Y) {
move_x = X[choose_y][choose_x - 1], move_y = Y[choose_y][choose_x - 1];
X[choose_y][choose_x - 1] = X[choose_y][choose_x], Y[choose_y][choose_x - 1] = Y[choose_y][choose_x]; //move_x,yにchoose_y,yが重なった
X[choose_y][choose_x] = move_x, Y[choose_y][choose_x] = move_y;
choose_x--;
change_non++;
move_string.push_back('L');
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << X[i][j];
            std::cout << Y[i][j];
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
return choose_x;
}

int my_ri(int choose_x, int choose_y, std::vector<std::vector<int>>& X, std::vector<std::vector<int>>& Y) {
move_x = X[choose_y][choose_x + 1], move_y = Y[choose_y][choose_x + 1];
X[choose_y][choose_x + 1] = X[choose_y][choose_x], Y[choose_y][choose_x + 1] = Y[choose_y][choose_x];//move_x,yにchoose_y,yが重なった
X[choose_y][choose_x] = move_x, Y[choose_y][choose_x] = move_y;
choose_x++;
change_non++;
move_string.push_back('R');
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << X[i][j];
            std::cout << Y[i][j];
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
return choose_x;
}
int main(){
   

    int W, H;//Wはx座標、Hはy座標
    std::cin >> W >> H;
    std::vector<std::vector<int>> X(W, std::vector<int>(H));//パズルピースのx座標
    std::vector<std::vector<int>> Y(W, std::vector<int>(H));//パズルピースのy座標
    std::vector<std::vector<int>> Z(W, std::vector<int>(H));//入力されるパズルピースのx座標、y座標
    int choose_x = 1000;//選択画像の現在のx座標(復元画像の右下端)
    int choose_y = 1000;//選択画像の現在のy座標(復元画像の右下端)
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            std::cin >> Z[i][j];
        }
    }
    for(int i = 0; i < H; i++){//座標数列Zを座標数列Xと座標数列Yの成分に分ける
        for(int j = 0; j < W; j++){
            X[i][j] = Z[i][j] / 10;     //XとY、上下逆になってました FJ
            Y[i][j] = Z[i][j] % 10;
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j= 0; j< 3;j++){
            if(X[H-3+j][W-3+i] == W-1 && Y[H-3+j][W-3+i] == H-1){
                choose_x = i; choose_y = j;
            }
        }
    }
//入力終了
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << X[i][j];
            std::cout << Y[i][j];
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for(int i = 0; i < H; i++){//実行する前の座標の状態を出力
        for(int j = 0; j < W; j++){
            std::cout << X[i][j] << Y[i][j] <<" ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << choose_x << " " << choose_y << std::endl;      //復元画像の右下端の座標の位置
    std::cout << X[choose_y][choose_x] << " " << Y[choose_y][choose_x] << std::endl; //選択画像の中身(2 2なら成功)の確認
//入力終了の確認
//＊以下コメントの「基本状態」の意味を「x,yの選択画像が右下端にある状態」と定義する。
    
    for(int i = 0; i < (W-1) - choose_x; i++){//x座標の選択画像を右下端に移動　i < を2からw-1にしたお FJ
        choose_x = my_ri(choose_x, choose_y, X, Y);
    }
    for(int j = 0; j < (H-1) - choose_y; j++){//y座標の選択画像を右下端に移動　i < を2からH-1にしました FJ
        choose_y = my_do(choose_x, choose_y, X, Y);
    }
    
    for(int i = 0; i < H; i++){//基本状態の確認
        for(int j = 0; j < W; j++){
            std::cout << X[i][j] << Y[i][j] <<  " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
//以下移動開始

    std::cout << "process1" << std::endl;
    int count = 1;   //左上に00を移動
    while(!(X[H-3][W-3] == W-3 && Y[H-3][W-3] == H-3)){
        choose_x = my_le(choose_x, choose_y, X, Y);
        choose_x = my_le(choose_x, choose_y, X, Y);
        choose_y = my_up(choose_x, choose_y, X, Y);
        choose_y = my_up(choose_x, choose_y, X, Y);
        choose_x = my_ri(choose_x, choose_y, X, Y);
        choose_x = my_ri(choose_x, choose_y, X, Y);
        choose_y = my_do(choose_x, choose_y, X, Y);
        choose_y = my_do(choose_x, choose_y, X, Y);
        count++;
        if(count == 8){
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            break;
        }
    }
    for(int i = 0; i < H; i++){//基本状態の確認
        for(int j = 0; j < W; j++){
            std::cout << X[i][j] << Y[i][j] <<  " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    //ここまでは完了
    std::cout << "process2" << std::endl;
    count = 0;
    while(!((Y[H-3][W-2] == H-3 && X[H-3][W-2] == W-2) && (Y[H-3][W-1] == H-3 && X[H-3][W-1] == W-1))){     //条件成功   ……してないやないか！ FJ 元:while(!((Y[H-3][W-2] == W-3 && X[H-3][W-2] == H-2) && (Y[H-3][W-1] == W-3 && X[H-3][W-1] == H-1))){
        if(Y[H-3][W-2] != H-3 && X[H-3][W-2] != W-1){    //if(!(Y[H-3][W-2] == W-3 && X[H-3][W-2] == H-3)){ でした FJ
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            //choose_x = my_le(choose_x, choose_y, X, Y); FJ
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
        }
        else if(Y[H-2][W-2] != 0/*H-3*/ && X[H-2][W-2] != 1/*W-2*/){   //if(Y[H-3][W-2] == W-3 && X[H-3][W-2] == H-1){ でしたFJ
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);std::cout << X[H-2][W-2] << Y[H-2][W-2] << std::endl;
            count++;
            /*if(Y[H-3][W-1] == W-2 && X[H-3][W-1] == H-1){
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_y = my_up(choose_x, choose_y, X, Y);
                choose_y = my_up(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
                choose_y = my_do(choose_x, choose_y, X, Y);
                choose_y = my_do(choose_x, choose_y, X, Y);
            }*/ //FJ
        }
        else{   //if(count == 6) でしあ FJ
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            /*choose_y = my_up(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);*/   //いらなかったお FJ
            std::cout << "count6" << std::endl;
            break;
        }
    }
    for(int i = 0; i < H; i++){//基本状態の確認
        for(int j = 0; j < W; j++){
            std::cout << X[i][j] << Y[i][j] <<  " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    /*
    count=0;
    while(!(X[H-3][W-2] == W-2 && Y[H-3][W-2] == H-3 && X[H-1][W-3] == W-3 && Y[H-1][W-3] == H-1)){
        if(!(X[H-3][W-2] == W-2 && Y[H-3][W-2] == H-3)){
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            count++;
            if(count == 4){
                choose_y = my_up(choose_x, choose_y, X, Y);
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_y = my_do(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
                choose_y = my_up(choose_x, choose_y, X, Y);
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_y = my_do(choose_x, choose_y, X, Y);
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_y = my_up(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
                choose_y = my_do(choose_x, choose_y, X, Y);
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_y = my_up(choose_x, choose_y, X, Y);
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_y = my_do(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
            }
        }
        choose_x = my_le(choose_x, choose_y, X, Y);
        choose_x = my_le(choose_x, choose_y, X, Y);
        choose_y = my_up(choose_x, choose_y, X, Y);
        choose_x = my_ri(choose_x, choose_y, X, Y);
        choose_x = my_ri(choose_x, choose_y, X, Y);
        choose_y = my_do(choose_x, choose_y, X, Y);
    }
    while(!(X[H-2][W-2] == W-2 && Y[H-2][W-2] == H-2 && X[H-1][W-2] == W-2 && Y[H-1][W-2] == H-1 && X[W-1][H-1] == W-1 && Y[W-1][H-1] == 1)){
        choose_x = my_le(choose_x, choose_y, X, Y);
        choose_y = my_up(choose_x, choose_y, X, Y);
        choose_y = my_ri(choose_x, choose_y, X, Y);
        choose_y = my_do(choose_x, choose_y, X, Y);
    }

    choose_non_x = ;
    choose_non_y = ;
    std::cout << std::dec << 1 << std::endl;
    std::cout << std::dec << choose_non_x << choose_non_y << std::endl;
    std::cout << std::dec << change_non << std::endl;
    std::cout << std::dec << move_string << std::endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << X[H-3+i][W-3+j] <<  " " ;
            if(j % 3 == 0)std::cout << std::endl;
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << Y[W-3+i][W-3+j] <<  " " ;
           if(j % 3 == 0)std::cout << std::endl;
        }
    }*/
}
