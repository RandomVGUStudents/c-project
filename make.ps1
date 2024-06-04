gcc -o tictactoe.exe tictactoe.c myUtils.c -Wall -Wextra -std=c17  -I src/headers -L src/lib -lraylib -lgdi32 -lwinmm -lopengl32
gcc -o minesweeper.exe minesweeper.c myUtils.c -Wall -Wextra -std=c17  -I src/headers  -L src/lib -lraylib -lgdi32 -lwinmm -lopengl32
gcc -o game.exe main.c myUtils.c -Wall -Wextra -std=c17  -I src/headers -L src/lib -lraylib -lgdi32 -lwinmm -lopengl32
