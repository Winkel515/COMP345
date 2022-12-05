#pragma once
#include <vector>
using std::vector;
#include <string>
using std::string;

class Player;
class Territory;

//TODO: Create constructors and destructors
class PlayerStrategy {
    public:
        Player * p;
        PlayerStrategy(Player* p);
        virtual vector<Territory*> toDefend() = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual bool issueOrder() = 0;
        virtual string getStrategyString() = 0;
};

class HumanPlayerStrategy : public PlayerStrategy {
    public:
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
        HumanPlayerStrategy(Player*);
        string getStrategyString();
};

class CheaterPlayerStrategy : public PlayerStrategy {
    public:
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
        CheaterPlayerStrategy(Player*);
        string getStrategyString();
};

class AggressivePlayerStrategy : public PlayerStrategy {
    public:
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
        AggressivePlayerStrategy(Player*);
        string getStrategyString();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
    public:
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
        BenevolentPlayerStrategy(Player*);
        string getStrategyString();
};

class NeutralPlayerStrategy : public PlayerStrategy {
    public:
        vector<Territory*> toDefend();
        vector<Territory*> toAttack();
        bool issueOrder();
        NeutralPlayerStrategy(Player*);
        string getStrategyString();
};

