import numpy as np
import matplotlib.pyplot as plt

# Grid
x = np.linspace(-10, 10, 200)
y = np.linspace(-10, 10, 200)
X, Y = np.meshgrid(x, y)


# Magnetic dipole at center
def magnetic_field(x, y, channel=True):
    r = np.sqrt(x ** 2 + y ** 2) + 1e-6  # Avoid divide-by-zero
    theta = np.arctan2(y, x)

    # Base field (simplified radial dipole)
    Bx = (x / r ** 3)
    By = (y / r ** 3)

    # Apply channel effect
    if channel:
        # U-channel concentrates field vertically
        By *= 2
        Bx *= 0.3
    else:
        # 3-piece plate — more leakage
        Bx *= 1.2
        By *= 1.0

    return Bx, By


# Plot both cases
fig, axs = plt.subplots(1, 2, figsize=(12, 5))
configs = ["U-Channel", "3-Piece Plate"]

for i, channel in enumerate([True, False]):
    Bx, By = magnetic_field(X, Y, channel)
    axs[i].streamplot(X, Y, Bx, By, color=np.log(np.sqrt(Bx ** 2 + By ** 2)), cmap='inferno', density=1.5)
    axs[i].set_title(f"Magnetic Field - {configs[i]}")
    axs[i].set_xlabel("X")
    axs[i].set_ylabel("Y")
    axs[i].set_xlim(-10, 10)
    axs[i].set_ylim(-10, 10)
    axs[i].set_aspect('equal')

plt.tight_layout()
plt.show()
