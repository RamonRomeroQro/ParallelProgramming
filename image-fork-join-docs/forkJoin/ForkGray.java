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
import java.util.concurrent.RecursiveAction;

public class ForkGray extends RecursiveAction {
	private static final int BLUR_WINDOW = 15;
	private static final long MIN = 10_000;
	private int src[], dest[], width, height, start, end;

	public ForkGray(int src[], int dest[], int width, int height, int start, int end) {
		this.src = src;
		this.dest = dest;
		this.width = width;
		this.height = height;
		this.start = start;
		this.end = end;
	}

	private void gray_pixel(int ren, int col) {
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

	public void computeDirectly() {
		int index, size;
		int ren, col;

		size = width * height;
		for (index = start; index < end; index++) {
			ren = index / width;
			col = index % width;
			gray_pixel(ren, col);
		}
	}

	@Override
	protected void compute() {
		if ( (this.end - this.start) <= ForkGray.MIN ) {
			computeDirectly();

		} else {
			int middle = (end + start) / 2;

			invokeAll(new ForkGray(src, dest, width, height, start, middle),
					  new ForkGray(src, dest, width, height, middle, end));
		}
	}
}
