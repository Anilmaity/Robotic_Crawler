Torque Calculation for 360-Degree Pivot Turn of Chain-Driven Robot
Parameters

Robot Dimensions: 
Length: 0.35 m
Width (track-to-track): 0.25 m
Height: 0.1 m
Chain width: 0.05 m per side


Mass: 10 kg
Turn: 360 degrees (2π radians) in 3 seconds
Coefficient of Friction: 0.7 (chains on firm ground)
Drive System: Two motors, each directly attached to a sprocket driving one chain

Calculation

Moment of Inertia (I):[I = \frac{1}{12} m (L^2 + W^2) = \frac{1}{12} \cdot 10 \cdot (0.35^2 + 0.25^2) = 0.1542 , \text{kg·m}^2]

Angular Acceleration (α):[\alpha = \frac{2 \cdot 2\pi}{t^2} = \frac{2 \cdot 6.2832}{3^2} = 1.3963 , \text{rad/s}^2]

Rotational Torque:[\tau_{\text{rot}} = I \cdot \alpha = 0.1542 \cdot 1.3963 = 0.2153 , \text{N·m}]

Frictional Torque:

Normal force per chain: ( F_{N,\text{per chain}} = \frac{m \cdot g}{2} = \frac{10 \cdot 9.81}{2} = 49.05 , \text{N} )
Frictional force per chain: ( F_{\text{friction}} = \mu \cdot F_{N,\text{per chain}} = 0.7 \cdot 49.05 = 34.335 , \text{N} )
Frictional torque per chain: ( \tau_{\text{friction, per chain}} = F_{\text{friction}} \cdot \frac{W}{2} = 34.335 \cdot 0.125 = 4.2919 , \text{N·m} )
Total frictional torque: ( \tau_{\text{friction, total}} = 2 \cdot 4.2919 = 8.5838 , \text{N·m} )


Total Torque:[\tau_{\text{total}} = \tau_{\text{rot}} + \tau_{\text{friction, total}} = 0.2153 + 8.5838 = 8.7991 , \text{N·m}]

Torque per Motor:[\tau_{\text{per motor}} = \frac{\tau_{\text{total}}}{2} = \frac{8.7991}{2} = 4.3996 , \text{N·m}]


Result
Each motor requires approximately 4.4 N·m of torque to achieve a 360-degree pivot turn in 3 seconds.
Notes

Adjust mass, turn time, or friction coefficient if specific values are known.
Motor selection should account for efficiency losses and peak torque requirements.
Terrain variations (e.g., mud, sand) may change the frictional torque significantly.
