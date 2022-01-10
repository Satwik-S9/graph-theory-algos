
#! WARNING!!! THIS FILE IS NOT WORKING PROPERLY DUE TO SOME ISSUE WITH THE FUNCTIONS NOT BEING 
#! ABLE TO ACCESS THE GLOBAL VARIABLES.

#! PLEASE DON'T USE OR REFERENCE THIS FILE UNTILL THE ISSUE IS FIXED

#* FOR LOGIC REFER TO THE CPP IMPLEMENTATION
 

""" 
You are trapped in a 2D Dungeon and need to find the quickest way out The dungeon is composed of unit cubes which 
may or may not be filled with rock. It takes one minute to move one unit north, south, east, west. You can't move
diagonally and maze is surrounded by solid rock on all sides.

* Is Escape possible ? If yes, how long will it take ?

The dungeon has a size of R * C and you start at S and theres an exit E. A cell full of rock is denoted by '#' and empty 
cells are represented by '.'      

* INPUT: 
R = 5, C = 7

. . . # . . .
. # . . . # .
. # . . . . .
. . # # . . .
# . # E . # . 

"""


INPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/input.txt'
OUTPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/output.txt'

rq, cq = [], []    

# Variables to track number of steps taken
MOVE_COUNT = 0
nodes_left_in_layer = 1
nodes_in_next_layer = 0

# Keep track if we have reached the end
reached_end = False 


def explore_neighbours(r, c, ):
    for i in range(4):
        rr = r + dr[i]
        cc = c + dc[i]
        
        # skip out of bounds locations
        if rr < 0 or cc < 0: continue
        if rr >= R or cc >= C: continue
        
        # skip visited locations or blocked cells
        if visited[rr][cc]: continue
        if m[rr][cc] == '#': continue 
        
        rq.append(rr)
        cq.append(cc)
        visited[rr][cc] = True
        nodes_in_next_layer += 1

def solve(sr, sc):
    rq.append(sr)
    cq.append(sc)
    visited[sr][sc] = True
    
    # BFS 
    while len(rq) > 0:  # or len(cq) > 0
        r = rq.pop(0)
        c = cq.pop(0)
        
        if m[r][c]  == 'E':
            reached_end = True
            break
        explore_neighbours(r, c, nodes_in_next_layer)
        nodes_left_in_layer -= 1
        if nodes_left_in_layer == 0:
            nodes_left_in_layer = nodes_in_next_layer
            nodes_in_next_layer = 0
            MOVE_COUNT += 1
    
    if reached_end:
        return MOVE_COUNT
    return -1

if __name__ == '__main__':
    # Some Global Variables 
    global R, C
    # print("Enter No. of Rows and Columns ... ")
    with open(INPUT_PATH, 'r') as f:
        R, C = (int(i) for i in f.readline().split(" "))

        global m
        # print("Enter the grid...")
        m = [[] for _ in range(R)]
        for i in range(R):
            m[i] = [x for x in f.readline().split(" ")]
        print(m)
    
        global sr, sc
        # print("Enter Starting Coordinates...")
        sr, sc = (int(i) for i in f.readline().split(" "))
        print(sr, sc)

    # R*C matrix of false values to check if we have visited the current node in the grid
    global visited
    visited = [[False for _ in range(C)] for _ in range(R)]
    print(visited)

    # North, South, East, West Direction vectors
    global dr, dc
    dr = [-1, +1, 0, 0]
    dc = [0, 0, +1, -1]
    
    ans = solve(sr, sc)
    print(ans)




