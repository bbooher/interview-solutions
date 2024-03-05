
#include <stdio.h>
#include <string.h>

void print_arr(int n, int arr[n][n]) {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            printf("%3d ", arr[x][y]);
        }
        printf("\n");
    }
}

int spiral_arr(int n, int arr[n][n])
{
    if (n <= 0) {
        printf("Invalid array size\n");
        return -1;
    }

    // Ensure arr is empty
    memset(arr, 0, n * n * sizeof(int));
    
    const int max_spiaral_val = n * n;
    int spiral_val = 1;
    
    int x = 0;
    int y = 0;
    arr[x][y] = spiral_val;
    
    const int rot_mat_size = 4;
    const int x_rot[] = {1, 0, -1, 0};
    const int y_rot[] = {0, 1, 0, -1};
    int rot_ndx = 0;
    
    while (++spiral_val <= max_spiaral_val) {
        // Get next x,y position
        x += x_rot[rot_ndx];
        y += y_rot[rot_ndx];
        
        // Determine whether position is invalid
        if ((arr[x][y] != 0) || (x_rot[rot_ndx] > 0 && x == n) || (x_rot[rot_ndx] < 0 && x < 0) || 
                                (y_rot[rot_ndx] > 0 && y == n) || (y_rot[rot_ndx] < 0 && y < 0)) {
            // Backtrack the update
            x -= x_rot[rot_ndx];
            y -= y_rot[rot_ndx];
            
            // Rotate
            rot_ndx = (rot_ndx + 1) % rot_mat_size;
            
            // Update new position
            x += x_rot[rot_ndx];
            y += y_rot[rot_ndx];
        }
        
        // Update position with spiral value
        arr[x][y] = spiral_val;
    }
    
    return 0;
}

int main()
{
    const int arr_size = 5;
    int arr[arr_size][arr_size];
    
    spiral_arr(arr_size, arr);
    
    print_arr(arr_size, arr);
    return 0;
}
