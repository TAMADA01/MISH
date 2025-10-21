#ifndef TEST_SRC_FIGURES_ABSTRACT_FIGURE_H_
#define TEST_SRC_FIGURES_ABSTRACT_FIGURE_H_

#include <string>

class Figure {
   public:
    Figure(const std::string &name){
      this->name = name;
    }

    virtual std::string Info() = 0;
    virtual double getPerimeter() = 0;
    virtual double getArea() = 0;
    std::string getName(){
      return name;
    };
 private:
  std::string name;
};

#endif //TEST_SRC_FIGURES_ABSTRACT_FIGURE_H_
