import matplotlib.pyplot as plt
import numpy as np
from kiwisolver import strength

# Dictionary of simplified grade strength multipliers (relative)
GRADE_STRENGTH = {
    'N35': 1.0,
    'N42': 1.2,
    'N52': 1.5,
    'N52H': 1.4,
    'N50': 1.45,
}

def estimate_pull_force(area_mm2, grade, air_gap_mm, decay_constant=0.8):
    """Estimate pull force (kgf) based on air gap and magnet properties."""
    grade_factor = GRADE_STRENGTH.get(grade.upper(), 1.0)
    return area_mm2 * grade_factor * np.exp(-air_gap_mm / decay_constant) / 1000  # convert to kgf

def generate_graph(length_mm, width_mm, height_mm, grade):
    area_mm2 = length_mm * width_mm
    air_gaps = np.linspace(0, 10, 100)  # 0 to 10mm
    forces = [estimate_pull_force(area_mm2, grade, gap) for gap in air_gaps]

    plt.figure(figsize=(8, 5))
    plt.plot(air_gaps, forces, label=f"Grade {grade}")
    plt.title("Pull Force vs Air Gap")
    plt.xlabel("Air Gap (mm)")
    plt.ylabel("Estimated Pull Force (kgf)")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()

# Example usage
if __name__ == "__main__":
    # Input: size in mm and magnet grade
    # length = float(input("Enter magnet length (mm): "))
    # width = float(input("Enter magnet width (mm): "))
    # height = float(input("Enter magnet height (mm): "))
    # grade = input("Enter magnet grade (e.g., N52, N42, N35): ")

    # length = 200
    # width = 200
    # height = 200
    # grade = 'N52'
    #
    #
    # generate_graph(length, width, height, grade)

    t = [3.5 , 7,9.5,13,16.5,20 ,23.5]
    ag = [0,1,2,3]

    B0 = 17*1.5

    for j in range(len(ag)):
        for i in range(len(t)):
            strength = ((t[i]/(t[i]+ag[j]))*(t[i]/(t[i]+ag[j])))
            total = B0*strength*20
            print(f"thickness {t[i] } mm and air gap {ag[j]} mm {round(strength,3)}" , round(B0*strength) , round(total) , round(total/4))