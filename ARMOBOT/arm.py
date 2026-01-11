import cv2
import mediapipe as mp
import math

cap = cv2.VideoCapture(0)

# MediaPipe Pose
mpPose = mp.solutions.pose
pose = mpPose.Pose()

# MediaPipe Hands
mpHands = mp.solutions.hands
hands = mpHands.Hands(max_num_hands=1)

mpDraw = mp.solutions.drawing_utils


# ----------------- Angle Function -----------------
def calculate_angle(a, b, c):
    ba = (a[0] - b[0], a[1] - b[1])
    bc = (c[0] - b[0], c[1] - b[1])

    dot_product = ba[0]*bc[0] + ba[1]*bc[1]
    mag_ba = math.sqrt(ba[0]**2 + ba[1]**2)
    mag_bc = math.sqrt(bc[0]**2 + bc[1]**2)

    angle = math.degrees(math.acos(dot_product / (mag_ba * mag_bc)))
    return angle


# ----------------- Main Loop -----------------
while True:
    success, frame = cap.read()
    if not success:
        break

    frame = cv2.flip(frame, 1)
    h, w, _ = frame.shape

    imgRGB = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # -------- Pose Detection --------
    pose_results = pose.process(imgRGB)
    if pose_results.pose_landmarks:
        # mpDraw.draw_landmarks(
        #     frame,
        #     pose_results.pose_landmarks,
        #     mpPose.POSE_CONNECTIONS
        # )

        lm = pose_results.pose_landmarks.landmark

        # Left arm landmarks
        shoulder = lm[11]
        elbow = lm[13]
        wrist = lm[15]

        # Convert to pixel coordinates
        s = (int(shoulder.x * w), int(shoulder.y * h))
        e = (int(elbow.x * w), int(elbow.y * h))
        wri = (int(wrist.x * w), int(wrist.y * h))

        # Calculate angle
        angle = calculate_angle(s, e, wri)

        # Draw joints
        # cv2.circle(frame, s, 8, (255, 0, 0), cv2.FILLED)
        # cv2.circle(frame, e, 8, (0, 255, 0), cv2.FILLED)
        # cv2.circle(frame, wri, 8, (0, 0, 255), cv2.FILLED)

        # Show angle
        cv2.putText(frame, f"{int(angle)} deg",
                    (e[0] + 10, e[1] - 10),
                    cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)

        print(f"Left Elbow Angle: {angle:.2f}")

    # -------- Hand Detection (Index Finger Tip) --------
    hand_results = hands.process(imgRGB)
    # if hand_results.multi_hand_landmarks:
    #     handLms = hand_results.multi_hand_landmarks[0]
    #     lm = handLms.landmark[8]  # index fingertip
    #
    #     x, y = int(lm.x * w), int(lm.y * h)
    #     cv2.circle(frame, (x, y), 12, (255, 0, 255), cv2.FILLED)
    #     cv2.putText(frame, "Index Tip", (x + 10, y),
    #                 cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 0, 255), 2)
    #
    #     mpDraw.draw_landmarks(frame, handLms, mpHands.HAND_CONNECTIONS)

    cv2.imshow("Pose + Hand + Elbow Angle", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


cap.release()
cv2.destroyAllWindows()
