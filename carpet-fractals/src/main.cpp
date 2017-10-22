#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>
#include <array>


int main() {
    int color_count;
    int iter_count;
    std::cin >> color_count >> iter_count;
    std::cout << color_count << std::endl;
    std::cout << iter_count << std::endl;
    int rules[color_count][9];

    for (int i = 0; i < color_count; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cin >> rules[i][j];
        }
    }

    std::cout << "Got:" << std::endl;

    for (int i = 0; i < color_count; ++i) {
        for (int j = 0; j < 9; ++j) {
            std::cout << rules[i][j];
        }
        std::cout << std::endl;
    }

    std::vector<std::vector<int>> buffers;

    for (int iteration = 0; iteration <= iter_count; ++iteration) {

        int size = pow(9, iteration);
        std::cout << "Iteration " << iteration << " with size " << size << std::endl;

        std::vector<int> new_buffer(size);
        buffers.push_back(new_buffer);

        if (iteration == 0) {
            buffers[0].push_back(0); // Start white

        } else {
            int old_size = pow(9, iteration - 1);
            int old_sqrt_size = pow(3, iteration - 1);

            for (int i = 0; i < old_size; ++i) {
                std::cout << buffers[iteration - 1][i];
                if ((i + 1) % old_sqrt_size == 0) {
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;

            int sqrt_size = pow(3, iteration);

            for (int i = 0; i < old_size; ++i) {
                // for each pixel in old buffer
                int color = buffers[iteration - 1][i];
                for (int k = 0; k < 9; ++k) {
                    int offset = i * old_size;
                    int pos = (k % 3) + ((k / 3) * sqrt_size);
                    std::cout << "offset:" << offset << " pos:" << pos << " old_color:" << color << " rule:" << rules[color][k] << std::endl;
                    buffers[iteration][offset+pos] = rules[color][k];
                }
            }

        }
    }

}