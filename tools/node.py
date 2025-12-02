import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as pltch
import time
import hall

# Proof of concept for the E vector live representation.
hall.init()
hall.init()

ax = plt.figure().add_subplot(projection="3d")

ax.set_xlim([-1,1])
ax.set_ylim([-1,1])
ax.set_zlim([-1,1])
ax.view_init(15, 45)

# x,y,z,i,j,k,
# We can read ijk from an interface with some "hall.read(datavec)"
# Obviously figuring out the scale here is a big concern, as well 
# as how to make these look better, but this is the _general_ idea...
ax.quiver(0, 0, 0, 1, 0, 0, color="#ff0000")
ax.quiver(0, 0, 0, 0, 1, 0, color="#00ff00")
ax.quiver(0, 0, 0, 0, 0, 1, color="#0000ff")

plt.show()

# Okay let's imagine it changing in time...
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
calibrate = np.zeros(4, np.float32)
avg = np.zeros(3, np.float32)

runavg = 8
calavg = 128

for i in range(calavg):
    hall.read(calibrate)
    calibrate = calibrate
    avg = avg + calibrate[:3]

calibrate[:3] = avg / calavg
print(calibrate)
        
while 1:
    avg = np.zeros(3, np.float32)
    # Okay obviously this is not efficient.. but it's fine? maybe...
    # alright yeah I'll confess that this is pretty fucking terrible... but it
    # _does_ sort of do what I want to show is doable.
    ax.cla()
    ax.set_xlim([-1,1])
    ax.set_ylim([-1,1])
    ax.set_zlim([-1,1])
    # ax.view_init(15, 45)
    
    for i in range(runavg):
        hall.read(data)
        data = data - calibrate
        avg = avg + data[:3]
        
    avg = avg / runavg
    
    # print(avg, ": error%: ", np.sqrt(np.inner(avg, avg) + (.3)**2) / np.sqrt(avg.dot(avg)) * 100)
    
    ax.quiver(0, 0, 0, data[0], 0, 0, color="#ff0000") # x
    ax.quiver(0, 0, 0, 0, data[1], 0, color="#00ff00") # y
    ax.quiver(0, 0, 0, 0, 0, data[2], color="#0000ff") # z
    ax.quiver(0, 0, 0, data[0], data[1], data[2], color="#ff8200") # composite
    
    # arrow = pltch.FancyArrowPatch((0,0,0), (data[0],0,0), mutation_scale=10,
    #                               color="#ff0000")
    # ax.add_patch(arrow)
    # arrow = pltch.FancyArrowPatch((0,0,0), (0,data[1],0), mutation_scale=10,
    #                               color="#00ff00")
    # ax.add_patch(arrow)
    # arrow = pltch.FancyArrowPatch((0,0,0), (0,0,data[2]), mutation_scale=10,
    #                               color="#0000ff")
    # ax.add_patch(arrow)
    # arrow = pltch.FancyArrowPatch((0,0,0), (data[0],data[1],data[2]), mutation_scale=10,
    #                               color="#ff8200")
    # ax.add_patch(arrow)

    plt.pause(0.01)
    
hall.end()
