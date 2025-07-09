import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm

# Plate parameters
plate_size = 800  # mm
thickness = 8     # mm (not used in 2D surface simulation)
center_temp = 1500  # °C
ambient_temp = 25   # °C
thermal_conductivity = 50  # W/m·K (for mild steel)

# Create a 2D grid (simulation in mm)
n = 200  # grid resolution (more = smoother)
x = np.linspace(-plate_size/2, plate_size/2, n)
y = np.linspace(-plate_size/2, plate_size/2, n)
X, Y = np.meshgrid(x, y)
R = np.sqrt(X**2 + Y**2)

# Simulate temperature drop: assume logarithmic radial decay
r0 = 5  # mm (effective heat source radius)
R[R < r0] = r0  # Avoid division by zero in log
temp_distribution = center_temp - (center_temp - ambient_temp) * np.log(R / r0) / np.log((plate_size/2) / r0)
temp_distribution = np.clip(temp_distribution, ambient_temp, center_temp)  # Clamp values

# Plotting
plt.figure(figsize=(8, 6))
contour = plt.contourf(X, Y, temp_distribution, levels=100, cmap=cm.inferno)
plt.title("Temperature Distribution Across 800x800 mm Mild Steel Plate")
plt.xlabel("X Position (mm)")
plt.ylabel("Y Position (mm)")
cbar = plt.colorbar(contour)
cbar.set_label("Temperature (°C)")
plt.gca().set_aspect('equal')
plt.tight_layout()
plt.show()
