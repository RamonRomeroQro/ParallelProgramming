

/*----------------------------------------------------------------
* Actividad de programación: Calculando Pi con threads en Java
* Single-thread program
* Fecha: 15-Sep-2018
* Autor: A01700318 Jose Ramon Romero Chavez
*--------------------------------------------------------------*/


public class Single {

    public static void main(String[] args) {
        double num_rect=0;

        if (args.length==0){
            num_rect= 100000;
        }else if (args.length==1){
            try {
            num_rect=Double.parseDouble(args[0]);
            }
            catch (Exception e) {
            System.err.println("Error: usage: java Single [iterations]");
                    System.exit(-1);

                }

        }else{
            System.err.println("Error: usage: java Single [iterations]");
            System.exit(-1);


        }
       
        
        double mid, height,width, area;
        double sum  = 0;
        width = 1.0/num_rect;

        for (double i = 0; i < num_rect ; i++) {
            mid=(i+.5)*width;
            height = 4.0 / (1.0 + mid* mid);
            double a=sum;

            sum+= height;


        }

        area = width * sum;
        System.out.println("\n\nThreads = 1");
        System.out.println("Iterations = " + num_rect);
        System.out.println("PI = " + area+"\n\n");
        System.exit(0);

	// write your code here

    }
}


