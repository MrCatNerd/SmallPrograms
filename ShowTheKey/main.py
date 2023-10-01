import tkinter as tk
from pynput import keyboard

captured_keys = ""

def format_key(key):
    if key == keyboard.Key.ctrl_l or key == keyboard.Key.ctrl_r:
        return "⌃"
    elif key == keyboard.Key.shift:
        return "⇧"
    elif key == keyboard.Key.tab:
        return "⇥"
    elif key == keyboard.Key.esc:
        return "⎋"
    elif key == keyboard.Key.space:
        return "␣"
    elif hasattr(key, 'char'):
        return key.char
    else:
        return str(key)

def on_press(key):
    global captured_keys
    key = format_key(key)
    
    # Define the allowed keys (excluding Hebrew)
    allowed_keys = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890'
    
    # Filter out control keys and space
    if key in allowed_keys or key in ["⌃", "⇧", "⇥", "⎋", "␣"]:
        # Append the pressed key to the list
        captured_keys += key
        
        if len(captured_keys) > 20:
            start = len(captured_keys) - 20
            captured_keys = captured_keys[start:]

        # Update the label with the captured keys
        label.config(text=captured_keys)

def on_release(key):
    if key == keyboard.Key.esc:
        # Stop listener
        return False

# Create the main window with a narrower width and smaller height
root = tk.Tk()
root.title("Pressed Keys Display")

# Calculate the screen width and height
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

# Set the window width, height, and position
window_height = 80  # Adjusted height
root.geometry(f"400x{window_height}+{screen_width - 400}+{screen_height - window_height * 2 - 10}")

# Make the window always on top
root.wm_attributes("-topmost", True)

# Set the window background color
root.configure(bg="black")

# Create a black box (Label widget) with Calibri font
label = tk.Label(root, bg="black", fg="white", font=("Calibri", 20), width=25, height=3)
label.pack(pady=10, padx=10)

# Start listening for key presses
listener = keyboard.Listener(on_press=on_press, on_release=on_release)
listener.start()

# Run the Tkinter main loop
root.mainloop()

