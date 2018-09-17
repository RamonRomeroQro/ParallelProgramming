
/*----------------------------------------------------------------
* Actividad de programación: Calculando Pi con threads en Java
* Multithread program
* Fecha: 15-Sep-2018
* Autor: A01700318 Jose Ramon Romero Chavez
*--------------------------------------------------------------*/

public class Main {
        

    public static void main(String[] args) {
         int MAXTHREADS = Runtime.getRuntime().availableProcessors();
         double SIZE=0;


        if (args.length==0){
            SIZE= 100000;
            MAXTHREADS = Runtime.getRuntime().availableProcessors();
        }else if (args.length==2){
            try {
                SIZE=Double.parseDouble(args[0]);
                int cores=Integer.parseInt(args[1]);
                    if (SIZE<MAXTHREADS){
                        System.err.println("Error: for a propper execution the iteration number must be a bigger than of the posible Processors -> ("+MAXTHREADS+")");
                        System.exit(-1);
                    }
                    if (cores<=MAXTHREADS){
                        MAXTHREADS=cores;

                    }else{
                        System.err.println("Error: you are not allowed to create more than -> ("+MAXTHREADS+") due to your amount of Processors");
                        System.exit(-1);
                    }
                } catch (Exception e) {
                    System.err.println("Error: usage: java Main [iterations] [cores]");
                    System.err.println(e.toString());
                    System.exit(-1);

                }

        }


        else{
            System.err.println("Error: usage: java Main [iterations] [threads]");
            System.exit(-1);


        }
        


        PiThread [] hilos = new PiThread[MAXTHREADS];
        int a=(int)(SIZE/MAXTHREADS);

        for (int i = 0; i < MAXTHREADS; i++) {
                if (i != MAXTHREADS - 1) {
                    hilos[i]= new PiThread(SIZE, (a*i),(a*(i+1)));
                } else {
                    hilos[i] = new PiThread(SIZE, (i * a), SIZE);
                }
        }





        for (int i = 0; i < MAXTHREADS ; i++) {
            hilos[i].start();
        }
        try {
            for (int i = 0; i < MAXTHREADS ; i++) {
                hilos[i].join();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        double s=0;

        for (int i = 0; i < MAXTHREADS; i++) {
            s=s+hilos[i].getSuma();
        }

        //--- get results and sum up ---


        System.out.println("\n\nThreads = "+MAXTHREADS);
        System.out.println("Iterations = " + SIZE);
        System.out.println("PI = " + (s)+"\n\n" );
    
        System.exit(0);
    }
}



class PiThread extends Thread {
     double N;         
     int start;      
     int stop;       
     double suma;    


    public PiThread( double N, double start, double stop ) {
        super( "Calculo:"+start+"-"+stop ); // give a name to the thread
        this.N      = N;
        this.start  = (int)start;
        this.stop   = (int)stop;
    }

    public double getSuma() {
        return suma;
    }


    public void run() {
        double mid, height,width;
        double sum  = 0;
        width = 1.0/(N);
        for (double i = start; i < stop ; i++) {
            mid=(i+.5)*width;
            height = 4.0 / (1.0 + mid* mid);
            sum+= height;
        }
        this.suma = width*sum;
    }

}



