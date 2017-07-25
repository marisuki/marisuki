package exper;
import java.math.*;
import java.nio.file.Paths;
import java.awt.event.*;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Frame;
import java.awt.Toolkit;

import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.EmptyBorder;


import java.util.*;
import java.util.Map.Entry;
import java.io.Console;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.lang.*;
import java.lang.reflect.Array;
import org.jfree.chart.*;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.*;
import org.jfree.data.category.DefaultCategoryDataset;
import org.jfree.data.xy.IntervalXYDataset;
import org.jfree.data.xy.XYBarDataset;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import exper.OOBMI.Student;
public class Main{
	public static void main(String[] args)
	{
		SwingBMI sw = new SwingBMI();
		sw.main(null);
	}
}
class SwingBMI extends JFrame
{
	//all field
	private OOBMI Frbmi = new OOBMI();
	
	//common
	private JTextPane idpane = new JTextPane();
	private JTextPane namepane = new JTextPane();
	private JTextPane weipane = new JTextPane();
	private JTextPane heipane = new JTextPane();
	
	private JMenuBar mba = new JMenuBar();
	private JMenu MenuHome = new JMenu("Choose Box");
	private JMenu MenuStatics = new JMenu("Statics");
	private JMenuItem REQ = new JMenuItem("Request");
	private JMenuItem INPUT = new JMenuItem("Input");
	private JMenuItem MODI = new JMenuItem("Modify");
	private JMenuItem DELE = new JMenuItem("Delete");
	//private JMenuItem STATIC = new JMenuItem("Static");
	private JMenuItem BMIStatics = new JMenuItem("Static of BMI");
	private JMenuItem HeightStatics = new JMenuItem("Static of Height");
	private JMenuItem WeightStatics = new JMenuItem("Statics of Weight");
	
	
	//request
	private JPanel reqmain = new JPanel();
	private JTextField idfield = new JTextField();
	private JButton reqbutt = new JButton("Requset");
	private JTextArea reqarea = new JTextArea();
	private JScrollPane areajsp = new JScrollPane(reqarea);
	private JButton disall = new JButton("Display all");
	private JButton sortid = new JButton("Sort ID");
	private JButton sortname = new JButton("Sort Name");
	private JButton sortwei = new JButton("Sort Weight");
	private JButton sorthei = new JButton("Sort Height");
	private JButton sortbmi = new JButton("Sort Bmi");
	
	//input
	private JPanel inpscre = new JPanel();
	private JTextField inidfie = new JTextField();
	private JTextField innamefie = new JTextField();
	private JTextField inweifie = new JTextField();
	private JTextField inheifie = new JTextField();
	private JButton inputting = new JButton("Submit");
	//private JPanel textback = new JPanel();
	
	//modify
	private JPanel modscre = new JPanel();
	private JTextField modinid = new JTextField();
	private JButton nextmod = new JButton("Next");
	private JPanel nextmodify = new JPanel();
	private JTextField modinname = new JTextField();
	private JTextField modinwei = new JTextField();
	private JTextField modinhei = new JTextField();
	private JButton modifying = new JButton("Modify");
	private JButton modquit = new JButton("Back");
	
	//delete
	private JPanel delscre = new JPanel();
	private JTextField delid = new JTextField();
	private JButton configdel = new JButton("Delete");

	//bmi statics
	private JPanel statscre = new JPanel();
	
	//common 
	public static Toolkit kit = Toolkit.getDefaultToolkit();
	public static Dimension screenSize = kit.getScreenSize();
	public static int screensizew=screenSize.width;
	public static int screensizeh=screenSize.height;
	public void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
				{
					public void run()
					{
						try{
							SwingBMI frame = new SwingBMI();
							frame.setVisible(true);
							frame.setExtendedState(Frame.MAXIMIZED_BOTH);
						}
						catch(Exception e)
						{
							e.printStackTrace();
						}
					}
				});
	}
	
	public SwingBMI()
	{
		reqmain.setLayout(null);
		inpscre.setLayout(null);
		modscre.setLayout(null);
		delscre.setLayout(null);
		nextmodify.setLayout(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100,100,450,300);
		setSize(screensizew/2, screensizeh/2);
		idpane.setText("ID= ");
		namepane.setText("Name= ");
		weipane.setText("Weight= ");
		heipane.setText("Height= ");
		idpane.setEditable(false);
		namepane.setEditable(false);
		weipane.setEditable(false);
		heipane.setEditable(false);
		idpane.setBackground(getBackground());
		weipane.setBackground(getBackground());
		namepane.setBackground(getBackground());
		heipane.setBackground(getBackground());
		reqmain.setVisible(true);
		inpscre.setVisible(false);
		modscre.setVisible(false);
		delscre.setVisible(false);
		setContentPane(reqmain);
		req();
		setJMenuBar(mba);
		mba.add(MenuHome);
		mba.add(MenuStatics);
		MenuHome.add(REQ);
		MenuHome.add(INPUT);
		MenuHome.add(MODI);
		MenuHome.add(DELE);
		MenuStatics.add(BMIStatics);
		MenuStatics.add(HeightStatics);
		MenuStatics.add(WeightStatics);
		REQ.addActionListener(new ActionListener(){
			//@Override
			public void actionPerformed(ActionEvent e) {
				reqmain.setVisible(true);
				inpscre.setVisible(false);
				modscre.setVisible(false);
				delscre.setVisible(false);
				setContentPane(reqmain);
				req();
			}
		});
		
		
		INPUT.addActionListener(new ActionListener(){
			//@Override
			public void actionPerformed(ActionEvent e) {
				reqmain.setVisible(false);
				inpscre.setVisible(true);
				modscre.setVisible(false);
				delscre.setVisible(false);
				setContentPane(inpscre);
				inpu();
			}
		});
		
		
		MODI.addActionListener(new ActionListener(){
			//@Override
			public void actionPerformed(ActionEvent e) {
				reqmain.setVisible(false);
				inpscre.setVisible(false);
				modscre.setVisible(true);
				delscre.setVisible(false);
				setContentPane(modscre);
				mod();
			}			
		});
		
		
		DELE.addActionListener(new ActionListener(){
			//@Override
			public void actionPerformed(ActionEvent e) {
				reqmain.setVisible(false);
				inpscre.setVisible(false);
				modscre.setVisible(false);
				delscre.setVisible(true);
				setContentPane(delscre);
				del();
			}
		});
		
		BMIStatics.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				statl();
			}
		});
		HeightStatics.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				stath();
			}
		});
		WeightStatics.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				statw();
			}
		});
	}
	
	public void req()
	{
		reqmain.setBorder(new EmptyBorder(5,5,5,5));
		idpane.setBounds(10,30,60,30);
		reqmain.add(idpane);
		idfield.setBounds(75,30,130,30);
		reqbutt.setBounds(270, 30, 100, 25);
		disall.setBounds(15, 90, 110,25);
		sortid.setBounds(150, 90, 110, 25);
		sortname.setBounds(285, 90, 110, 25);
		sortwei.setBounds(15, 130, 110, 25);
		sorthei.setBounds(150, 130, 110, 25);
		sortbmi.setBounds(285, 130, 110, 25);
		reqmain.add(disall);
		reqmain.add(sortid);
		reqmain.add(sortname);
		reqmain.add(sortwei);
		reqmain.add(sorthei);
		reqmain.add(sortbmi);
		reqmain.add(idfield);
		reqmain.add(reqbutt);
		areajsp.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
		areajsp.setBounds(5,160,600,150);;
		reqarea.setEditable(false);
		reqarea.setLineWrap(true);
		reqarea.setWrapStyleWord(true);
		reqmain.add(areajsp);
		//reqarea.setText("ll\n\n\n\n\n\n\n\nkjokj\n\n\n\n\n\n\npopjo\n\n\n\n\n\n");
		reqbutt.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				String idd=idfield.getText();
				Student tmp = Frbmi.idFind(idd);
				String ans="ID   \tName   \tHeight    \tWeight   \tBmi\n\n\n";
				if(tmp!=null)
				{
					reqarea.setText(ans+tmp.Getid()+"\t"+tmp.Getname()+"\t"+tmp.Getheight()+"\t"+tmp.Getweight()+"\t"+tmp.Getbmi()+"\n");
				}
				else
				{
					reqarea.setText("Student not found! \n");
				}
			}
		});
		reqmain.add(reqbutt);
		disall.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				String ans="ID   \tName   \tHeight    \tWeight   \tBmi\n\n";
				for(Student it :Frbmi.students)
				{
					ans+= it.Getid()+"\t"+it.Getname()+"\t"+it.Getheight()+"\t"+it.Getweight()+"\t"+it.Getbmi()+"\n";
				}
				reqarea.setText(ans);
			}
		});
		sortid.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				ArrayList<Student> ttl = Frbmi.sortBy(Frbmi.new IdComp());
				String ans="ID   \tName   \tHeight    \tWeight   \tBmi\n\n";
				for(Student it :ttl)
				{
					ans+= it.Getid()+"\t"+it.Getname()+"\t"+it.Getheight()+"\t"+it.Getweight()+"\t"+it.Getbmi()+"\n";
				}
				reqarea.setText(ans);
			}
		});
		sortname.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				ArrayList<Student> ttl = Frbmi.sortBy(Frbmi.new NameComp());
				String ans="ID   \tName   \tHeight    \tWeight   \tBmi\n\n";
				for(Student it :ttl)
				{
					ans+= it.Getid()+"\t"+it.Getname()+"\t"+it.Getheight()+"\t"+it.Getweight()+"\t"+it.Getbmi()+"\n";
				}
				reqarea.setText(ans);
			}
		});
		sortwei.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				ArrayList<Student> ttl = Frbmi.sortBy(Frbmi.new WeightComp());
				String ans="ID   \tName   \tHeight    \tWeight   \tBmi\n\n";
				for(Student it :ttl)
				{
					ans+= it.Getid()+"\t"+it.Getname()+"\t"+it.Getheight()+"\t"+it.Getweight()+"\t"+it.Getbmi()+"\n";
				}
				reqarea.setText(ans);
			}
		});
		sorthei.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				ArrayList<Student> ttl = Frbmi.sortBy(Frbmi.new HeightComp());
				String ans="ID   \tName   \tHeight    \tWeight   \tBmi\n\n";
				for(Student it :ttl)
				{
					ans+= it.Getid()+"\t"+it.Getname()+"\t"+it.Getheight()+"\t"+it.Getweight()+"\t"+it.Getbmi()+"\n";
				}
				reqarea.setText(ans);
			}
		});
		sortbmi.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				ArrayList<Student> ttl = Frbmi.sortBy(Frbmi.new BmiComp());
				String ans="ID   \tName   \tHeight    \tWeight   \tBmi\n\n";
				for(Student it :ttl)
				{
					ans+= it.Getid()+"\t"+it.Getname()+"\t"+it.Getheight()+"\t"+it.Getweight()+"\t"+it.Getbmi()+"\n";
				}
				reqarea.setText(ans);
			}
		});
	}
	public void inpu()
	{
		inpscre.setBorder(new EmptyBorder(5,5,5,5));
		idpane.setBounds(10, 30, 50, 30);
		namepane.setBounds(10, 70, 50, 30);
		heipane.setBounds(10,110,50,30);
		weipane.setBounds(10,150,50,30);
		inpscre.add(idpane);
		inpscre.add(namepane);
		inpscre.add(weipane);
		inpscre.add(heipane);
		inidfie.setBounds(80,30,100,30);
		innamefie.setBounds(80,70,100,30);
		inweifie.setBounds(80,110,100,30);
		inheifie.setBounds(80, 150, 100, 30);
		inpscre.add(innamefie);
		inpscre.add(inidfie);
		inpscre.add(inweifie);
		inpscre.add(inheifie);
		inputting.setBounds(90, 200, 100, 20);
		inputting.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
				String id = inidfie.getText();
				String name = innamefie.getText();
				double weight = Double.valueOf(inweifie.getText());
				double height = Double.valueOf(inheifie.getText());
				boolean inornot = Frbmi.idExit(id);
				if(inornot==true)
				{
					int sel1101 = JOptionPane.showConfirmDialog(inpscre,"Failed. The id has already existed. ID="+id, "Warning!",JOptionPane.PLAIN_MESSAGE,JOptionPane.ERROR_MESSAGE);
				}
				else
				{
					Frbmi.inputplain(id, name, weight, height);
					int sel1102 = JOptionPane.showConfirmDialog(inpscre, "Succeed! Successfully added a student. ID="+id, "Config.", JOptionPane.PLAIN_MESSAGE);
				}
			}
		});
		inpscre.add(inputting);
	}
	public void del()
	{
		delscre.setBorder(new EmptyBorder(5,5,5,5));
		idpane.setBounds(10, 30, 40, 30);
		delscre.add(idpane);
		delid.setBounds(60, 30, 100, 30);
		delscre.add(delid);
		configdel.setBounds(70, 100, 80, 30);
		configdel.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				String id = delid.getText();
				int index=Frbmi.findStudent(id);
				if(index!=-1)
				{
					Frbmi.deletStudent(index);
					int sel1202 = JOptionPane.showConfirmDialog(inpscre, "Succeed! Successfully deleted a student. ID="+id, "Config.", JOptionPane.PLAIN_MESSAGE);
				}
				else
				{
					int sel1201 = JOptionPane.showConfirmDialog(inpscre,"Failed. The id not exist. ID="+id, "Warning!",JOptionPane.PLAIN_MESSAGE,JOptionPane.ERROR_MESSAGE);
				}
			}
		});
		delscre.add(configdel);
	}
	public void mod()
	{
		modscre.setBorder(new EmptyBorder(5,5,5,5));
		nextmodify.setBorder(new EmptyBorder(5,5,5,5));
		idpane.setBounds(10, 30, 50, 30);
		modscre.add(idpane);
		modinid.setBounds(90,30,100,30);
		modscre.add(modinid);
		nextmod.setBounds(90, 100, 100, 30);
		modscre.add(nextmod);
		namepane.setBounds(70, 10, 100, 30);
		heipane.setBounds(70, 110, 100, 30);
		weipane.setBounds(70, 70, 100, 30);
		nextmodify.add(namepane);
		nextmodify.add(heipane);
		nextmodify.add(weipane);
		modinname.setBounds(270,10,100,30);
		modinwei.setBounds(270, 70,100,30);
		modinhei.setBounds(270, 110, 100, 30);
		nextmodify.add(modinname);
		nextmodify.add(modinwei);
		nextmodify.add(modinhei);
		modifying.setBounds(300, 240, 100, 30);
		nextmodify.add(modifying);
		modquit.setBounds(300, 300, 100, 30);
		nextmodify.add(modquit);
		nextmodify.setVisible(false);
		modscre.setVisible(true);
		setContentPane(modscre);
		nextmod.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				String id=modinid.getText();
				int index=Frbmi.findStudent(id);
				if(index==-1)
				{
					int sel1301 = JOptionPane.showConfirmDialog(inpscre,"Failed. The id not exist. ID="+id, "Warning!",JOptionPane.PLAIN_MESSAGE,JOptionPane.ERROR_MESSAGE);
				}
				else
				{
					nextmodify.setVisible(true);
					modscre.setVisible(false);
					setContentPane(nextmodify);
					Student stt=Frbmi.idFind(id);
					modinname.setText(stt.Getname());
					modinwei.setText(""+stt.Getweight());
					modinhei.setText(""+stt.Getheight());
					modifying.addActionListener(new ActionListener(){
						@Override
						public void actionPerformed(ActionEvent e) {
							String name = modinname.getText();
							double weight = Double.valueOf(modinwei.getText());
							double height = Double.valueOf(modinhei.getText());
							Frbmi.deletStudent(index);
							Frbmi.inputplain(id, name, height, weight);
							int sel1202 = JOptionPane.showConfirmDialog(inpscre, "Succeed! Successfully modified a student. ID="+id, "Config.", JOptionPane.PLAIN_MESSAGE);
						}
					});
					modquit.addActionListener(new ActionListener(){
						@Override
						public void actionPerformed(ActionEvent e) {
							nextmodify.setVisible(false);
							modscre.setVisible(true);
							setContentPane(modscre);
						}
					});
				}
			}
			
		});
	}
	public void statl()
	{;
		ArrayList<Student> ttl = (ArrayList<Student>) Frbmi.sortBy(Frbmi.new BmiComp()).clone();
		int cnt=0;
		double maxbmi=0,minbmi=1000;
		for(Student it: ttl)
		{
			if(cnt==0)
			{
				maxbmi=it.Getbmi();
			}
			else if (cnt==ttl.size()-1)
			{
				minbmi=it.Getbmi();
			}
			cnt+=1;
		}
		double lenb = ((maxbmi-minbmi)/11.0);
		IntervalXYDataset xyw = changetoXY(ttl,minbmi,maxbmi,lenb,"BMI");
		JFreeChart chartb = ChartFactory.createXYBarChart("BMI Statistics","Intervals", false, "Number of Students", xyw, PlotOrientation.VERTICAL, true, false, false);
		ChartFrame chafr = new ChartFrame("BMI Statics",chartb);
		chafr.pack();
		chafr.setVisible(true);
	}
	public void stath()
	{
		ArrayList<Student> tth = (ArrayList<Student>) Frbmi.sortBy(Frbmi.new HeightComp()).clone();
		int cnt=0;
		double maxh=0,minh=10.00;
		for(Student it: tth)
		{
			if(cnt==0)
			{
				maxh=it.Getheight();
			}
			else if (cnt==tth.size()-1)
			{
				minh=it.Getheight();
			}
			cnt+=1;
		}
		double lenh =((maxh-minh)/11.0);
		System.out.println("len="+lenh);
		System.out.println(maxh+"  "+minh);
		IntervalXYDataset xyh = changetoXYh(tth,Math.min(minh, maxh),Math.max(minh, maxh), lenh,"Height");
		JFreeChart chartb = ChartFactory.createXYBarChart("Height Statistics","Intervals", false, "Number of Students", xyh, PlotOrientation.VERTICAL, true, false, false);
		ChartFrame chafr = new ChartFrame("Height Statics",chartb);
		chafr.pack();
		chafr.setVisible(true);
	}
	public void statw()
	{
		ArrayList<Student> ttw = (ArrayList<Student>) Frbmi.sortBy(Frbmi.new WeightComp()).clone();
		int cnt=0;
		double maxw=0,minw=1000;
		for(Student it: ttw)
		{
			if(cnt==0)
			{
				maxw=it.Getweight();
			}
			else if (cnt==ttw.size()-1)
			{
				minw=it.Getweight();
			}
			cnt+=1;
		}
		System.out.println(""+maxw+"  "+minw);
		double lenw=((maxw-minw)/11.0);
		IntervalXYDataset xyw = changetoXYw(ttw,Math.min(minw, maxw),Math.max(minw, maxw),lenw,"Weight");
		JFreeChart chartb = ChartFactory.createXYBarChart("Weight Statistics","Intervals", false, "Number of Students", xyw, PlotOrientation.VERTICAL, true, false, false);
		ChartFrame chafr = new ChartFrame("Weight Statics",chartb);
		chafr.pack();
		chafr.setVisible(true);
	}
	public IntervalXYDataset changetoXY(ArrayList<Student> al, double l, double r,double len, String fla)
	{
		XYSeries xys = new XYSeries(fla);
		int [] count= new int[1000];
		for(Student it: al)
		{
			count[(int)(Math.abs(((it.Getbmi()-l)/len)))]+=1;
		}
		for(int i=0;i<10;i++)
		{
			xys.add(len*i+l, count[i]);
		}
		XYSeriesCollection xysc = new XYSeriesCollection();
		xysc.addSeries(xys);
		return new XYBarDataset(xysc, 1.0);
	}
	public IntervalXYDataset changetoXYh(ArrayList<Student> al, double l, double r,double len, String fla)
	{
		XYSeries xys = new XYSeries(fla);
		int [] count= new int[1000];
		for(Student it: al)
		{
			count[(int)(Math.abs(((it.Getheight()-l)/len)))]+=1;
		}
		for(int i=0;i<10;i++)
		{
			xys.add(len*i+l, count[i]);
		}
		XYSeriesCollection xysc = new XYSeriesCollection();
		xysc.addSeries(xys);
		return new XYBarDataset(xysc, 1.0);
	}
	public IntervalXYDataset changetoXYw(ArrayList<Student> al, double l, double r,double len, String fla)
	{
		XYSeries xys = new XYSeries(fla);
		int [] count= new int[1000];
		for(Student it: al)
		{
			count[(int)(Math.abs(((it.Getweight()-l)/len)))]+=1;
		}
		for(int i=0;i<10;i++)
		{
			xys.add(len*i+l, count[i]);
		}
		XYSeriesCollection xysc = new XYSeriesCollection();
		xysc.addSeries(xys);
		return new XYBarDataset(xysc, 1.0);
	}
}
class OOBMI
{
	public class  Student
	{
		private  String id;
		private  String name;
		private  double height;
		private  double weight;
		private  double bmi;
		public Student()
		{
			this.id="";
			this.name="";
			this.height=(float) 1.00;
			this.weight=(float) 1.00;
			this.bmi=this.weight/(this.height*this.height);
		}
		public Student(String id,String names,double weights,double heights)
		{
			this.id=id;
			this.name=names;
			this.height=heights;
			this.weight=weights;
			this.bmi=this.weight/(this.height*this.height);
		}
		public void SetInfo(String ids,String names,double weights ,double heights)
		{
			this.id=ids;
			this.name=names;
			this.height=heights;
			this.weight=weights;
			this.bmi=this.weight/(this.height*this.height);
		}
		public void Setname(String name)
		{
			this.name=name;
		}
		public void Setheight(float height)
		{
			this.height=height;
			this.bmi=this.weight/(this.height*this.height);
		}
		public void Setweight(float weight)
		{
			this.weight=weight;
			this.bmi=this.weight/(this.height*this.height);
		}
		public String Getid()
		{
			return id;
		}
		public String Getname()
		{
			return name;
		}
		public double Getheight()
		{
			return height;
		}
		public double Getweight()
		{
			return weight;
		}
		public double Getbmi()
		{
			return bmi;
		}
		public int CompareToid(Student stu0)
		{
			return this.id.compareTo(stu0.id);
		}
		public int CompareToname(Student stu0)
		{
			return this.name.compareTo(stu0.name);
		}
		public int CompareToheight(Student stu0)
		{
			if(this.height<stu0.height)
				return 1;
			else if(this.height==stu0.height)
				return 0;
			else return -1;
		}
		public int CompareToweight(Student stu0)
		{
			if(this.weight<stu0.weight)
				return 1;
			else if(this.weight==stu0.weight)
				return 0;
			else return -1;
		}
		public int CompareTobmi(Student stu0)
		{
			if(this.bmi<stu0.bmi)
				return 1;
			else if(this.bmi==stu0.bmi)
				return 0;
			else return -1;
		}
	}
	public static ArrayList<Student> students=new ArrayList<Student>();
	public static int cnt=0;
	public static String filepath="";
	public void Input()
	{
		Scanner in = new Scanner(System.in);
		System.out.print("id:");
		String id=in.nextLine();
		if(idExit(id))
		{
			System.out.println("Student already exist");
			return;
		}
		System.out.print("name");
		String name=in.nextLine();
		System.out.print("height");
		double height=in.nextFloat();in.nextLine();
		System.out.print("weight");
		double weight=in.nextFloat();
		System.out.println("ID="+id+"\t Name="+name+"\t Weight="+weight+"\t Height="+height);
		Student stt=new Student(id,name,weight,height);
		students.add(stt);
		return;
	}
	public void inputStudents()
	{
		Scanner in =new Scanner(System.in);
		System.out.print("\n Continue? (y/n) ");
		String ans=in.nextLine();
		while(ans.equals("y")==true)
		{
			cnt+=1;
			System.out.print("id:");
			String id=in.next();
			in.nextLine();
			if(idExit(id))
			{
				System.out.println("Student already exist");
				continue;
			}
			System.out.print("name:");
			String name=in.nextLine();
			System.out.print("height:");
			double height=in.nextFloat();in.nextLine();
			System.out.print("weight:");
			double weight=in.nextFloat();
			double bmi=weight/(height*height);
			Student stt=new Student(id,name,weight,height);
			System.out.println("ID="+id+"\t Name="+name+"\t Weight="+weight+"\t Height="+height+"\t Bmi="+bmi);
			students.add(stt);
			System.out.print("Continue? (y/n) ");
			ans=in.nextLine();
		}
		return;
	}
	public void genStudents(int n)
	{
		String model="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		String number="0123456789";
		Random r=new Random();
		cnt=n;
		for(int i=0;i<n;i++)
		{
			int len=r.nextInt(20);
			StringBuffer sbb = new StringBuffer();
			for(int x=0;x<n;x++)
			{
				int indexx=r.nextInt(model.length());
				sbb.append(model.substring(indexx, indexx+1));
			}
			String name=sbb.toString();
			StringBuffer sbc=new StringBuffer();
			for(int x=0;x<15;x++)
			{
				int indexx=r.nextInt(number.length());
				sbc.append(number.charAt(indexx));
			}
			String ids=sbc.toString();
			if(idExit(ids))
			{
				i--;
				continue;
			}
			double weight=Math.abs(r.nextGaussian());
			double height=Math.abs(r.nextGaussian());
			Student stt=new Student(ids,name,weight,height);
			students.add(stt);
			System.out.println("ID="+ids+"\t Name="+name+"\t Weight="+weight+"\t Height="+height);
		}
		return;
	}
	public void inputplain(String id,String name,double height,double weight)
	{
		Student stt=new Student(id,name,(float)weight,(float)height);
		students.add(stt);
		cnt = students.size();
		return;
	}
	public boolean idExit(String id)
	{
		if(students==null) 
		{
			System.out.println("Warning: null students");
			return false;
		}
		for(Student item : students)
		{
			if(item.Getid().equals(id))
			{
				return true;
			}
		}
		return false;
	}
	public Student idFind(String id)
	{
		if(students==null) 
		{
			System.out.println("Warning: null students");
			return null;
		}
		for(Student item : students)
		{
			if(item.Getid().equals(id))
			{
				return item;
			}
		}
		return null;
	}
	public double AverBmi()
	{
		double sum=0;
		Iterator<Student> it = students.iterator();
		while(it.hasNext())
		{
			cnt+=1;
			sum+=((Student) it.next()).Getbmi();
		}
		return (sum/(cnt*1.0));
	}
	public double MidBmi()
	{
		int cnn=0;
		int flag=0;
		double sum=0;
		Iterator<Student> it =students.iterator();
		while(it.hasNext())
		{
			cnn+=1;
			if(cnn==cnt/2&&cnt%2==0)
			{
				return ((Student) it.next()).Getbmi();
			}
			else if((cnn==cnt/2&&cnt%2==1))
			{
				sum+=((Student) it.next()).Getbmi();
			}
			if(cnn==cnt/2+1)
			{
				return (sum/2.0);
			}
		}
		return 0;
	}
	public double MostBmi()
	{
		int [] sum=new int[40000];
		final double prec=1e-3;
		int maxx=0,index=0;
		for(Student it: students)
		{
			sum[(int)it.Getbmi()*1000]+=1;
		}
		for(int i=1;i<40000;i++)
		{
			if(maxx<sum[i])
			{
				index=i;
				maxx=sum[i];
			}
		}
		return (index*1.00/1000.0);
	}
	public double SquareBiasBmi()
	{
		double bias=0;
		double aver=AverBmi();
		for(Student item: students)
		{
			bias+=(item.Getbmi()-aver)*(item.Getbmi()-aver);
		}
		return bias/cnt;
	}
	public void printStatics(ArrayList<Student> stu)
	{
		for (Student items:stu)
		{
			System.out.println("ID="+items.Getid()+"\t Name="+items.Getname()+"\t Weight="+items.Getweight()+"\t Height="+items.Getheight()+"\t Bmi="+items.Getbmi());
		}
		System.out.println("\n Aver="+AverBmi()+"\n MidBmi="+MidBmi()+"\n MostBmi="+MostBmi()+"\n SquareBiasBmi="+SquareBiasBmi());
		return;
	}
	public void saveFile(ArrayList<Student> students, String filename) throws FileNotFoundException
	{
		PrintWriter pw= new PrintWriter(filename);
		for(Student items:students)
		{
			pw.println(items.Getid()+" "+items.Getname()+" "+items.Getweight()+" "+items.Getheight()+" "+items.Getbmi());
		}
		return;
	}
	public ArrayList<Student> readFile(String filename) throws IOException
	{
		ArrayList<Student> ast = new ArrayList<Student>();
		Scanner in = new Scanner(Paths.get(filename));
		while(in.hasNext())
		{
			Student stmp= new Student(in.next(),in.next(),in.nextFloat(),in.nextFloat());
			ast.add(stmp);
		}
		return ast;
	}
	public int findStudent(String id)
	{
		int index=0;
		for(Student items:students)
		{
			index+=1;
			if(items.Getid().equals(id))
			{
				System.out.println("ID="+items.Getid()+"\t Name="+items.Getname()+"\t Weight="+items.Getweight()+"\t Height="+items.Getheight()+"\t Bmi="+items.Getbmi());
				return index-1;
			}
		}
		return -1;
	}
	public void modifyStudent(int index,String id)
	{
		Scanner in= new Scanner(System.in);
		System.out.println("Input Student name:");
		students.remove(index);
		String name=in.nextLine();
		System.out.println("Input Student height:");
		double height = in.nextFloat();
		System.out.println("Input Student weight:");
		double weight=in.nextFloat();
		Student tmp=new Student(id,name,weight,height);
		students.add(tmp);
		return;
	}
	public void deletStudent(int index)
	{
		students.remove(index);
		return;
	}
	public ArrayList<Student> sortBy(Comparator<Student> c)
	{
		ArrayList<Student> als = (ArrayList<Student>) students.clone();
		als.sort(c);
		return als;
	}
	class IdComp implements Comparator<Student>
	{
		@Override
		public int compare(Student o1, Student o2)
		{
			return o1.CompareToid(o2);
		}
	}
	class NameComp implements Comparator<Student>
	{
		@Override
		public int compare(Student o1, Student o2)
		{
			return o1.CompareToname(o2);
		}
	}
	class BmiComp implements Comparator<Student>
	{
		@Override
		public int compare(Student o1,Student o2)
		{
			return o1.CompareTobmi(o2);
		}
	}
	class WeightComp implements Comparator<Student>
	{
		@Override
		public int compare(Student o1, Student o2)
		{
			return o1.CompareToweight(o2);
		}
	}
	class HeightComp implements Comparator<Student>
	{
		@Override
		public int compare(Student o1,Student o2)
		{
			return o1.CompareToheight(o2);
		}
	}
}