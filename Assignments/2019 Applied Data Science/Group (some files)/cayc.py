"""
:filename: cayc.py
:summary: CAYC Algorithm - cake the other players
:authors: 
    - Chaoyi 
    - Akira 
    - Yongsee 
    - Calvin
"""
########################### IMPORTS ##########################

# Standard modules
import sys
import json
import numpy as np
import pickle as pkl
import dateutil.parser
from datetime import timedelta, datetime

# Global defined variables
X, Y = 87, 141
RES = 30
SHIFT_MINS = 12 * 60
DAY_MINS = 24 * 60
WEEK_MINS = 7 * DAY_MINS
TOT_DAYS = 365 + 366

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

SHIFT_START, DESTINATION, AVAILABLE, REWARD = None, None, None, None

SHIFTS = 0

######################## CAYC Player #######################


def pick_noon(_time):
    
    global SHIFTS, SHIFT_START, DESTINATION, AVAILABLE, REWARD
    day = _time.weekday()
    choices = MORNING[day], AFTERNOON[day], MORNING[day + 1], AFTERNOON[day + 1], MORNING[day + 2], AFTERNOON[day + 2]
    SHIFTS += 1
    
    for start in choices:
        if start is None:
            break
        
        dow = start // DAY_MINS
        tod = start % DAY_MINS
        h, m = tod // 60, tod % 60
        
        shift = datetime(_time.year, _time.month, _time.day)
        shift += timedelta(days = dow - day, hours = h, minutes = m)
        
        if shift > _time:
            if dow == 3 and SHIFTS == 4:
                continue
            SHIFT_START = shift
            with open(f'provided_files/Players/AltMarkov{RES}/outputs_start{start}_res{RES}.pkl', 'rb') as fp:
                DESTINATION, AVAILABLE, REWARD = pkl.load(fp)
            return SHIFT_START
    
    SHIFT_START = _time + timedelta(minutes=1)    
    with open(f'provided_files/Players/AltMarkov{RES}/outputs_start{AFTERNOON[-3]}_res{RES}.pkl', 'rb') as fp:
        DESTINATION, AVAILABLE, REWARD = pkl.load(fp)
    return SHIFT_START

def play_turn(current_datetime, currentCell, neighbours):
    """
    Plays a turn given the current time, cell and neighbouring cells
    """
    global SHIFT_START

    x, y = map(int, currentCell.split(':'))
    curr = x * Y + y

    time = min((current_datetime - SHIFT_START).seconds // 60, SHIFT_MINS - 1)
    state = "FORHIRE"
    next_move = DESTINATION[time][curr]
    action = "STAY" if curr == next_move else "MOVE"

    return {"state": state, "action": action, "moveTo": f'{next_move//Y}:{next_move%Y}'}


def select_shift(current_time):
    """
    Decides when and where to start a shift given current time
    """
    
    global DESTINATION, AVAILABLE, REWARD

    start = pick_noon(current_time)
    best = max(REWARD[0], key=lambda x: REWARD[0][x])

    return {"defer": start, "moveTo": f'{best//Y}:{best%Y}'}


def first_move(start_datetime):
    return select_shift(start_datetime)


def next_shift(current_time):
    return select_shift(current_time + timedelta(hours=8))


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