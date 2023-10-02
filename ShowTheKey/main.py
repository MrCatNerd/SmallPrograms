import re
from pynput import keyboard
import tkinter as tk

captured_keys = ""
buffer = ""


def format_key(key):
    # Function to format the pressed key
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
    elif key == keyboard.Key.alt:
        return "⎇"
    elif key == keyboard.Key.backspace:
        return "⌫"
    elif hasattr(key, "char"):
        return key.char
    else:
        return str(key)


def on_press(key):
    global captured_keys, buffer
    key = format_key(key)

    # Define the allowed keys
    allowed_keys = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890;.,/\\`!@#$%^&*()_+=-|?<>'\":"

    # Filter out control keys and space
    if key in allowed_keys or key in ["⌃", "⇧", "⇥", "⎋", "␣", "⌫", "⎇"]:
        # Append the pressed key to the list
        captured_keys += key

        if len(buffer) > 20:
            buffer = buffer[len(buffer) - 20 :]

            captured_keys = captured_keys[len(captured_keys) - 30 :]

        # Update the label with the captured keys
        label.config(text=buffer)

    buffer = compress_string(captured_keys)


def on_release(key):
    if key == keyboard.Key.esc:
        pass  # I don't want to exit


def compress_string(string: str) -> str:  # this script is kinda trash but it works
    allowed_keys = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,/\\`!@#$%^&*()_+:;=-|?<>\"'⌃⇧⇥⎋␣⌫⎇"
    subscripts = "₀₁₂₃₄₅₆₇₈₉"

    pattern = r"([" + allowed_keys + r"])\1*"

    def compress(match):
        char = match.group(1)
        count = len(match.group(0))
        if count > 1:
            count_str = "".join(subscripts[int(digit)] for digit in str(count))
            return char + count_str
        return char

    compressed_string = re.sub(pattern, compress, string)

    return compressed_string


# Create the main window with a narrower width and smaller height
root = tk.Tk()
root.title("Pressed Keys Display")

# Calculate the screen width and height
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

# Set the window width, height, and position
window_height = 80  # Adjusted height
root.geometry(
    f"400x{window_height}+{screen_width - 400}+{screen_height - window_height * 2 - 10}"
)

# Make the window always on top
root.lift()
root.wm_attributes("-topmost", True)

root.wm_attributes("-transparent", "grey")
root.attributes("-alpha", 0.5)
root.overrideredirect(True)

# Set the window background color
root.configure(bg="grey")

# Create a black box (Label widget) with Calibri font
label = tk.Label(root, bg="black", fg="white", font=("Calibri", 20), width=25, height=3)
label.pack(pady=10, padx=10)

# Start listening for key presses
listener = keyboard.Listener(on_press=on_press, on_release=on_release)
listener.start()

# Run the Tkinter main loop
root.mainloop()
