/*
 *The purpose of this program is to help a local restaurant automate
 *its billing system.
 *By Adam Thiemann
 */
 #include <iostream>
 #include <string>
 #include <fstream>
 #include <iomanip>
 using namespace std;
 
struct MenuItem
{
    string name;
    double price;
};

/*
*The purpose of this function is to load the item and price data from
*a file name menu.txt.  This function is called in main.
*/
int getData(MenuItem itemArray[], int length);

/*
 *The purpose of this function is to show the different menu items
 *and tell how to select the items.  This function is called in main.
 */
void showMenu(const MenuItem ITEM_ARRAY[], const int LENGTH);

/*
 *The purpose of this function is to allow the customer to choose 
 *the menu items and quantity that they want.
 *This function is called in main.
 */
void makeSelection(int quantArray[], const int LENGTH);

/*
 * The purpose of this function is to display the billing receipt to
 * the user.  This function is called in main.
 */
void printReceipt(const MenuItem ITEM_ARRAY[], const int QUANT_ARRAY[], const int LENGTH);

int main() 
{
    const int LENGTH = 10;
    //Hold up to 10 menu items, each index has a string and a double.
    MenuItem itemArray[LENGTH];

    //Finds the actual length of the array.
    //Load in the menu data and get array length.
    int newLength;
    newLength = getData(itemArray, LENGTH);
    //cout <<"This is the new length: " << newLength << endl;

    //If the file didn't correctly load, end the program.
    if (newLength == -1)
        return 0;

    //Create a parallel array to hold quantities and initialize
    int quantArray[LENGTH];
    for (int index = 0; index < LENGTH; index++)
        quantArray[index] = 0;

    //display the information taken from the input file so that the user
    //can pick what they want.
    showMenu(itemArray, newLength);

    //Ask the user what food they want
    makeSelection(quantArray, newLength);

    //Display the receipt for billing
    printReceipt(itemArray, quantArray, newLength);

    return 0;
}

int getData(MenuItem itemArray[], int length)
{
    //Name of the file to be opened, not changed.
    const string FILE_NAME = "Menu.txt";
    ifstream fileIn;
    length = 0;

    //Open the file
    fileIn.open(FILE_NAME);
    if (fileIn.fail())
        return -1;

    while (!fileIn.eof())
    {
        //cout << "Loop ran";
        //Read in the string by name until the line hits a tab
        getline(fileIn, itemArray[length].name, '\t');

        //ignore all values to the dollar sign
        fileIn.ignore(256, '$');

        //Read in the price
        fileIn >> itemArray[length].price;

        //ignore all values to the new line
        fileIn.ignore(256, '\n');
        //******************************************DELETE UPON COMPLETION******************
        //cout << "name: " << itemArray[length].name << endl;
        //cout << "and the length is " << itemArray[length].name.length() << endl;
        //cout << "price: " << itemArray[length].price << endl;
        length++;
    }
    fileIn.close(); //Close the file
    return length;
}

void showMenu(const MenuItem ITEM_ARRAY[], const int LENGTH)
{
    cout << " Welcome to the Programmers' Cafe" << endl;
    cout << "-----------Today's Menu-----------" << endl;
    for (int index = 0; index < LENGTH; index++)
    {
        cout << setw(2) << right << index + 1 << ": ";
        cout << setw(25) << left << ITEM_ARRAY[index].name;
        cout << "$" << fixed << setprecision(2) << ITEM_ARRAY[index].price;
        cout << endl;
    }
}

void makeSelection(int quantArray[], const int LENGTH)
{
    char order = 'a';
    int itemNum;
    int quant;

    do
    {
        cout << "Do you want to place an order? (y/n): ";
        cin >> order;
        cout << endl;
        if (order != 'y' && order != 'Y' && order != 'n' && order != 'N')
            break;
        else if (order == 'n' || order == 'N')
            break;
        else
        {
            //Get the item number
            cout << "Enter item number: ";
            cin >> itemNum;
            cout << endl;

            //if the input doesn't make sense
            while (itemNum > LENGTH || itemNum < 1)
            {
               cout << "Enter item number between 1 and " << LENGTH << ": ";
               cin >> itemNum;
               cout << endl;
            }

            //Get the item quantity
            cout << "Enter item quantity: ";
            cin >> quant;
            cout << endl;

            //Set the parallel array to equal the quantity purchased
            //at the itemNum displayed, minus 1 to get the proper index.
            quantArray[itemNum - 1] = quant;
            //*************************************DELETE********************************
            //cout << "This is the item quantity for index " << itemNum - 1 << ": " <<
            //    quantArray[itemNum - 1] << endl;
        }
    }
    while (order == 'y' || order == 'Y');
}

void printReceipt(const MenuItem ITEM_ARRAY[], const int QUANT_ARRAY[], const int LENGTH)
{
    const double TAX_RATE = .07;
    double total = 0;

    //Receipt header
    cout << setw(25) << right << "Thank you for eating at" << endl;
    cout << setw(24) << right << "The Programmers' Cafe" << endl;
    cout << setw(35) << setfill('-') << "" << setfill(' ') << endl;
    cout << left << setw(23) << "Receipt";
    cout << setw(3) << right << "Qty";
    cout << setw(9) << right << "Amount" << endl;
    cout << setw(35) << setfill('-') << "" << setfill(' ') << endl;

    //Itemized receipt
    for (int index = 0; index < LENGTH; index++)
    {
        if (QUANT_ARRAY[index] != 0)
        {
            cout << setw(23) << left << ITEM_ARRAY[index].name;
            cout << setw(3) << right << QUANT_ARRAY[index];
            cout << setw(3) << right << "$";
            cout << setw(6) << right << fixed << setprecision(2)
                << QUANT_ARRAY[index] * ITEM_ARRAY[index].price;
            cout << endl;
            total += QUANT_ARRAY[index] * ITEM_ARRAY[index].price;
        }
    }

    //Tax
    cout << '\t' << setw(20) << left << "Tax";
    cout << "$";
    cout << setw(6) << right << fixed << setprecision(2) << total * TAX_RATE;
    cout << endl;

    //Total
    cout << '\t' << setw(20) << left << "Amount Due";
    cout << "$";
    cout << setw(6) << right << fixed << setprecision(2) << total + (total * TAX_RATE);
    cout << endl;
}