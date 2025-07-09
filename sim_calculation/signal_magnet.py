import numpy as np

# Function to estimate surface Gauss of a rectangular magnet
def estimate_surface_gauss(length_mm, width_mm, thickness_mm, grade="N35"):
    # Surface field ranges based on empirical data (central pole face)
    grade_surface_gauss = {
        "N35": 11700,
        "N42": 13000,
        "N48": 13700,
        "N52": 14500
    }

    if grade not in grade_surface_gauss:
        raise ValueError(f"Unsupported grade: {grade}")

    # Estimate based on proportional thickness effect
    reference_thickness_mm = 5  # base thickness for listed field
    base_gauss = grade_surface_gauss[grade]
    effective_gauss = base_gauss * (thickness_mm / reference_thickness_mm)**0.33  # cube-root scaling

    return effective_gauss

# Input dimensions and grade
length_mm = 40
width_mm = 13.5
thickness_mm = 5
grade = "N35"

# Estimate surface Gauss
surface_gauss = estimate_surface_gauss(length_mm, width_mm, thickness_mm, grade)
