#!/usr/bin/env python3
"""
Skrypt generujący proste sprite'y dla gracza
Tworzy 8 klatek animacji ruchu w 4 kierunkach (góra, dół, lewo, prawo)
"""

from PIL import Image, ImageDraw

# parametry sprite'ów
WIDTH = 32
HEIGHT = 32
COLORS = {
    'up': '#FF0000',        # czerwony - góra
    'down': '#00FF00',      # zielony - dół
    'left': '#0000FF',      # niebieski - lewo
    'right': '#FFFF00',     # żółty - prawo
}

DIRECTIONS = [
    ('up', '#FF0000'),
    ('down', '#00FF00'),
    ('left', '#0000FF'),
    ('right', '#FFFF00'),
]

def create_sprite(color, direction_name, frame_num):
    """
    Tworzy prosty sprite - kolorowy kwadrat z numerem klatki
    """
    img = Image.new('RGBA', (WIDTH, HEIGHT), (0, 0, 0, 0))
    draw = ImageDraw.Draw(img)
    
    # główny kwadrat
    draw.rectangle(
        [2, 2, WIDTH-2, HEIGHT-2],
        fill=color,
        outline='white',
        width=2
    )
    
    # numer klatki
    draw.text((10, 10), str(frame_num), fill='white')
    
    return img

def main():
    """
    Generuje sprite'y dla wszystkich kierunków i klatek
    """
    sprites_dir = '/workspaces/grafika-1---1.0/testsfml2.5/testsfml2.5/sprites'
    
    import os
    os.makedirs(sprites_dir, exist_ok=True)
    
    # dla każdego kierunku
    for direction, color in DIRECTIONS:
        # tworzymy 4 klatki animacji
        for frame in range(4):
            sprite = create_sprite(color, direction, frame)
            filename = f'{sprites_dir}/player_{direction}_{frame}.png'
            sprite.save(filename, 'PNG')
            print(f'Utworzono: {filename}')

if __name__ == '__main__':
    main()
