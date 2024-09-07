# Unreal Async Node Task

This Unreal Engine project demonstrates the use of asynchronous nodes in blueprints to handle communication between two actors. The task involves a listener actor that waits for a boolean variable (`m_TargetBoolean`) in another actor to change, and upon detecting the change, performs a specific action (in this case, destruction of the listener actor).

## Project Overview

### Actors Involved:
1. **Target Actor (Cube)**:
   - Presented by a mesh cube.
   - Holds a boolean variable (`m_TargetBoolean`) that changes based on interaction with another actor (a small pawn).
   - When this boolean is set to `true`, it signals the listening actor to take action.

2. **Listening Actor (Sphere)**:
   - Presented by a sphere mesh.
   - Uses an asynchronous node in its blueprint to wait for the `m_TargetBoolean` to change in the Target Actor.
   - Upon detecting that the boolean is set to `true`, the Listening Actor gets destroyed.

3. **Small Pawn**:
   - A simple actor used to trigger the boolean change in the Target Actor by overlapping with it.

### Use Case:
- The project showcases a practical scenario where the **Small Pawn** overlaps with the **Target Actor** (Cube), causing its `m_TargetBoolean` to change to `true`.
- The **Listening Actor** (Sphere), which is asynchronously waiting for this boolean change, detects the update and subsequently destroys itself.

## Key Features:
- Demonstrates the use of **async nodes** in Unreal Engine Blueprints for non-blocking event handling.
- Simple and intuitive communication between actors based on variable changes.
- Effective use of overlap events to trigger logic within the actors.

## License:
This project is licensed under the Apache 2.0 License. See the `LICENSE` file for more details.

---

This version removes the "How to Run" and "Future Improvements" sections and updates the license to Apache 2.0.