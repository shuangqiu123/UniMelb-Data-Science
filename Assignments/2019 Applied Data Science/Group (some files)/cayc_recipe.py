import sys
import pickle as pkl
import numpy as np
import json
from collections import Counter
from collections import defaultdict as dd
from multiprocessing import Pool

"""
python3 cayc.py RES N_THREADS DIR SAVE [START_TIMES]

The maximum expected reward is printed to STDOUT.

RES           - Bin size for the aggregates (for parameter estimates). Must have ran agg.ipynb with that RES.
N_THREADS     - Number of threads to use. Multiprocessing is only implemented for multiple start times.
DIR           - Directory of the parameter estimates.
SAVE          - Any nonzero integer will save the results (actions and rewards), otherwise specify as 0.
[START_TIMES] - If integers, interpret as list of start times. If single string, interpret as file of start times, one per line.
                Times are to be inputted as number of minutes starting from Mon 00:00.
"""

RES, N_THREADS, SAVE = map(int, sys.argv[1:4])

try:
    STARTS = [int(x) for x in sys.argv[4:]]
except:
    # filename given
    with open(sys.argv[4]) as fp:
        STARTS = [int(x) for x in fp.read().split()]

X, Y = 87, 141
SHIFT_MINS = 12 * 60
DAY_MINS = 24 * 60
WEEK_MINS = 7 * DAY_MINS
TOT_DAYS = 365 + 366
BINS = WEEK_MINS // RES

with open(f'{DIR}/counts_res{RES}.pkl', 'rb') as fp:
    counts = pkl.load(fp)
    print("[1] Loading Done...")
with open(f'{DIR}/revs_res{RES}.pkl', 'rb') as fp:
    revs = pkl.load(fp)
    print("[2] Loading Done...")
with open(f'{DIR}/durs_res{RES}.pkl', 'rb') as fp:
    durs = pkl.load(fp)
    print("[3] Loading Done...")    
    
with open('provided_files/shapefiles/game_board_2019.geojson') as fp:
    board = json.load(fp)
idToX = {}
idToY = {}
nbs = {}
for cell in board['features']:
    cellID = cell['properties']['id']
    cellTuple = tuple(map(int, cellID.split(':')))
    idToX[cellID], idToY[cellID] = cellTuple
    nbs[cellTuple] = [tuple(map(int, nb.split(':'))) for nb in cell['properties']['neighbours']]
    
for x in (counts, revs, durs):
    x.append(x[0])
    
def idx2int(t):
    return t[0] * 141 + t[1]

nbs_int = {idx2int(k): [idx2int(x) for x in v] for k, v in nbs.items()}

def dp(start_time, counts, revs, durs):
    """
    Dynammic programming to optimise expected reward.
    `start_time` is the minute of the week.
    See README_CAYC.md for format of other arguments.
    """
    dest = [{} for _ in range(SHIFT_MINS)]
    avail = [{} for _ in range(SHIFT_MINS)]
    reward = [{} for _ in range(SHIFT_MINS)]
    
    # last minute, be available
    dest[-1] = {k: k for k in nbs_int}
    avail[-1] = {k: True for k in nbs_int}
            
    for t in range(SHIFT_MINS - 1, -1, -1):
        # minute of week
        m = (start_time + t) % RES
        
        # w0 and w1 are smoothing parameters
        # each estimated value is a weighted average of two binned parameter estimates,
        # corresponding to bins rt0 and rt1
        if m < RES // 2:
            rt1 = (start_time + t) % WEEK_MINS // RES
            rt0 = rt1 - 1
            w0 = (RES - 1 - m * 2) / (2 * RES)
            w1 = (RES + 1 + m * 2) / (2 * RES)
        else:
            rt0 = (start_time + t) % WEEK_MINS // RES
            rt1 = rt0 + 1
            w0 = (3 * RES - 1 - m * 2) / (2 * RES)
            w1 = (1 - RES + m * 2) / (2 * RES)
        
        # loc is start cell
        for loc in nbs_int:
            # found_trip is expected earnings if obtain trip
            found_trip = 0
            # k is end cell
            for k in set(counts[rt0][loc]) | set(counts[rt1][loc]):
                # average arrival time
                arrival = t + max(1, int(round(w0 * durs[rt0][loc][k] + w1 * durs[rt1][loc][k])))
                # increment expected earnings if obtain trip
                found_trip += (
                    w0 * revs[rt0][loc][k] +
                    w1 * revs[rt1][loc][k] +
                    (reward[arrival][k] if arrival < SHIFT_MINS else 0)
                ) * (w0 * counts[rt0][loc][k] + w1 * counts[rt1][loc][k])            
            
            # normalise by dividing by the total number of trips
            tot = w0 * sum(counts[rt0][loc].values()) + w1 * sum(counts[rt1][loc].values())
            if tot:
                found_trip /= tot
            
            # DP initialisation for last column
            if t == SHIFT_MINS - 1:
                reward[t][loc] = found_trip * min(1, tot / 104 / RES)
                
            # no_trip is expecting earnings if no trip obtained
            else:
                dest[t][loc] = best_nb = max(nbs_int[loc] + [loc], key=lambda x: reward[t + 1][x])
                reward[t][loc] = no_trip = reward[t + 1][best_nb]
                
                # if the expected trip obtained is worth, be available
                if found_trip > no_trip:
                    avail[t][loc] = True
                    reward[t][loc] += (found_trip - no_trip) * min(1, tot / 104 / RES)
                else:
                    avail[t][loc] = False          
    
    return dest, avail, reward

def compute(start):
    """
    Prints the expected reward, and saves the matrix if the cmd argument SAVE is nonzero.
    `start` is the minute of the week.
    Note that the expected reward is grossly overestimated due to overfitting.    
    """
    output = dp(start, counts, revs, durs)
    day = start // DAY_MINS
    tod = start % DAY_MINS
    hour = tod // 60
    minute = tod % 60
    print(f'day {day} {hour}:{minute:02d} ${max(output[2][0].values()):.2f}')
    if SAVE:
        """
        if str(RES) == "10":
            DIRECTORY = './provided_files/Players/res10/'
        elif str(RES) == "20":
            DIRECTORY = './provided_files/Players/res30/'
        elif str(RES) == "30":
            DIRECTORY = './provided_files/Players/Markov/'
        else:
            DIRECTORY = './data/'
        """
        with open(f'{DIR}/outputs_start{start}_res{RES}.pkl', 'wb') as fp:
            pkl.dump(output[:2], fp)

print("[4] Loading Done...") 
p = Pool(N_THREADS)
results = p.map(compute, STARTS)
p.close()
p.join()