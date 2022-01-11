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


# Initial Operations
INPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/input.txt'
OUTPUT_PATH = '/home/freyr/dev/GraphTheory/code/python/output.txt'
# clearing the contents of the file if any
open(OUTPUT_PATH, 'w').close()


# === Defining global Variables === #

with open(INPUT_PATH, 'r') as f:
    R, C = (int(i) for i in f.readline().split(" "))
    
    M = [[] for _ in range(R)]
    for i in range(R):
        M[i] = [x for x in f.readline().split(" ")]
    
    SR, SC = (int(i) for i in f.readline().split(" "))

# Matrix denoting whether a node in the grid is visited or not    
visited = [[False for _ in range(C)] for _ in range(R)]

# Keeping Track of whether we reached the end or not
reached_end = False

# direction vectors and Queue Containers
dr = [-1, +1, 0, 0]
dc = [0, 0, +1, -1]

rq, cq = [], []


# === MAIN METHODS FOR THE SOLUTION === #

def solve():
    nodes_left_in_layer = 1
    move_count = 0
    
    rq.append(SR)
    cq.append(SC)
    visited[SR][SC] = True
    
    while len(rq) > 0:
        r = rq.pop(0)
        c = cq.pop(0)
        
        if M[r][c] == 'E':
            reached_end = True
            break
        nodes_in_next_layer = explore_neighbours(r, c)
        nodes_left_in_layer = nodes_left_in_layer - 1 
        
        if nodes_left_in_layer == 0:
            nodes_left_in_layer = nodes_in_next_layer
            move_count = move_count + 1
            
    if reached_end:
        return move_count
    
    return -1        

def explore_neighbours(r, c, nodes_in_next_layer=0):
    for i in range(4):
        rr = r + dr[i]
        cc = c + dc[i]
        
        # check if out of bounds
        if (rr < 0 or cc < 0): continue
        if (rr >= R or cc >= C): continue
        
        # skip visited locations or blocked cells
        if (visited[rr][cc]): continue
        if (M[rr][cc] == '#'): continue
        
        rq.append(rr)
        cq.append(cc)
        visited[rr][cc] = True
        nodes_in_next_layer = nodes_in_next_layer + 1
        
    return nodes_in_next_layer
        
        
if __name__ == '__main__':
    ans = solve()
    with open(OUTPUT_PATH, 'a') as f:
        f.write(f"Length of the Shortest Path to exit is: {ans}")