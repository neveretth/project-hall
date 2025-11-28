import matplotlib.pyplot as plt
import matplotlib.patches as pltch
import numpy as np
import pandas as pd

ds_pdframe = pd.read_csv("../datadump/good.csv")
data_np = ds_pdframe["2"].to_numpy()

divisions = np.size(data_np)

fig = plt.figure()
ax = fig.add_subplot(polar=True)
ax.set_rlabel_position(-36.5)
# ax.set_rticks([])
# ugh
scale_len = np.max([data_np.max(), np.abs(data_np.min())]) * 1.2
ax.set_rmax(scale_len * 2)

for i in range(divisions):
    cang = (np.pi * 2 / divisions) * i # characteristic angle
    if data_np[i] > 0: # polar north (red)
        arrow = pltch.FancyArrowPatch((cang, scale_len), (cang, scale_len + np.abs(data_np[i])),
                                 mutation_scale=10, color=(1.0, 0.0, 0.0))
    else: # polar south (blue)
        arrow = pltch.FancyArrowPatch((cang, scale_len), (cang, scale_len - np.abs(data_np[i])),
                                 mutation_scale=10, color=(0.0, 0.0, 1.0))
        
    # if data_np[i] > 0: # polar north (red)
    #     arrow = pltch.FancyArrowPatch((0, 0), (cang, np.abs(data_np[i])),
    #                              mutation_scale=10, color=(1.0, 0.0, 0.0))
    # else: # polar south (blue)
    #     arrow = pltch.FancyArrowPatch((0, 0), (cang, np.abs(data_np[i])),
    #                              mutation_scale=10, color=(0.0, 0.0, 1.0))
    ax.add_patch(arrow)

plt.show()
