#include <cstdlib>
#include <iostream>
#include "lib_objectsReader/objetsOFF.hpp"

off::Objet offLoader;

int main(void)
{
    std::cout << "Loading sphere.off :" << std::endl;

    offLoader.charge_OFF((const char*) "objects/sphere.off");

    offLoader.affiche();

    return EXIT_SUCCESS;
}
