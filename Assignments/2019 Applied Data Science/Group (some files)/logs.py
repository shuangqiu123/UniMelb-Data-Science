from utility import *

print("\n\n")

for player in os.listdir('logs'):
    games = [i for i in os.listdir('logs/' + player) if '.csv' in i]
    player_total = pd.DataFrame()
    
    for game in games:
        df = pd.read_csv('./logs/' + player + f"/{game}")
        player_total = pd.concat([player_total, df]).drop("Unnamed: 9", axis=1)
    
    print(f"Player: {player}")
    print(player_total.describe().loc[['mean','std','min'],['earnings','fares','tips','trips']])
    print("\n\n")

for player in os.listdir('logs'):
    games = [i for i in os.listdir('logs/' + player) if '.csv' in i]
    player_total = pd.DataFrame()
    
    for game in games:
        df = pd.read_csv('./logs/' + player + f"/{game}")
        player_total = pd.concat([player_total, df]).drop("Unnamed: 9", axis=1)[['earnings','fares','tips','trips']]
        
    fig, ax = plt.subplots(ncols = 2, nrows=2, figsize=(15, 10))
    
    for r, v in (((0,0), "earnings"), ((0,1), "trips"), ((1,0), "fares"), ((1,1), "tips")):
        temp = player_total.sort_values(v).reset_index()[v]
        ax[r[0]][r[1]].plot(temp)
        
        ax[r[0]][r[1]].set_title(f"{player} {v.title()}")
        ax[r[0]][r[1]].set_xlabel("Number of Games")
        ax[r[0]][r[1]].set_ylabel(f"Cumulative {v.title()}")
        
        ax[0][0].set_ylim(700, 4500)
        ax[0][1].set_ylim(0, 400)
        ax[1][0].set_ylim(600, 4500)
        ax[1][1].set_ylim(40, 600)
        
        ax[r[0]][r[1]].plot(0, temp.min(),'o-',markersize=5, zorder=1)
        ax[r[0]][r[1]].annotate(f'{temp.min():.0f}', xy=(0, temp.min()), xytext=(5, 15), 
                 xycoords=('axes fraction', 'data'), textcoords='offset points')
        
        ax[r[0]][r[1]].plot(len(temp)-1, temp.max(),'o-',markersize=5, zorder=1)
        ax[r[0]][r[1]].annotate(f'{temp.max():.0f}', xy=(1, temp.max()), xytext=(-25, -15), 
                 xycoords=('axes fraction', 'data'), textcoords='offset points')
        
    plt.savefig(f"./plots/{player}_summary.jpg")
    

# todo combine all for comp 
fig, ax = plt.subplots(ncols = 2, nrows=2, figsize=(15, 10))
for player in os.listdir('logs'):
    games = [i for i in os.listdir('logs/' + player) if '.csv' in i]
    player_total = pd.DataFrame()
    
    for game in games:
        df = pd.read_csv('./logs/' + player + f"/{game}")
        player_total = pd.concat([player_total, df]).drop("Unnamed: 9", axis=1)[['earnings','fares','tips','trips']]
        
    for r, v in (((0,0), "earnings"), ((0,1), "trips"), ((1,0), "fares"), ((1,1), "tips")):
        temp = player_total.sort_values(v).reset_index()[v]
        ax[r[0]][r[1]].plot(temp, label=player)
        
        ax[r[0]][r[1]].set_title(f"Comparision: {v.title()}")
        ax[r[0]][r[1]].set_xlabel("Number of Games")
        ax[r[0]][r[1]].set_ylabel(f"Cumulative {v.title()}")
        
        ax[0][0].set_ylim(700, 4500)
        ax[0][1].set_ylim(0, 400)
        ax[1][0].set_ylim(600, 4500)
        ax[1][1].set_ylim(40, 600)
        
        ax[r[0]][r[1]].legend()
        ax[r[0]][r[1]].plot(0, temp.min(),'o-',markersize=5, zorder=1)
        ax[r[0]][r[1]].plot(len(temp)-1, temp.max(),'o-',markersize=5, zorder=1)
        
        ax[r[0]][r[1]].annotate(f'{temp.min():.0f}', xy=(0, temp.min()), xytext=(5, 15), 
                     xycoords=('axes fraction', 'data'), textcoords='offset points')

        ax[r[0]][r[1]].annotate(f'{temp.max():.0f}', xy=(1, temp.max()), xytext=(-25, -15), 
                     xycoords=('axes fraction', 'data'), textcoords='offset points')

        
plt.savefig(f"./plots/agent_comparision.jpg")

print("TRIP INFERENCE FOR THE FIRST GAME!")
from collections import defaultdict

# for our greedy and markov model players
for player in os.listdir('logs')[:2]:
    
    # get the game files with the full details
    games = [i for i in os.listdir('logs/' + player) if "trips" not in i or ".csv" not in i]
    
    # for each game playerd (1 - 25 iterations)
    for game in games:
        
        # initialize a counter for duration
        shifts = defaultdict(float)
        shift_time = defaultdict(float)
        with open(f"logs/{player}/" + game) as f:
            # keep rows that denote a pickup or end of shift
            week = [i for i in f.readlines() if "pickedup" in i or "End of Shift" in i or "starting" in i]
            
            # initialize shift count from 1 (up to the 6th weekly shift)
            shift_count = 1
            
            # for each row in the weekly simulation
            for minute in week:
                action = minute.split(",")
                
                if "starting" in action[1]:
                    start = pd.to_datetime(action[1].split()[-1])
                    
                # if end of shift, then we increase shift count to the next one (max of 6)
                elif "End of Shift" in action[1]:
                    end = pd.to_datetime(action[1].split()[-1])
                    shift_time[shift_count] += (end - start).seconds
                    shift_count += 1
                else:
                    # action[3:5] gives us the start time and end time of the pickup
                    times = action[3:5]
                    
                    # duration in seconds
                    duration = (pd.to_datetime(times[1]) - pd.to_datetime(times[0])).seconds
                    
                    # if the duration is greater than an hour, we should print it out to double check
                    if duration/60/60 > 1:
                        print(f"Long Trip in shift {shift_count} with time {duration/60/60:.3f} hours")
                    
                    # add it in to the counter
                    shifts[shift_count] += duration
        
        j = 1
        for i in shifts.items():
            print(f"[Game ID: {game.split('_')[1]}] Shift {i[0]}: {i[1]/60/60:.3f} hours (Shift End - Shift Start = {shift_time[j]/60/60:.3f} hours)")
            j += 1
                  
        print("**********************************************")
        break