#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[30];
    int numOfItems;
    struct items itm[50];
};

//func to generate bill head
void generateBillHeader(char name[50], char date[30]);
//func to generate bill body
void generateBillBody(char item[30], int qty, float price);
//func to generate bill foot
void generateBillFooter(float total);

int main(void){

    int opt, noOfItem ;
    struct orders ord;
    struct orders order;
    char saveBill = 'y';
    char contFlag='y';
    char name[50]; 
    FILE *fp;


    while(contFlag=='y'){

        int invoiceFound = 0;
    
        //Dashboard
        printf("\t     Leo's 🦁 Restaurant");
        printf("\n\nPlease select your prefered operation:\t");
        printf("\n\n1➜Generate Invoice ");
        printf("\n2➜Show All Invoices ");
        printf("\n3➜Search Invoice ");
        printf("\n4➜Exit ");

        printf("\n\nYour choice:\t");
        scanf("%d", &opt);
        fgetc(stdin);

        switch(opt){
            case 1:
                system("clear");
                float total=0;
                printf("\t    🇮🇳Leo's 🦁 Restaurant");
                printf("\nPlease enter the name of 💁customer:\t");
                fgets(ord.customer, 50, stdin);
                ord.customer[strlen(ord.customer)-1]=0;
                strcpy(ord.date, __DATE__);
                printf("Please enter the number of 📦items:\t");
                scanf("%d", &noOfItem);
                ord.numOfItems = noOfItem;

                for(int i=0; i<noOfItem; ++i){
                    fgetc(stdin);
                    printf("\n\n");
                    printf("Please enter the 🪣item %d:\t", i+1);
                    fgets(ord.itm[i].item, 20, stdin);
                    ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0;
                    printf("Please enter the 🔢quantity:\t");
                    scanf("%d",&ord.itm[i].qty);
                    printf("Please enter the unit 🏷️price:\t");
                    scanf("%f",&ord.itm[i].price);
                    total += ord.itm[i].qty * ord.itm[i].price;
                }

                generateBillHeader(ord.customer, ord.date);
                for(int i=0;i<ord.numOfItems;++i){
                    generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
                }
                generateBillFooter(total);

                printf("\n Do you want to save the invoice[y/n]:\t");
                scanf("%s", &saveBill);
                if(saveBill =='y'){
                    fp = fopen("RestaurantBill.bat","a+");
                    fwrite(&ord, sizeof(struct orders),1,fp);
                    printf("\nSuccessfully saved");
                
                    fclose(fp);
                }
                break;
            case 2:
                system("clear");
                fp = fopen("RestaurantBill.bat", "r");
                printf("\t   🇮🇳Leo's 🦁 Restaurant");
                printf("\n\t   ---------------------");
                printf("\n\t📜Your Previous Invoices📜\n");
                while(fread(&order, sizeof(struct orders),1,fp)){
                    float tot=0;
                    generateBillHeader(order.customer, order.date);
                    for(int i=0; i<order.numOfItems; ++i){
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(tot);
                }
                fclose(fp);
                break;
            case 3:
                printf("\nEnter the name of the customer:\t");
                //fgetc(stdin);
                fgets(name, 50, stdin);
                name[strlen(name)-1] = 0;
                fp = fopen("RestaurantBill.bat", "r");
                printf("\t   🇮🇳Leo's 🦁 Restaurant");
                printf("\n\t   ---------------------");
                printf("\n\t   📜Invoice of %s📜\n", name);
                while(fread(&order, sizeof(struct orders),1,fp)){
                    if(!strcmp(order.customer, name)){
                        float tot=0;
                        generateBillHeader(order.customer, order.date);
                        for(int i=0; i<order.numOfItems; ++i){
                            generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                            tot += order.itm[i].qty * order.itm[i].price;
                        }
                        generateBillFooter(tot);
                        invoiceFound=1;
                    }
                    if(!invoiceFound){
                        printf("Sorry the invoice for %s does not exist", name);
                    }
                }
                    fclose(fp);
                break;
            case 4:
                printf("\n \t\t👋🏻 Bye Bye 🥹\n\n");
                exit(0);
                break;
            default:
                printf("Sorry Invalid Option");
                break;
                
        }
        printf("Do you want to perform another operation?[y/n]:\t");
        scanf("%s",&contFlag);
        system("clear");
    }
    printf("\n\n");

    return 0;
}

void generateBillHeader(char name[50], char date[30]){
    printf("\n\n");
        printf("\n📆Date: %s", date); 
        printf("\n🤵🏻Invoice To: %s ✨", name); 
        printf("\n");
        printf("----------------------------------------\n");
        printf("🪣Items\t\t"); 
        printf("📦Qty\t\t"); 
        printf("💰Total\t\t"); 
        printf("\n----------------------------------------");
        printf("\n\n");
}

void generateBillBody(char item[30], int qty, float price){
    printf("%s\t\t",item);
        printf(" %d\t\t", qty);
        printf(" %2.f\t\t", qty*price);
        printf("\n");
}

void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal, grandTotal = netTotal + 2*cgst; 
    printf("----------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t--------");
    printf("\nNet Total \t\t\t%.2f", netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%", cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%", cgst);
    printf("\n----------------------------------------");
    printf("\nGrant Total \t\t\t%.2f", grandTotal);
    printf("\n----------------------------------------\n");
}
