#include <SFML/Window.hpp>
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

            int sqrt_size = pow(3, iteration);

            for (int i = 0; i < old_size; ++i) {
                // for each pixel in old buffer
                int color = buffers[iteration - 1][i];
                for (int k = 0; k < 9; ++k) {
                    int x_offset = (i % old_sqrt_size) * 3;
                    int y_offset = (i / old_sqrt_size) * (size / old_sqrt_size);
                    int offset = x_offset + y_offset;
                    int pos = (k % 3) + ((k / 3) * sqrt_size);
                    buffers[iteration][offset+pos] = rules[color][k];
                }
            }

            // Output as numbers to stdout
            /*for (int i = 0; i < size; ++i) {
                std::cout << buffers[iteration][i];
                if ((i + 1) % sqrt_size == 0) {
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl;*/
        }
    }

    const int last_iter_size = pow(9, iter_count);
    const int window_size_target = 1920;
    const int sqrt_size = pow(3, iter_count);
    const int upscale_factor = window_size_target / sqrt_size;
    const int upscaled_sqrt_size = sqrt_size * upscale_factor;

    sf::RenderWindow window(sf::VideoMode(upscaled_sqrt_size, upscaled_sqrt_size), "Window", sf::Style::Default);

    sf::Texture texture;
    if (!texture.create(sqrt_size, sqrt_size)) {
        std::cout << "Failed to create texture" << std::endl;
        return -1;
    }

    sf::Uint8* pixels = new sf::Uint8[last_iter_size * 4];

    std::cout << "last_iter_size: " << last_iter_size << " upscaled_sqrt_size: " << upscaled_sqrt_size << std::endl;

    // Fill pixels
    for (int i = 0; i < last_iter_size; ++i) {
        int value = buffers[iter_count][i];
        int c = ((color_count - 1) - value) * 255 / (color_count - 1);
        pixels[(i * 4)] = c;
        pixels[(i * 4) + 1] = c;
        pixels[(i * 4) + 2] = c;
        pixels[(i * 4) + 3] = 255; // not transparent
    }

    texture.update(pixels);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sprite.setPosition(sf::Vector2f(0, 0));
    sprite.scale(sf::Vector2f(upscale_factor, upscale_factor));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

}