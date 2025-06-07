#pragma once
#include <memory>
#include <string>
#include <vector>

class Instruction {
 public:
  virtual ~Instruction(){};
  virtual std::string toString() const = 0;
};

class Start : public Instruction {
 public:
  std::string toString() const override;
};

class Finish : public Instruction {
 public:
  std::string toString() const override;
};

class Turn : public Instruction {
 public:
  explicit Turn(const std::string& direction);
  std::string toString() const override;

 private:
  std::string direct;
};

class Ringroad : public Instruction {
 public:
  explicit Ringroad(int number);
  std::string toString() const override;

 private:
  int num;
};

class Forward : public Instruction {
 public:
  explicit Forward(int lenght);
  std::string toString() const override;

 private:
  int len;
};