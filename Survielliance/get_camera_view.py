import cv2

# Open default webcam (0 = built-in / USB webcam)
cap = cv2.VideoCapture(0)

# Check if camera opened successfully
if not cap.isOpened():
    print("Error: Cannot open webcam")
    exit()

while True:
    # Read frame from webcam
    ret, frame = cap.read()

    if not ret:
        print("Error: Can't receive frame")
        break

    # Show frame
    cv2.imshow("Webcam Live", frame)

    # Press 'q' to exit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release camera and close windows
cap.release()
cv2.destroyAllWindows()