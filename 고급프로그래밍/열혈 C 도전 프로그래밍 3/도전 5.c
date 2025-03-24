#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
   int win = 0, draw = 0, lose = 0;
   char RSP[4][10] = { " ", "바위", "가위", "보" };
   while (1) {
      srand((int)time(NULL));
      printf("바위는 1, 가위는 2, 보는 3 : ");
      int player, computer = rand() % 3 + 1;
      scanf_s("%d", &player);
      if (player == computer) {
         draw++;
         printf("당신은 %s 선택, 컴퓨터는 %s 선택, 비겼습니다!\n", RSP[player], RSP[computer]);
      }
      else if (player - computer == -1 || player - computer == 2) {
         win++;
         printf("당신은 %s 선택, 컴퓨터는 %s 선택, 이겼습니다!\n", RSP[player], RSP[computer]);
      }
      else {
         printf("당신은 %s 선택, 컴퓨터는 %s 선택, 당신이 졌습니다!\n", RSP[player], RSP[computer]);
         break;
      }
   }
   printf("게임의 결과 : %d승, %d무", win, draw);
   return 0;
}
