# Train transport system simulation

## C++ project simulating a consumer-producer system combined with transport system, using C++ threads and ncurses library for visualization

### Design summary:
- Trains (threads) are moving on designated tracks and transport cargo. In each wagon there is a **different kind** of cargo. There is also a **capacity limit** for each wagon.
- Tracks have sections suited only for **one train at a time**, all other trains have to wait for the section to clear.
- Train Stations are loading and unloading cargo from the trains. One station can load and unload only **one** type of cargo.
- Each station has a storage with loaded/unloaded cargo, which has a **capacity limit** as well.
- There are threads which **increase** amount of cargo to be loaded and **decrease** amount of cargo to be unloaded.
