#include<stdio.h>
#include<string.h>
unsigned long long int index[26];
char inpstr[20];
void setIndex()
{
    index[0]=0;
    index[1]=341816;
    index[2]=593389;
    index[3]=1032372;
    index[4]=1283414;
    index[5]=1471302;
    index[6]=1640857;
    index[7]=1791830;
    index[8]=2005819;
    index[9]=2189209;
    index[10]=2228229;
    index[11]=2285503;
    index[12]=2431952;
    index[13]=2710705;
    index[14]=2915451;
    index[15]=3089627;
    index[16]=3581782;
    index[17]=3623812;
    index[18]=3858411;
    index[19]=4443906;
    index[20]=4727250;
    index[21]=5027388;
    index[22]=5099837;
    index[23]=5229245;
    index[24]=5235474;
    index[25]=5251705;
}

struct node
{
    char c;
    int isAword;
    struct node *child[27];
}*tree=NULL;


struct node * NewNode(char c)
{
    struct node * newnode;
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->c = c;
    newnode->isAword=0;
    for(int i = 0 ;i<27;i++)
        newnode->child[i]=NULL;
    return newnode;
}


int ge_Index(char i)
{
    if(i == '-' )
        return 26;
    return i-97 ;
}

void AddElement(char c[])
{
	struct node *ptr ,*par;
	if(tree == NULL)
        tree = NewNode(c[0]);
    par = tree ;
	for(int i = 1 ; c[i] !='\0' ;i++)
	{
	    if(ge_Index(c[i]) != -87)
            {
                ptr = par->child[ge_Index(c[i])];
                if(ptr == NULL)
                    par->child[ge_Index(c[i])] = NewNode(c[i]);
                par = par->child[ge_Index(c[i])] ;
            }
	}
	par->isAword =1;
}

void lowercase(char c[])
{
    for(int i = 0 ;c[i] != '\0';i++)
    {
        if(c[i]>64 && c[i]<91)
            c[i]=c[i]+32;

    }
}


void Predict(struct node *ptr , char st[] )
{
    static int count = 0;
    if(ptr != NULL)
    {
        char a[2];         a[0]=ptr->c ;         a[1]='\0';
        strcat(st,a);
        for(int i = 0 ;i<27;i++)
            Predict(ptr->child[i] , st);
        if(ptr->isAword==1)
            printf("%s\n",st);
        st[strlen(st)-1] = '\0';
        count++;
    }
}



void Travserse()
{
    struct node *ptr = tree;
    for(int i=1 ;inpstr[i] !='\0' ;i++)
        ptr = ptr->child[ge_Index(inpstr[i])];
    printf("Predicting....\n");
    inpstr[strlen(inpstr)-1] = '\0';
    Predict(ptr,inpstr);
}


void main()
{
    char line[51];
    FILE *fp1 = fopen("words.txt","r");
    int ch;
    printf("Start entering a word and press enter whenever required : ");
    scanf("%s",inpstr);
    lowercase(inpstr);

    setIndex();
    if(inpstr[0] < 97)
        ch = inpstr[0]-65;
    else
        ch = inpstr[0]-97;

    fseek(fp1,index[ch],SEEK_SET);

    fgets(line,51,fp1);
    while((line[0]==inpstr[0] || abs(line[0]-inpstr[0]) == 32) && line[0] != '_')
    {

        lowercase(line);
        AddElement(line);
        fgets(line,51,fp1);
    }
    Travserse();
}