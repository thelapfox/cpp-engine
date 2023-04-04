#ifndef ENTITY_
#define ENTITY_


// Entity that 
//
class Entity {
private:
    const unsigned int _id; 
    Entity(unsigned int id) : _id() {}

    friend class EntityFactory;

};

template <typename E> class EntityFactory {
public:
    static E Instantiate() {
        E obj = E(1);
        return obj;
    }
};

#endif  // ENTITY_