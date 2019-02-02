
 //***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class medicine
{
 int bno,qty1;
 char medicine_name[50],mfg[10],exp_date[10];
 float price,qty,tax,dis;
 public:
	void create_medicine()
	{
	 cout<<"\n1. Please Enter The batch No:  ";
	 cin>>bno;
	 cout<<"\n\n2. Please Enter The Name of The medicine:  ";
	 gets(medicine_name);
	 cout<<endl<<endl<<"3. Manufatcuring date(dd/mm/yy) : ";
	 gets(mfg);
			 cout<<endl;
	 cout<<endl<<"4. Expiry date(dd/mm/YY)  : ";
	 gets(exp_date);
	 cout<<"\n5. Please Enter The Price of The medicine:  ";
	 cin>>price;
	 cout<<"\n6. Please Enter The Discount (%):  ";
	 cin>>dis;
	 cout<<"\n7.Enter the quantity of the medicine: ";
	 cin>>qty1;
	 }

	void show_medicine()
	{
	 cout<<"\n1. The batch No. of The medicine : "<<bno;
	 cout<<"\n2. The Name of The medicine : ";
	 puts(medicine_name);
	 cout<<endl<<endl<<"3. Manufatcuring date: ";
			 puts(mfg);
	 cout<<endl<<endl<<"4. expiry date  : ";
	 puts(exp_date);
	 cout<<"\n5. The Price of The medicine : "<<price;
	 cout<<"\n6. Discount : "<<dis;
	 }

  int  retbno()
  {return bno;}

  float retprice()
  {return price;}

  char* retname()
  {return medicine_name;}

  int retdis()
  {return dis;}

  char* retmfg()
  {return mfg;}

  char* retexp()
  {return exp_date;}

  int retqty()
  {return qty1;}

};         //class ends here



//***************************************************************
//    	global declaration for stream object, object
//****************************************************************

 fstream fp;
 medicine pr;


//***************************************************************
//    	function to write in file
//****************************************************************

void write_medicine()
	{
	 fp.open("Shop.dat",ios::out|ios::app);
	 pr.create_medicine();
	 fp.write((char*)&pr,sizeof(medicine));
	 fp.close();
	 cout<<"\n\nThe medicine Has Been Created.  ";
	 getch();
	}


//***************************************************************
//    	function to read all records from file
//****************************************************************


void display_all()
{
	 clrscr();
	 cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	 fp.open("Shop.dat",ios::in);
	 while(fp.read((char*)&pr,sizeof(medicine)))
	{
	 pr.show_medicine();
	 cout<<"\n\n=================================================\n";
	 getch();
	 }
	 fp.close();
	 getch();
}


//***************************************************************
//    	function to read specific record from file
//****************************************************************


void display_sp(int n)
{
	 int flag=0;
	 fp.open("Shop.dat",ios::in);
	 while(fp.read((char*)&pr,sizeof(medicine)))
	{
	 if(pr.retbno()==n)
		{
		 clrscr();
		 pr.show_medicine();
		 flag=1;
		}
	}
	 fp.close();
if(flag==0)
 cout<<"\n\nRecord does not exist";
	 getch();
}


//***************************************************************
//    	function to modify record of file
//****************************************************************


void modify_medicine()
{
	 int no,found=0;
	 clrscr();
	 cout<<"\n\n\tTo Modify:  ";
	 cout<<"\n\n\tPlease Enter The batch No. of The medicine: ";
	 cin>>no;
	 fp.open("Shop.dat",ios::in|ios::out);
	 while(fp.read((char*)&pr,sizeof(medicine)) && found==0)
	 {
		 if(pr.retbno()==no)
				{
			 pr.show_medicine();
			 cout<<"\nPlease Enter The New Details of medicine: "<<endl;
			 pr.create_medicine();
			 int pos=-1*sizeof(pr);
			 fp.seekp(pos,ios::cur);
			 fp.write((char*)&pr,sizeof(medicine));
			 cout<<"\n\n\t Record Updated. ";
			 found=1;
		 }
	 }
	 fp.close();
	 if(found==0)
	 cout<<"\n\n Record Not Found.  ";
	 getch();
}




//***************************************************************
//    	function to display all medicines price list
//****************************************************************

	 void menu()
	 {
	  clrscr();
	  fp.open("Shop.dat",ios::in);
	  if(!fp)
	  {
		 cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File. ";
		 cout<<"\n\n\n Program is closing ....";
		 getch();
		 exit(1);
	  }
	  cout<<"\t\t\t\t MAX MEDICARE"<<endl;
	  cout<<"================================================================================";
	  cout<<"\n\n\t\t\t\tSTOCK INVENTORY\n\n";
	  cout<<"===============================================================================\n";
	  cout<<"B.NO.\tNAME\t\tQty\t\tMfg\t\tExp\t\tPRICE\n";
	  cout<<"================================================================================\n";

		while(fp.read((char*)&pr,sizeof(medicine)))
	 {
		cout<<pr.retbno()<<"   "<<pr.retname()<<"\t\t "<<pr.retqty()<<"\t      "<<pr.retmfg()<<"\t     "<<pr.retexp()<<"\t         "<<pr.retprice()<<endl;
	}
	  fp.close();
}




//***************************************************************
//    	function to place order and generating bill for medicines
//****************************************************************

	void place_order()
	{
	 int  order_arr[50],quan[50],c=0;
	 float amt,damt,total=0;
	 char ch;
	 menu();
	 cout<<"\n================================================================================";
	 cout<<"\n\t\t\t\tPLACE YOUR ORDER";
	 cout<<"\n================================================================================\n";
	 do{
	 a:
	 cout<<"\n\nEnter The batch No. Of The medicine : ";
	 cin>>order_arr[c];
		if(order_arr[c]!=pr.retbno())
			{cout<<"\nyou have entered the invalid batch no......try again";
			 goto a ;
			}
	 cout<<"\nQuantity in number : ";
	 cin>>quan[c];
	 if(quan[c]>pr.retqty())
			{cout<<"\nInsufficient stock!!!!!\n You can place order within precscribed quantity:  ";
			cout<<pr.retqty();

			 goto a ;
			}
	 c++;
	 cout<<"\nDo You Want To Order Another medicine ? (y/n)";
	 cin>>ch;
	 }while(ch=='y' ||ch=='Y');
	 cout<<"\n\nThank You For Placing The Order";getch();clrscr();
		cout<<"\n\n***********************************INVOICE***********************************\n";
		cout<<"\nB No.\tMed Name\tQuantity \tPrice \tAmount \tDiscounted amount\n";
		for(int x=0;x<=c;x++)
	{
		 fp.open("Shop.dat",ios::in);
		 fp.read((char*)&pr,sizeof(medicine));
		  while(!fp.eof())
			{
			if(pr.retbno()==order_arr[x])
				{
				 amt=pr.retprice()*quan[x];
				 damt=amt-(amt*pr.retdis()/100);
				 cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
				 total+=damt;
				}
			fp.read((char*)&pr,sizeof(medicine));
			}

		 fp.close();
	 }
		 cout<<"\n\n\t\t\t\t\t\tTOTAL= "<<total;
	 getch();
	 }




//***************************************************************
//    	ADMINSTRATOR MENU FUNCTION
//****************************************************************
void admin_menu()
{
  clrscr();
  int ch2;
  cout<<"============================================================================";
  cout<<"\t\t\t\t\tMAX MEDICARE";
  cout<<endl<<"====================================================================";
  cout<<"\n\n\n\tADMIN MENU";
  cout<<"\n\n\t1.CREATE medicine";
  cout<<"\n\n\t2.DISPLAY ALL medicineS";
  cout<<"\n\n\t3.QUERY ";
  cout<<"\n\n\t4.MODIFY medicine";
  cout<<"\n\n\t5.VIEW medicine MENU";
  cout<<"\n\n\t6.BACK TO MAIN MENU";
  cout<<"\n\n\tPlease Enter Your Choice (1-6):  ";
  cin>>ch2;
  switch(ch2)
  {
	 case 1: clrscr();
			write_medicine();
			break;
	 case 2: display_all();break;
	 case 3:
			 int num;
			 clrscr();
			 cout<<"\n\n\tPlease Enter The medicine No:  ";
			 cin>>num;
			 display_sp(num);
			 break;
		case 4:modify_medicine();break;

		case 5:menu();
			 getch();
		case 6 :break;
		default:admin_menu();
	}
}


//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


void main()
{
  char ch;


  do
	 {
	  clrscr();
  cout<<"================================================================================";
  cout<<"\t\t\t\tMAX MEDICARE\n================================================================================";

	  cout<<"\n\n\n\tMAIN MENU";
	  cout<<"\n\n\t01. CUSTOMER";
	  cout<<"\n\n\t02. ADMINISTRATOR";
	  cout<<"\n\n\t03. EXIT";
	  cout<<"\n\n\tPlease Select Your Option (1-3):  ";
	  ch=getche();
	  switch(ch)
	  {
		 case '1': clrscr();
				place_order();
				getch();
				break;
		  case '2': admin_menu();
				 break;
		  case '3':exit(0);
		  default :cout<<"\a";
	}
	 }while(ch!='3');
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************












