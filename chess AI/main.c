#include <stdio.h>
#include <stdlib.h> // For exit()
#include "game.h"
#include "board.h"
#include "ai.h" // Thêm include cho AI
#include <unistd.h>

int main() {
    Game game;
    int choice;
    int aiDepth = 3; // Độ sâu của thuật toán Minimax (có thể thay đổi)

    printf("Chào mừng đến với Cờ tướng C!\n");
    printf("Chọn chế độ chơi:\n");
    printf("1. Chơi với người (Người vs Người)\n");
    printf("2. Chơi với máy (Người vs Máy)\n");
    printf("3. Máy chơi với máy (AI vs AI)\n");
    printf("Chọn lựa của bạn: ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // Xóa bộ đệm

    initializeGame(&game);

    if (choice == 1) {
        while (game.state == GAME_RUNNING) {
            printBoard(game.board);
            if (!processPlayerTurn(&game)) {
                if (game.state == GAME_EXIT) {
                    printf("Game kết thúc. Hẹn gặp lại!\n");
                    break;
                }
                continue;
            }
            checkGameEndConditions(&game);
        }
    } else if (choice == 2) {
        printf("Máy sẽ chơi Đỏ, bạn sẽ chơi Đen. Độ sâu AI: %d\n", aiDepth);
        while (game.state == GAME_RUNNING) {
            printBoard(game.board);
            if (game.currentPlayer == RED) {
                processAITurn(&game, aiDepth); // Máy chơi đỏ
            } else {
                if (!processPlayerTurn(&game)) { // Người chơi đen
                    if (game.state == GAME_EXIT) {
                        printf("Game kết thúc. Hẹn gặp lại!\n");
                        break;
                    }
                    continue;
                }
            }
            checkGameEndConditions(&game);
        }
    } else if (choice == 3) {
        printf("Chế độ AI vs AI. Độ sâu AI: %d\n", aiDepth);
        while (game.state == GAME_RUNNING) {
            printBoard(game.board);
            printf("AI (%s) đang suy nghĩ...\n", game.currentPlayer == RED ? "Đỏ" : "Đen");
            processAITurn(&game, aiDepth);
            checkGameEndConditions(&game);
            printBoard(game.board);
            usleep(10000000); // Đợi 0.5 giây cho dễ quan sát (cần #include <unistd.h> nếu trên Linux)
        }
    } else {
        printf("Lựa chọn không hợp lệ. Thoát game.\n");
        return 1;
    }

    // In kết quả cuối cùng
    printBoard(game.board);
    printf("\n=====================================\n");
    if (game.state == GAME_RED_WINS) {
        printf(" ĐỎ THẮNG CUỘC!!!\n");
    } else if (game.state == GAME_BLACK_WINS) {
        printf(" ĐEN THẮNG CUỘC!!!\n");
    } else if (game.state == GAME_DRAW) {
        printf(" HÒA!!!\n");
    } else {
        printf(" GAME KẾT THÚC!\n");
    }
    printf("=====================================\n");

    return 0;
}

