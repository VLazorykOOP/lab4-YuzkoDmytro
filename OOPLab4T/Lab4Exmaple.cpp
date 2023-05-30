#include "Lab4Exmaple.h"
#include "ComplexMatrix.h"
#include "ComplexVector.h"
#include "MyAssoc.h"
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>

/* Задача 1.1.
Створити тип даних - клас VectorInt (вектор цілих чисел), який має вказівник на
int, число елементів size і змінну стану codeError. У класі визначити

o конструктор без параметрів( виділяє місце для одного елемента та інінціалізує
його в нуль);
o конструктор з одним параметром - розмір вектора( виділяє місце та інінціалізує
масив значенням нуль);
o конструктор із двома параметрами - розмір вектора та значення
ініціалізації(виділяє місце (значення перший аргумент) та інінціалізує
значенням другого аргументу) ;
o конструктор копіювання;
o деструктор звільняє пам'ять;
o перевантаження операцій (операції перевантажувати через функції класу або
дружні функції, якщо не вказано яким чином це робити):
• унарних префіксних та постфіксних ++ та --: одночасно збільшує
(зменшує) значення елементів масиву на 1;
• унарної логічної ! (заперечення): повертає значення true, якщо
елементи якщо size не дорівнює – нулю, інакше false;
• унарної побітової ~ (заперечення): повертає побітове заперечення для
всіх елементів масиву класу вектор;
• унарний арифметичний - (мінус) : повертає всі елементи масиву
класу вектор з протилежним знаком;
• присвоєння =: копіює вектор(перевантажити через функцію класу);
• присвоєння з (перевантажити через функцію класу)
o += - додаванням векторів;
o -= - відніманням векторів;
o *= - множення, вектора на число типу int;
o /= - ділення, вектора на число типу int;
o %= - остача від ділення, вектора на число типу int;
o |= -побітове додаванням векторів;
o ^= - побітове додавання за модулем 2 векторів;
o &= - побітове по-елементне множення векторів;
• арифметичних бінарні:
o + - додавання векторів;
o – - віднімання векторів;
o * - множення, вектора на число типу int;
o / - ділення, вектора на число типу int;
o % - остача від ділення, вектора на число типу int;
• побітові бінарні
o | - побітове додавання векторів;
o ^ - побітове додавання за модулем 2 векторів;
o & - побітове по-елементне множення векторів;
• побітові операції зсувів, як дружні операції введення та виведення
вектора у потік (перевантажувати через дружні функції)
o введення >> (побітовий зсув право) ;
o введення << (побітовий зсув ліво);
• рівності == та нерівності!= , функція-операція виконує певні дії над
кожною парою елементів векторів за індексом;
• операцію індексації [] – функцію, яка звертається до елементу
масиву за індексом, якщо індекс невірний функція вказує на останній
елемент масиву та встановлює код помилки у змінну codeError;
• розподілу пам’яті new та delete;
• виклику функції ();
• порівняння (функція-операція виконує певні дії над кожною парою
елементів векторів за індексом), які повертають true або false:
o > (більше) для двох векторів;
o >= (більше рівне) для двох векторів;
o < (менше) для двох векторів;
o <=(менше рівне) для двох векторів.
У змінну стани встановлювати код помилки, коли не вистачає пам'яті, виходить за
межі масиву. Передбачити можливість підрахунку числа об'єктів даного типу.
Перевірити роботу цього класу.  */

enum codeError { None, BAD_INIT, Out_Of_Range, BAD_VALUE };

class VectorInt {
  int *point;
  int size;
  int codeError = None;

public:
  VectorInt() {
    size = 1;
    point = new int(size);
    point[0] = 0;
  }
  VectorInt(int len) {
    size = len;
    point = new int(size);
    for (int i = 0; i < size; i++) {
      point[i] = 0;
    }
  }

  VectorInt(int len, int value) {
    size = len;
    point = new int(size);
    for (int i = 0; i < size; i++) {
      point[i] = value;
    }
  }

  VectorInt(VectorInt &v) {
    size = v.size;
    if (v.point == nullptr) {
      codeError = BAD_INIT;
    }
    point = new int(v.size);
    for (int i = 0; i < v.size; i++) {
      point[i] = v.point[i];
    };
    codeError = v.codeError;
  }

  ~VectorInt() { delete[] point; }

  void print() {
    for (int i = 0; i < size; i++) {
      cout << point[i] << " ";
    }
    cout << endl;
  };

  VectorInt operator++() {
    for (int i = 0; i < size; i++) {
      point[i] = point[i] + 1;
    };
    return *this;
  };

  VectorInt operator--() {
    for (int i = 0; i < size; i++) {
      point[i] = point[i] - 1;
    };
    return *this;
  };

  VectorInt &operator++(int) {
    for (int i = 0; i < size; i++) {
      point[i] = point[i] + 1;
    };
    return *this;
  };

  VectorInt &operator--(int) {
    for (int i = 0; i < size; i++) {
      point[i] = point[i] - 1;
    };
    return *this;
  };

  bool operator!() {
    if (size) {
      return true;
    }
    return false;
  }

  VectorInt operator~() {
    VectorInt result(*this);
    for (int i = 0; i < size; i++) {
      result.point[i] = ~point[i];
    };
    return result;
  }

  VectorInt operator-() {
    VectorInt result(*this);
    for (int i = 0; i < size; i++) {
      result.point[i] = -point[i];
    };
    return result;
  }

  VectorInt &operator=(const VectorInt &v) {
    if (this != &v) {
      delete[] point;
      point = new int[v.size];
      for (int i = 0; i < v.size; i++) {
        point[i] = v.point[i];
      }
      size = v.size;
      codeError = v.codeError;
    }
    return *this;
  }

  VectorInt &operator+=(const VectorInt &v) {
    if (size != v.size) {
      codeError = Out_Of_Range;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] += v.point[i];
    }
    return *this;
  }

  VectorInt &operator-=(const VectorInt &v) {
    if (size != v.size) {
  codeError = Out_Of_Range;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] -= v.point[i];
    }
    return *this;
  }

  VectorInt &operator*=(int value) {
    for (int i = 0; i < size; i++) {
      point[i] *= value;
    }
    return *this;
  }

  VectorInt &operator/=(int value) {
    if (value == 0) {
      codeError = BAD_VALUE;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] /= value;
    }
    return *this;
  }

  VectorInt &operator%=(int value) {
    if (value == 0) {
      codeError = BAD_VALUE;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] %= value;
    }
    return *this;
  }

  VectorInt &operator|=(const VectorInt &v) {
    if (size != v.size) {
      codeError = Out_Of_Range;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] |= v.point[i];
    }
    return *this;
  }

  VectorInt &operator^=(const VectorInt &v) {
    if (size != v.size) {
      codeError = Out_Of_Range;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] ^= v.point[i];
    }
    return *this;
  }

  VectorInt &operator&=(const VectorInt &v) {
    if (size != v.size) {
      codeError = Out_Of_Range;
      return *this;
    }
    for (int i = 0; i < size; i++) {
      point[i] &= v.point[i];
    }
    return *this;
  }

  VectorInt operator+(const VectorInt &v) {
    if (size != v.size) {
      VectorInt result;
      result.codeError = Out_Of_Range;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] + v.point[i];
    }
    return result;
  }
  VectorInt operator-(const VectorInt &v) {
    if (size != v.size) {
      VectorInt result;
      result.codeError = Out_Of_Range;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] - v.point[i];
    }
    return result;
  }
  VectorInt operator*(int n) {
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] * n;
    }
    return result;
  }
  VectorInt operator/(int n) {
    if (n == 0) {
      VectorInt result;
      result.codeError = BAD_VALUE;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] / n;
    }
    return result;
  }
  VectorInt operator%(int n) const {
    if (n == 0) {
      VectorInt result;
      result.codeError = BAD_VALUE;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] %= n;
    }
    return result;
  }

  VectorInt operator|(const VectorInt &v) {
    if (size != v.size) {
      VectorInt result;
      result.codeError = Out_Of_Range;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] | v.point[i];
    }
    return result;
  }

  VectorInt operator^(const VectorInt &v) {
    if (size != v.size) {
      VectorInt result;
      result.codeError = Out_Of_Range;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] ^ v.point[i];
    }
    return result;
  }

  VectorInt operator&(const VectorInt &v) {
    if (size != v.size) {
      VectorInt result;
      result.codeError = Out_Of_Range;
      return result;
    }
    VectorInt result(size);
    for (int i = 0; i < size; i++) {
      result.point[i] = point[i] & v.point[i];
    }
    return result;
  }

  friend istream &operator>>(istream &input, VectorInt &vector);
  friend ostream &operator<<(ostream &output, const VectorInt &vector);

  bool operator==(const VectorInt &v) {
    if (size != v.size) {
      return false;
    }
    for (int i = 0; i < size; i++) {
      if (point[i] != v.point[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const VectorInt &v) {
    if (size != v.size) {
      return true;
    }
    for (int i = 0; i < size; i++) {
      if (point[i] != v.point[i]) {
        return true;
      }
    }
    return false;
  }

  int operator[](int index) {
    if (index < 0 || index > size) {
      index = size;
    }

    return point[index];
  }

  void *operator new(size_t size_new) {
    void *v = malloc(size_new);
    return v;
  }

  void operator delete(void *v) { free(v); }

  void operator()() { cout << "Function work"; }

  bool operator>(const VectorInt &v) {
    double length1 = 0, length2 = 0;
    for (int i = 0; i < size; i++) {
      length1 += point[i] * point[i];
    }

    length1 = sqrt(length1);

    for (int i = 0; i < v.size; i++) {
      length2 += v.point[i] * v.point[i];
    }

    length2 = sqrt(length2);

    if (length1 > length2) {
      return true;
    }
    return false;
  }

  bool operator>=(const VectorInt &v) {
    double length1 = 0, length2 = 0;
    for (int i = 0; i < size; i++) {
      length1 += point[i] * point[i];
    }

    length1 = sqrt(length1);

    for (int i = 0; i < v.size; i++) {
      length2 += v.point[i] * v.point[i];
    }

    length2 = sqrt(length2);

    if (length1 >= length2) {
      return true;
    }
    return false;
  }

  bool operator<(const VectorInt &v) {
    double length1 = 0, length2 = 0;
    for (int i = 0; i < size; i++) {
      length1 += point[i] * point[i];
    }

    length1 = sqrt(length1);

    for (int i = 0; i < v.size; i++) {
      length2 += v.point[i] * v.point[i];
    }

    length2 = sqrt(length2);

    if (length1 < length2) {
      return true;
    }
    return false;
  }

  bool operator<=(const VectorInt &v) {
    double length1 = 0, length2 = 0;
    for (int i = 0; i < size; i++) {
      length1 += point[i] * point[i];
    }

    length1 = sqrt(length1);

    for (int i = 0; i < v.size; i++) {
      length2 += v.point[i] * v.point[i];
    }

    length2 = sqrt(length2);

    if (length1 <= length2) {
      return true;
    }
    return false;
  }
};

istream &operator>>(istream &input, VectorInt &v) {
  for (int i = 0; i < v.size; i++) {
    input >> v.point[i];
  }
  return input;
}

ostream &operator<<(ostream &output, const VectorInt &v) {
  for (int i = 0; i < v.size; i++) {
    output << v.point[i] << ' ';
  }
  output << endl;
  return output;
}

int exersice1() {
  int length, value;
  cout << "Enter the length and value of vector:";
  cin >> length;
  cin >> value;
  VectorInt v1(length, value);
  cout << "Entered vector" << endl;
  cout << v1;
  cout << "vector++" << endl;
  v1++;
  cout << v1;
  cout << "vector--" << endl;
  v1--;
  cout << v1;
  cout << "Vector2, legth 4 value 2" << endl;
  VectorInt v2(4, 2);
  cout << v2;
  cout << "Vector1 + Vector2" << endl;
  cout << (v1 + v2) << endl;
  cout << "Vector1 - Vector2" << endl;
  cout << (v1 - v2) << endl;
  cout << "Entered vector < Vector2" << endl;
  cout << (v1 < v2) << endl;
  cout << "Entered vector > Vector2" << endl;
  cout << (v1 > v2) << endl;
  cout << "Entered vector <= Vector2" << endl;
  cout << (v1 <= v2) << endl;
  cout << "Entered vector >= Vector2" << endl;
  cout << (v1 >= v2) << endl;
  return 0;
};

/*
Побудувати асоційований клас збереження двох сутностей. В завданні створити
клас, який представляє собою асоціативний масив між двома сутностями. Написати
функцію створення набору асоціативних сутностей. Перевантажити операцію
індексації [] – функцію, яка звертається до об’єкта класу, за однією сутністю,
якщо індекс, повертає асоціативну сутність, альтернативні звернення через
перевантаження операції виклику функції(); перевантажити дружні операції
введення та виведення.
Задача 2.1. Цілих чисел від 1 до 100 та цілі прописом. Наприклад, 1 та
один, 10 та десять.
*/

class Record {
public:
  int key;
  string value;
  Record() {};
  Record(int k, string v) {
    key = k;
    value = v;
  }
};

class Numbers {
public:
  vector<Record> records;
  Numbers(vector<Record> values) { records = values; }

  string operator[](int key) {
    for (auto r : records) {
      if (r.key == key) {
        return r.value;
      }
    }
    return "Not found";
  };
  void operator()() { cout << "Function work"; };

  friend istream &operator>>(istream &input, Numbers &number);
  friend ostream &operator<<(ostream &output, const Numbers &number);
};

istream &operator>>(istream &input, Numbers &n) {
  int key;
  string value;
  input >> key >> value;
  n.records.push_back(Record(key, value));
  return input;
}

ostream &operator<<(ostream &output, const Numbers &n) {
  for (auto r : n.records) {
    output << r.key << " " << r.value << '\t';
  }
  output << endl;
  return output;
}

void exersice2() {
  int find_element;
  ifstream inputFile;
  inputFile.open("numbers.txt");
  vector<Record> records;
  Numbers numbers(records);
  for (int i = 0; i< 100; i++) {
    inputFile >> numbers;
  }
  cout << "Enter the number we need found:";
  cin >> find_element;
  cout << numbers[find_element] << endl;
};
