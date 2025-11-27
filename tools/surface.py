import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np

import hall

hall.init()

resolution = 4

# Adjust because of how np grids work (which is that there has to be this
# random extra thing, why, I do not FUCKING KNOW, and I'm too lazy to figure
# it out). Go fuck yourself.
resolution = resolution + 1

fig, ax = plt.subplots(subplot_kw={"projection": "3d"})

theta = np.linspace(0, 2 * np.pi, resolution)
phi = np.linspace(0, .5 * np.pi, resolution)

theta, phi = np.meshgrid(theta, phi)

rho = 1

x = rho * np.sin(phi) * np.cos(theta)
y = rho * np.sin(phi) * np.sin(theta)
z = rho * np.cos(phi)

# effectively [height][wrap][R/G/B]
surface_colors = np.zeros((resolution, resolution, 3))

runavg = 16
calavg = 64

data = np.zeros(4, np.float32)
calibrate = np.zeros(4, np.float32)
avg = np.zeros(4, np.float32)

for i in range(calavg):
    hall.read(calibrate)
    calibrate = calibrate
    avg = avg + calibrate

for i in range(resolution - 1):
    for j in range(resolution - 1):
        # It ain't fast, it ain't pretty, but it works and that's what counts.
        input(f"Ready to read wrap {i} row {j}: <press enter>")
        for k in range(runavg):
            hall.read(data)
            data = data - calibrate
            avg = avg + data
            
        avg = avg / runavg
        
        surface_colors[j][i][0] = avg[0]

# TODO: normalize data to 1
# something like: (1 / surface_colors.max()) * all vals (like an X renorm)

surface_colors = surface_colors - surface_colors.min()
print(surface_colors.max())
print(surface_colors)

surface_colors = (1 / surface_colors.max()) * surface_colors

print(surface_colors)

surface = ax.plot_surface(x, y, z, facecolors=surface_colors, shade=False)

# This adjusts the scale such that it appears spherical.
# ax.set_box_aspect([1, 1, .9]) # Full sphere
ax.set_box_aspect([1, 1, .5]) # Hemi sphere

plt.show()

hall.end()
