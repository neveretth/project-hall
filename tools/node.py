import numpy as np
import matplotlib.pyplot as plt
import time
import hall

hall.init()

plt.ion()
fig, ax = plt.subplots()
fig.clf()
ax.cla()
ax = fig.add_subplot(projection="3d")
ax.view_init(15, 45)
ax.set_xlim([-1,1])
ax.set_ylim([-1,1])
ax.set_zlim([-1,1])
plt.show()

data = np.zeros(4, np.float32)

while 1:
    ax.cla()
    ax.set_xlim([-1,1])
    ax.set_ylim([-1,1])
    ax.set_zlim([-1,1])
    # ax.view_init(15, 45)
    
    hall.read(data)
    print(data)
    
    ax.quiver(0, 0, 0, data[0], 0, 0, color="#ff0000") # x
    ax.quiver(0, 0, 0, 0, data[1], 0, color="#00ff00") # y
    ax.quiver(0, 0, 0, 0, 0, data[2], color="#0000ff") # z
    ax.quiver(0, 0, 0, data[0], data[1], data[2], color="#ff8200") # composite
    
    plt.pause(0.01)
    

hall.end()
