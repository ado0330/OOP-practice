# Card-Game
Element Duel - C++ OOP Card Game
1. Objective
Defeat the computer by reducing its HP (Health Points) from 100 to 0.
2. Element Mechanics
Every card belongs to one of the three elements. Success depends on understanding the Element Circle:
Fire beats Grass
Grass beats Water
Water beats Fire
3. Damage Calculation
Super Effective (Advantage): Deals 2.0x damage.
Not Effective (Disadvantage): Deals 0.5x damage.
Neutral: Deals base damage.
4. Game Flow
Draw Phase: Both you and the computer start with 3 random cards.
Selection Phase: Choose one card from your hand (input index 0, 1, or 2).
Battle Phase: Both cards are revealed. Damage is calculated simultaneously based on element types.
Recovery: After each round, both players draw a new card to maintain a 3-card hand.
Victory: The game ends when someone's HP hits 0.
