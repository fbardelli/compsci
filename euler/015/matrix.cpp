#include <iostream>
using namespace std;

int main()
{
    const int GRID_SIZE = 20;
    long long grid[GRID_SIZE+1][GRID_SIZE+1];
    grid[0][0] = 1;
    for(int x = 0; x <= GRID_SIZE; x++){
        for(int y = 0; y <= GRID_SIZE; y++){
            if(x == 0 || y == 0){
              grid[x][y] = 1;
            }else{
              grid[x][y] = grid[x-1][y]+grid[x][y-1];
            }
        }
    }
    for(int i=1;i <= GRID_SIZE; i++){
        cout << i << "," << i << ":" << grid[i][i] << endl;
    }
    cout << grid[GRID_SIZE][GRID_SIZE] << endl;
}
