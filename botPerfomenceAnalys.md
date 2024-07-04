# Report on Bot Performance

In our game, we have four different bots, each written with different algorithms:
* **Random Bot** - makes random moves.
* **MCS Bot** - uses a Minimax algorithm with depth 1, and many random simulations as a heuristic evaluation function (besed on monte carlo simulation)
* **Minimax Bot** - employs alpha-beta pruning optimization.
* **MCTS Bot** - basic implementation using random simulations as a heuristic evaluation function.

We have three different variants for the MCS, Minimax, and MCTS bots: easy, medium, and hard. We performed battles between each bot and below are results of their perfomance.

---

### MCS Bot

##### Overall Performance:
| Easy Bot | Medium Bot | Hard Bot | 
| --- | --- | --- | 
| ![image](data/charts/bot1results.png) | ![image](data/charts/bot2results.png) | ![image](data/charts/bot3results.png) |

##### Performance Between MCT Bots:
| Easy vs Random | Medium vs Easy | Hard vs Medium |
| --- | --- | ---|
| ![image](data/charts/battle1vs0.png) |![image](data/charts/battle2vs1.png) | ![image](data/charts/battle3vs2.png) |

---

### Minimax Bot

##### Overall Performance:
| Easy Bot | Medium Bot | Hard Bot | 
| --- | --- | --- | 
| ![image](data/charts/bot4results.png) | ![image](data/charts/bot5results.png) | ![image](data/charts/bot6results.png) |

##### Performance Between Minimax Bots:
| Easy vs Random | Medium vs Easy | Hard vs Medium |
| --- | --- | ---|
| ![image](data/charts/battle4vs0.png) |![image](data/charts/battle5vs4.png) | ![image](data/charts/battle6vs5.png) |

---

### MCTS Bot

##### Overall Performance:
| Easy Bot | Medium Bot | Hard Bot | 
| --- | --- | --- | 
| ![image](data/charts/bot7results.png) | ![image](data/charts/bot8results.png) | ![image](data/charts/bot9results.png) |

##### Performance Between MCTS Bots:
| Easy vs Random | Medium vs Easy | Hard vs Medium |
| --- | --- | ---|
| ![image](data/charts/battle7vs0.png) |![image](data/charts/battle8vs7.png) | ![image](data/charts/battle9vs8.png) |

---

### Ranking of Bot Performance 

![image](data/charts/ranking.png)

---

### More accurate stats of battle between bots

| heatmap of wins | heatmap of loses | heatmap of ties| 
| --- | --- | --- | 
| ![image](data/charts/heatmap_wins.png) | ![image](data/charts/heatmap_loses.png) | ![image](data/charts/heatmap_tie.png) |

---

### Conclusions

As we see, even the easy bots easily beat the random bot.\
Approximately, increasing the bot's level makes it 10 times harder to beat.\
The best algorithm for Super Tic Tac Toe is MCS.