#include "ball.h"
#include <math.h>
#include <stdint.h>
#define BALL_BASE_COLOR 0xFCA0

uint8_t r = ((BALL_BASE_COLOR >> 11) & 0x1F) << 3;
uint8_t g = ((BALL_BASE_COLOR >> 5) & 0x3F) << 2;
uint8_t b = (BALL_BASE_COLOR & 0x1F) << 3;


void draw_sleepy_ball_sdl(SDL_Renderer* renderer, int cx, int cy, int r, float angle_rad, float vx, float vy) {
    float light_theta = angle_rad;
    float light_x = cosf(light_theta) * 0.3f;
    float light_y = sinf(light_theta) * 0.3f;
    float light_z = 1.0f;

    float move_dir = atan2f(vy, vx);
    float front_x = cosf(move_dir);
    float front_y = sinf(move_dir);
    float front_z = 0.0f;

    for (int dy = -r; dy <= r; dy++) {
        for (int dx = -r; dx <= r; dx++) {
            if (dx * dx + dy * dy > r * r) continue;

            float nx = dx / (float)r;
            float ny = dy / (float)r;
            float nz = sqrtf(fmaxf(0.0f, 1.0f - nx * nx - ny * ny));

            float dot = nx * light_x + ny * light_y + nz * light_z;
            float brightness = 0.4f + 0.6f * fmaxf(dot, 0.0f);

            uint8_t r_col = (uint8_t)(BALL_BASE_R * brightness);
            uint8_t g_col = (uint8_t)(BALL_BASE_G * brightness);
            uint8_t b_col = (uint8_t)(BALL_BASE_B * brightness);

            SDL_SetRenderDrawColor(renderer, r_col, g_col, b_col, 255);
            SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
        }
    }

    // 눈 (∪ ∪)
    for (int i = -r / 4; i <= r / 4; i++) {
        float dx = i / (float)r;
        float dy = -0.25f;
        float dz = sqrtf(fmaxf(0.0f, 1.0f - dx * dx - dy * dy));
        float dot = dx * front_x + dy * front_y + dz * front_z;

        if (dot > 0.0f) {
            int lx = cx + (int)(dx * r) - r / 4;
            int rx = cx + (int)(dx * r) + r / 4;
            int y_pos = cy + (int)(dy * r);

            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
            SDL_RenderDrawPoint(renderer, lx, y_pos);
            SDL_RenderDrawPoint(renderer, rx, y_pos);
        }
    }
}
