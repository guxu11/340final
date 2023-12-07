#include <iostream>
#include "unittests.h"

int main() {
    std::cout << std::boolalpha << "testNodeDefaultConstructor: " << UNIT_TESTS::testNodeDefaultConstructor() << std::endl;
    std::cout << std::boolalpha << "testNodeConstructor2: " << UNIT_TESTS::testNodeConstructor2() << std::endl;
    std::cout << std::boolalpha << "testNodeConstructor3: " << UNIT_TESTS::testNodeConstructor3() << std::endl;
    std::cout << std::boolalpha << "testGraphDefaultConstructor: " << UNIT_TESTS::testGraphDefaultConstructor() << std::endl;
    std::cout << std::boolalpha << "testGraphCopyConstructor: " << UNIT_TESTS::testGraphCopyConstructor() << std::endl;
    std::cout << std::boolalpha << "testGraphCopyAssignment: " << UNIT_TESTS::testGraphCopyAssignment() << std::endl;
    UNIT_TESTS::testGraphDestructor();
    std::cout << std::boolalpha << "testGraphAddEdge: " << UNIT_TESTS::testGraphAddEdge() << std::endl;
    std::cout << std::boolalpha << "testGraphAddEdges: " << UNIT_TESTS::testGraphAddEdges() << std::endl;
    std::cout << std::boolalpha << "testGraphAddVertex: " << UNIT_TESTS::testGraphAddVertex() << std::endl;
    std::cout << std::boolalpha << "testBFS: " << UNIT_TESTS::testBFS() << std::endl;
    UNIT_TESTS::testBFSTree();
    UNIT_TESTS::testPrintPath();
    return 0;
}
