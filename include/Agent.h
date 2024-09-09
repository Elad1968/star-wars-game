#ifndef HW03_AGENT_H
#define HW03_AGENT_H

#include <string>
#include <memory>

class Agent {
public:
    const std::string &getName() const;
protected:
    explicit Agent(std::string name);
    virtual ~Agent();
    virtual void print(std::ostream &stream) const;
    virtual void printType(std::ostream &stream) const = 0;
    friend std::ostream &operator<<(std::ostream &stream, const Agent &agent);
private:
    std::string name;
};

class Shipman : public Agent {
public:
    ~Shipman() override;
    explicit Shipman(const std::string &name);
    void printType(std::ostream &stream) const override;
};

class Commander : public Agent {
public:
    ~Commander() override;
    explicit Commander(const std::string &name);
    void printType(std::ostream &stream) const override;
};

class Admiral : public Agent {
public:
    ~Admiral() override;
    explicit Admiral(const std::string &name);
    void printType(std::ostream &stream) const override;
};

class AgentFactory {
public:
    virtual ~AgentFactory();
    virtual std::shared_ptr<Agent> create(const std::string &name) const = 0;
};

class ShipmanFactory : public AgentFactory {
public:
    ~ShipmanFactory() override;
    std::shared_ptr<Agent> create(const std::string &name) const override;
};

class CommanderFactory : public AgentFactory {
public:
    ~CommanderFactory() override;
    std::shared_ptr<Agent> create(const std::string &name) const override;
};

class AdmiralFactory : public AgentFactory {
public:
    ~AdmiralFactory() override;
    std::shared_ptr<Agent> create(const std::string &name) const override;
};

#endif //HW03_AGENT_H
