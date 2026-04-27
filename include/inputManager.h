#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "key.h"
#include <vector>
class inputManager{
public:
    std::vector<Key*> keys;
    void handleKey(int key, int action)
    {
        for(Key* k : keys)
        {
            k->press(action, key);
        }
    }
private:
};
#endif