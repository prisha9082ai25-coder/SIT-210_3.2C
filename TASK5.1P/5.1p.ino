import tkinter as tk
from gpiozero import LED

# GPIO PIN CONFIGURATION
# The LED class from gpiozero is used to control the LEDs
# connected to the Raspberry Pi GPIO pins.
#
# GPIO 17 -> Living Room LED
# GPIO 27 -> Bathroom LED
# GPIO 22 -> Closet LED
#
# The LED objects allow us to easily turn each LED ON or OFF
# using the .on() and .off() functions.

# GPIO pins
living_room = LED(17)
bathroom = LED(27)
closet = LED(22)

# FUNCTION: SELECT ROOM

# This function controls which room's LED should be switched ON.
#
# The function receives the selected room as a parameter.
# First, all three LEDs are turned OFF so that only one LED
# can remain ON at a time.
#
# After turning all LEDs OFF, the function checks which room
# was selected and turns the corresponding LED ON.

# Control the LEDs
def select_room(room):
    # Turn all LEDs OFF
    # This ensures that only the selected room's light
    # will be switched ON.
    living_room.off()
    bathroom.off()
    closet.off()

    # Turn ON the selected room
    # Check the value received in the 'room' parameter.
    # If it matches a room name, turn ON that room's LED.
    if room == "Living Room":
        living_room.on()

    elif room == "Bathroom":
        bathroom.on()

    elif room == "Closet":
        closet.on()

# FUNCTION: EXIT APPLICATION

# This function is called when the user presses the Exit button.
#
# Before closing the GUI, all LEDs are turned OFF.
# This is important because it prevents a light from remaining
# ON after the application has been closed.
#
# root.destroy() then closes the Tkinter GUI window.

# Exit the program
def exit_app():
    # Turn OFF all LEDs before closing the application.
    living_room.off()
    bathroom.off()
    closet.off()

    # Destroy/close the main Tkinter window.
    root.destroy()

# CREATE THE MAIN GUI WINDOW

# tk.Tk() creates the main window of the Tkinter application.
#
# The title() function sets the name displayed in the
# application window's title bar.
#
# geometry() defines the size of the GUI window.
# Here, the window is 300 pixels wide and 250 pixels high.

# Create the main GUI window
root = tk.Tk()
root.title("House Light Control")
root.geometry("300x250")

# GUI HEADING

# A Label is used to display text on the GUI.
#
# The heading tells the user the purpose of the application.
#
# font=("Arial", 16) sets the font type to Arial and the
# font size to 16.
#
# pack(pady=15) places the label in the window and adds
# 15 pixels of vertical spacing around it.

# Heading
title = tk.Label(
    root,
    text="House Light Control",
    font=("Arial", 16)
)
title.pack(pady=15)

# ROOM SELECTION VARIABLE

# StringVar() is a Tkinter variable that stores a string value.
#
# It is connected to the radio buttons below.
# When the user selects a radio button, the corresponding
# room name is stored in this variable.
#
# The radio buttons use the same variable so that only one
# room can be selected at a time.

# Radio buttons
room = tk.StringVar()
    
# LIVING ROOM RADIO BUTTON

# This radio button allows the user to select the Living Room.
#
# variable=room connects the button to the StringVar created
# above.
#
# value="Living Room" means that selecting this button stores
# "Living Room" in the room variable.
#
# command=lambda: select_room("Living Room") calls the
# select_room() function when the button is selected.
#
# pack(anchor="w", padx=50) places the button on the left side
# of the GUI with 50 pixels of horizontal spacing.

living_button = tk.Radiobutton(
    root,
    text="Living Room",
    variable=room,
    value="Living Room",
    command=lambda: select_room("Living Room")
)
living_button.pack(anchor="w", padx=50)

# BATHROOM RADIO BUTTON

# This radio button allows the user to select the Bathroom.
#
# When selected, the value "Bathroom" is stored in the
# room variable and select_room("Bathroom") is executed.
#
# The function then turns OFF all LEDs and switches ON
# the Bathroom LED connected to GPIO 27.

bathroom_button = tk.Radiobutton(
    root,
    text="Bathroom",
    variable=room,
    value="Bathroom",
    command=lambda: select_room("Bathroom")
)
bathroom_button.pack(anchor="w", padx=50)

# CLOSET RADIO BUTTON

# This radio button allows the user to select the Closet.
#
# When selected, the value "Closet" is stored in the room
# variable and select_room("Closet") is called.
#
# The function turns OFF the other LEDs and switches ON
# the Closet LED connected to GPIO 22.

closet_button = tk.Radiobutton(
    root,
    text="Closet",
    variable=room,
    value="Closet",
    command=lambda: select_room("Closet")
)
closet_button.pack(anchor="w", padx=50)

# EXIT BUTTON

# This button allows the user to safely close the application.
#
# text="Exit" sets the text displayed on the button.
#
# command=exit_app means that the exit_app() function will
# execute when the user presses the button.
#
# pack(pady=20) places the button in the GUI with vertical
# spacing around it.

# Exit button
exit_button = tk.Button(
    root,
    text="Exit",
    command=exit_app
)
exit_button.pack(pady=20)

# START THE GUI APPLICATION

# mainloop() starts Tkinter's event loop.
#
# The event loop continuously waits for user actions such as:
# - Selecting a room
# - Pressing the Exit button
#
# Without mainloop(), the GUI window would not remain active
# and would close immediately.

# Start the GUI
root.mainloop()
