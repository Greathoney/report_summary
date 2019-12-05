import java.util.Random;
import java.util.Scanner;

class Seat{
    public static void main(String [] args){

        int [][] seat_left1 = new int [10][10];
        seat_reset(seat_left1);
        seat_print(seat_left1);
        seat_get(seat_left1);
        
    }
    
    static void seat_reset(int [][] seat_left){
        Random r = new Random();
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                if (r.nextInt(2)== 1){
                    seat_left[i][j] = 1;
                }
                else{
                    seat_left[i][j] = 0;
                }                  
                
            }
        }
    }

    static void seat_print(int [][] seat_left){
        System.out.printf("   ");
        for (int i = 1; i <= 10; i++){
            System.out.printf("%3d", i);
        }
        System.out.println();
        for (int i = 0; i < 10; i++){  
            System.out.printf("%c  ", 'a'+i);
            for (int j = 0; j < 10; j++){
                if (seat_left[i][j] == 1){
                    System.out.printf("  X");
                }
                else{
                    System.out.printf("   ");
                }
            }
            System.out.println();
        }
    }

    static void seat_get(int [][] seat_left){
        Scanner s = new Scanner(System.in);

        String answer = "";
        String row = "";
        int column = 0;
        int row_int = 0;
        while (true){    
            System.out.printf("예약하시겠습니까(Y,y / N,n)? ");
            answer = s.next();
            if (answer.equalsIgnoreCase("y")){
                while (true){
                    System.out.printf("몇 행? ");
                    row = s.next();
                    System.out.printf("몇 열? ");
                    column = s.nextInt();
                    
                    row_int = Integer.parseInt(String.format("%d", row.charAt(0)-'a'));
                    if (seat_left[row_int][column-1] == 1){
                        System.out.printf("이미 예약된 좌석입니다. 다른 좌석을 선택하세요.\n");
                    }
                    else{
                        seat_left[row_int][column-1] = 1;
                        System.out.printf("%c행 %d열 예약에 성공하였습니다.\n", row_int+'a', column);
                        seat_print(seat_left);
                        break;
                    }
                }
            }
            else if (answer.equalsIgnoreCase("n")){
                System.out.printf("예약시스템을 종료합니다. ");
                break;
            }
        }

        s.close();
    }
}