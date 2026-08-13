# Electronic Dice 🎲

A tiny Arduino project that turns a single 7-segment display and a push button into a digital dice. Press the button, watch it flicker for a second like it's "rolling," and it lands on a number between 1 and 6. That's it, no app, no Bluetooth, just a satisfying little circuit that does one thing well.

I built this as a beginner-friendly project to actually get hands on with digital output pins, debouncing, and pseudo-randomness on a microcontroller.

## What you'll need

- 1x Arduino Uno or Nano
- 1x single-digit 7-segment display (**common cathode**)
- 7x 220Ω–330Ω resistors (one per segment don't skip these, more on that below)
- 1x push button
- Breadboard + jumper wires

## Wiring it up

The idea is simple: each segment of the display (a through g) connects to its own digital pin on the Arduino, and the button connects to another pin plus ground.

| Segment | Arduino Pin |
|---------|-------------|
| a | D2 |
| b | D3 |
| c | D4 |
| d | D5 |
| e | D6 |
| f | D7 |
| g | D8 |
| Common cathode | GND |

Button: one leg to D9, the other leg to GND.

**One thing that'll trip you up if you skip it:** every single segment wire needs its own resistor between the Arduino pin and the display. I learned this the hard way in a simulator — no resistors means no current limiting, and the segments try to pull way more current than they should. In real life that either burns out an LED or fries the pin; in a simulator it just throws up an angry warning icon. Either way 7 resistors, one per segment, no shortcuts.

The button doesn't need an external resistor, since the code uses the Arduino's built-in pull-up resistor instead.

## How it actually works

At a high level, there's nothing fancy going on, the whole thing is basically two ideas stacked together:

**1. A lookup table for what each digit looks like.**
A 7-segment display is just 7 individual LEDs arranged to spell out numbers when you light the right combination. So the code has a little table that says, for each digit 1 through 6, which segments should be on and which should be off. Want a "1"? Light up only the two right-side bars. Want an "8"-ish looking "6"? Light up almost everything except the top-right bar. The code just looks up the row for whatever number it wants to show and flips the pins to match.

**2. A button press that triggers a random pick.**
The button uses the Arduino's internal pull-up, which is a neat trick, it means the pin normally sits at HIGH, and pressing the button physically drags it down to LOW. The code watches for that exact moment of switching from HIGH to LOW (not just "is it being held down"), waits a tiny beat to filter out the electrical jitter that mechanical buttons produce (this is called debouncing), and then triggers the roll.

The roll itself flashes a handful of random digits in quick succession, purely for the visual effect of it "rolling" — before settling on the real, final random number between 1 and 6, which stays lit until you press again.

That's genuinely the whole project. No libraries, no sensors, just pins turning on and off in the right pattern at the right time.

## Uploading the code

1. Open the `.ino` file in the Arduino IDE.
2. Plug in your Arduino, select the right board and port under the Tools menu.
3. Hit upload.
4. Wire it up as described above, power it on, and start pressing the button.

## Things worth trying next

If you want to push this further instead of leaving it as-is:

- Add a second 7-segment display and roll two dice at once for actual board games.
- Swap the flicker effect for something fancier, like a fading brightness sweep.
- Replace the button with a tilt/shake sensor so you physically "shake" the dice to roll.

## Why bother with a project this small

Honestly, projects like this are underrated. It's small enough to finish in an evening, but it touches real skills — reading a datasheet, wiring a circuit that doesn't fry itself, debouncing a mechanical input, and structuring code with lookup tables instead of a wall of if-statements. Those are the exact fundamentals that show up in bigger embedded and hardware-adjacent work later on.

---

Built as a learning project. Feel free to fork it, break it, and make it weirder.
