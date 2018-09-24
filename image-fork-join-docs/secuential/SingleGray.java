/*----------------------------------------------------------------

*

* Actividad de programación: Fork-join framework

* Fecha: 23-Sep-2018

* Autor: A01700318 Ramon Romero

*

*--------------------------------------------------------------*/
import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;

public class SingleGray {
	private static final int BLUR_WINDOW = 15;
	private int src[], dest[], width, height;

	public SingleGray(int src[], int dest[], int width, int height) {
		this.src = src;
		this.dest = dest;
		this.width = width;
		this.height = height;
	}

	private void grax_pixel(int ren, int col) {

		int side_pixels, i, j, cells;
		int tmp_ren, tmp_col, pixel, dpixel;
		float r, g, b, avg;

		r = 0; g = 0; b = 0;

		pixel = src[(ren * width) + col];

				r = (float) ((pixel & 0x00ff0000) >> 16);
				g = (float) ((pixel & 0x0000ff00) >> 8);
				b = (float) ((pixel & 0x000000ff) >> 0);
				avg=(r+g+b)/3;



		dpixel = (0xff000000)
				| (((int) (avg)) << 16)
				| (((int) (avg)) << 8)
				| (((int) (avg)) << 0);
		dest[(ren * width) + col] = dpixel;
	}

	void doMagic() {
		int index, size;
		int ren, col;

		size = width * height;
		for (index = 0; index < size; index++) {
			ren = index / width;
			col = index % width;
			grax_pixel(ren, col);
		}
	}
}
