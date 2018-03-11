import java.io.*;
import java.lang.*;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Vector;
public class MagicSquare{
    public static void main(String[] s)
    {
        String[] ss = {"txt/1.txt",
                "txt/2.txt",
                "txt/3.txt",
                "txt/4.txt",
                "txt/5.txt",
                "txt/6.txt"};
        MagicSquare1 jdg = new MagicSquare1();
        try {
            for(int i=0;i<5;i++)
            {
                if(!jdg.isLegalMagicSquare(ss[i]))
                {
                    System.out.println("false");
                    System.out.println("Wrong Matrix...");
                }
                else
                {
                    System.out.println("true");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        Integer tmp = 0;
        while(true)
        {
            try{
                Scanner sse = new Scanner(System.in);
                Integer it = sse.nextInt();
                generateMagicSquare(it);
                tmp = it;
            }catch(Exception e)
            {
                e.printStackTrace();
                System.out.println("false");
                break;
            }
        }
        System.out.print("Try: n=");
        System.out.print(tmp);
        System.out.println("...");
        try{
            if(!jdg.isLegalMagicSquare(ss[5]))
            {
                System.out.println("false");
                System.out.println("Wrong Matrix...");
            }
            else
            {
                System.out.println("true");
            }
        }catch(Exception e)
        {
            e.printStackTrace();
        }
    }
    private static boolean generateMagicSquare(int n) throws IOException {
        String[] ss = {"txt/1.txt",
                "txt/2.txt",
                "txt/3.txt",
                "txt/4.txt",
                "txt/5.txt",
                "txt/6.txt"};
        PrintWriter fwt = new PrintWriter(ss[5]);
        int magic[][] = new int[n][n];
        int row = 0, col = n / 2, i, j, square = n * n;
        for (i = 1; i <= square; i++) {
            magic[row][col] = i;
            if (i % n == 0)
                row++;
            else {
                if (row == 0)
                    row = n - 1;
                else
                    row--;
                if (col == (n - 1))
                    col = 0;
                else
                    col++;
            }
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++){
                System.out.print(magic[i][j] + "\t");
                //
                fwt.print(magic[i][j]);
                fwt.print("\t");
            }
            fwt.print("\n");
            System.out.println();
        }
        fwt.close();
        return true;
    }
}


class MagicSquare1 {
    private Integer n = 0;
    private boolean flag = true;
    boolean isLegalMagicSquare(String str) throws Exception {
        return judger(ReadFileJaba(str));
    }
    int getN(){
        return n;
    }
    void prints(Double[][] dat)
    {
        if(dat == null) return;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                System.out.print(dat[i][j]);
                System.out.print("\t");
            }
            System.out.print('\n');
        }
    }
    boolean judger(Double[][] dat)
    {
        if(!flag) return false;
        Double esp = 1e-5;
        Double cst = -1.0;
        Double sum = 0.;
        Integer numm = n*n + 1;
        Integer[] os = new Integer[numm];
        for(int i=0;i<n*n+1;i++)
        {
            os[i]=0;
        }
        try
        {
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    if(os[dat[i][j].intValue()] == 1)
                        return false;
                    else
                        os[(int)dat[i][j].intValue()]=1;
                }
            }
        }catch(Exception e)
        {
            return false;
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                sum += dat[i][j];
            }
            if(cst + 1 > esp)//cst!=-1
            {
                if(cst - sum >esp)
                {
                    return false;
                }
            }
            else cst = sum;
            sum = 0.;
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                sum += dat[j][i];
            }
            if(cst - sum > esp)
            {
                return false;
            }
            sum = 0.;
        }
        for(int i=0;i<n;i++)
        {
            //System.out.println(dat[i][0]);
            sum += dat[i][n-i-1];
            //System.out.println(sum);
        }
        if(cst - sum >esp) return false;
        sum = 0.;
        for(int i=0;i<n;i++)
        {
            sum += dat[n-i-1][i];
        }
        return !(cst - sum > esp);
    }
    private Double Convert(String num)
    {
        Double ans = 0.;
        boolean st = false;
        int indp = 0;
        for(int i=0;i<num.length();i++)
        {
            if(num.charAt(i) == '.')
            {
                st = true;
            }
            else
            {
                if(st)
                {
                    indp +=1 ;
                    ans += Math.pow(10.0, -indp)*(num.charAt(i)-'0');
                }
                else
                {
                    ans = ans*10 + num.charAt(i) - '0';
                }
            }
        }
        return ans;
    }
    Double[][] ReadFileJaba(String filename) throws Exception
    {
        Scanner sc = new Scanner(new File(filename));
        Double[][] ana = new Double [500][500];
        int hold = -1;
        int line= 0;
        while(true)
        {
            try{
                String str = sc.nextLine();
                String[] sst = str.split("\t");
                if(hold != -1)
                {
                    if(hold != sst.length)
                    {
                        flag = false;
                        return ana;
                    }
                }
                else
                {
                    hold = sst.length;
                }
                for(int o = 0;o<sst.length;o++)
                {
                    ana[line][o]= Convert(sst[o]);
                }
            }catch(Exception e)
            {
                break;
            }
            line += 1;
        }
        n = line;
        if(line != hold) flag = false;
        return ana;
    }
}