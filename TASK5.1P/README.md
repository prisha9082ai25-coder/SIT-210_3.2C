import tkinter as tk
from gpiozero import LED

# GPIO pins
living_room = LED(17)
bathroom = LED(27)
closet = LED(22)


# Control the LEDs
def select_room(room):
    # Turn all LEDs OFF
    living_room.off()
    bathroom.off()
    closet.off()

    # Turn ON the selected room
    if room == "Living Room":
        living_room.on()

    elif room == "Bathroom":
        bathroom.on()

    elif room == "Closet":
        closet.on()


# Exit the program
def exit_app():
    living_room.off()
    bathroom.off()
    closet.off()
    root.destroy()


# Create the main GUI window
root = tk.Tk()
root.title("House Light Control")
root.geometry("300x250")

# Heading
title = tk.Label(
    root,
    text="House Light Control",
    font=("Arial", 16)
)
title.pack(pady=15)


# Radio buttons
room = tk.StringVar()

living_button = tk.Radiobutton(
    root,
    text="Living Room",
    variable=room,
    value="Living Room",
    command=lambda: select_room("Living Room")
)
living_button.pack(anchor="w", padx=50)

bathroom_button = tk.Radiobutton(
    root,
    text="Bathroom",
    variable=room,
    value="Bathroom",
    command=lambda: select_room("Bathroom")
)
bathroom_button.pack(anchor="w", padx=50)

closet_button = tk.Radiobutton(
    root,
    text="Closet",
    variable=room,
    value="Closet",
    command=lambda: select_room("Closet")
)
closet_button.pack(anchor="w", padx=50)


# Exit button
exit_button = tk.Button(
    root,
    text="Exit",
    command=exit_app
)
exit_button.pack(pady=20)


# Start the GUI
root.mainloop()
