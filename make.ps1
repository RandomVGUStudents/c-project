gcc -o tictactoe.exe src/tictactoe.c src/myUtils.c -Wall -Wextra -std=c17  -I src/headers -L src/lib -lraylib -lgdi32 -lwinmm -lopengl32
gcc -o minesweeper.exe src/minesweeper.c src/myUtils.c -Wall -Wextra -std=c17  -I src/headers  -L src/lib -lraylib -lgdi32 -lwinmm -lopengl32
gcc -o game.exe src/gameui.c src/myUtils.c -Wall -Wextra -std=c17  -I src/headers -L src/lib -lraylib -lgdi32 -lwinmm -lopengl32
