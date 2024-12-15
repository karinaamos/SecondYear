#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "BitField.h"

/*
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
*/
int main() {
    BitField bf;
    bf.AddNumber(0);
    bf.AddNumber(1);
    bf.AddNumber(10);
    bf.AddNumber(1023);
    bf.AddNumber(1024);
    bf.AddNumber(0);

    for (size_t i = 0; i < bf.GetNumNumbers(); ++i) {
        std::cout << "Number " << i << ": " << bf.GetNumber(i) << std::endl;
    }

    std::cout << "Total bits: " << bf.GetTotalBits() << std::endl;
    return 0;
}