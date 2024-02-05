#include <keypadc.h>
#include <graphx.h>

#define BLACK 0
#define LIGHT_BLUE 30
#define BLUE 27
#define DARK_BLUE 25

gfx_point_t isoToPixel(gfx_point_t iso);
void drawCube(gfx_point_t iso);
bool step();
void draw();

gfx_point_t cursor = {0,0};
int grid[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 4, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 4, 3, 2, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 1, 1, 1, 6, 1, 1, 1, 1, 1}};

		 bool partialRedraw = false;

int main() {
	gfx_Begin();
	gfx_SetDrawBuffer();
	
	do {
		if (partialRedraw) {
			gfx_BlitScreen();
		}
		draw();
		gfx_SwapDraw();
	} while ( step() );
	
	gfx_End();
	return 0;
}

void draw() {
	if (!partialRedraw) {
		gfx_FillScreen(255);
		// partialRedraw = true;
		gfx_point_t isoPoint = {0, 0};
		for (isoPoint.x = 0; isoPoint.x < 10; ++isoPoint.x) {
			for (isoPoint.y = 9; isoPoint.y >= 0; --isoPoint.y) {
				drawCube(isoPoint);
			}
		}
	}
}

bool step() {
	kb_Scan();
	if (kb_Data[7]) {
		if ( (kb_Data[7] & kb_Up) && (cursor.y != (int)sizeof(grid)) )
			cursor.y++;
		if ( (kb_Data[7] & kb_Down) && (cursor.y != 0) )
			cursor.y--;
		if ( (kb_Data[7] & kb_Right) && (cursor.x != (int)sizeof(grid[0])) )
			cursor.x++;
		if ( (kb_Data[7] & kb_Left) && (cursor.x != 0) )
			cursor.x++;
	}
	return (kb_Data[6] != kb_Clear);
}

gfx_point_t isoToPixel(gfx_point_t iso) {
	gfx_point_t pixel;
	pixel.x = 16 + 16*iso.x + 16*iso.y;
	pixel.y = 160 + 8*iso.x - 8*iso.y;
	return pixel;
}

void drawCube(gfx_point_t iso) {
	gfx_point_t pixel = isoToPixel(iso);
	int height = (grid[iso.y][iso.x]-1)*16;
	gfx_SetColor(BLUE);
	gfx_FillTriangle_NoClip(pixel.x, pixel.y, pixel.x+16, pixel.y-8, pixel.x+16, pixel.y-(24+height));
	gfx_FillTriangle_NoClip(pixel.x, pixel.y, pixel.x, pixel.y-(16+height), pixel.x+16, pixel.y-(24+height));
	
	gfx_SetColor(DARK_BLUE);
	gfx_FillTriangle_NoClip(pixel.x, pixel.y, pixel.x-16, pixel.y-8, pixel.x-16, pixel.y-(24+height));
	gfx_FillTriangle_NoClip(pixel.x, pixel.y, pixel.x, pixel.y-(16+height), pixel.x-16, pixel.y-(24+height));
	
	gfx_SetColor(LIGHT_BLUE);
	gfx_FillTriangle_NoClip(pixel.x, pixel.y-(16+height), pixel.x, pixel.y-(32+height), pixel.x+16, pixel.y-(24+height));
	gfx_FillTriangle_NoClip(pixel.x, pixel.y-(16+height), pixel.x, pixel.y-(32+height), pixel.x-16, pixel.y-(24+height));
	
	gfx_SetColor(BLACK);
	gfx_Line(pixel.x, pixel.y, pixel.x+16, pixel.y-8);
	gfx_Line(pixel.x, pixel.y, pixel.x-16, pixel.y-8);
	gfx_Line(pixel.x, pixel.y, pixel.x, pixel.y-16);
	gfx_Line(pixel.x-16, pixel.y-8, pixel.x-16, pixel.y-24);
	gfx_Line(pixel.x+16, pixel.y-8, pixel.x+16, pixel.y-24);
	gfx_Line(pixel.x, pixel.y-16, pixel.x+16, pixel.y-24);
	gfx_Line(pixel.x, pixel.y-16, pixel.x-16, pixel.y-24);
	gfx_Line(pixel.x-16, pixel.y-24, pixel.x, pixel.y-32);
	gfx_Line(pixel.x+16, pixel.y-24, pixel.x, pixel.y-32);

}
