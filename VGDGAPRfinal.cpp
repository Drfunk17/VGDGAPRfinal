#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>

class Character {
public:
    std::string name;
    std::string ancestry;
    std::string characterClass;
    int strength, dexterity, constitution, wisdom, intelligence, charisma;
    int hitPoints, attack, defense, experience, level, gold;
    std::vector<std::string> inventory;
    std::vector<std::string> equippedItems;

    Character() : experience(0), level(1), hitPoints(0), attack(0), defense(0), gold(10) {}

    void createCharacter() {
        inputName();
        inputAncestry();
        inputClass();
        generateAbilityScores();
        calculateDerivedStats();
        addBasicKit();
        printCharacterInfo();
    }

    void inputName() {
        std::cin.ignore(); 
        do {
            std::cout << "Enter your hero's name (1-10 characters): ";
            std::getline(std::cin, name);
        } while (name.empty() || name.length() > 10);
    }

    void inputAncestry() {
        std::cout << "Choose your ancestry:\n1. Demigod\n2. Nymph\n3. Satyr\n4. Spartan\n5. Oracle\n";
        int choice;
        do {
            std::cout << "Enter choice (1-5): ";
            std::cin >> choice;
        } while (choice < 1 || choice > 5);
        ancestry = getAncestryName(choice);
    }

    void inputClass() {
        std::cout << "Choose your class:\n1. Warrior\n2. Mage\n3. Rogue\n4. Priest\n5. Archer\n";
        int choice;
        do {
            std::cout << "Enter choice (1-5): ";
            std::cin >> choice;
        } while (choice < 1 || choice > 5);
        characterClass = getClassName(choice);
    }

    void generateAbilityScores() {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        strength = getRandomAbilityScore();
        dexterity = getRandomAbilityScore();
        constitution = getRandomAbilityScore();
        wisdom = getRandomAbilityScore();
        intelligence = getRandomAbilityScore();
        charisma = getRandomAbilityScore();
    }

    void calculateDerivedStats() {
        hitPoints = constitution * 2;
        attack = strength + (level * 2);
        defense = dexterity + (level * 2);
    }

    void addBasicKit() {
        inventory = { "Sword", "Shield", "Health Potion", "10 Gold" };
    }

    void printCharacterInfo() const {
        std::cout << "\nCharacter Details:\n";
        std::cout << "Name: " << name << "\nAncestry: " << ancestry << "\nClass: " << characterClass << "\n";
        std::cout << "Strength: " << strength << " Dexterity: " << dexterity << " Constitution: " << constitution << "\n";
        std::cout << "Wisdom: " << wisdom << " Intelligence: " << intelligence << " Charisma: " << charisma << "\n";
        std::cout << "Hit Points: " << hitPoints << " Attack: " << attack << " Defense: " << defense << "\n";
        std::cout << "Gold: " << gold << "\n";
        std::cout << "Inventory: ";
        for (const auto& item : inventory) std::cout << item << " ";
        std::cout << "\nEquipped Items: ";
        for (const auto& item : equippedItems) std::cout << item << " ";
        std::cout << "\n";
    }

    void levelUp() {
        experience += 100; 
        level++;
        std::cout << name << " has leveled up to level " << level << "!\n";
        strength += 1;
        constitution += 1;
        calculateDerivedStats();
    }

    bool isDefeated() const {
        return hitPoints <= 0;
    }

    void equipItem(const std::string& item) {
        equippedItems.push_back(item);
        std::cout << item << " has been equipped.\n";
    }

    void unequipItem(const std::string& item) {
        auto it = std::find(equippedItems.begin(), equippedItems.end(), item);
        if (it != equippedItems.end()) {
            equippedItems.erase(it);
            std::cout << item << " has been unequipped.\n";
        }
        else {
            std::cout << item << " is not equipped.\n";
        }
    }

    void recoverHealth() {
        hitPoints = constitution * 2; 
        std::cout << "You have fully recovered your health!\n";
    }

private:
    std::string getAncestryName(int choice) {
        switch (choice) {
        case 1: return "Demigod";
        case 2: return "Nymph";
        case 3: return "Satyr";
        case 4: return "Spartan";
        case 5: return "Oracle";
        default: return "Unknown";
        }
    }

    std::string getClassName(int choice) {
        switch (choice) {
        case 1: return "Warrior";
        case 2: return "Mage";
        case 3: return "Rogue";
        case 4: return "Priest";
        case 5: return "Archer";
        default: return "Unknown";
        }
    }

    int getRandomAbilityScore() {
        return 8 + (std::rand() % 11);  
    }
};

class Enemy {
public:
    std::string name;
    int hitPoints;
    int attack;
    int defense;
    int experienceReward;
    int goldReward;

    Enemy(std::string enemyName, int hp, int atk, int def, int expReward, int gold)
        : name(enemyName), hitPoints(hp), attack(atk), defense(def), experienceReward(expReward), goldReward(gold) {}

    bool isDefeated() const {
        return hitPoints <= 0;
    }
};

void displayStory() {
    std::cout << "\nWelcome to your mythic adventure! The gods have chosen you for a perilous quest. "
        "Dark forces threaten to plunge the world into chaos, and only a hero of exceptional "
        "strength and valor can prevent it. Prove yourself by defeating mythical creatures like Harpies, "
        "Cyclopes, and Gorgons, solving ancient riddles, and claiming the treasures of the gods.\n";
}

void combat(Character& hero, Enemy& enemy) {
    std::cout << "\nYou encounter a " << enemy.name << "!\n";

    while (!hero.isDefeated() && !enemy.isDefeated()) {
        std::cout << "\nChoose an action:\n1. Attack\n2. Retreat\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "\nYou attack the " << enemy.name << "!\n";
            int damageToEnemy = hero.attack - enemy.defense;
            if (damageToEnemy > 0) {
                enemy.hitPoints -= damageToEnemy;
                std::cout << "You deal " << damageToEnemy << " damage!\n";
            }
            else {
                std::cout << "Your attack was too weak to harm the " << enemy.name << "!\n";
            }

            if (enemy.isDefeated()) {
                std::cout << "You have defeated the " << enemy.name << "!\n";
                hero.experience += enemy.experienceReward;
                hero.gold += enemy.goldReward;
                std::cout << "You gained " << enemy.experienceReward << " experience and " << enemy.goldReward << " gold!\n";
                if (hero.experience >= 100) {
                    hero.levelUp();
                }
                return;
            }

           
            std::cout << enemy.name << " attacks you!\n";
            int damageToHero = enemy.attack - hero.defense;
            if (damageToHero > 0) {
                hero.hitPoints -= damageToHero;
                std::cout << "You take " << damageToHero << " damage! Remaining HP: " << hero.hitPoints << "\n";
            }
            else {
                std::cout << "You defend against the attack!\n";
            }

            if (hero.isDefeated()) {
                std::cout << "You have been defeated!\nGame Over.\n";
                return;
            }
        }
        else if (choice == 2) { 
            std::cout << "You decide to retreat from the battle.\n";
            return;
        }
        else {
            std::cout << "Invalid choice! Please select again.\n";
        }
    }
}

void town(Character& hero) {
    std::cout << "\nWelcome to the town!\n";
    std::cout << "1. Rest and recover health\n2. Visit merchant\n";

    int choice;
    std::cin >> choice;
    if (choice == 1) {
        hero.recoverHealth();
    }
    else if (choice == 2) {
        std::cout << "Welcome to the Merchant's shop!\n";
        std::cout << "Items available for purchase:\n";
        std::cout << "1. Sword Upgrade (50 Gold)\n2. Shield Upgrade (50 Gold)\n3. Health Potion (10 Gold)\n";

        int itemChoice;
        std::cout << "Select an item to purchase (1-3) or 0 to leave: ";
        std::cin >> itemChoice;

        if (itemChoice == 1 && hero.gold >= 50) {
            hero.equipItem("Sword Upgrade");
            hero.gold -= 50;
            std::cout << "You purchased a Sword Upgrade.\n";
        }
        else if (itemChoice == 2 && hero.gold >= 50) {
            hero.equipItem("Shield Upgrade");
            hero.gold -= 50;
            std::cout << "You purchased a Shield Upgrade.\n";
        }
        else if (itemChoice == 3 && hero.gold >= 10) {
            hero.inventory.push_back("Health Potion");
            hero.gold -= 10;
            std::cout << "You purchased a Health Potion.\n";
        }
        else if (itemChoice != 0) {
            std::cout << "You don't have enough gold or entered an invalid option.\n";
        }
    }
    else {
        std::cout << "Invalid choice! Please select again.\n";
    }
}

void gameLoop() {
    Character hero;
    hero.createCharacter();

    displayStory();
    std::cout << "Press Enter to begin your adventure...";
    std::cin.ignore();
    std::cin.get(); 

    int battleCount = 0;

    while (!hero.isDefeated()) {
        std::cout << "\nChoose your action:\n1. Explore\n2. Go to Town\n3. View Inventory\n4. Quit\n";
        int actionChoice;
        std::cin >> actionChoice;

        if (actionChoice == 1) {
           
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            int enemyType = rand() % 3;
            Enemy enemy("Harpies", (enemyType + 1) * 20, (enemyType + 1) * 5, (enemyType + 1), (enemyType + 1) * 20, (enemyType + 1) * 10);
            combat(hero, enemy);
            battleCount++;

           
            if (battleCount >= 3) {
                std::cout << "\nA powerful Cyclops appears! Prepare for the boss fight!\n";
                Enemy boss("Cyclops", 100, 15, 8, 50, 20);
                combat(hero, boss);
                break; 
            }
        }
        else if (actionChoice == 2) {
            town(hero);
        }
        else if (actionChoice == 3) {
            hero.printCharacterInfo();
        }
        else if (actionChoice == 4) {
            std::cout << "Thanks for playing!\n";
            break;
        }
        else {
            std::cout << "Invalid choice! Please select again.\n";
        }
    }

    if (!hero.isDefeated()) {
        std::cout << "Congratulations, " << hero.name << "! You have completed your quest!\n";
    }
}

int main() {
    gameLoop();
    return 0;
}
