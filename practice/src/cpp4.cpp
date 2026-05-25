#include <iostream>
#include <vector>

class Entity {
protected:
	std::string name;
	float x;
	float y;
public:
	Entity(std::string name, float x, float y): name(name), x(x), y(y) {}
	virtual ~Entity() { std::cout << "Deleting Entity: [" << name << "]" << std::endl; }
	virtual void update() = 0;
	virtual void interact() = 0;
};

class Player : public Entity {
private:
	int ammo;
public:
	Player(std::string name, float x, float y, int ammo) : Entity(name, x, y), ammo(ammo) {}
	~Player() {
		std::cout << "Deleting Player: [" << name << "]" << std::endl;
	}
	void update() override {
		x += 1.0f;
		y += 1.0f;
	}
	void interact() override {
		std::cout << "[" 
			<< name 
			<< "] fires weapon! Ammo remaining: " 
			<< (ammo - 1) << std::endl;
		ammo--;
	}
};

class Enemy : public Entity {
private:
	int attackPower;
public:
	Enemy(std::string name, float x, float y, int attackPower) : Entity(name, x, y), attackPower(attackPower) {}
	~Enemy() {
		std::cout << "Deleting Enemy: [" << name << "]" << std::endl;
	}
	void update() override {
		x -= 1.0f;
	}
	void interact() override {
		std::cout << "[" 
			<< name 
			<< "] attacks for " 
			<< attackPower
			<< " damage!" << std::endl;
	}
};

int main() {
	std::vector<Entity*> entities;
	entities.push_back(new Player("Hero", 0.0f, 0.0f, 10));
	entities.push_back(new Enemy("Goblin", 5.0f, 5.0f, 15));
	entities.push_back(new Enemy("Orc", 10.0f, 10.0f, 20));

	std::cout << "--- Game Engine Start ---" << std::endl;
	for (Entity* entity : entities) {
		entity->update();
		entity->interact();
	}

	std::cout << "\n--- Game Engine Shutdown ---" << std::endl;
	for (Entity* entity : entities) {
		delete entity;
	}

	return 0;
}