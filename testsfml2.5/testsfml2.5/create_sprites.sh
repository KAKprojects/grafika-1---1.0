#!/bin/bash
# Skrypt generujący proste sprite'y dla gracza
# Tworzy 16 sprite'ów w czterech kolorach (czerwony, zielony, niebieski, żółty)

SPRITES_DIR="sprites"
mkdir -p "$SPRITES_DIR"

# Funkcja tworząca prosty sprite 32x32 jako dane binarnych PPM (łatwiejsze niż PNG)
# Konwertujemy do PNG za pomocą ImageMagick, ale zamiast tego tworzymy PNG bezpośrednio

# Najprostsze rozwiązanie: tworzymy minimalne PNG'i za pomocą echo + printf
# PNG magic number + IHDR chunk + IDAT chunk + IEND chunk

create_png_sprite() {
    local color_r=$1
    local color_g=$2
    local color_b=$3
    local direction=$4
    local frame=$5
    local filename="$SPRITES_DIR/player_${direction}_${frame}.png"
    
    # Tworzymy PPM (ASCII, można łatwo przekonwertować)
    # Zamiast tego, użyjemy ffmpeg jeśli dostępny, lub skopiujemy placeholder
    
    # Najprostsze: tworzymy 1x1 PNG z czystym kolorem jako placeholder
    # (W praktyce, przydałyby się ścięte sprite'y, ale dla testu wystarczą)
    
    # Tymczasowo: tworzymy pliki PPM i konwertujemy
    printf "P6\n32 32\n255\n" > "$SPRITES_DIR/temp_${direction}_${frame}.ppm"
    
    # Generujemy 32x32 pikseli o podanym kolorze
    python3 - <<EOF "$color_r" "$color_g" "$color_b" "$SPRITES_DIR/temp_${direction}_${frame}.ppm"
import sys
import struct
r, g, b = int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3])
ppm_file = sys.argv[4]

# Dopisz dane pikseli do PPM
with open(ppm_file, 'ab') as f:
    for _ in range(32 * 32):
        f.write(struct.pack('BBB', r, g, b))
EOF
    
    # Konwertuj PPM do PNG
    if command -v pnmtopng &> /dev/null; then
        pnmtopng "$SPRITES_DIR/temp_${direction}_${frame}.ppm" > "$filename"
        rm "$SPRITES_DIR/temp_${direction}_${frame}.ppm"
        echo "Utworzono: $filename"
    elif command -v ffmpeg &> /dev/null; then
        ffmpeg -f rawvideo -video_size 32x32 -pixel_format rgb24 -i "$SPRITES_DIR/temp_${direction}_${frame}.ppm" -c:v png "$filename" -y 2>&1 | grep -v "frame=" || true
        rm "$SPRITES_DIR/temp_${direction}_${frame}.ppm"
    else
        # Fallback: przenieś PPM jako PNG (nie będzie to prawidłowy PNG, ale dla testów może wystarczyć)
        mv "$SPRITES_DIR/temp_${direction}_${frame}.ppm" "$filename"
        echo "UWAGA: Utworzono plik PPM zamiast PNG: $filename"
    fi
}

# Kierunki i kolory: (R, G, B)
create_png_sprite 255 0 0 "up" 0
create_png_sprite 255 0 0 "up" 1
create_png_sprite 255 0 0 "up" 2
create_png_sprite 255 0 0 "up" 3

create_png_sprite 0 255 0 "down" 0
create_png_sprite 0 255 0 "down" 1
create_png_sprite 0 255 0 "down" 2
create_png_sprite 0 255 0 "down" 3

create_png_sprite 0 0 255 "left" 0
create_png_sprite 0 0 255 "left" 1
create_png_sprite 0 0 255 "left" 2
create_png_sprite 0 0 255 "left" 3

create_png_sprite 255 255 0 "right" 0
create_png_sprite 255 255 0 "right" 1
create_png_sprite 255 255 0 "right" 2
create_png_sprite 255 255 0 "right" 3

echo "Sprite'y gotowe!"
ls -lh "$SPRITES_DIR/" | head -20
