#include <iostream>
#include <stdexcept>
#include "hello-triangle-app.hpp"

int main()
{
  using namespace triangle;

  HelloTriangleApp app;

  try
  {
    app.run();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}


