#pragma once
#include <vector>

using std::vector;

class Player;
class Territory;

//TODO: Create constructors and destructors
class PlayerStrategy {
    public:
        Player * p;
        virtual vector<Territory*> toDefend() = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual bool issueOrder() = 0;
        PlayerStrategy(Player*);
};

class HumanPlayerStrategy : public PlayerStrategy {
    public:
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
        HumanPlayerStrategy(Player*);
};

class CheaterPlayerStrategy : public PlayerStrategy {
    public:
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
        CheaterPlayerStrategy(Player*);
};

class AggressivePlayerStrategy : public PlayerStrategy {
    public:
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
        AggressivePlayerStrategy(Player*);
};

class BenevolentPlayerStrategy : public PlayerStrategy {
    public:
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
        BenevolentPlayerStrategy(Player*);
};

class NeutralPlayerStrategy : public PlayerStrategy {
    public:
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
        NeutralPlayerStrategy(Player*);
};

