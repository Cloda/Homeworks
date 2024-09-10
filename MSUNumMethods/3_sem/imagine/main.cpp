// не надо пробовать test1 * test2 * test3 тк надо прописывать много условий
// один из параметров является параллелограммов, а второй явл точками
// надо прописывать много условий на принадлежание этой точке к границе
#include "Paralleg.h"

using namespace std;

int main(void){
    Paralleg test1(-3000, 0, 0, 0, 0, -3000);
    Paralleg test2(1000, 0, 0, 0, 0, 1000); 
    Paralleg test3(-5812, 6457, 365, -880, -3488, 5615);
    Paralleg test4(-3956, -8596, -9336, 8103, 2811, 474);
    Paralleg test5(-4538, 502, -4554, -2433, 1112, -5941);
    Paralleg test6(1619, -2280, 8233, -2, -7918, -7145);


    Point prob1 = test1 + test2 + test3 ;
    prob1.DrawLines();

    // test1.DrawLines();
    // test2.DrawLines();
    // test3.DrawLines();



    Point test = test1 + test3 - test2 - test3;
    // Point test6 = test1 + test3;

    test.DrawLines();
    
    return 0;
}