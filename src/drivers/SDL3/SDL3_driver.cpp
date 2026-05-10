#include "SDL3_driver.h"

#ifdef SDL3_DRIVER

SDL_Color get_colour(RGB colour)
{
    SDL_Color c = {colour.get_red(), colour.get_green(), colour.get_blue(), 255};

    return c;
}

SDL3_driver::SDL3_driver(uint16_t window_width, uint16_t window_height)
{
    optimize_rendering = false;
    width = window_width;
    height = window_height;

    SDL_SetAppMetadata("Embedded GUI Framework", "1.0", "embedded_gui_framework");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return;
    }

    if (!TTF_Init())
    {
        SDL_Log("TTF_Init failed");
        return;
    }

    if (!SDL_CreateWindowAndRenderer("GUI", window_width, window_height, SDL_WINDOW_OPENGL, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return;
    }

    SDL_SetRenderColorScale(renderer, 1.0f);

    font = TTF_OpenFont("src/font.ttf", 128);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_SetRenderVSync(renderer, 1);
}

SDL3_driver::~SDL3_driver()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void SDL3_driver::get_text_bounds(const char *text, uint16_t *width, uint16_t *height)
{
    int w, h;

    if (text == NULL)
    {
        return;
    }

    TTF_GetStringSize(font, text, 0, &w, &h);

    *width = (uint16_t)w;
    *height = (uint16_t)h;
}

uint16_t SDL3_driver::center_text_vertical(char *str, uint16_t container_h, uint16_t container_y)
{
    uint16_t text_w, text_h;

    if (str == NULL)
    {
        return 0;
    }

    get_text_bounds(str, &text_w, &text_h);

    return container_y + (container_h / 2) - (text_h / 2);
}

uint16_t SDL3_driver::center_text_horizontal(char *str, uint16_t container_w, uint16_t container_x)
{
    uint16_t text_w, text_h;

    if (str == NULL)
    {
        return 0;
    }

    get_text_bounds(str, &text_w, &text_h);

    return container_x + (container_w / 2) - (text_w / 2);
}

int16_t SDL3_driver::get_display_width()
{
    return width;
}

int16_t SDL3_driver::get_display_height()
{
    return height;
}

void SDL3_driver::draw_text(int16_t x, int16_t y, const char *text, uint8_t size, RGB colour)
{
    SDL_FRect src;
    SDL_FRect dst;
    uint16_t text_width, text_height;

    SDL_Color text_colour = get_colour(colour);
    float scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

    TTF_SetFontSize(font, size * 8 * scale);

    get_text_bounds(text, &text_width, &text_height);

    SDL_Surface *surface = TTF_RenderText_Blended(
        font,
        text, strlen(text), text_colour);

    SDL_Texture *font_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    SDL_SetTextureScaleMode(font_texture, SDL_SCALEMODE_NEAREST);

    src.w = text_width;
    src.h = text_height;
    src.x = 0;
    src.y = 0;

    dst.x = x;
    dst.y = y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderTexture(renderer, font_texture, &src, &dst);
}

void SDL3_driver::draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, RGB colour)
{
    SDL_SetRenderDrawColor(renderer, colour.get_red(), colour.get_green(), colour.get_blue(), 255);

    SDL_RenderLine(renderer, x1, y1, x2, y2);
}

void SDL3_driver::draw_filled_circle(int16_t x, int16_t y, int16_t r, RGB colour)
{
    SDL_SetRenderDrawColor(renderer, colour.get_red(), colour.get_green(), colour.get_blue(), 255);

    for (int dy = -r; dy <= r; dy++)
    {
        int dx = (int)SDL_sqrt((double)(r * r - dy * dy));
        SDL_RenderLine(renderer, x - dx, y + dy, x + dx, y + dy);
    }
}

void SDL3_driver::draw_filled_round_rect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t border_radius, RGB colour)
{
    SDL_SetRenderDrawColor(renderer, colour.get_red(), colour.get_green(), colour.get_blue(), 255);

    for (int dy = 0; dy < height; dy++)
    {
        int row = y + dy;
        int x0 = x, x1 = x + width;

        if (dy < border_radius)
        {
            int reach = (int)SDL_sqrt((double)(border_radius * border_radius - (border_radius - dy) * (border_radius - dy)));
            x0 = x + border_radius - reach;
            x1 = x + width - border_radius + reach;
        }
        else if (dy >= height - border_radius)
        {
            int reach = (int)SDL_sqrt((double)(border_radius * border_radius - (border_radius - (height - 1 - dy)) * (border_radius - (height - 1 - dy))));
            x0 = x + border_radius - reach;
            x1 = x + width - border_radius + reach;
        }

        SDL_RenderLine(renderer, x0, row, x1, row);
    }
}

void SDL3_driver::draw_filled_rect(int16_t x, int16_t y, int16_t width, int16_t height, RGB colour)
{
    SDL_FRect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, colour.get_red(), colour.get_green(), colour.get_blue(), 255);
    SDL_RenderFillRect(renderer, &rect);
}

void SDL3_driver::draw_filled_triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, RGB colour)
{
    SDL_SetRenderDrawColor(renderer, colour.get_red(), colour.get_green(), colour.get_blue(), 255);

    if (y1 > y2)
    {
        int tx = x1, ty = y1;
        x1 = x2;
        y1 = y2;
        x2 = tx;
        y2 = ty;
    }
    if (y1 > y3)
    {
        int tx = x1, ty = y1;
        x1 = x3;
        y1 = y3;
        x3 = tx;
        y3 = ty;
    }
    if (y2 > y3)
    {
        int tx = x2, ty = y2;
        x2 = x3;
        y2 = y3;
        x3 = tx;
        y3 = ty;
    }

    int total_h = y3 - y1;
    if (total_h == 0)
        return;

    for (int dy = 0; dy <= total_h; dy++)
    {
        bool upper_half = dy < (y2 - y1) && (y2 != y1);

        float alpha = (float)dy / total_h;
        float beta;

        if (upper_half)
        {
            beta = (float)dy / (y2 - y1);
        }
        else
        {
            int lower_h = y3 - y2;
            if (lower_h == 0)
                beta = 1.0f;
            else
                beta = (float)(dy - (y2 - y1)) / lower_h;
        }

        int ax = x1 + (int)((x3 - x1) * alpha);
        int bx = upper_half
                     ? x1 + (int)((x2 - x1) * beta)
                     : x2 + (int)((x3 - x2) * beta);

        if (ax > bx)
        {
            int t = ax;
            ax = bx;
            bx = t;
        }
        SDL_RenderLine(renderer, ax, y1 + dy, bx, y1 + dy);
    }
}

void SDL3_driver::draw_bitmap(int16_t x, int16_t y, int16_t width, int16_t height, void *bitmap, BITMAP_TYPE bitmap_type, RGB colour)
{
    int scale = 1;

    if (bitmap_type == BITMAP_RGB565)
    {
        uint16_t *bitmap_data = (uint16_t *)bitmap;
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                uint16_t color = bitmap_data[row * width + col];

                uint8_t r5 = (color >> 11) & 0x1F;
                uint8_t g6 = (color >> 5) & 0x3F;
                uint8_t b5 = (color) & 0x1F;

                uint8_t r = (r5 << 3) | (r5 >> 2);
                uint8_t g = (g6 << 2) | (g6 >> 4);
                uint8_t b = (b5 << 3) | (b5 >> 2);

                SDL_FRect px = {
                    x + col * scale,
                    y + row * scale,
                    scale, scale};
                SDL_SetRenderDrawColor(renderer, r, g, b, 255);
                SDL_RenderFillRect(renderer, &px);
            }
        }
    }
    else if (bitmap_type == BITMAP_ALPHA_MAP)
    {
        uint8_t *bitmap_data = (uint8_t *)bitmap;
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                int byte_idx = (row * width + col) / 8;
                int bit_idx = 7 - (col % 8);

                if (bitmap_data[byte_idx] & (1 << bit_idx))
                {
                    SDL_FRect px = {
                        x + col * scale,
                        y + row * scale,
                        scale, scale};
                    SDL_SetRenderDrawColor(renderer, colour.get_red(), colour.get_green(), colour.get_blue(), 255);
                    SDL_RenderFillRect(renderer, &px);
                }
            }
        }
    }
}
#endif /* SDL3_DRIVER */
