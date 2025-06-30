#pragma once

#include <string>

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
