#include "layer_descriptor.cpp"
#include "virtual_layer.cpp"

using namespace std;

const size_t a = 10;
const size_t b = 2;

int main()
{
  ld Ld(a, b);
  Ld.Prev.push_back(&Ld);
  Ld.Prev.push_back(&Ld);

  cout << Ld << '\n';

  vl Vl(Ld);
  //cout << '\n' << Vl.Weights.size() << '\n' << Vl.Bias.size() << '\n' << Vl.Error.size() << '\n';
  cout << '\n' << Vl << '\n';
  return 0;
}
