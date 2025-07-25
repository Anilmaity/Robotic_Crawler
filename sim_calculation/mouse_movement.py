# from pynput import mouse
#
# def on_move(x, y):
#     # 1800 px = 85 mm
#     print(f"Mouse moved to ({x}, {y})")
#
# def on_click(x, y, button, pressed):
#     if pressed:
#         print(f"Mouse clicked at ({x}, {y}) with {button}")
#     else:
#         print(f"Mouse released at ({x}, {y}) with {button}")
#
# def on_scroll(x, y, dx, dy):
#     print(f"Mouse scrolled at ({x}, {y}) with delta ({dx}, {dy})")
#
# # Start listening to mouse events
# with mouse.Listener(
#         on_move=on_move,
#         on_click=on_click,
#         on_scroll=on_scroll) as listener:
#     listener.join()


from pynput import mouse
import time

print("🧪 Step 1: Calibration")
print("Place your mouse on a ruler. Move it exactly 10 cm in a straight line and release the click.")
print("Click to start...")

pixels_moved = 0
start_x = None

def calibrate():
    global pixels_moved, start_x
    def on_move(x, y):
        global pixels_moved, start_x

        if start_x is None:
            start_x = x
        else:
            pixels_moved = abs(x - start_x)

    def on_click(x, y, button, pressed):
        if not pressed:
            return False  # Stop listener

    with mouse.Listener(on_move=on_move, on_click=on_click) as listener:
        listener.join()

    cm_per_pixel = 10 / pixels_moved
    print(f"Calibration done. Pixels for 10 cm: {pixels_moved}")
    print(f"Conversion factor: {cm_per_pixel:.5f} cm per pixel")
    return cm_per_pixel

cm_per_pixel = calibrate()

# Step 2: Measure mat
print("\n📏 Step 2: Measure the mat")
print("Now move the mouse across the mat. Click and release to start and stop the measurement.")

start_pos = None
end_pos = None

def measure():
    global start_pos, end_pos
    def on_click(x, y, button, pressed):
        global start_pos, end_pos
        if pressed:
            start_pos = (x, y)
            print(f"Start position: {start_pos}")
        else:
            end_pos = (x, y)
            print(f"End position: {end_pos}")
            return False  # Stop listener

    with mouse.Listener(on_click=on_click) as listener:
        listener.join()

    dx = abs(end_pos[0] - start_pos[0])
    dy = abs(end_pos[1] - start_pos[1])
    real_dx = dx * cm_per_pixel
    real_dy = dy * cm_per_pixel

    print(f"\n📐 Measured Distance:")
    print(f"X: {real_dx:.2f} cm")
    print(f"Y: {real_dy:.2f} cm")

measure()


