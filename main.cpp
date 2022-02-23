#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <memory>
#include <math.h>

using namespace std;

constexpr double PI = 3.14;

class Figure {
  public:
  virtual string Name() const = 0;
  virtual double Perimeter() const = 0;
  virtual double Area() const = 0;
};

class Triangle : public Figure {
  public:
  Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {}

  virtual string Name() const override {
    return "TRIANGLE";
  }

  virtual double Perimeter() const override {
    return a_ + b_ + c_;
  }

  virtual double Area() const override {
    double s = (a_ + b_ + c_) / 2;
    return sqrt(s * (s - a_) * (s - b_) * (s - c_));
  }

  private:
  const double a_;
  const double b_;
  const double c_;
};

class Rect : public Figure {
  public:
  Rect(double w, double h) : w_(w), h_(h) {}

  virtual string Name() const override {
    return "RECT";
  }

  virtual double Perimeter() const override {
    return 2 * w_ + 2 * h_;
  }

  virtual double Area() const override {
    return w_ * h_;
  }

  private:
  const double w_;
  const double h_;
};

class Circle : public Figure {
  public:
  Circle(double r) : r_(r) {}

  virtual string Name() const override {
    return "CIRCLE";
  }

  virtual double Perimeter() const override {
    return 2 * PI * r_;
  }

  virtual double Area() const override {
    return PI * r_ * r_;
  }

  private:
  const double r_;
};

shared_ptr<Figure> CreateFigure(istream &is) {
  string figure_str;
  is >> figure_str;
  if (figure_str == "RECT") {
    double w, h;
    is >> w >> h;
    return make_shared<Rect>(w, h);
  }
  if (figure_str == "TRIANGLE") {
    double a, b, c;
    is >> a >> b >> c;
    return make_shared<Triangle>(a, b, c);
  }
  if (figure_str == "CIRCLE") {
    double r;
    is >> r;
    return make_shared<Circle>(r);
  }
  return shared_ptr<Figure>();  // Should never happen
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      // Пропускаем "лишние" ведущие пробелы.
      // Подробнее об std::ws можно узнать здесь:
      // https://en.cppreference.com/w/cpp/io/manip/ws
      is >> ws;
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}