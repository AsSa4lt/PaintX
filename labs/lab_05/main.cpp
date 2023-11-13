#include <iostream>
#include "map"

class Animal {
public:
    std::string  name;
    size_t portion = 0;
    Animal(std::string_view name, size_t portion)
            : name(name), portion(portion) {}
    virtual void speak() = 0;
    void eat(size_t& stock){
        if(stock >= portion) {
            stock -= portion;
        }else{
            throw std::runtime_error("Not enough food");
        }
    }
    virtual ~Animal() = default;
    virtual std::unique_ptr<Animal> clone() const = 0;

};

class Dog: public Animal{
    virtual void speak (){
        std::cout<<name<<": Woof!" << std::endl;
    }

public:
    Dog(std::string_view name, size_t portion)
            : Animal(name, portion) {}
    std::unique_ptr<Animal> clone() const override {
        return std::make_unique<Dog>(*this);
    }
};

class Cat: public Animal{
    virtual void speak (){
        std::cout<<name<<": Meow!" << std::endl;
    }
public:
    Cat(std::string_view name, size_t portion)
    : Animal(name, portion) {}

    std::unique_ptr<Animal> clone() const override {
        return std::make_unique<Cat>(*this);
    }

};

class Fly: public  Animal{
    virtual void speak (){
        std::cout<<name<<": bzzzz!" << std::endl;
    }
public:
    Fly(std::string_view name, size_t portion)
    : Animal(name, portion) {}
    std::unique_ptr<Animal> clone() const override {
        return std::make_unique<Fly>(*this);
    }
};

class Zoo {
public:

    void insert(std::unique_ptr<Animal> p_animal){
        _animal.emplace(p_animal->name, std::move(p_animal));
    }
    void erase(std::string_view name){
        _animal.erase(std::string (name));
    }

    void restock(size_t amount){
        portion+=amount;
    }


    Zoo() = default;
    // Rule of 5 special functions
    ~Zoo() noexcept = default;
    Zoo(const Zoo& zoo) {
        for (const auto& [k, p_a] : zoo._animal) {
            insert((*p_a).clone());
        }
        portion = zoo.portion;
    }

    Zoo& operator=(const Zoo& zoo) {
        if (&zoo == this) return *this;
        return *this = Zoo(zoo);
    };
    Zoo(Zoo&& other) = default;
    Zoo& operator=(Zoo&& other) = default;


    static std::unique_ptr<Animal> spawn_animal(std::string_view  type, std::string_view name, size_t portion){
        if(type == "dog"){
            return std::make_unique<Dog>(name, portion);
        }else if(type == "cat"){
            return std::make_unique<Cat>(name, portion);
        }else if(type == "fly"){
            return std::make_unique<Fly>(name, portion);
        }else{
            throw std::runtime_error("You can't buy this animal");
        }
    }

    void speak() const{
        for(auto& [name, p_animal] : _animal){
            p_animal->speak();
        }
    }

    void feed(){
        for(auto& [name, p_animal] : _animal){
            p_animal->eat(portion);
        }
        std::cout<<portion<<std::endl;
    }
private:
    std::map<std::string, std::unique_ptr<Animal>> _animal;
    size_t portion = 0;

};

int main() {
    Zoo zoo;
    for(std::string  cmd; std::cin>> cmd;){
        if(cmd == "buy"){
            std::string  type;
            std::cin >> type;
            std::string name;
            std::cin >> name;
            size_t portion;
            std::cin>>portion;
            auto animal = zoo.spawn_animal(type, name, portion);
            zoo.insert(std::move(animal));
        }else if(cmd == "sell"){
            std::string name;
            std::cin>>name;
            zoo.erase(name);
        }else if (cmd == "restock"){
            size_t portion;
            std::cin>>portion;
            zoo.restock(portion);
        }else if (cmd == "speak"){
            zoo.speak();
        }else if (cmd == "feed"){
            try{
                zoo.feed();
            }catch (const std::runtime_error e){
                std::cout<<e.what() << std::endl;
            }
        }else{
            throw std::runtime_error("Unsupported command!");
        }
    }
    return 0;
}
