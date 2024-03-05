namespace targets {
// TODO: Insert the code for the alien class here
class Alien{
private: 
    int health{3};
public: 
    int x_coordinate{0};
    int y_coordinate{0};

    Alien(int x, int y)
        : x_coordinate{x}, y_coordinate{y}
        {
            
        }
    int get_health() const{ return health;}
    bool hit() { 
        --health;
        return health;
    }
    bool is_alive() const {
        if (health <= 0 || health == 0)
            return false;
        else 
            return true;
    }
    bool teleport(int x_new, int y_new){
        x_coordinate = x_new;
        y_coordinate = y_new;
        return true;
    }
    bool collision_detection(const Alien& alien){
        return (x_coordinate == alien.x_coordinate && y_coordinate == alien.y_coordinate);
    }
};
}  // namespace targets