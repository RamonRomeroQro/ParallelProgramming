
/*----------------------------------------------------------------
* Actividad de programación: Calculando Pi con threads en Java
* Multithread program
* Fecha: 15-Sep-2018
* Autor: A01700318 Jose Ramon Romero Chavez
*--------------------------------------------------------------*/

public class Main {


	public static void initarr(int limit,int []a) {
	  int c;
	  for(c = 2; c < limit; c++) {
	      a[c] = 0;
	  }
	}

	public static void  printprimes(int limit, int []arr) {
	  int c;

	  for(c = 2; c <limit; c++) {
	      if(arr[c] == 0) {
					System.out.print(""+c+" ");
	      }
	  }
		System.out.print("\n");
	  /* code */
	}

    public static void main(String[] args) {
         int MAXTHREADS = Runtime.getRuntime().availableProcessors();

				 //System.out.println("IO: "+args[0]+" "+ args.length);

				 int limit=16;
			   if (args.length>1){
					 System.err.println("Error: uso: %s [limite_superior_positivo]\n");
					 System.exit(-1);
			   }else if (args.length==1) {
			     int parsed=Integer.parseInt(args[0]);
					 //System.err.println(parsed);

			     if (parsed<0){
						 System.err.println("Error: uso: %s [limite_superior_positivo]\n");
						 System.exit(-1);
			     }else{
			       limit=parsed;
			     }
			   }
        SieveThread [] hilos = new SieveThread[MAXTHREADS];
        int a=(int)(limit/MAXTHREADS);
				int sqroot = (int)Math.sqrt(limit);
				int [] arr = new int[limit];

        for (int i = 0; i < MAXTHREADS; i++) {
                if (i != MAXTHREADS - 1) {
                    hilos[i]= new SieveThread((a*i),(a*(i+1)), arr);
                } else {
                    hilos[i] = new SieveThread((i * a), limit, arr);
                }
        }



				//initarr(limit, arr);
				int c;
				int m;



				for(c = 2; c <= sqroot; c++) {
						if(arr[c] == 0) {

							for (int i = 0; i < MAXTHREADS; i++) {
			                    hilos[i].ct=c;
			        }


							for (int i = 0; i < MAXTHREADS ; i++) {
			            hilos[i].run();
			        }


						}
				}
				try {
	 				 for (int i = 0; i < MAXTHREADS ; i++) {
	 						 hilos[i].join();
	 				 }
	 		 } catch (InterruptedException e) {
	 				 e.printStackTrace();
	 		 }

			printprimes(limit, arr);







        System.exit(0);
    }
}



class SieveThread extends Thread {
     public int [] arr;
     public int ct=-1;
		 public int begin;
		 public int end;


    public SieveThread( int b, int e, int [] a ) {
        this.arr     = a;
        this.begin  = b;
        this.end   = e;
    }

    public int[] getArr() {
        return arr;
    }


    public void run() {
			for (int i = this.begin+1; i < this.end; i++) {
				//System.err.println(ct+" "+i);

				this.arr[ct] = 0;
				if(i%ct == 0) {
						this.arr[i] = 1;

				}

			}

    }

}
