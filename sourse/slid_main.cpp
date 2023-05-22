#include <iostream>
#include <vector>
#include <fstream>

//i=y,j=x注意

std::string move_string;   //交換操作（提出）
int change_non = 0;    //交換回数（提出）
int move_x = 1000, move_y = 1000;   //choose_yの移動先の復元座標
bool jude = 0;  //判定用変数。いろいろ使ってる

int my_do(int choose_x, int choose_y, std::vector<std::vector<int>>& X, std::vector<std::vector<int>>& Y) {
	move_x = X[choose_y + 1][choose_x], move_y = Y[choose_y + 1][choose_x];
	X[choose_y + 1][choose_x] = X[choose_y][choose_x], Y[choose_y + 1][choose_x] = Y[choose_y][choose_x];	//move_x,yにchoose_y,yが重なった
	X[choose_y][choose_x] = move_x, Y[choose_y][choose_x] = move_y;
	choose_y++;
	change_non++;
	move_string.push_back('D');
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
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
	X[choose_y - 1][choose_x] = X[choose_y][choose_x], Y[choose_y - 1][choose_x] = Y[choose_y][choose_x];	//move_x,yにchoose_y,yが重なった
	X[choose_y][choose_x] = move_x, Y[choose_y][choose_x] = move_y;
	choose_y--;
	change_non++;
	move_string.push_back('U');
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
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
	X[choose_y][choose_x - 1] = X[choose_y][choose_x], Y[choose_y][choose_x - 1] = Y[choose_y][choose_x];	//move_x,yにchoose_y,yが重なった
	X[choose_y][choose_x] = move_x, Y[choose_y][choose_x] = move_y;
	choose_x--;
	change_non++;
	move_string.push_back('L');
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
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
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
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
    //std::ifstream problem("C:\\Users\\proken\\source\\repos\\slide\\Debug\\problem.txt");
    //std::ifstream problem("C:\\Users\\jun\\souse\\input.txt");
    int W, H;   //要素時は-1忘れずに
    std::cin >> std::hex >> W >> H;
    std::vector<std::vector<int>> X(W, std::vector<int>(H));
	std::vector<std::vector<int>> Y(W, std::vector<int>(H));
    std::vector<std::vector<int>> Z_dec(W, std::vector<int>(H));  //16進数を10進数にするためのクッション変数

    for(int i = 0; i < W; i++){
        for(int j = 0; j < H; j++){
            std::cin >> std::hex >> Z_dec[i][j];
            //problem >> std::hex >> Z_dec[i][j];
        }
    }

    for(int i = 0; i < W; i++){
        for(int j = 0; j < H; j++){
            X[i][j] = Z_dec[i][j] / 16;
            Y[i][j] = Z_dec[i][j] % 16;
        }
    }

    //cin終了

    int choose_non_x = 1000, choose_non_y = 1000;   //選択画像の選択時の位置（提出）
    int first_x = 1000, first_y = 1000;     //今直したい画像の現在地。なお、移動中は変更する必要ないので変更なし。
    int choose_y = 1000, choose_x = 1000;   //選択画像の現在地
    int next_x = 0, next_y = 0;   //今から直す行、列
    int distan_x = 1000, distan_y = 1000;   //choose-firstを入れる。chooseがfirstに行くための距離。chooseの右下に着くようにする。できない位置の場合はfristをどかす
    int need_x = 1000, need_y = 1000;   //firstが移動するための距離。first-next。

    //choose探索開始
    for(int i = 0; i < W; i++){
        for(int j = 0; j < H; j++){
            if(X[j][i] == W-1 && Y[j][i] == H-1){
                choose_x = i;
                choose_y = j;
                choose_non_x = i, choose_non_y = j;
            }
        }
    }
        //choose探索終了
    for(int k = 0; k < (H-3)*W; k++){
        //first探索開始
        for(int i = 0; i < W; i++){
            for(int j = 0; j < H; j++){
                if(X[j][i] == next_x && Y[j][i] == next_y){
                    first_x = i;
                    first_y = j;
                }
            }
        }
        //端の車庫入れその１
        if(next_x == W-2){
            for(int i = 0; i < W; i++){
                for(int j = 0; j < H; j++){
                    if(X[j][i] == next_x+1 && Y[j][i] == next_y){
                        first_x = i;
                        first_y = j;
                    }
                }
            }
        }

        //車庫入れその２
        if(next_x == W-1){
            for(int i = 0; i < W; i++){
                for(int j = 0; j < H; j++){
                    if(X[j][i] == next_x-1 && Y[j][i] == next_y){
                        first_x = i;
                        first_y = j;
                    }
                }
            }
        }
        //first探索終了

        //choose移動開始
        distan_x = choose_x-first_x, distan_y = choose_y-first_y;

        //chooseがx移動でfirstを動かしちゃう時
        if(first_y == choose_y){
            if(distan_x < 0){
                distan_x++;
                first_x--;
            }
        }
        //終了

        //firstが右端の時
        if(first_x == W-1){
            distan_x++;
            //firstがy移動でchooseを動かしちゃうので
            if(distan_y < 0){
                distan_y++;
                first_y--;
            }
        }
        //終了

        //firstが下端の時
        if(first_y == H-1){
            distan_y++;
        }
        //終了
        std::cout << "distan_x=" << distan_x << " " << "distan_y=" << distan_y << std::endl;

        if(distan_x <= 0){
            for(int i = 0; i < abs(distan_x); i++){
                choose_x = my_ri(choose_x, choose_y, X, Y);
            }
            choose_x = my_ri(choose_x, choose_y, X, Y);
        }
        else{
            for(int i = 1; i < distan_x; i++){
                choose_x = my_le(choose_x, choose_y, X, Y);
            }
        }

        if(distan_y <= 0){
            for(int i = 0; i < abs(distan_y); i++){
                choose_y =  my_do(choose_x, choose_y, X, Y);
            }
            choose_y = my_do(choose_x, choose_y, X, Y);
        }
        else if(distan_y > 0){
            for(int i = 1; i < distan_y; i++){
                choose_y = my_up(choose_x, choose_y, X, Y);
            }
        }

        if(first_x == W-1 && first_y == H-1){
                    jude = 1;
        }

        //firstが右端の時
        if(first_x == W-1){
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            first_x--;
        }

        //firstが下端の時
        if(first_y == H-1){
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            first_y--;
            std::cout << 234 << std::endl;
        }

        if(jude == 1){
            choose_y = my_do(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_ri(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
            first_x--;
            first_y--;
        }

        jude = 0;

        //終了ｘ２

        //choose移動完了
        std::cout << "first_x=" << first_x << " first_y=" << first_y << " next_x=" << next_x << " next_y=" << next_y << std::endl;
        need_x = first_x - next_x, need_y = first_y - next_y;

        //車庫入れ
        if(next_x == W-1 && need_x > 0){
            need_x--;
            need_y--;   //なんでだろうね
        }
        else if(next_x == W-1 && need_x < 0){
            need_x++;
            need_y--;   //なんでだろうね
            std::cout << 250 << std::endl;
        }

        std::cout << "need_x=" << need_x << " need_y=" << need_y << std::endl;

        //first移動開始
        if(need_x > 0){
            for(int i = 0; i < need_x; i++){
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_y = my_up(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
                choose_y = my_do(choose_x, choose_y, X, Y);
            }
        }
        else if(need_x < 0){
            for(int i = 0; i < abs(need_x); i++){
                choose_y = my_up(choose_x, choose_y, X, Y);
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_y = my_do(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
            }
        }

        if(need_y > 0){
            for(int i = 0; i < need_y; i++){
                choose_y = my_up(choose_x, choose_y, X, Y);
                choose_y = my_up(choose_x, choose_y, X, Y);
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_y = my_do(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
            }
        }
        else if(need_y < 0){
            for(int i = 0; i < need_y; i++){
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_y = my_up(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
                choose_y = my_do(choose_x, choose_y, X, Y);
                choose_y = my_do(choose_x, choose_y, X, Y);
            }
        }

        std::cout << 294 << std::endl;

        //車庫入れ
        if(next_x == W-1){
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_y = my_up(choose_x, choose_y, X, Y);
            choose_x = my_le(choose_x, choose_y, X, Y);
            choose_y = my_do(choose_x, choose_y, X, Y);
        }
        //first移動完了

        if(next_x < W-1){
            next_x++;
        }
        else if(next_x == W-1){
            next_x = 0;
            next_y++;
        }
        std::cout << "next_x=" << next_x << " next_y=" << next_y << std::endl;
    }



    for(int i = 0; i < W; i++){
        for(int j = 0; j < H; j++){
            std::cout << X[i][j];
            std::cout << Y[i][j];
            std::cout << ' ';
        }
        std::cout << std::endl;
    }












































































    std::cout << "3linehgahgahgahgahgahgalkjhgaearhtiuqahgfoehgfiehgifhevdsanfsjbfcw73t48o32qtrxgdq7hntfocwnyercr,jfkngwbcw66dryowfcsbtdykued7kxsz3welfa" << std::endl;
    //縦がラスト3列になった
    for(int i = 0; i < 3/*(W-3)*3*/; i++){
        for(int j = H-3; j < H; j++){
            std::cout << "next_x=" << next_x << " next_y=" << next_y << std::endl;
            if(next_y == H-3){
                //first探索開始
                std::cout << 425 << std::endl;
                for(int i = 0; i < W; i++){
                    for(int j = 0; j < H; j++){
                        if(X[j][i] == next_x && Y[j][i] == next_y){
                            first_x = i;
                            first_y = j;
                        }
                    }
                }
                std::cout << "first_x=" << first_x << " first_y=" << first_y << std::endl;
                //first探索終了

                //choose移動開始
                distan_x = choose_x-first_x, distan_y = choose_y-first_y;
                std::cout << "distan_x=" << distan_x << " distan_y=" << distan_y << std::endl;
                //chooseがx移動でfirstを動かしちゃう時
                if(first_y == choose_y){
                    if(distan_x < 0){
                        distan_x++;
                        first_x--;
                        std::cout << 445 << std::endl;
                    }
                }
                //終了

                //firstが右端の時
                if(first_x == W-1){
                    distan_x++;
                    //firstがy移動でchooseを動かしちゃうので
                    if(distan_y < 0){
                        distan_y++;
                        first_y--;
                        std::cout << 457 << std::endl;
                    }
                }
                //終了
                //firstが下端の時
                if(first_y == H-1 && jude == 0){
                    distan_y++;
                    std::cout << 464<< std::endl;
                }
                //終了

                std::cout << "distan_x=" << distan_x << " distan_y=" << distan_y << std::endl;
                if(distan_x <= 0){
                    std::cout << 450 << std::endl;
                    for(int i = -1; i < distan_x*-1; i++){
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                        }
                }
                else if(distan_x > 0){
                    std::cout << 456 << std::endl;
                    for(int i = 1; i < distan_x; i++){
                        choose_x = my_le(choose_x, choose_y, X, Y);
                    }
                }

                if(distan_y <= 0){
                    std::cout << 483 << std::endl;
                    for(int i = -1; i < abs(distan_y); i++){
                        choose_y = my_do(choose_x, choose_y, X, Y);
                    }
                }
                else if(distan_y > 0){
                    std::cout << 469 << std::endl;
                    for(int i = 1; i < distan_y; i++){
                        choose_y = my_up(choose_x, choose_y, X, Y);
                    }
                }

                if(first_x == W-1 && first_y == H-1){
                    jude = 1;
                }

                //firstが右端の時
                if(first_x == W-1 && jude == 0){
                    choose_x = my_le(choose_x, choose_y, X, Y);
                    choose_y = my_up(choose_x, choose_y, X, Y);
                    choose_x = my_ri(choose_x, choose_y, X, Y);
                    choose_y = my_do(choose_x, choose_y, X, Y);
                    first_x--;
                    std::cout << 506 << std::endl;
                }

                //firstが下端の時
                if(first_y == H-1 && jude == 0){
                    choose_y = my_up(choose_x, choose_y, X, Y);
                    choose_x = my_le(choose_x, choose_y, X, Y);
                    choose_y = my_do(choose_x, choose_y, X, Y);
                    choose_x = my_ri(choose_x, choose_y, X, Y);
                    first_y--;
                    std::cout << 516 << std::endl;
                }

                if(jude == 1){
                    choose_y = my_do(choose_x, choose_y, X, Y);
                    choose_x = my_le(choose_x, choose_y, X, Y);
                    choose_y = my_up(choose_x, choose_y, X, Y);
                    choose_x = my_ri(choose_x, choose_y, X, Y);
                    choose_y = my_do(choose_x, choose_y, X, Y);
                    first_x--;
                    first_y--;
                }

                jude = 0;

                //終了ｘ２
                std::cout << "choose_x=" << choose_x << " choose_y=" << choose_y << " first_x=" << first_x << " first_y=" << first_y << std::endl;
                //choose移動完了
                need_x = first_x - next_x, need_y = first_y - next_y;
                std::cout << "need_x=" << need_x << " need_y=" << need_y << std::endl;
                //first移動開始(
                if(need_x > 0){
                    for(int i = 0; i < need_x; i++){
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                    }
                }
                else if(need_x < 0){
                    for(int i = 0; i < need_x; i++){
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                    }
                }

                if(need_y > 0){
                    for(int i = 0; i < need_y; i++){
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                    }
                }
                else if(need_y < 0){
                    for(int i = 0; i < need_y; i++){
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                    }
                }
                //first移動完了
            }








            else if(next_y == H-2){
                //first探索開始
                std::cout << 586 << std::endl;
                for(int i = 0; i < W; i++){
                    for(int j = 0; j < H; j++){
                        if(X[j][i] == next_x && Y[j][i] == next_y+1){
                            first_x = i;
                            first_y = j;
                        }
                    }
                }
                std::cout << "first_x=" << first_x << " first_y=" << first_y << std::endl;
                //first探索終了

                //choose移動開始
                distan_x = choose_x-first_x, distan_y = choose_y-first_y;
                std::cout << "distan_x=" << distan_x << " distan_y=" << distan_y << std::endl;

                //chooseがx移動でfirstを動かしちゃう時
                if(first_y == choose_y){
                    if(distan_x < 0){
                        distan_x++;
                        first_x--;
                        std::cout << 571 << std::endl;
                    }
                }
                //終了

                //firstが右端の時
                if(first_x == W-1){
                    distan_x++;
                    //firstがy移動でchooseを動かしちゃうので
                    if(distan_y < 0){
                        distan_y++;
                        jude = 1;
                        std::cout << 585 << std::endl;
                    }
                }
                //終了
                //firstが下端の時
                /*if(first_y == H-1 && jude == 0){
                    distan_y++;
                    std::cout << 626 << std::endl;
                }*/     //保留
                jude = 0;
                //終了

                std::cout << "distan_x=" << distan_x << " distan_y=" << distan_y << std::endl;
                if(distan_x <= 0){
                    std::cout << 599 << std::endl;
                    for(int i = -1; i < abs(distan_x); i++){
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                        }
                }
                else if(distan_x > 0){
                    std::cout << 639 << std::endl;
                    for(int i = 1; i < distan_x; i++){
                        choose_x = my_le(choose_x, choose_y, X, Y);
                    }
                }

                if(distan_y <= 0){
                    std::cout << 612 << std::endl;
                    for(int i = 0; i < abs(distan_y); i++){
                        choose_y = my_do(choose_x, choose_y, X, Y);
                    }
                }
                else if(distan_y > 0){
                    std::cout << 615 << std::endl;
                    for(int i = 1; i < distan_y; i++){
                        choose_y = my_up(choose_x, choose_y, X, Y);
                    }
                }

                if(first_x == W-1 && first_y == H-1){
                    jude = 1;
                }

                //firstが右端の時
                if(first_x == W-1 && jude == 0){
                    choose_x = my_le(choose_x, choose_y, X, Y);
                    choose_y = my_up(choose_x, choose_y, X, Y);
                    choose_x = my_ri(choose_x, choose_y, X, Y);
                    choose_y = my_do(choose_x, choose_y, X, Y);
                    first_x--;
                    std::cout << 697 << std::endl;
                }

                //firstが下端の時
                if(first_y == H-1 && jude == 0){
                    choose_y = my_up(choose_x, choose_y, X, Y);
                    choose_x = my_le(choose_x, choose_y, X, Y);
                    choose_y = my_do(choose_x, choose_y, X, Y);
                    choose_x = my_ri(choose_x, choose_y, X, Y);
                    first_y--;
                    std::cout << 641 << std::endl;
                }

                if(jude == 1){
                    choose_y = my_do(choose_x, choose_y, X, Y);
                    choose_x = my_le(choose_x, choose_y, X, Y);
                    choose_y = my_up(choose_x, choose_y, X, Y);
                    choose_x = my_ri(choose_x, choose_y, X, Y);
                    choose_y = my_do(choose_x, choose_y, X, Y);
                    first_x--;
                    first_y--;
                }

                jude = 0;

                //終了ｘ２
                std::cout << "choose_x=" << choose_x << " choose_y=" << choose_y << " first_x=" << first_x << " first_y=" << first_y << std::endl;
                //choose移動完了
                need_x = first_x - next_x, need_y = first_y - next_y;
                std::cout << "need_x=" << need_x << " need_y=" << need_y << std::endl;

                //first移動開始
                if(need_y > 0){
                    for(int i = 0; i < need_y; i++){
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                    }
                }
                else if(need_y < 0){
                    for(int i = 0; i < abs(need_y); i++){
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                    }
                }
                if(need_x > 0){
                    for(int i = 0; i < need_x; i++){
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                    }
                }
                else if(need_x < 0){
                    for(int i = 0; i < need_x; i++){
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                    }
                }
                //first移動完了
            }
            //終了







            else if(next_y == H-1){
                //first探索開始
                std::cout << 749 << std::endl;
                for(int i = 0; i < W; i++){
                    for(int j = 0; j < H; j++){
                        if(X[j][i] == next_x && Y[j][i] == next_y-1){
                            first_x = i;
                            first_y = j;
                        }
                    }
                }
                std::cout << "first_x=" << first_x << " first_y=" << first_y << std::endl;
                //first探索終了

                //choose移動開始
                distan_x = choose_x-first_x, distan_y = choose_y-first_y;
                std::cout << "distan_x=" << distan_x << " distan_y=" << distan_y << std::endl;
                //chooseがx移動でfirstを動かしちゃう時
                if(first_y == choose_y){
                    if(distan_x < 0){
                        distan_x++;
                        first_x--;
                        std::cout << 424 << std::endl;
                    }
                }
                //終了

                //firstが右端の時
                if(first_x == W-1 && jude == 0){
                    distan_x++;
                    //firstがy移動でchooseを動かしちゃうので
                    if(distan_y < 0){
                        distan_y++;
                        first_y--;
                        std::cout << 781 << std::endl;
                    }
                }
                //終了
                //firstが下端の時
                if(first_y == H-1 && jude == 0){
                    distan_y++;
                    std::cout << 788 << std::endl;
                }

                std::cout << "distan_x=" << distan_x << " distan_y=" << distan_y << std::endl;
                if(distan_x <= 0){
                    std::cout << 794 << std::endl;
                    for(int i = -1; i < distan_x*-1; i++){
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                        }
                }
                else if(distan_x > 0){
                    std::cout << 800 << std::endl;
                    for(int i = 1; i < distan_x; i++){
                        choose_x = my_le(choose_x, choose_y, X, Y);
                    }
                }

                if(distan_y <= 0){
                    std::cout << 463 << std::endl;
                    for(int i = -1; i < abs(distan_y); i++){
                        choose_y = my_do(choose_x, choose_y, X, Y);
                    }
                }
                else if(distan_y > 0){
                    std::cout << 813 << std::endl;
                    for(int i = 1; i < distan_y; i++){
                        choose_y = my_up(choose_x, choose_y, X, Y);
                    }
                }

                if(first_x == W-1 && first_y == H-1){
                    jude = 1;
                }

                //firstが右端の時
                if(first_x == W-1 && jude == 0){
                    choose_x = my_le(choose_x, choose_y, X, Y);
                    choose_y = my_up(choose_x, choose_y, X, Y);
                    choose_x = my_ri(choose_x, choose_y, X, Y);
                    choose_y = my_do(choose_x, choose_y, X, Y);
                    first_x--;
                    std::cout << 477 << std::endl;
                }

                //firstが下端の時
                if(first_y == H-1 && jude == 0){
                    choose_y = my_up(choose_x, choose_y, X, Y);
                    choose_x = my_le(choose_x, choose_y, X, Y);
                    choose_y = my_do(choose_x, choose_y, X, Y);
                    choose_x = my_ri(choose_x, choose_y, X, Y);
                    first_y--;
                    std::cout << 487 << std::endl;
                }

                if(jude == 1){
                    choose_y = my_do(choose_x, choose_y, X, Y);
                    choose_x = my_le(choose_x, choose_y, X, Y);
                    choose_y = my_up(choose_x, choose_y, X, Y);
                    choose_x = my_ri(choose_x, choose_y, X, Y);
                    choose_y = my_do(choose_x, choose_y, X, Y);
                    first_x--;
                    first_y--;
                }

                jude = 0;

                //終了ｘ２
                std::cout << "choose_x=" << choose_x << " choose_y=" << choose_y << " first_x=" << first_x << " first_y=" << first_y << std::endl;
                //choose移動完了
                need_x = first_x - next_x-1, need_y = first_y - next_y+1;   //移動させたいところはnextの右上なので
                std::cout << "need_x=" << need_x << " need_y=" << need_y << std::endl;
                //first移動開始(
                if(need_x > 0){
                    for(int i = 0; i < need_x; i++){
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                    }
                }
                else if(need_x < 0){
                    for(int i = 0; i < need_x; i++){
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                    }
                }

                if(need_y > 0){
                    for(int i = 0; i < need_y; i++){
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                    }
                }
                else if(need_y < 0){
                    for(int i = 0; i < abs(need_y); i++){
                        choose_x = my_le(choose_x, choose_y, X, Y);
                        choose_y = my_up(choose_x, choose_y, X, Y);
                        choose_x = my_ri(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                        choose_y = my_do(choose_x, choose_y, X, Y);
                    }
                }
                //first移動完了
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_x = my_le(choose_x, choose_y, X, Y);
                choose_y = my_up(choose_x, choose_y, X, Y);
                choose_x = my_ri(choose_x, choose_y, X, Y);
            }
            //終了

            if(next_y < H-1){
                next_y++;
            }
            else if(next_y == H-1){
                next_y = H-3;
                next_x++;
            }
        }
    }




	std::cout << std::dec << 1 << std::endl;
	std::cout << std::dec << choose_non_x << choose_non_y << std::endl;
	std::cout << std::dec << change_non << std::endl;
	std::cout << std::dec << move_string << std::endl;


    for(int i = 0; i < W; i++){
        for(int j = 0; j < H; j++){
            std::cout << X[i][j];
            std::cout << Y[i][j];
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}