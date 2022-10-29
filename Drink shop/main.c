#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define fileName "data.txt"

int selectMainCase();
void editStock();
int readData();
void printAllProduct();
int selectCase(char arr[4][20]);
void addProduct();
void editProduct();
void clearProduct();
void deleteProduct();
void buyProducts();
void searchProduct();
void printAllProductInCart();
void addToCart();
void addAnountherToCart();
void removeFromCart();
void payBill();
void clearCart(int isPay);

struct product
{
	char name[25];
	int amount;
	int price;
} products[100], cart[100];

int numberOfProducts = 0;
int numberOfProductsInCart = 0;

int main()
{
	int processType = -1;
	char allProcess[4][20] = {"Edit Stock", "Buy Products", "Show Products", "Exit"};

	readData();
	printf("===== Welcome to beverage vending machine =====\n");

	while (processType != 3)
	{
		// printf("DEBUG -> processType = %d \n", processType);
		switch (processType)
		{
		case 0:
			editStock();
			processType = -1;
			break;
		case 1:
			printAllProduct();
			buyProducts();
			processType = -1;
			break;
		case 2:
			printAllProduct();
			processType = -1;
			break;
		default:
			processType = selectCase(allProcess);
			// printf("DEBUG -> %s\n", allProcess[processType]);
			break;
		}
	}

	return 0;
}

int readData()
{
	char ch;

	FILE *fp;

	clearProduct();
	fp = fopen(fileName, "r"); // read mode

	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		return 0;
	}

	// printf("read file suscess\nThe contents of %s file are:\n", file_name);

	int count = 0;
	char str[60] = "";
	int iter = 0;

	ch = fgetc(fp);
	while (ch != EOF)
	{
		// printf("%c", ch);

		if (ch != ',' && ch != '\n')
		{
			str[iter] = ch;
			iter++;
		}
		else
		{
			// printf("DEBUG -> index: %d %s\n", count % 3, str);
			if (count % 3 == 0)
				strcpy(products[count / 3].name, str);
			else if (count % 3 == 1)
				products[count / 3].amount = atoi(str);
			else if (count % 3 == 2)
			{
				products[count / 3].price = atoi(str);
				numberOfProducts += 1;
				// printf("products number %d -> %s %d %d", numberOfProducts, products[numberOfProducts - 1].name, products[numberOfProducts - 1].amount, products[numberOfProducts - 1].price);
			}
			// strcpy(str, "");
			for (int i = 0; i < iter; i++)
				str[i] = '\0';
			// printf("clear");
			// printf("DEBUG -> after index: %d %s\n", count % 3, str);
			iter = 0;
			count += 1;
		}

		ch = fgetc(fp);
	}

	printf("\n");

	fclose(fp);
	return 0;
}

int selectCase(char arr[4][20])
{
	int n;
	char text[5];
	printf("\n\tPlease select what you want to do\n");
	printf("1 %-20s   2 %-20s   3 %-20s   4 %-20s\nEnter you choice: ", arr[0], arr[1], arr[2], arr[3]);
	scanf("%s", &text);
	n = (int)(text[0]) - '0';
	// printf("DEBUG -> %d", n);
	--n;
	if (n >= 0 && n <= 2)
		return n;
	else
		return 3;
}

void editStock()
{
	int n;
	int state = -1;
	char allCase[4][20] = {"Add Product", "Edit Product", "Delete Product", "Back"};
	printAllProduct();
	while (state != 3)
	{
		state = selectCase(allCase);
		switch (state)
		{
		case 0:
			addProduct();
			printAllProduct();
			break;
		case 1:
			editProduct();
			printAllProduct();
			break;
		case 2:
			deleteProduct();
			printAllProduct();
			break;
		default:
			break;
		}
	}
}

void addProduct()
{
	char content[100];
	FILE *fp;
	printf("Please enter your product detail in format\n ** name(no space),amount(integer),price(integer)\n");
	printf("Your input is: ");
	scanf("%s", &content);

	fp = fopen(fileName, "a+");

	// printf("DEBUG -> content: %s", content);
	fprintf(fp, "%s\n", content);

	fclose(fp);
	numberOfProducts++;
	readData();
}

void editProduct()
{
	int id, temp = 1;
	char content[100];
	char ch;
	int done = 0;
	FILE *fileptr1, *fileptr2;

	printf("Please enter your product number: ");
	scanf("%d", &id);
	if (id > 0 && id <= numberOfProducts)
	{
		printf("Enter new product detail in format\n ** name(no space),amount(integer),price(integer)\n");
		printf("Your input is: ");
		scanf("%s", &content);

		fileptr1 = fopen(fileName, "r");
		rewind(fileptr1);

		fileptr2 = fopen("replica.c", "w");
		ch = getc(fileptr1);
		while (ch != EOF)
		{
			if (ch == '\n')
				temp++;
			if (temp != id)
				putc(ch, fileptr2);
			else if (temp == id && done == 0)
			{
				if (id > 1)
					fprintf(fileptr2, "\n%s", content);
				else
					fprintf(fileptr2, "%s", content);
				done = 1;
			}
			ch = getc(fileptr1);
		}

		// printf("DEBUG -> content: %s", content);
		fclose(fileptr1);
		fclose(fileptr2);
		remove(fileName);
		//rename the file replica.c to original name
		rename("replica.c", fileName);
		readData();
	}
	else
		printf("---->>> This product's number is not valid\n");
}

void deleteProduct()
{
	int id, temp = 1;
	char content[100];
	char ch;
	int done = 0;
	FILE *fileptr1, *fileptr2;

	printf("Please enter your product's number: ");
	scanf("%d", &id);
	if (id > 0 && id <= numberOfProducts)
	{
		fileptr1 = fopen(fileName, "r");
		rewind(fileptr1);

		fileptr2 = fopen("replica.c", "w");
		ch = getc(fileptr1);

		while (ch != EOF)
		{
			if (ch == '\n')
				temp++;
			if (temp != id)
				putc(ch, fileptr2);
			ch = getc(fileptr1);
		}

		// printf("DEBUG -> content: %s", content);
		fclose(fileptr1);
		fclose(fileptr2);
		remove(fileName);
		//rename the file replica.c to original name
		rename("replica.c", fileName);
		readData();
	}
	else
		printf("---->>> This product's number is not valid\n");
}

void printAllProduct()
{
	int i = 0;
	// printf("numberOfProducts: %d\n", numberOfProducts);
	printf("=============================================\n");
	printf("\tThis is all product\n");
	printf("No.\t\tName\t\tamount\tprice\n");
	for (i; i < numberOfProducts; i++)
		printf("%-3d %-25s\t %-3d\t %-3d\n", i + 1, products[i].name, products[i].amount, products[i].price);
	printf("=============================================\n");
}

void clearProduct()
{
	char str[25] = "";
	for (int i = 0; i < numberOfProducts; i++)
	{
		strcpy(products[i].name, str);
		products[i].amount = 0;
		products[i].price = 0;
		numberOfProducts = 0;
	}
}

void buyProducts()
{
	int processType = -1;
	char allProcess[4][20] = {"Add Remove Pay", "Search Product", "Show My Cart", "Back"};

	while (processType != 3)
	{
		switch (processType)
		{
		case 0:
			addToCart();
			processType = -1;
			break;
		case 1:
			searchProduct();
			processType = -1;
			break;
		case 2:
			printAllProductInCart();
			processType = -1;
			break;
		default:
			processType = selectCase(allProcess);
			// printf("DEBUG -> %s\n", allProcess[processType]);
			break;
		}
	}
}

void searchProduct()
{
	char targetName[25];
	int done = 0;
	printf("Please enter product name: ");
	scanf("%s", &targetName);

	for (int i = 0; i < numberOfProducts; i++)
	{
		if (strcmp(products[i].name, targetName) == 0 && done == 0)
		{
			printf("No.\t\tName\t\tamount\tprice\n");
			printf("%-3d %-25s\t %-3d\t %-3d\n", i + 1, products[i].name, products[i].amount, products[i].price);
			done = 1;
			break;
		}
	}
	if (done == 0)
		printf("---->>> don't have this product\n");
}

void printAllProductInCart()
{

	if (numberOfProductsInCart > 0)
	{
		int i = 0;
		// printf("numberOfProducts: %d\n", numberOfProducts);
		printf("=============================================\n");
		printf("\tThis is all product in cart\n");
		printf("No.\t\tName\t\tamount\tprice\n");
		for (i; i < numberOfProductsInCart; i++)
			printf("%-3d %-25s\t %-3d\t %-3d\n", i + 1, cart[i].name, cart[i].amount, cart[i].price);
		printf("=============================================\n");
	}
	else
		printf("---->>> Your cart is empty\n");
}

void addToCart()
{
	int processType = -1;
	char allProcess[4][20] = {"Add Another", "Remove My Item", "Pay Bill", "Back"};

	while (processType != 3)
	{
		switch (processType)
		{
		case 0:
			addAnountherToCart();
			printAllProductInCart();
			processType = -1;
			break;
		case 1:
			removeFromCart();
			printAllProductInCart();
			processType = -1;
			break;
		case 2:
			payBill();
			processType = -1;
			break;
		default:
			processType = selectCase(allProcess);
			// printf("DEBUG -> %s\n", allProcess[processType]);
			break;
		}
	}
}

void addAnountherToCart()
{
	int number;
	int amount = 1;

	printf("Please enter product's number and number that you want in format\n ** product's number(integer),amount(integer)\n");
	printf("Your input is: ");
	scanf("%d,%d", &number, &amount);

	char targetProductName[25];
	strcpy(targetProductName, products[number - 1].name);
	int found = 0;

	for (int i = 0; i < numberOfProductsInCart; i++)
	{
		// printf("DEBUG -> %s == %s? %d\n", targetProductName, cart[i].name, strcmp(targetProductName, cart[i].name));
		if (strcmp(cart[i].name, targetProductName) == 0)
		{
			found = 1;
			printf("---->>> You have this item on your cart yet\n");
		}
	}
	if (found == 0)
	{
		if (amount <= products[number - 1].amount)
		{
			strcpy(cart[numberOfProductsInCart].name, targetProductName);
			cart[numberOfProductsInCart].amount = amount;
			cart[numberOfProductsInCart].price = products[number - 1].price;
			numberOfProductsInCart++;
		}
		else
			printf("---->>> Not enough stuff\n");
	}
}

void removeFromCart()
{
	int number;
	int found = 0;

	printf("Please enter product's number on cart that you want to remove: ");
	scanf("%d", &number);

	if (number > 0 && number <= numberOfProductsInCart)
	{
		for (int i = number - 1; i < numberOfProductsInCart; i++)
		{
			if (i + 1 < 100)
			{
				strcpy(cart[i].name, cart[i + 1].name);
				cart[i].amount = cart[i + 1].amount;
				cart[i].price = cart[i + 1].price;
			}
		}
		numberOfProductsInCart--;
	}
	else
		printf("---->>> Your cart don't have this number\n");
}

void payBill()
{
	char status;
	char text[5];
	int role = -1;
	float discount[4] = {0.7, 0.8, 0.9, 1};
	float total = 0;
	float cash;
	if (numberOfProductsInCart > 0)
	{
		printf("Are you a member? Y/N : ");
		scanf("%s", &text);
		status = text[0];
		if (status == 'Y' || status == 'y')
		{
			while (role == -1)
			{
				char temp[10];
				printf("\tPlease select what your role\n");
				printf("1 Platinum   2 Gold   3 Silver   \nEnter you choice: ");
				scanf("%s", &temp);
				role = (int)temp[0] - '0';

				if (role < 1 || role > 3)
					role = -1;
			}
		}
		else
			role = 4;

		for (int i = 0; i < numberOfProductsInCart; i++)
		{
			total += cart[i].amount * cart[i].price;
		}

		printAllProductInCart();
		printf("\tSubtotal\t\t %10.2f\n", total);
		printf("\tDiscount\t\t-%10.2f\n", (1 - discount[role - 1]) * total);
		printf("\tTotal   \t\t %10.2f\n", discount[role - 1] * total);

		printf("Plese input your cash: ");
		scanf("%f", &cash);

		printf("\tChange  \t\t %10.2f\n", cash - discount[role - 1] * total);
		clearCart(1);
	}
	else
		printf("---->>> Your cart is empty\n");
}

void clearCart(int isPay)
{
	for (int i = 0; i < numberOfProductsInCart; i++)
	{
		if (isPay == 1)
		{
			char productName[25];
			strcpy(productName, cart[i].name);

			for (int j = 0; j < numberOfProducts; j++)
			{
				if (strcmp(products[j].name, productName) == 0)
				{
					products[j].amount -= cart[i].amount;
					break;
				}
			}
		}
		strcpy(cart[i].name, "");
		cart[i].amount = 0;
		cart[i].price = 0;
	}
	numberOfProductsInCart = 0;

	FILE *fp;
	char content[100];
	fp = fopen(fileName, "w+");

	// printf("DEBUG -> content: %s", content);
	for (int i = 0; i < numberOfProducts; i++)
		fprintf(fp, "%s,%d,%d\n", products[i].name, products[i].amount, products[i].price);

	fclose(fp);
	readData();
}