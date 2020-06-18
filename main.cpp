#include "model.hpp"
#include "view.hpp"
#include <thread>

int main(void)
{
    Model model;
    Controller controller(&model);
    View view(&model, &controller);
    view.run();
}