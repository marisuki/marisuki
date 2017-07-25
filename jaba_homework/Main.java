import java.math.*;
import java.nio.file.Paths;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.util.*;
import java.util.Map.Entry;
import java.util.regex.MatchResult;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JApplet;
import javax.swing.JDialog;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import java.io.BufferedReader;
import java.io.Console;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.*;
import java.lang.reflect.Array;
import java.applet.AudioClip;
import java.awt.*;


public class Main {
	public static void main(String[] args)
	{
		Danmurain dmr=new Danmurain("C:\\Users\\康瑞\\Desktop\\DanmuRain\\hirahirahirara.txt");
		/**for(int i=0;i<dmr.ColDanMu.length;i++)
		{
			if(dmr.DanMu[i]!=null)
				System.out.println(dmr.DanMu[i]);
		}*/
		dmr.start();
	}
}

class Danmurain extends JDialog
{
	private Random random = new Random();
	private Dimension size = new Dimension();
	private Color Foreground=Color.GREEN,Background=Color.BLACK;
	private String extFileName=new String();
	public String[] DanMu=new String[2000];
	public Color[] ColDanMu=new Color[2000];
	private boolean colorful=false;
	private boolean hasMusic=false;
	private AudioClip musicpiece;
	//private JPanel graph = new JPanel();
	//private Font rainFont;
	private boolean isStart=false;
	private ArrayList<rainstart> Rains = new ArrayList<rainstart>();
	private DrawDanMuRain danmurainning= new DrawDanMuRain();
    private String urlofcrusor = "C:\\Users\\康瑞\\Desktop\\63354286_p0.png";
    Toolkit tk = Toolkit.getDefaultToolkit();
	Image image = new ImageIcon(urlofcrusor).getImage();
    int imX;
    int imY;
	public void start()
	{
		if(hasMusic)
		{
			musicpiece.loop();
		}
		for(int i=0;i<1000;i++)
		{
			newrain(i);
		}
		isStart=true;
		for(rainstart r: Rains)
		{
			new Thread(r).start();
		}
		new Thread(new Runnable() {
			@Override
			public void run() {
				// TODO Auto-generated method stub
				while(isStart)
					danmurainning.repaint();
			}
			
		}).start();
	}
	
	private void newrain(int index) {
		// TODO Auto-generated method stub
		rainstart rst = new rainstart(DanMu[index],ColDanMu[index],(int) (size.width-random.nextGaussian()*4000),(int) ((random.nextGaussian())*size.height),10,0); 
		Rains.add(rst);
		new Thread(rst).start();
	}

	public Danmurain(String filefrom)
	{
		try
		{
			//ReadFileJava("C:\\Users\\康瑞\\Desktop\\DanmuRain\\3829202_1.xml");
			//ReadFilePy("C:\\Users\\康瑞\\Desktop\\DanmuRain\\3829202_1.xml","C:\\Users\\康瑞\\Desktop\\DanmuRain\\data.dat")
			extFileName=filefrom;
			LoadDanmu();
			
		}
		catch(Exception e){
			e.printStackTrace();
		}
		initial();
	}
	private Color initialfontcolor(String Colors, int state)
	{
		if(Colors==null||Colors.isEmpty())
		{
			return new Color(255,255,255);
		}
		else
		{
			if(Colors.startsWith("#")&&state==16)
			{
				int i = Integer.valueOf(Colors.substring(1), 16);
				return new Color(i);
			}
			else if(state==16)
			{
				int i = Integer.valueOf(Colors, 16);
			}
			else
			{
				return new Color(255,255,255);
			}
		}
		return new Color(0,0,0);
	}
	public void initial()
	{
		size=Toolkit.getDefaultToolkit().getScreenSize();
		Background=Color.BLACK;
		//keypresslistener ksp = new keypresslistener();
		//this.addKeyListener(ksp);
		//Cursor cursor = tk.createCustomCursor(image, new Point(10, 10), "norm");
		setLayout(new BorderLayout());
		setAlwaysOnTop(true);
        setResizable(false);
        setUndecorated(true);
		setTitle("Avoid DanMu");
		//setCursor(cursor);
		//BufferedImage cursor = new BufferedImage(16, 16, BufferedImage.TYPE_INT_RGB);
		//setCursor(Toolkit.getDefaultToolkit().createCustomCursor(cursor, new Point(8, 8), "Enable Cursor"));
		setSize(size);
		setLocationRelativeTo(null);
        addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent event) {
                if ((event.isAltDown() && event.getKeyCode() == KeyEvent.VK_F4) || (event.getKeyCode() == KeyEvent.VK_ESCAPE)) {
                    setVisible(false);
                    System.exit(0);
                }
                else
                {
                	if(event.getKeyCode()==KeyEvent.VK_UP)
            		{
            			imY=Math.max(0,imY-2);
            		}
            		else if(event.getKeyCode()==KeyEvent.VK_DOWN)
            		{
            			imY=imY+7;
            		}
            		else if(event.getKeyCode()==KeyEvent.VK_LEFT)
            		{
            			imX=Math.max(0,imX-2);
            		}
            		else if(event.getKeyCode()==KeyEvent.VK_RIGHT)
            		{
            			imX=imX+7;
            		}
                }
            }
        });
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent event) {
                if (!isStart)
                	musicpiece.stop();
          
                System.exit(0);
            }
        });
        add(danmurainning, BorderLayout.CENTER);
        setVisible(true);
        imX=0;
        imY=(int) (0.5*size.height);
    }	
	public void GenerateFontandColor(String line,int index)
	{
		int cotecnt=0;
		String color=new String();
		String danmu=new String();
		for(int i=0;i<line.length();i++)
		{
			if(cotecnt==6)
			{
				color= new String(line.substring(i+1, i+8));
				cotecnt = 0;
			}
			if(line.substring(i,i+1)==",")
			{
				cotecnt+=1;
			}
			if(line.substring(i,i+1)==">")
			{
				int pos=i+1;
				while(line.substring(pos,pos+1)!="<") pos+=1;
				danmu=new String(line.substring(i+1,pos));
			}
		}
		ColDanMu[index]=initialfontcolor(color,16);
		DanMu[index]=danmu;
		return;
	}
	public void ReadFileJava(String file) throws Exception
	{
		BufferedReader in = new BufferedReader( new FileReader(file));
		//String mx = "<d p=\"226.25,1,25,38979,1458451747,0,e0d94f88,1695062109\">表示给我们语文老师看了歌词后她一脸懵逼</d>";
		Pattern pattern = Pattern.compile("<d p=.*?>(.*?)</d>");
		//Pattern pattern = Pattern.compile("<d p=.*?>(.*?)</b>",Pattern.UNICODE_CASE);
		String Line = new String();
		String Colorcraw = new String();
		String Textcraw = new String();
		int index=0;
		while((Line=in.readLine())!=null)
		{
			Matcher m = pattern.matcher(Line);
			while(m.find()) {
				Colorcraw = "#"+m.group(0);
				System.out.println("inner"+Colorcraw);
				Textcraw = m.group(1);
				DanMu[index] = Textcraw;
				ColDanMu[index] = initialfontcolor(Colorcraw,16);
			}
		}
		in.close();
	}
	public void ReadFilePy(String filenameopen, String filenamesave) throws IOException
	{
		Process proc = Runtime.getRuntime().exec("python acm.py "+filenameopen+" "+filenamesave);
	}
	public void LoadDanmu() throws IOException
	{
		BufferedReader in = new BufferedReader(new FileReader(extFileName));
		String Line = new String();
		int index=0;
		while((Line = in.readLine())!=null)
		{
			DanMu[index]=Line;
			ColDanMu[index++] = Color.GREEN;
		}
		in.close();
		for(int i=0;!(DanMu[i].equals("")||DanMu[i]==null);i++)
		{
			Rains.add(new rainstart(DanMu[i],ColDanMu[i],size.width,(int)Math.random()*size.height,10,0));
		}
	}
	private class meta extends JApplet
	{
		//music: waiting
	}
	private class imagePost extends JApplet
	{
		
	}
	private class rainstart implements Runnable
	{
        public float rainSpeedX,rainSpeedY;
        public int rainX, rainY;
        public int position;
        public String font;
        private Color fontcolor;
        private float fontSize;
		public rainstart(String rainfont,Color fontcol, int x, int y, int speedX, int speedY,float fontsize) {
			if(speedX!=0 && speedY!=0)
			{
				this.rainSpeedX=speedX;
				speedY=0;
				position = 1;
			}
			else 
			{
				this.rainSpeedY=speedY;
				position = 0;
			}
			this.rainX=x;
			this.rainY=y;
			if(rainfont!=null)
				this.font=rainfont;
			else this.font="aaaaaaa";
			this.fontSize=fontsize;
			this.fontcolor=fontcol;
		}
		public rainstart(String rainfont,Color fontcol, int x, int y, int speedX, int speedY) {
			if(speedX!=0)
			{
				this.rainSpeedX=speedX;
				this.rainSpeedY=0;
				speedY=0;
				position = 1;
			}
			else 
			{
				this.rainSpeedX=0;
				this.rainSpeedY=speedY;
				position = 0;
			}
			this.rainX=x;
			this.rainY=y;
			if(rainfont!=null)
				this.font=rainfont;
			else this.font="aaaaaaa";
			this.fontSize=30.0f;
			this.fontcolor=fontcol;
		}
		@Override
		public void run()
		{
			while(isStart)
			{
				int endX=0;
				int endY=0;
				try
				{
					endX=(int) (-(this.font.length()+1)*this.fontSize);
					endY=(int) (size.height+(this.font.length()+1)*this.fontSize);
					//System.out.println(font);
				}
				catch(Exception e)
				{
					//System.out.println(font);
				}
				if(position==1 && rainX>endX)
				{
					if(rainSpeedX<=0)
					{
						break;
					}
					try {
						Thread.sleep((int)rainSpeedX+1);
					}
					catch(InterruptedException e)
					{
						e.printStackTrace();
					}
					rainX-=2;
					rainSpeedX-=0.0f;
				}
				else if(position==0 && rainY>endY)
				{
					if(rainSpeedY<=0)
					{
						break;
					}
					try {
						Thread.sleep((int)rainSpeedY+1);
					}
					catch(InterruptedException e)
					{
						e.printStackTrace();
					}
					rainY+=5;
					rainSpeedY-=0.0f;
				}
				else
				{
					break;
				}
			}
			
			
		}
	}
	private class DrawDanMuRain extends JPanel
	{
		private String imageSortage= new String("");
		
		public DrawDanMuRain(String imagesource) {
			imageSortage=imagesource;
		}
		public DrawDanMuRain() {}
		@SuppressWarnings("static-access")
		@Override
		public void paint(Graphics gic)
		{
			System.out.println(imX);
			
			BufferedImage img;
			Graphics2D g2d;
			
			try {
				img = ImageIO.read(new File(imageSortage));
				g2d = (Graphics2D) img.getGraphics();
				g2d.setColor(Color.BLACK);
			}
			catch(Exception e)
			{
				img = new BufferedImage(size.width,size.height,BufferedImage.TYPE_INT_RGB);
				g2d = (Graphics2D) img.getGraphics();
				g2d.setColor(Color.BLACK);
				g2d.fillRect(0, 0, size.width, size.height);
			}
			g2d.setColor(Color.GREEN);
			for(rainstart it:Rains)
			{
				if(Math.abs(it.rainY-imY)<=10&&Math.abs(it.rainX-imX)<=10)
				{
					imY=size.height/2;
					imX=0;
				}
				if(imX>=size.width-40)
				{
					Font rainfont = new Font("arial",Font.BOLD,30);
					g2d.setFont(rainfont.deriveFont(72));
					g2d.drawString("You winned!", size.width/2, size.height/2);
				}
			}
			/*
			Queue<rainstart> que = new LinkedList<rainstart>();
			que.clear();
			for(rainstart it: Rains)
			{
				que.offer(it);
			}
			gic.drawImage(img,0,0,this);
			while(true)
			{
				rainstart it = que.poll();
				Font rainfont = new Font("arial",Font.BOLD,(int)it.fontSize);
				g2d.setColor(new Color((int) (255*Math.random()),(int) (255*Math.random()), (int) (255*Math.random())));
				g2d.setFont(rainfont.deriveFont(it.fontSize).decode("utf-8"));
				int x = it.rainX;
				int y = it.rainY;
				for(int i=0;i<it.font.length();i++)
				{
					g2d.drawString(it.font.substring(i, i+1), x, y);
					x+=it.fontSize;
				}
				
				try {
					Thread.sleep(100);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				que.offer(it);
			}*/
			
			
			Collection<rainstart> collections = (Collection<rainstart>) Rains.clone();
			Iterator<rainstart> itor = collections.iterator();
			int ind=0;
			
			while(itor.hasNext())
			{
				rainstart tmp = itor.next();
				if(tmp.rainSpeedX<0||tmp.rainSpeedY<0)
				{
					Rains.remove(tmp);
					newrain((int)((int)1000*Math.random()));
					continue;
				}
				ind+=1;
				Font rainfont = new Font("arial",Font.BOLD,30);
				g2d.setFont(rainfont.deriveFont(72).decode("UTF-8"));
				//tmp.rainX-=Math.random()*tmp.font.length();
				//tmp.rainY-=Math.random()*tmp.font.length();
				int x = tmp.rainX;
				int y = tmp.rainY;
				//g2d.setColor(tmp.fontcolor);
				for(int i=0;i<Math.min(tmp.font.length(),100);i++)
				{
					g2d.drawString(tmp.font.substring(i, i+1), x, y);
					if(tmp.rainSpeedX!=0)
						x+=tmp.fontSize;
					else
						y-=tmp.fontSize;
				}
			}
			
			gic.drawImage(img,0,0,this);
			gic.drawImage(image, imX, imY, 40,40,this);
			
		}
	}
}