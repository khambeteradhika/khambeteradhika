#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<process.h>
class product
{
	int pno;
	char pname[50];
	float price,dis;
	public:
	void getproduct()
	{
		cout<<"\nenter product no.-->\t" ;
		cin>>pno;
		cout<<"\nenter product name-->\t" ;
		gets(pname);
		cout<<"\nenter the price of product-->\t";
		cin>>price;
		cout<<"\nenter the discount on product(%)-->\t";
		cin>>dis;
	}
	void putproduct()
	{
		cout<<"\nproduct no.-->"<<pno;
		cout<<"\nproduct name-->";
		puts(pname);
		cout<<"\nproduct price-->"<<price;
		cout<<"\ndiscount on product-->"<<dis;
	}
	int retpno()
	{
		return pno;
	}
	char* retpname()
	{
		return pname;

	}
	float retprice()
	{
		return price;
	}
	float retdis()
	{
		return dis;
	}
};
//CLASS ENDS
fstream fp;//global declaration of object
product pr;
//***************************************************************
// function to write in file
//****************************************************************

void create_product()        //to create product in file
{
	fp.open("Market.txt",ios::out | ios::app);
	pr.getproduct();
	fp.write((char*)& pr,sizeof(product));
	fp.close();
	cout<<"product is created\n\n";
	getch();
}
//***************************************************************
// function to read all records from file
//****************************************************************
void show_all()        //to show all contents of file
{
	clrscr();
	fp.open("Market.txt",ios::in);
	fp.read((char*)&pr,sizeof(product));
	while(fp.read((char*)&pr,sizeof(product)))
	{
		pr.putproduct();
		cout<<"\n\n=======================\n";
		getch();
	}
	fp.close();
	getch();
}
//***************************************************************
// function to read specific record from file
//****************************************************************
void get_specific()	//to find a prticular product
{
	clrscr();
	int n,flag=0;
	cout<<"\n\n for finding specific product\n";
	cout<<"enter the product number-->\n";
	cin>>n;
	fp.open("Market.txt",ios::in);
	fp.read((char*)&pr,sizeof(product));
	while(fp.read((char*)&pr,sizeof(product)))
	{
		if(pr.retpno() == n)
		{
			clrscr();
			pr.putproduct();
			flag=1;
			break;

		}
		fp.close();
	}
	if(flag==0)
       
		cout<<"\n\n!!!Product not found!!!\n";
		getch();
	
}
//***************************************************************
// function to modify record of file
//****************************************************************
void modify_product()
{
	
	int no,found = 0;
	clrscr();
	cout<<"\n\nTo modify\n";
	cout<<"Enter the product no.\t\t";
	cin>>no;
	fp.open("Market.txt",ios::in | ios::out);
	
	while(fp.read((char * ) & pr, sizeof(product)) && found == 0)
	{   
		
		if(pr.retpno()==no)
		{
			pr.putproduct();
			cout<<"enter the new product details:\n\n";
			pr.getproduct();
			int pos = -1 * sizeof(pr);
			fp.seekp(pos, ios::cur);
			fp.write((char*)& pr,sizeof(product));
			cout<<"\n\n\trecord updated";
			found=1;
			
		}
	}    
		fp.close();
		if(found == 0)

			cout<<"product not found";
		     getch();
	
	
}
void delete_product()
{
	int no;
	cout<<"\n\n To delete record\n";
	cout<<"enter the product no. which is to be deleted:";
	cin>>no;
	fp.open("Market.txt",ios::in | ios::out );
	fstream fp2;
	fp2.open("tempo.txt",ios::out);
	fp.seekp(0, ios::beg);
	while(fp.read((char*) & pr,sizeof(product)))
	{
		if(pr.retpno() !=no)
		{
			fp2.write((char*) & pr,sizeof(product));
		}
	}
		fp2.close();
		fp.close();
		remove("Market.txt");
		rename("tempo.txt","Market.txt");
		cout<<"record is deleted";
		getch();

}
void menu()	//to display all product price list
{

	clrscr();
	fp.open("Market.txt",ios::in);
	if(!fp)
	{
		cout<<"ERROR!! FILE NOT TO BE OPENED!!!\n\n";
		cout<<"Program is closing............";
		getch();
		exit(0);
	}
	cout<<"\n\nProduct Menu\n\n";
	cout<<"================================\n";
	cout<<"\tPNO.\t\tNAME\t\tPRICE\n";
	cout<<"=================================\n";

	while (fp.read((char * ) & pr, sizeof(product)))
    {
	cout << pr.retpno() << "\t\t" << pr.retpname() << "\t\t" << pr.retprice() << endl;
    }
	fp.close();
}
void place_order()	//to place order and generate bill
{
	//product po;
	int order_arr[50],quant[50],c=0;
	float amt,damt,total=0;
	char ch='Y';
	menu();
	cout<<"======================================\n";
	cout<<"PLACE YOUR ORDER\n";
	cout<<"======================================\n";
	do
	{
		cout<<"enter the product no:\n";
		cin>>order_arr[c];
		cout<<"\nQuantity in number:\n";
		cin>>quant[c];
		c++;
		cout<<"\nyou want to order another product?(y/n)";
		cin>>ch;
	 }
	 while(ch =='y'||ch =='Y');
	 cout<<"Thank you for placing order\n";
	 getch();
	 clrscr();
	 cout<<"###########################################INVOICE########################################\n\n";
	 cout<<"\t Pr No.\t\tPrName\t\tQuantity\t\tPrice\t\tAmount\t\tAmount after discount\n";
	 fp.open("Market.txt",ios::in);
	 for(int x = 0 ; x <= c; x++)
	 {
		fp.read((char*)&pr,sizeof(product));

		while(!fp.eof())
		{

			if(pr.retpno()==order_arr[x])
			{
				amt = pr.retprice()*quant[x];
				damt = amt-(amt*pr.retdis()/100);
				cout<<"\n\t"<<order_arr[x]<<"\t\t"<<pr.retpname()<<"\t\t"<<pr.retprice()<<"\t\t"<<amt<<"\t\t"<<damt<<endl;
				total=+damt;
				break;
			}
			  fp.read((char*)&pr,sizeof(product));
		}

	 }
	 fp.close();
	 cout<<"\n\n\t\t\tTOTAL=\t"<<total;
	 getch();

}
void admin_menu()
{
	clrscr();
	char ch2;
	cout<<"\n\n\n\tADMIN MENU";
	cout<<"\n1->\tCREATE PRODUCT";
	cout<<"\n2->\tDISPLAY ALL PRODUCTS";
	cout<<"\n3->\tQYUERY";
	cout<<"\n4->\tMODIFY PRODUCT";
	cout<<"\n5->\tDELETE PRODUCT";
	cout<<"\n6->\tVIEW PRODUCT MENU";
	cout<<"\n7->\tBACK TO MAIN MENU";
	cout<<"Enter you choice from 1-7:\t\t";
	cin>>ch2;
	switch(ch2)
	{
		case '1':
			clrscr();
			create_product();
			break;
		case '2':
			show_all();
			break;
		case '3':
			clrscr();
			get_specific();
			break;
		case '4':
			modify_product();
			break;
		case '5':
			delete_product();
			break;
		case'6':
			menu();
			getch();
			break;
		case '7':
			break;
		default:
			cout<<"\a";
			admin_menu();
	}
}
void main() 	//main function
{
	char ch;
	clrscr();
	do
	{
		cout<<"\n\n\tMAIN MENU";
		cout<<"\n\n\t1->\tCUSTOMER";
		cout<<"\n\n\t2->\tADMINISTRATOR";
		cout<<"\n\n\t3->\tEXIT";
		cout<<"\n\n\tSelect your choice:\t";
		cin>>ch;
		switch(ch)
		{
			case '1':
				clrscr();
				place_order();
				break;
			case '2':
				clrscr();
				admin_menu();
				break;
			case '3':
				exit(0);
			default:
				cout<<"\a";

		}


	}
	while(ch!='3');
}










