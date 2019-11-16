"""
:filename: greedy.py
:summary: Greedy Agent
"""
########################### IMPORTS ##########################

# Standard modules
import sys
import json
import random
import pickle
import datetime
import dateutil.parser
from datetime import timedelta

# Global defined variables
with open('provided_files/Players/Greedy/refinedManhattan.pickle', 'rb') as handle:
    M = pickle.load(handle)

with open('provided_files/Players/Greedy/refinedJFK.pickle', 'rb') as handle:
    J = pickle.load(handle)

with open('provided_files/Players/Greedy/refinedLaguardia.pickle', 'rb') as handle:
    L = pickle.load(handle)

with open('provided_files/Players/Greedy/cells.txt') as fp:
    CELLS = [line[:-1] for line in fp]

START_CELL = CELLS[0]
DEFAULT_STATE = "FORHIRE"

DAY_MINS = 24 * 60
MORNING = [0 * DAY_MINS +  5 * 60 + 30,
           1 * DAY_MINS +  5 * 60 + 20,
           2 * DAY_MINS +  5 * 60 + 30,
           3 * DAY_MINS +  5 * 60 + 10,
           4 * DAY_MINS +  4 * 60 + 50,
           5 * DAY_MINS +  5 * 60 + 40,
           6 * DAY_MINS +  5 * 60 + 40, None, None]
AFTERNOON = [0 * DAY_MINS + 13 * 60 + 50,
             1 * DAY_MINS + 14 * 60 + 40,
             2 * DAY_MINS + 15 * 60 + 20,
             3 * DAY_MINS + 16 * 60 + 10,
             4 * DAY_MINS + 17 * 60 +  0,
             5 * DAY_MINS + 15 * 60 + 30,
             6 * DAY_MINS + 11 * 60 + 30, None, None]

SHIFTS = 0

######################## Greedy Player #######################

def convert(cell):
    x, y = cell.split(':')
    return (int(x), int(y))


def explore(nbs):
    global CELLS
    for cell in CELLS:
        if cell in nbs:
            return cell

    return random.choice(nbs) # should not happen


def play_turn(current_datetime, current_cell, nbs):
    """
    A greedy heuristic which will choose locally optimal moves.
    :heuristic: Always take a trip if possible, else move towards the closest "best zone"
    :zones: Manhattan, JFK Airport and LaGuardia Airport
    :returns: dictionary of form {"state": STATE, "action": MOVE, "moveTo": NEXT_MOVE}
    """
    global DEFAULT_STATE

    neighbours = [convert(i) for i in nbs]

    best = []

    for cell in neighbours:
        lowest_dist = (cell, min(M[cell], J[cell], L[cell]))
        best.append(lowest_dist)
        
    best = sorted(best, key=lambda x: x[1])[0]

    cell, dist = best[0], best[1]

    if dist == 0:
        cell = explore(nbs + [current_cell])
    else:
        cell = f"{cell[0]}:{cell[1]}"

    move = {"state": DEFAULT_STATE,
            "action": "MOVE" if cell != current_cell else "STAY",
            "moveTo": cell}

    return move

def optimal_hour(_time):
    
    global SHIFTS
    day = _time.weekday()
    choices = MORNING[day], AFTERNOON[day], MORNING[day + 1], AFTERNOON[day + 1], MORNING[day + 2], AFTERNOON[day + 2]
    SHIFTS += 1
    
    for start in choices:
        if start is None:
            break
        
        dow = start // DAY_MINS
        tod = start % DAY_MINS
        h, m = tod // 60, tod % 60
        
        shift = datetime.datetime(_time.year, _time.month, _time.day)
        shift += timedelta(days = dow - day, hours = h, minutes = m)
        
        if shift > _time:
            if dow == 3 and SHIFTS == 4:
                continue
            return {"defer": shift, "moveTo": START_CELL}
        
    return {"defer": _time + timedelta(minutes=1), "moveTo": START_CELL}
    

    day = _time.weekday()

    start = OPT_STARTS[day]
    

    shift = datetime.datetime(_time.year, _time.month, _time.day, h, m)
    
    if shift < _time:
        diff = OPT_STARTS[day + 1] - OPT_STARTS[day]
        shift += timedelta(minutes=diff)

    
    return {"defer": shift, "moveTo": START_CELL}

def first_move(start_datetime):
    start = optimal_hour(start_datetime)
    return start


def next_shift(current_time):
    next_shift = optimal_hour(current_datetime + timedelta(hours=8))
    return next_shift


################################################################################################################################
################################################################################################################################
# loops until shutdown, waiting for new turn requests on StdIn
while True:
    # Read input from StdIn
    req = json.loads(sys.stdin.readline())
    reqtype = req['type']
    current_datetime = dateutil.parser.parse(req['time'])

    if(reqtype == "FIRSTMOVE"):
        action = first_move(current_datetime)

        # Create response named list that will be converted to JSON
        resp = {}
        resp["defer"] = action['defer'].strftime("%Y-%m-%dT%H:%M")
        resp["nextMove"] = "REPOSITION"
        resp["moveTo"] = action['moveTo']
        print("MAST30034:" + json.dumps(resp))
        sys.stdout.flush()
    elif(reqtype == "PLAYTURN"):
        current_cell = req['currentCell']
        neighbours = req['neighbours']
        action = play_turn(current_datetime, current_cell, neighbours)
        print("MAST30034:" + json.dumps(action))
        sys.stdout.flush()
    elif(reqtype == "NEXTSHIFT"):
        action = next_shift(current_datetime)

        # Create response named list that will be converted to JSON
        resp = {}
        resp["defer"] = action['defer'].strftime("%Y-%m-%dT%H:%M")
        resp["nextMove"] = "REPOSITION"
        resp["moveTo"] = action['moveTo']
        print("MAST30034:" + json.dumps(resp))
        sys.stdout.flush()
