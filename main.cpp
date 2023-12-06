#include <iostream>
#include <vector>
#include <unordered_map>
#include <type_traits>

using namespace std;

template <typename T1, typename T2>
class IHandler
{
public:
  virtual T2 handle(T1 argument) { return T2(); }
};

class GuitarHandler : public IHandler<int, int>
{
public:
  int handle(int arg) override
  {
    return arg * arg;
  }
};

class Mediator
{
private:
  unordered_map<string, void *> values;

  template <typename T1, typename T2>
  bool exists() { return values.count(typeid(IHandler<T1, T2>).name()); }

public:
  template <typename T1, typename T2>
  void addHandler(IHandler<T1, T2> *value)
  {
    values[typeid(IHandler<T1, T2>).name()] = value;
  }

  template <typename T1, typename T2>
  T2 handle(T1 input)
  {
    if (!exists<T1, T2>())
      throw runtime_error("Requested not existing type of handler!");
    return static_cast<IHandler<T1, T2> *>(values[typeid(IHandler<T1, T2>).name()])->handle(input);
  }
};

int main()
{
  Mediator _mediator;
  _mediator.addHandler(new GuitarHandler());
  // int res = _mediator.handle<int <-- input, int <-- output>(3 <-- input);
  int res = _mediator.handle<int, int>(3);
  cout << "Result: " << res << endl;

  cout << "\nworks\n";
  return 0;
}