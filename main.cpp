#include "Hashtable.h"

int main() {
HashT<int> tab(100);
    fill_the_table(tab);
    tab.add();
    std::cout<<find(tab ,"Xalus");
}

