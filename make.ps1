gcc -o src/tictactoe.exe src/tictactoe.c myUtils.c -Wall -Wextra -std=c17  -I src/headers -L src/lib -lraylib -lgdi32 -lwinmm -lopengl32
gcc -o src/minesweeper.exe src/minesweeper.c myUtils.c -Wall -Wextra -std=c17  -I src/headers  -L src/lib -lraylib -lgdi32 -lwinmm -lopengl32
gcc -o src/game.exe main.c src/myUtils.c -Wall -Wextra -std=c17  -I src/headers -L src/lib -lraylib -lgdi32 -lwinmm -lopengl32
