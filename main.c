#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "ball.h"

#define WIDTH 240
#define HEIGHT 320




int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Maze Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

int ball_x = 110;
int ball_y = 160;
int r = 10;
float angle_rad = 0.0f;
float vx = 1.0f;
float vy = 0.0f;

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // 배경 흰색
        SDL_RenderClear(renderer);

        // 예시: 파란 공 그리기
       SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
draw_sleepy_ball_sdl(renderer, ball_x, ball_y, r, angle_rad, vx, vy);


        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // 약 60FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    

    
return 0;

}
