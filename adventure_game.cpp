#include <iostream>
#include <string>

struct Item {
    std::string name;
    std::string description;
    int value;
};

struct Location {
    std::string name;
    std::string description;
    Item item;
    Location* exits[4]; // North, South, East, West
};

int main() {
    // Create items
    Item key = {"Key", "A shiny golden key", 5};
    Item sword = {"Sword", "A sharp sword", 10};

    // Create locations
    Location start = {"Start Room", "You are in a dimly lit room.", key, {nullptr, nullptr, nullptr, nullptr}};
    Location treasureRoom = {"Treasure Room", "You've found a room full of treasures!", sword, {nullptr, nullptr, nullptr, nullptr}};

    // Define connections between locations
    start.exits[2] = &treasureRoom;
    treasureRoom.exits[3] = &start;

    // Initialize player
    Location* currentLocation = &start;
    Item inventory[5];
    int inventorySize = 0;

    // Game loop
    bool gameOver = false;
    while (!gameOver) {
        // Display current location and item
        std::cout << "You are in the " << currentLocation->name << ". " << currentLocation->description << std::endl;
        std::cout << "You see a " << currentLocation->item.name << " here." << std::endl;

        // User interaction
        std::cout << "What would you like to do? (take/examine/go/quit): ";
        std::string action;
        std::cin >> action;

        if (action == "take") {
            // Add the item to the inventory
            if (inventorySize < 5) {
                inventory[inventorySize] = currentLocation->item;
                inventorySize++;
                std::cout << "You picked up the " << currentLocation->item.name << "." << std::endl;
                currentLocation->item = {"", "", 0}; // Remove the item from the location
            } else {
                std::cout << "Your inventory is full!" << std::endl;
            }
        } else if (action == "examine") {
            // Examine the item
            std::cout << "You examine the " << currentLocation->item.name << ". " << currentLocation->item.description << std::endl;
        } else if (action == "go") {
            // Move to a neighboring location
            std::cout << "Where do you want to go? (north/south/east/west): ";
            std::string direction;
            std::cin >> direction;

            if (direction == "north" && currentLocation->exits[0] != nullptr) {
                currentLocation = currentLocation->exits[0];
            } else if (direction == "south" && currentLocation->exits[1] != nullptr) {
                currentLocation = currentLocation->exits[1];
            } else if (direction == "east" && currentLocation->exits[2] != nullptr) {
                currentLocation = currentLocation->exits[2];
            } else if (direction == "west" && currentLocation->exits[3] != nullptr) {
                currentLocation = currentLocation->exits[3];
            } else {
                std::cout << "You cannot go that way." << std::endl;
            }
        } else if (action == "quit") {
            gameOver = true;
        } else {
            std::cout << "Invalid action." << std::endl;
        }
    }

    std::cout << "Game over. Thanks for playing!" << std::endl;
    return 0;
}
