//
//  main.cpp
//  suudoku
//
//  Created by 野原将人 on 2019/03/22.
//  Copyright © 2019 野原将人. All rights reserved.
//

#include <stdio.h>

//簡単（候補を絞っていくだけで解けた）
int suudoku[9][9] = {
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,2,7},
    {4,0,0,6,0,8,0,0,0},
    {0,7,1,0,0,0,3,0,0},
    {2,3,8,5,0,6,4,1,9},
    {9,6,4,1,0,0,7,5,0},
    {3,9,5,0,2,7,8,0,0},
    {1,8,2,0,6,0,9,7,4},
    {0,4,6,8,1,9,2,0,5}
    };

//最高難度
//int suudoku[9][9] = {
//    {0,3,0,0,9,0,0,1,0},
//    {1,0,9,0,8,0,0,0,6},
//    {6,0,0,7,0,0,0,0,0},
//    {0,0,1,0,0,0,8,0,0},
//    {2,0,6,0,0,8,0,0,0},
//    {0,0,0,0,0,3,0,4,0},
//    {0,0,7,6,0,1,0,0,8},
//    {0,0,2,0,0,0,0,3,4},
//    {0,0,0,0,0,0,9,0,0}
//    };


int kouho[9][9][9]; //i j kとすると、i jのますの候補としてありえない数字に１を立てる

void print_suudoku(){
    for(int i=0;i <= 8; i++){
        for(int j=0;j <= 8; j++){
            printf("%d ",suudoku[i][j]);
            if (j % 3 == 2){
                printf("| ");
            }
        }
        if (i % 3 == 2){
            printf("\n-----------------------");
        }
        printf("\n");
    }
}

void print_kouho(){
    for(int i=0;i <= 8; i++){
        for(int j=0;j <= 8; j++){
            for(int k=0;k <= 8; k++){
                printf("%d",kouho[i][j][k]);
            }
            printf("\n");
        }
    }
}

void find_kouho(){
    for(int i=0;i <= 8; i++){
        for(int j=0;j <= 8; j++){
            if (suudoku[i][j] == 0){
//                縦と横のの情報から候補を絞る
                for (int k=0;k <= 8; k++){
                    if (suudoku[i][k] != 0){
                        kouho[i][j][suudoku[i][k] - 1] = 1;
                    }
                    if (suudoku[k][j] != 0){
                        kouho[i][j][suudoku[k][j] - 1] = 1;
                    }
                }

                //ボックスの情報から候補を絞る
                int kizyunn_x = (i / 3)*3;
                int kizyunn_y = (j / 3)*3;
                for (int k=0;k <= 2; k++){
                    for(int l=0;l<=2;l++){
                        if (suudoku[kizyunn_x + k][kizyunn_y + l] != 0){
                            kouho[i][j][suudoku[kizyunn_x + k][kizyunn_y + l] - 1] = 1;
                        }
                    }
                }
                
                // 候補が一個に絞られればsuudokuの配列の値を更新する
                int num = 0;
                for (int k=0;k <= 8; k++){
                    if(kouho[i][j][k] == 0){
                        suudoku[i][j] = k + 1;
                        num += 1;
                    }
                    if (num >= 2){
                        suudoku[i][j] = 0;
                    }
                }
            }
        }
    }
}

int main(int argc, char *args[])
{
//    print_suudoku();
    int time = 0;
    while(time <= 81){
        find_kouho();
        int is_finished = 1;
        for(int i=0;i <= 8; i++){
            for(int j=0;j <= 8; j++){
                if (suudoku[i][j] == 0){
                    is_finished = 0;
                }
            }
        }
        if (is_finished == 1){
            break;
        }
        time += 1;
    }
    print_suudoku();
    return 0;
}
