#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "key.h"
#include <vector>
class inputManager{
public:
    std::vector<Key*> keys;
    std::vector<bool> keyStates;
    void handleKey(int key, int action)
    {
        for(Key* k : keys)
        {
            if(k->GLFWKey == key)
            {
            //std::cout << "Handling key: " << key << " with action: " << action << std::endl; // Debug output
                k->press(action, key);
                break;
            }
        }
    }
private:
};
#endif