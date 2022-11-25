#pragma once
#include <vector>

using std::vector;

class Player;
class Territory;

class PlayerStrategy {
    public:
        Player * p;
        PlayerStrategy(Player* p);
        virtual vector<Territory*> toDefend() = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual bool issueOrder() = 0;
};

class HumanPlayerStrategy : public PlayerStrategy {
    public:
        Player * p; //TODO: remove?
        HumanPlayerStrategy(Player* p);
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
};

class CheaterPlayerStrategy : public PlayerStrategy {
    public:
        Player * p;
        CheaterPlayerStrategy(Player* p);
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
};

class AggressivePlayerStrategy : public PlayerStrategy {
    public:
        Player * p;
        AggressivePlayerStrategy(Player* p);
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
    public:
        Player * p;
        BenevolentPlayerStrategy(Player* p);
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
};

class NeutralPlayerStrategy : public PlayerStrategy {
    public:
        Player * p;
        NeutralPlayerStrategy(Player* p);
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
};

