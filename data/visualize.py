import matplotlib.pyplot as plt
import numpy as np

name = ['random', 'mcs easy', 'mcs medium', 'mcs hard', 'minmax easy', 'minmax medium', 'minmax hard', 'mcts easy', 'mcts medium', 'mcts hard']
win, lose, tie = [0] * 10, [0] * 10, [0] * 10
grid_win, grid_lose, grid_tie = [[0] * 10 for _ in range(10)], [[0] * 10 for _ in range(10)], [[0] * 10 for _ in range(10)]
with open("data/results.txt", 'r') as file:
    for line in file:
        bot1, bot2, wb1, wb2, t = map(int, line.split())
        grid_win[bot1][bot2] += wb1
        grid_lose[bot1][bot2] += wb2
        grid_win[bot2][bot1] += wb2 
        grid_lose[bot2][bot1] += wb1
        grid_tie[bot1][bot2] += t
        grid_tie[bot2][bot1] += t
        win[bot1] += wb1 
        win[bot2] += wb2 
        tie[bot1] += t 
        tie[bot2] += t 
        lose[bot1] += 100 - t - wb1 
        lose[bot2] += 100 - t - wb2 
        
# making heatmap of wins, loses and ties
plt.figure(figsize=(10, 9))
plt.imshow(grid_win, cmap='Greens', interpolation='nearest')
plt.xticks(ticks=range(10), labels=name, rotation=45, ha='right', fontsize=12)
plt.yticks(ticks=range(10), labels=name, fontsize=12)
plt.colorbar()
plt.title('Heatmap of wins', fontsize=20)
plt.savefig('data/charts/heatmap_wins.png', bbox_inches='tight')
plt.clf()

plt.figure(figsize=(10, 9))
plt.imshow(grid_lose, cmap='Reds', interpolation='nearest')
plt.xticks(ticks=range(10), labels=name, rotation=45, ha='right', fontsize=12)
plt.yticks(ticks=range(10), labels=name, fontsize=12)
plt.colorbar()
plt.title('Heatmap of loses', fontsize=20)
plt.savefig('data/charts/heatmap_loses.png', bbox_inches='tight')
plt.clf()

plt.figure(figsize=(10, 9))
plt.imshow(grid_tie, cmap='YlOrBr', interpolation='nearest')
plt.xticks(ticks=range(10), labels=name, rotation=45, ha='right', fontsize=12)
plt.yticks(ticks=range(10), labels=name, fontsize=12)
plt.colorbar()
plt.title('Heatmap of ties', fontsize=20)
plt.savefig('data/charts/heatmap_tie.png', bbox_inches='tight')
plt.clf()

# piechart of invidual bots
for i in range(10):
    data = [win[i], lose[i], tie[i]]
    labels = ['Win', 'Lose', 'Tie']
    colors = ['green', 'red', 'yellow']
    
    plt.figure()
    wedges, texts, autotexts = plt.pie(data, labels=labels, colors=colors, autopct='%1.1f%%', startangle=140)
    legend_labels = [f'Win: {win[i]}', f'Lose: {lose[i]}', f'Tie: {tie[i]}']
    plt.legend(wedges, legend_labels, loc="upper right", bbox_to_anchor=(1.2, 1.1))
    plt.title(f'Resutls of bot {name[i]}')
    plt.savefig(f'data/charts/bot{i}results.png', bbox_inches='tight')
    plt.close()
    
# ploting ranking 
bots = list(zip(name, win, lose, tie))
bots_sorted = sorted(bots, key=lambda x: (x[1], x[3]))
name_sorted, win_sorted, lose_sorted, tie_sorted = zip(*bots_sorted)
x = np.arange(len(name_sorted))
width = 0.3 

fig, ax = plt.subplots(figsize=(12, 8))
bar_width = 0.5
y = np.arange(len(name_sorted))
ax.barh(y, win_sorted, color='green', edgecolor='white', label='Win', height=bar_width)
ax.barh(y, tie_sorted, left=win_sorted, color='yellow', edgecolor='white', label='Tie', height=bar_width)
ax.barh(y, lose_sorted, left=np.add(win_sorted, tie_sorted), color='red', edgecolor='white', label='Lose', height=bar_width)

ax.set_ylabel('Bots')
ax.set_title('Ranking of Bots by Performance')
ax.set_yticks(y)
ax.set_yticklabels(name_sorted, rotation=45, ha='right')
ax.legend()


rects_win = ax.patches[:len(win_sorted)]
rects_tie = ax.patches[len(win_sorted):2*len(win_sorted)]
rects_lose = ax.patches[2*len(win_sorted):]  

fig.tight_layout()
plt.savefig('data/charts/ranking', bbox_inches='tight')
plt.close()

# making plots of difference between same class of bots
subname = ['mcs', 'minmax', 'mcts']
for i in range(3):
    bot1, bot2 = 3 * i + 1, 0
    data = [grid_win[bot1][bot2], grid_lose[bot1][bot2], grid_tie[bot1][bot2]]
    labels = ['Win', 'Lose', 'Tie']
    colors = ['green', 'red', 'yellow']
    plt.figure()
    wedges, texts, autotexts = plt.pie(data, labels=labels, colors=colors, autopct='%1.1f%%', startangle=140)
    legend_labels = [f'Win: {grid_win[bot1][bot2]}', f'Lose: {grid_lose[bot1][bot2]}', f'Tie: {grid_tie[bot1][bot2]}']
    plt.legend(wedges, legend_labels, loc="upper right", bbox_to_anchor=(1.2, 1.1))
    plt.title(f'Resutls of battle bot {subname[i]} easy vs bot random')
    plt.savefig(f'data/charts/battle{bot1}vs{bot2}.png', bbox_inches='tight')
    plt.close()
    
    bot1, bot2 = 3 * i + 2, 3 * i + 1
    data = [grid_win[bot1][bot2], grid_lose[bot1][bot2], grid_tie[bot1][bot2]]
    labels = ['Win', 'Lose', 'Tie']
    colors = ['green', 'red', 'yellow']
    plt.figure()
    wedges, texts, autotexts = plt.pie(data, labels=labels, colors=colors, autopct='%1.1f%%', startangle=140)
    legend_labels = [f'Win: {grid_win[bot1][bot2]}', f'Lose: {grid_lose[bot1][bot2]}', f'Tie: {grid_tie[bot1][bot2]}']
    plt.legend(wedges, legend_labels, loc="upper right", bbox_to_anchor=(1.2, 1.1))
    plt.title(f'Resutls of battle bot {subname[i]} medium vs bot {subname[i]} easy')
    plt.savefig(f'data/charts/battle{bot1}vs{bot2}.png', bbox_inches='tight')
    plt.close()
    
    bot1, bot2 = 3 * i + 3, 3 * i + 2
    data = [grid_win[bot1][bot2], grid_lose[bot1][bot2], grid_tie[bot1][bot2]]
    labels = ['Win', 'Lose', 'Tie']
    colors = ['green', 'red', 'yellow']
    plt.figure()
    wedges, texts, autotexts = plt.pie(data, labels=labels, colors=colors, autopct='%1.1f%%', startangle=140)
    legend_labels = [f'Win: {grid_win[bot1][bot2]}', f'Lose: {grid_lose[bot1][bot2]}', f'Tie: {grid_tie[bot1][bot2]}']
    plt.legend(wedges, legend_labels, loc="upper right", bbox_to_anchor=(1.2, 1.1))
    plt.title(f'Resutls of battle bot {subname[i]} hard vs bot {subname[i]} medium')
    plt.savefig(f'data/charts/battle{bot1}vs{bot2}.png', bbox_inches='tight')
    plt.close()